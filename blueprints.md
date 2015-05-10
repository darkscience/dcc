# Terrible Gaming System - Developer Manual
In this new dawn of computing, we bring the TGS to the common man for an
affordable price. Compromises have been made on the featureset of the device
but we believe the experience will be revolutionary in the gaming business,
directly competing with the major boardgame manufacturers.

This document contains all required information to write games for the TGS.

## Overview

            _   _   _   _
    A *    |_| |_| |_| |_|
    B *    |_| |_| |_| |_| 

Above is a artist's impression of the machine's top panel. The system provides
the player with two buttons marked A and B, and four 7-segment displays which
can be used for displaying numbers, characters and even basic graphics. Inside
is a powerful state-of-the-art 50 kHz 8-bit processor.

## Registers
Hardware is exposed to the processor via special registers, a full list of
registers follows:

   - R0 to R7
       Eight general purpose registers.
   - BA and BB
       Read-only registers containing the button statuses. These hold 0 by default and a
       1 indicates the respective button has been pressed.
   - D0 to D3
       Write-only registers for the four 7-segment displays. The most
       significant bit is unused.
   - PC
       Program counter. Normally incremented with each succesively executed
       opcode, but can be set to arbitrary values by branch instructions.
   - CR
       Comparison result. The result of a comparison instruction is stored in
       this register as a two's complement signed byte.

All these registers are the size of one byte.

### Display registers
The following image shows which bit is used for what part of the display:

     1
    6 2
     7
    5 3
     4

The least significant, or right-most, bit is considered to be the first bit.
For example, to show the number 5 on the screen, you need to write the
following byte to D0:

    01101101

### Machine code
The registers have the following representations in machine code:

   - R0 .. R7   0000.0000 .. 0000.0111
   - BA    BB   0001.0000    0001.0001
   - D0 .. D3   0001.0010 .. 0001.0101
   - PC         0001.0110
   - CR         0001.0111

## Instruction set
All instructions consist of 3 bytes. The first byte holds the opcode, the
second and third byte are reserved for any potential arguments. The PC register
always points to the opcode in these 3 byte sequences. The result of an
operation is usually stored in the register that is supplied in the first
argument (second byte).

The subsections below use the following operation description format:

   - opcode   mnemonic target source
     byte 1            byte 2 byte 3

Most instructions have two opcodes. The used opcode indicates whether the
second argument (third byte) will be a literal value or a register's machine
code representation.

### Arithmetic operations
Addition and substraction.

   - 0001.0000   ADD <register> <register>
   - 0001.0001   ADD <register> <value>
   - 0001.0010   SUB <register> <register>
   - 0001.0011   SUB <register> <value>

### Bitwise operations
Left and right shifts, and boolean logic.

   - 0010.0000   LSH <register> <register>
   - 0010.0001   LSH <register> <value>
   - 0010.0010   RSH <register> <register>
   - 0010.0011   RSH <register> <value>
   - 0011.0000   AND <register> <register>
   - 0011.0001   AND <register> <value>
   - 0011.0010   OR  <register> <register>
   - 0011.0011   OR  <register> <value>
   - 0011.0100   XOR <register> <register>
   - 0011.0101   XOR <register> <value>
 
 ### Branching operations
 After comparing two values, the program can branch (or jump) to different
 locations in the program, depending on the result. The following conditions
 are represented with the different branching instructions: always, equal,
 not equal, greater than, less than.

   - 0100.0000   CMP <register> <register>
   - 0100.0001   CMP <register> <value>
   - 0101.0000   BR  <value> <unused>
   - 0101.0010   BE  <value> <unused>
   - 0101.0100   BNE <value> <unused>
   - 0101.0110   BG  <value> <unused>
   - 0101.1000   BL  <value> <unused>

The value used in the branching instructions corresponds with the index of the
intructions of the program. The first instruction is at index 0, the second
instruction at index 1.
 
### Move operations
  - 0110.0000   MOV <register> <register>
  - 0110.0001   MOV <register> <value>
 
## Example application
The program below will display the word 'hi' on the screen whenever the user
presses a button.

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
 
Or, in machine code (in hex):

    60 00 10
    10 00 11
    41 00 00 
    54 09 00
    61 12 00
    61 13 00
    61 14 00
    61 15 00
    50 00 00
    61 13 06
    61 14 74
    50 00 00

## TGS 2
The second revision of our Terrible Gaming System adds the following features:

   - 8kB of fully-addressable RAM
   - Hardware buffered serial IO for use with a VT100-compatible terminal
 
The original TGS top panel with the display and buttons is still present for
backwards compatibility with any games released for the first TGS.

### RAM
As a byte can only hold up to 256 addresses, the 1kB RAM is addressed using two
registers: S0 and S1, where S0 holds the least significant half of the address.

The following instructions are added to be able to store and retrieve data from
the stack that utilises the RAM extension:

   - 0111.0000   PSH <register> <unused>
   - 0111.0001   POP <register> <unused>

Both of these instructions refer to the S0 and S1 registers to know what part
of RAM to address, and will modify the registers afterwards. A push increments
the address by 1, a pop decrements the address by 1.

### Serial IO
The UI peripherals available on the TGS will be too limited for more advanced
applications as time progresses. In order to anticipate the need for a more
extensive and modular UI, buffered serial IO support will be added so users
can connect any VT100-style terminal to their TGS2 and enjoy a 80x24 ASCII
output with keyboard input.

The following instructions are added to store and retrieve the bytes sent over
the buffered serial connection:

   - 1000.0000   BSI <register> <unused>
   - 1000.0010   BSO <register> <unused>
   - 1000.0011   BSO <value>    <unused>

The serial peripheral buffers all ingoing and outgoing bytes, communication
with the terminal happens at 300 baud and does not need to be timed correctly
by the application.
