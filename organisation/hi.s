MOV %R0, %BA ; Copy Button A's status into R0
ADD %R0, %BB ; Add Button B's value to R0
CMP %R0, $0  ; Either of the buttons pressed?
BNE $9       ; If so, branch to code that displays 'hi'
MOV %D0, $0  ; Clear all displays
MOV %D1, $0
MOV %D2, $0
MOV %D3, $0
BR  $0       ; Start over
MOV %D1, $6  ; i, 0b00000110
MOV %D2, $116; h, 0b01110100
BR  $0       ; Start over
