#ifndef __TGS_H
#define __TGS_H

#include <stdint.h>

//define register mnemonics
#define R0 0b00000000
#define R1 0b00000001
#define R2 0b00000010
#define R3 0b00000011
#define R4 0b00000100
#define R5 0b00000101
#define R6 0b00000110
#define R7 0b00000111

#define BA 0b00010000
#define BB 0b00010001

#define D0 0b00010010
#define D1 0b00010011
#define D2 0b00010100
#define D3 0b00010101

#define PC 0b00010110

#define CR 0b00010111

#define LAST_REG (CR+1)

//define register names
//if there is need of speed make array where reg names is by opcode value
typedef struct _reg_name 
{
	uint8_t reg;
	char *name;
} _reg_name;

extern _reg_name reg_names[];


typedef enum inst_params
{
	NONE=0,
	REG,
	VAL
} inst_params;

typedef struct inst_t
{
	uint8_t opcode;
	uint8_t param_num; //1 or 2 usually
	inst_params param[2];
	char *opname;
} inst_t;


//all instructions are 3 byte long, i fill lucky
extern inst_t inst_table[];
#define I_ADD_RR 0b00010000
#define I_ADD_RV 0b00010001
#define I_SUB_RR 0b00010010
#define I_SUB_RV 0b00010011

#define I_LSH_RR 0b00100000
#define I_LSH_RV 0b00100001
#define I_RSH_RR 0b00100010
#define I_RSH_RV 0b00100011
#define I_AND_RR 0b00110000
#define I_AND_RV 0b00110001
#define I_OR_RR  0b00110010
#define I_OR_RV  0b00110011
#define I_XOR_RR 0b00110100
#define I_XOR_RV 0b00110101

#define I_CMP_RR 0b01000000
#define I_CMP_RV 0b01000001
#define I_BR     0b01010000
#define I_BE     0b01010010
#define I_BNE    0b01010100
#define I_BG     0b01010110
#define I_BL     0b01011000

#define I_MOV_RR 0b01100000
#define I_MOV_RV 0b01100001


//if not NULL then pointer, if pointer FREE it
const char *reg2name( uint8_t reg_num );
//if return 0xFF unknown register name
uint8_t name2reg( const char *reg_name );
uint8_t name2instr( const char *instr_name, inst_params p1, inst_params p2 );
int val2int( const char *val );

char *inst2str( uint8_t *data );

//parse 1 line to 3byte instruction
//free result
uint8_t* str2instr( const char *str );

#endif