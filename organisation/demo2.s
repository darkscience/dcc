MOV %D3, $94  ; Display 'd'
MOV %D2, $119 ; Display 'A'
MOV %D1, $80  ; Display 'r'
MOV %D0, $118 ; Display 'k' (sort of)
CMP %R0, $255 ; Use two loops as a delay
BE $8         ; First count finished, skip first loop
ADD %R0, $1   ; First count not done, increment
BR $4         ; and go back
MOV %R0, $0   ; Reset first counter
CMP %R1, $200 ; Inner delay loop
BE $13        ; Second count finished, skip second loop
ADD %R1, $1   ; Second count not done, increment
BR $9         ; and go back
MOV %R1, $0   ; Reset second counter
MOV %D3, $119 ; Display 'A'
MOV %D2, $80  ; Display 'r'
MOV %D1, $118 ; Display 'k' (sort of)
MOV %D0, $109 ; Display 's'
CMP %R0, $255 ; Use two loops as a delay
BE $22        ; First count finished, skip first loop
ADD %R0, $1   ; First count not done, increment
BR $18        ; and go back
MOV %R0, $0   ; Reset first counter
CMP %R1, $200 ; Inner delay loop
BE $27        ; Second count finished, skip second loop
ADD %R1, $1   ; Second count not done, increment
BR $23        ; and go back
MOV %R1, $0   ; Reset second counter
MOV %D3, $80  ; Display 'r'
MOV %D2, $118 ; Display 'k' (sort of)
MOV %D1, $109 ; Display 's'
MOV %D0, $57  ; Display 'c'
CMP %R0, $255 ; Use two loops as a delay
BE $36        ; First count finished, skip first loop
ADD %R0, $1   ; First count not done, increment
BR $32        ; and go back
MOV %R0, $0   ; Reset first counter
CMP %R1, $200 ; Inner delay loop
BE $41        ; Second count finished, skip second loop
ADD %R1, $1   ; Second count not done, increment
BR $37        ; and go back
MOV %R1, $0   ; Reset second counter
MOV %D3, $118 ; Display 'k' (sort of)
MOV %D2, $109 ; Display 's'
MOV %D1, $57  ; Display 'c'
MOV %D0, $6   ; Display 'i'
CMP %R0, $255 ; Use two loops as a delay
BE $50        ; First count finished, skip first loop
ADD %R0, $1   ; First count not done, increment
BR $46        ; and go back
MOV %R0, $0   ; Reset first counter
CMP %R1, $200 ; Inner delay loop
BE $55        ; Second count finished, skip second loop
ADD %R1, $1   ; Second count not done, increment
BR $51        ; and go back
MOV %R1, $0   ; Reset second counter
MOV %D3, $109 ; Display 's'
MOV %D2, $57  ; Display 'c'
MOV %D1, $6   ; Display 'i'
MOV %D0, $121 ; Display 'E'
CMP %R0, $255 ; Use two loops as a delay
BE $64        ; First count finished, skip first loop
ADD %R0, $1   ; First count not done, increment
BR $60        ; and go back
MOV %R0, $0   ; Reset first counter
CMP %R1, $200 ; Inner delay loop
BE $69        ; Second count finished, skip second loop
ADD %R1, $1   ; Second count not done, increment
BR $65        ; and go back
MOV %R1, $0   ; Reset second counter
MOV %D3, $57  ; Display 'c'
MOV %D2, $6   ; Display 'i'
MOV %D1, $121 ; Display 'E'
MOV %D0, $55  ; Display 'n'
CMP %R0, $255 ; Use two loops as a delay
BE $78        ; First count finished, skip first loop
ADD %R0, $1   ; First count not done, increment
BR $74        ; and go back
MOV %R0, $0   ; Reset first counter
CMP %R1, $200 ; Inner delay loop
BE $83        ; Second count finished, skip second loop
ADD %R1, $1   ; Second count not done, increment
BR $79        ; and go back
MOV %R1, $0   ; Reset second counter
MOV %D3, $6   ; Display 'i'
MOV %D2, $121 ; Display 'E'
MOV %D1, $55  ; Display 'n'
MOV %D0, $57  ; Display 'c'
CMP %R0, $255 ; Use two loops as a delay
BE $92        ; First count finished, skip first loop
ADD %R0, $1   ; First count not done, increment
BR $88        ; and go back
MOV %R0, $0   ; Reset first counter
CMP %R1, $200 ; Inner delay loop
BE $97        ; Second count finished, skip second loop
ADD %R1, $1   ; Second count not done, increment
BR $93        ; and go back
MOV %R1, $0   ; Reset second counter
MOV %D3, $121 ; Display 'E'
MOV %D2, $55  ; Display 'n'
MOV %D1, $57  ; Display 'c'
MOV %D0, $121 ; Display 'E'
CMP %R0, $255 ; Use two loops as a delay
BE $106       ; First count finished, skip first loop
ADD %R0, $1   ; First count not done, increment
BR $102       ; and go back
MOV %R0, $0   ; Reset first counter
CMP %R1, $200 ; Inner delay loop
BE $111       ; Second count finished, skip second loop
ADD %R1, $1   ; Second count not done, increment
BR $107       ; and go back
MOV %R1, $0   ; Reset second counter
MOV %D3, $55  ; Display 'n'
MOV %D2, $57  ; Display 'c'
MOV %D1, $121 ; Display 'E'
MOV %D0, $0   ; Display ' '
CMP %R0, $255 ; Use two loops as a delay
BE $120       ; First count finished, skip first loop
ADD %R0, $1   ; First count not done, increment
BR $116       ; and go back
MOV %R0, $0   ; Reset first counter
CMP %R1, $200 ; Inner delay loop
BE $125       ; Second count finished, skip second loop
ADD %R1, $1   ; Second count not done, increment
BR $121       ; and go back
MOV %R1, $0   ; Reset second counter
MOV %D3, $57  ; Display 'c'
MOV %D2, $121 ; Display 'E'
MOV %D1, $0   ; Display ' '
MOV %D0, $94  ; Display 'd'
CMP %R0, $255 ; Use two loops as a delay
BE $134       ; First count finished, skip first loop
ADD %R0, $1   ; First count not done, increment
BR $130       ; and go back
MOV %R0, $0   ; Reset first counter
CMP %R1, $200 ; Inner delay loop
BE $139       ; Second count finished, skip second loop
ADD %R1, $1   ; Second count not done, increment
BR $135       ; and go back
MOV %R1, $0   ; Reset second counter
MOV %D3, $121 ; Display 'E'
MOV %D2, $0   ; Display ' '
MOV %D1, $94  ; Display 'd'
MOV %D0, $119 ; Display 'A'
CMP %R0, $255 ; Use two loops as a delay
BE $148       ; First count finished, skip first loop
ADD %R0, $1   ; First count not done, increment
BR $144       ; and go back
MOV %R0, $0   ; Reset first counter
CMP %R1, $200 ; Inner delay loop
BE $153       ; Second count finished, skip second loop
ADD %R1, $1   ; Second count not done, increment
BR $149       ; and go back
MOV %R1, $0   ; Reset second counter
MOV %D3, $0   ; Display ' '
MOV %D2, $94  ; Display 'd'
MOV %D1, $119 ; Display 'A'
MOV %D0, $80  ; Display 'r'
CMP %R0, $255 ; Use two loops as a delay
BE $162       ; First count finished, skip first loop
ADD %R0, $1   ; First count not done, increment
BR $158       ; and go back
MOV %R0, $0   ; Reset first counter
CMP %R1, $200 ; Inner delay loop
BE $167       ; Second count finished, skip second loop
ADD %R1, $1   ; Second count not done, increment
BR $163       ; and go back
MOV %R1, $0   ; Reset second counter
BR $0         ; Start over
