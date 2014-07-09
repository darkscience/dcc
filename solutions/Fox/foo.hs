----------------------------------------------------------------------------------
-- What does the Fox say?                                                   Fox'--
--    ____    |\/|                      HTTP-Math-Fetch-Parse-Evaluate-Responder--
--    \  /\   / ..__.                                                           --
--     \/  \__\   _/                                                            --
--      \__   __  \                                                   in Haskell--
--        \____\___\                            DarkScience Code Contest January--
----------------------------------------------------------------------------------

-- Perl:   eval "print LWP::UserAgent->new()->post('http://directus.darkscience.net:6789', {'answer' => $1*$2})->decoded_content() =~ /(Correct|Wrong)/g;\n" if get("http://directus.darkscience.net:6789") =~ /([0-9]+) x ([0-9]+)/g

-- Python: print re.search('(Correct|Wrong)', requests.post(u, {'answer': eval(re.search('[0-9]+ x [0-9]+', requests.get(u).text).group(0).replace('x', '*'))}).text).group(0)

-- PHP:    ($u='http://directus.darkscience.net:6789/')&&!($a=array())&&preg_match('/[0-9]+ x [0-9]+/',file_get_contents($u),$a)&&(preg_match('(Correct|Wrong)',file_get_contents($u,false,stream_context_create(array('http'=>array('header'=>"Content-type: application/x-www-form-urlencoded\r\n",'method'=>'POST','content'=>http_build_query(array('answer'=>eval('return ('.str_replace('x','*',$a[0].');')))))))),$a)) && die(reset($a));

-- JS:     (x=new XMLHttpRequest)&&!x.open("GET","http://directus.darkscience.net:6789",false)&&!x.send(null)&&(r=/([0-9]+) x ([0-9]+)/g.exec(x.responseText))&&(a="answer="+eval(r[1]+"*"+r[2]))&&!x.open("POST","http://directus.darkscience.net:6789",false)&&!x.setRequestHeader("Content-type","application/x-www-form-urlencoded")&&!x.send(a)&&alert(/(Correct|Wrong)/.exec(x.responseText)[0])

-- Ruby:   (a, b = Net::HTTP.get(URI.parse("http://directus.darkscience.net:6789")).scan(/([0-9]+) x ([0-9]+)/)[0]) and print /(Correct|Wrong)/.match(Net::HTTP.post_form(URI.parse("http://directus.darkscience.net:6789"), {"answer" => (a.to_i.send '*', b.to_i)}).body)

module Main
where

import Network.HTTP.Conduit
import Network.HTTP.Types.Method
import Control.Applicative
import Text.Regex.Posix
import Language.Haskell.Interpreter
import Data.String.Utils
import Data.Char

import qualified Control.Exception as E

import qualified Data.ByteString as BS
import qualified Data.ByteString.Lazy as LBS
import qualified Data.ByteString.Char8 as BS8

-- Our input URL
dccUrl  = "http://directus.darkscience.net:6789/"

-- Definition of our grammar
data Expression
data Operator = Plus           -- We have support for Plus
              | Minus          -- Minus
              | Multiplication -- Multiplication
              | Division       -- Division
    deriving (Show, Eq)

-- ^
data Token = TokenOperator Operator -- We have an Operator token
           | TokenAssign            -- Assignment token
           | TokenLeftParentheses   -- Left parentheses
           | TokenRightParentheses  -- Right parentheses
           | TokenIdentifier String -- Identifier
           | TokenNumber Double     -- Number
           | TokenEnd               -- End of expression
    deriving (Show, Eq)

-- ^
data Tree = SumNode Operator Tree Tree  -- A summation traverses into two trees
          | ProductNode Operator Tree Tree -- A product traverses into two trees
          | AssignNode String Tree      -- An assignment traverses into one tree
          | UnaryNode Operator Tree     -- A unary traverses into one tree
          | NumNode Double              -- A number
          | VarNode String              -- A variable
    deriving Show

-- Convert an inputted Char to an Operator
operator :: Char -> Operator
operator c | c == '+' = Plus            -- Plus           => "+"
           | c == '-' = Minus           -- Minus          => "-"
           | c == 'x' = Multiplication  -- Multiplication => "x"
           | c == '/' = Division        -- Division       => "/"

-- Tokenize an input string into a list of Tokens
tokenize :: String -> [Token]
tokenize [] = []                                               -- In case of an empty set, return an empty set
tokenize (c : cs)
    | elem c "+-x/" = TokenOperator (operator c) : tokenize cs -- If we've encountered one of "+-x/" fetch c as the operator, recursively work with the rest of the string
    | isDigit c = number c cs                                  -- In case of a digit, treat c as a number
    | isSpace c = tokenize cs                                  -- In case of a space, recursively work with the current string
    | otherwise = error $ "Cannot tokenize " ++ [c]            -- Else we have a problem

