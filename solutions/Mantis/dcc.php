<?php
if(preg_match('/(\d+)\s+([x|\/|\+|\-])\s+(\d+)/', file_get_contents('http://directus.darkscience.net:6789/'), $matches))
{
    $ch = curl_init();

    $math_result = 0;
    switch($matches[2])
    {
        case '/':
            $math_result = $matches[1] / $matches[3];
            break;

        case '+':
            $math_result = $matches[1] + $matches[3];
            break;

        case '-':
            $math_result = $matches[1] - $matches[3];
            break;

        case 'x':
        default:
            $math_result = $matches[1] * $matches[3];
            break;

    }

    curl_setopt_array($ch, [
        CURLOPT_URL            => 'http://directus.darkscience.net:6789/',
        CURLOPT_POST           => 1,
        CURLOPT_RETURNTRANSFER => 1,
        CURLOPT_POSTFIELDS     => 'answer=' . $math_result,
    ]);

    $x = curl_exec($ch);

    curl_close($ch);

    echo (preg_match('/correct/i', $x) ? 'Correct' : 'Wrong');
}
?>
