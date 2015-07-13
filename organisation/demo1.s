CMP %BA, $1   ; Button A pressed?
BNE $5        ;
ADD %R0, $1   ; Increment number
CMP %BA, $0   ; Wait for button release
BNE $3
CMP %BB, $1   ; Button B pressed?
BNE $16
SUB %R0, $1   ; Decrement number
CMP %BB, $0   ; Wait for button release
BNE $8
CMP %R0, $10  ; Check for limits
BL $16        ; Less, so 0-9, skip adjusting number
BNE $15       ; More, so underflow, skip setting 0
MOV %R0, $0   ; Has to be 10, so set to 0
BR $16        ; Skip setting 9
MOV %R0, $9   ; Branched here because of underflow, set 9
CMP %R0, $0   ; Check which number we are on and branch
BE $36        ; to the right display instruction
CMP %R0, $1
BE $38
CMP %R0, $2
BE $40
CMP %R0, $3
BE $42
CMP %R0, $4
BE $44
CMP %R0, $5
BE $46
CMP %R0, $6
BE $48
CMP %R0, $7
BE $50
CMP %R0, $8
BE $52
CMP %R0, $9
BE $54
MOV %D0, $63  ; Draw 0
BR $0         ; Start over
MOV %D0, $6   ; Draw 1
BR $0         ; Start over
MOV %D0, $91  ; Draw 2
BR $0         ; Start over
MOV %D0, $79  ; Draw 3
BR $0         ; Start over
MOV %D0, $102 ; Draw 4
BR $0         ; Start over
MOV %D0, $109 ; Draw 5
BR $0         ; Start over
MOV %D0, $125 ; Draw 6
BR $0         ; Start over
MOV %D0, $7   ; Draw 7
BR $0         ; Start over
MOV %D0, $127 ; Draw 8
BR $0         ; Start over
MOV %D0, $111 ; Draw 9
BR $0         ; Start over