-- This actually is a simply head operation, returning TokenEnd on empty list
lookAhead :: [Token] -> Token
lookAhead []     = TokenEnd -- Pattern match empty list, [], to reflect TokenEnd
lookAhead (t:ts) = t        -- Pattern match t as head, ts as tail, to reflect head

-- This actually is a simple tail operation, returning an error on empty list
accept :: [Token] -> [Token]
accept []     = error "Nothing to accept" -- Pattern match empty list to trigger error
accept (t:ts) = ts                        -- Pattern match t as head, ts as tail to reflect tail

number :: Char -> [Char] -> [Token]
number c cs =
   let (digs, cs') = span isDigit cs in
        TokenNumber (read (c : digs)) : tokenize cs'

expression :: [Token] -> (Tree, [Token])
expression toks =
   let (termTree, toks') = term toks
   in
      case lookAhead toks' of
         (TokenOperator op) | elem op [Plus, Minus] ->
            let (exTree, toks'') = expression (accept toks')
            in (SumNode op termTree exTree, toks'')
         TokenAssign ->
            case termTree of
               VarNode str ->
                  let (exTree, toks'') = expression (accept toks')
                  in (AssignNode str exTree, toks'')
               _ -> error "Assignment on non-variable!"
         _ -> (termTree, toks')

term :: [Token] -> (Tree, [Token])
term toks =
   let (facTree, toks') = factor toks
   in
      case lookAhead toks' of
         (TokenOperator op) | elem op [Multiplication, Division] ->
            let (termTree, toks'') = term (accept toks')
            in (ProductNode op facTree termTree, toks'')
         _ -> (facTree, toks')

factor :: [Token] -> (Tree, [Token])
factor toks =
   case lookAhead toks of
      (TokenNumber x)     -> (NumNode x, accept toks)   -- In case we've encountered a TokenNumber, x is NumNode, accept toks
      (TokenIdentifier x) -> (VarNode x, accept toks)   -- In case we've encountered a TokenIdentifier, x is VarNode, accept toks
      (TokenOperator op) | elem op [Plus, Minus] ->     -- In case we've encountered a TokenOperator,
            let (facTree, toks') = factor (accept toks)
            in (UnaryNode op facTree, toks')
      TokenLeftParentheses      ->
         let (expTree, toks') = expression (accept toks)
         in
            if lookAhead toks' /= TokenRightParentheses
            then error "Missing right parenthesis"
            else (expTree, accept toks')
      _ -> error $ "Syntax error on token: " ++ show toks -- Oops, syntax error!

parse :: [Token] -> Tree
parse toks = let (tree, toks') = expression toks
             in
               if null toks'                                                 -- Traverse the
               then tree                                                     -- ^ tree
               else error $ "Syntax error (left over token): " ++ show toks' -- Oops, syntax error!

-- Evaluate a SumNode tree, reflect Double
evaluate :: Tree -> Double
evaluate (SumNode op left right) =
    let lft = evaluate left
        rgt = evaluate right
    in
        case op of
            Plus  -> lft + rgt
            Minus -> lft - rgt

-- Evaluate a ProductNode tree, reflect Double
evaluate (ProductNode op left right) =
    let lft = evaluate left
        rgt = evaluate right
    in
        case op of
            Multiplication -> lft * rgt
            Division       -> lft / rgt

-- Evaluate a UnaryNode tree, reflect Double
evaluate (UnaryNode op tree) =
    let x = evaluate tree
    in case op of
            Plus  -> x
            Minus -> -x

-- Evaluate a NumNode, reflect Number
evaluate (NumNode x) = x

-- Convert lazy ByteString to ByteString
lazyToStrictBS :: LBS.ByteString -> BS.ByteString
lazyToStrictBS x = BS.concat $ LBS.toChunks x

-- Entry point
main :: IO ()
main = do
    b <- simpleHttp dccUrl

    let eq = (map (chr . fromIntegral) $ BS.unpack $ lazyToStrictBS b) =~ "[0-9]+ [+-x/] [0-9]+" :: String
    let answer = show $ round $ evaluate $ parse $ tokenize eq

    initReq <- parseUrl dccUrl
    let request = (flip urlEncodedBody) initReq $ [(BS8.pack "answer", BS8.pack answer)]
    res <- withManager $ httpLbs request
    let result = (show $ lazyToStrictBS $ responseBody res) =~ "(Correct|Wrong)" :: String

    print (eq ++ " = " ++ answer ++ " is " ++ result)

    main