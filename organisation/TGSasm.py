#!/usr/bin/env python2
# Assembler for the Terrible Gaming System
# Made by Derecho

import sys
import re

opcode_map = {
        'ADD': (0b00010000, 0b00010001),
        'SUB': (0b00010010, 0b00010011),
        'LSH': (0b00100000, 0b00100001),
        'RSH': (0b00100010, 0b00100011),
        'AND': (0b00110000, 0b00110001),
        'OR' : (0b00110010, 0b00110011),
        'XOR': (0b00110100, 0b00110101),
        'CMP': (0b01000000, 0b01000001),
        'BR' : (0b01010000,),
        'BE' : (0b01010010,),
        'BNE': (0b01010100,),
        'BG' : (0b01010110,),
        'BL' : (0b01011000,),
        'MOV': (0b01100000, 0b01100001),
        }

register_map = {
        'R0': 0b00000000,
        'R1': 0b00000001,
        'R2': 0b00000010,
        'R3': 0b00000011,
        'R4': 0b00000100,
        'R5': 0b00000101,
        'R6': 0b00000110,
        'R7': 0b00000111,
        'BA': 0b00010000,
        'BB': 0b00010001,
        'D0': 0b00010010,
        'D1': 0b00010011,
        'D2': 0b00010100,
        'D3': 0b00010101,
        'PC': 0b00010110,
        'CR': 0b00010111,
        }

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print "Usage {} <asm file> <bin file>".format(sys.argv[0])
        sys.exit(1)

    asm_expr = re.compile("[ ]*(?P<instruction>[\w]+)[ ]*(?P<argument_left>[%\$\w]+)[, ]*(?P<argument_right>[%\$\w]+)?[ ]*(?P<comment>.+)?")

    asm_file = open(sys.argv[1], 'r')
    bin_file = open(sys.argv[2], 'wb')

    for line in asm_file.xreadlines():
        matches = asm_expr.match(line)

        opcode = opcode_map[matches.group('instruction')]
        argument_left = matches.group('argument_left')
        argument_right = matches.group('argument_right')

        if(len(opcode) == 2):
            if argument_right[0] == '%':
                opcode = opcode[0]
            elif argument_right[0] == '$':
                opcode = opcode[1]
            else:
                print "Invalid asm file"
                sys.exit(255)

            #TODO remove
        else:
            opcode = opcode[0]
        
        operand_left = 0
        if(argument_left[0]) == '%':
            operand_left = register_map[argument_left[1:]]
        elif argument_left[0] == '$':
            operand_left = int(argument_left[1:])
        else:
            print "Invalid asm file"
            sys.exit(255)
        
        operand_right = 0
        if(argument_right != None):
            if(argument_right[0]) == '%':
                operand_right = register_map[argument_right[1:]]
            elif argument_right[0] == '$':
                operand_right = int(argument_right[1:])
            else:
                print "Invalid asm file"
                sys.exit(255)

        print "{:02x} {:02x} {:02x}".format(opcode, operand_left, operand_right)
        bin_file.write(chr(opcode))
        bin_file.write(chr(operand_left))
        bin_file.write(chr(operand_right))
    
    asm_file.close()
    bin_file.close()
