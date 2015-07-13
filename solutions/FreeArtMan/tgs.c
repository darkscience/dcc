#include "tgs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "debug.h"

_reg_name reg_names[] = 
{
	{R0,"\%R0"},
	{R1,"\%R1"},
	{R2,"\%R2"},
	{R3,"\%R3"},
	{R4,"\%R4"},
	{R5,"\%R5"},
	{R6,"\%R6"},
	{R7,"\%R7"},
	{BA,"\%BA"},
	{BB,"\%BB"},
	{D0,"\%D0"},
	{D1,"\%D1"},
	{D2,"\%D2"},
	{D3,"\%D3"},
	{PC,"\%PC"},
	{CR,"\%CR"},
	{0,0}
};

inst_t inst_table[] = 
{
	//arithmetic
	{I_ADD_RR, 2, {REG, REG},  "ADD"},
	{I_ADD_RV, 2, {REG, VAL},  "ADD"},
	{I_SUB_RR, 2, {REG, REG},  "SUB"},
	{I_SUB_RV, 2, {REG, VAL},  "SUB"},

	//bitwise
	{I_LSH_RR, 2, {REG, REG},  "LSH"},
	{I_LSH_RV, 2, {REG, VAL},  "LSH"},
	{I_RSH_RR, 2, {REG, REG},  "RSH"},
	{I_RSH_RV, 2, {REG, VAL},  "RSH"},
	{I_AND_RR, 2, {REG, REG},  "AND"},
	{I_AND_RV, 2, {REG, VAL},  "AND"},
	{I_OR_RR,  2, {REG, REG},  "OR"},
	{I_OR_RV,  2, {REG, VAL},  "OR"},
	{I_XOR_RR, 2, {REG, REG},  "XOR"},
	{I_XOR_RV, 2, {REG, VAL},  "XOR"},

	//branching
	{I_CMP_RR, 2, {REG, REG},  "CMP"},
	{I_CMP_RV, 2, {REG, VAL},  "CMP"},
	{I_BR,     1, {VAL, NONE}, "BR"},
	{I_BE,     1, {VAL, NONE}, "BE"},
	{I_BNE,    1, {VAL, NONE}, "BNE"},
	{I_BG,     1, {VAL, NONE}, "BG"},
	{I_BL,     1, {VAL, NONE}, "BL"},

	//move
	{I_MOV_RR, 2, {REG, REG},  "MOV"},
	{I_MOV_RV, 2, {REG, VAL},  "MOV"},
	{0,0,{0,0},0}
};


const char *reg2name( uint8_t reg_num )
{
	char *ret=NULL;
	int i;

	//R0 has value 0, last element have value 0 
	i = 0;
	while (reg_names[i].name != NULL)
	{
		if ( reg_names[i].reg == reg_num )
		{
			ret = reg_names[i].name;
			break;
		}
		i += 1;
	}

	return ret;
}


uint8_t name2reg( const char *reg_name )
{
	uint8_t ret=0xFF;
	int i;

	PRINT("%s\n", reg_name);

	//R0 = 0 and last element in reg_names arr = 0
	i = 0;
	while ( reg_names[i].name != 0 )
	{
		//hope all registers have 3 byte names, dont check on NULL =P
		if ( strncmp(reg_names[i].name, reg_name, 3) == 0)
		{
			ret = reg_names[i].reg;
			break;
		}
		i += 1;
	}

	return ret;
}


uint8_t name2instr( const char *instr_name, inst_params p1, inst_params p2 )
{
	uint8_t ret=0xFF;
	int i;

	i = 0;
	while ( inst_table[i].opname != 0 )
	{
		if ( strcmp( inst_table[i].opname, instr_name ) == 0 )
		{
			if ( inst_table[i].param_num == 2 )
			{
				if ( (inst_table[i].param[0] == p1) && 
					 (inst_table[i].param[1] == p2))
				{
					ret = inst_table[i].opcode;
				}
			} else if ( inst_table[i].param_num == 1 )
			{
				if ( inst_table[i].param[0] == p1 )
				{
					ret = inst_table[i].opcode;
				}
			} else
			{
				ERROR("Unknow param num\n");
			}
		}
		i += 1;
	}

	return ret;
}


int val2int( const char *val )
{
	int ret=-1;

	if ( val != NULL )
	{
		ret = atoi( val )&0xFF;
	}

	return ret;
}


char *inst2str( uint8_t *data )
{
	int i;
	char *ret = NULL;
	char *str = NULL;


	str = malloc( 128 );
	if ( str == NULL )
	{
		ENL();
		return NULL;
	}

	i = 0;
	while ( inst_table[i].opcode != 0 )
	{
		if (data[0] == inst_table[i].opcode )
		{
			if ( inst_table[i].param_num == 2 )
			{
				if ( (inst_table[i].param[0] == REG) &&
					 (inst_table[i].param[1] == REG) )
				{
					snprintf( str, 128, "%s %s, %s", 
						inst_table[i].opname, reg2name( data[1] ), reg2name( data[2] ) );
					ret = str;
				} else if ( (inst_table[i].param[0] == REG) && (inst_table[i].param[1] == VAL))
				{
					//printf("%s\n",reg2name(data[1]));
					snprintf( str, 128, "%s %s, $%d", 
						inst_table[i].opname, reg2name( data[1] ), data[2] );
					ret = str;
				} else
				{
					ENL();
				}
			} else if ( inst_table[i].param_num == 1 )
			{
				if (inst_table[i].param[0] == VAL)
				{
					snprintf( str, 128, "%s $%d", 
						inst_table[i].opname, data[1]);
					ret = str;
				} else
				{
					ENL();
					break;
				}
			} else
			{
				ENL();
				break;
			}
		}
		i += 1;
	}

	return ret;
}


uint8_t* str2instr( const char *str )
{
	const int TOKEN_CMD = 1;
	const int TOKEN_REG = 2;
	const int TOKEN_VAL = 3;

	#define S_START   1
	#define S_END     2
	#define S_CMD     3
	#define S_SPC     4
	#define S_REG     5
	#define S_VAL     6
	#define S_COMMENT 7

	uint8_t *ret = NULL;
	char *p = (char *)str;
	int state = S_START;

	uint8_t *data = malloc( 3 );

	char p_cmd[4];
	char p_param1[6]; inst_params tag_param1=NONE;
	char p_param2[6]; inst_params tag_param2=NONE;

	memset( p_cmd,    0, 4 );
	memset( p_param1, 0, 6 );
	memset( p_param2, 0, 6 );

	while ( state != S_END )
	{
		switch ( state )
		{
			//start line
			case S_START:
				{
					PRINT("S_START\n");
					if ( isalpha(*p) )
					{
						state = S_CMD;
					} else if ( *p == ' ' || *p == '\t' )
					{
						state = S_SPC;
					} else if ( *p == ';' )
					{
						state = S_COMMENT;
					} else if ( *p == '\n' )
					{
						state = S_END;
					} else {
						ERROR("\n");
					}
				}
				break;
			//end of line
			case S_END:
				{
					PRINT("S_END\n");
				}
				break;
			//find 3 character commands
			case S_CMD:
				{
					char *s=p, *e;
					PRINT("S_CMD\n");
					while ( isalpha(*p) )
					{
						p++;
					}

					//-------------------------------
					e = p;
					if ( e-s > 3)
					{
						ERROR("Too big command\n");
						break;
					}
					memcpy( p_cmd, s, e-s+1 );
					p_cmd[e-s] = 0;

					//-------------------------------
					if ( (*p==' ')||(*p=='\t'))
					{
						state = S_SPC;
						break;
					}

				}
				break;
			//bypass space tabes and newlines
			case S_SPC:
				{
					PRINT("S_SPC\n");
					while( (*p==' ')||(*p=='\t'))
					{
						p++;
					}
					if (*p=='%')
					{
						state = S_REG;
					} else if (*p=='$')
					{
						state = S_VAL;
					} else if ( *p == ';' )
					{
						state = S_COMMENT;
					} else if ( *p == '\n' || *p == '\0')
					{
						state = S_END;
					} else {
						ERROR("%c %02x\n",*p, *p);
					}
				}
				break;
			//parse register name
			case S_REG:
				{
					char *s, *e;
					PRINT("S_REG\n");

					s = p;
					if (*p == '%') p++;					
					if (*p == 'R' || *p == 'D' || *p == 'B' || *p == 'P' || *p == 'C')
					{
						while(isalnum(*p))
							p++;
					}
					e = p;
					if (e-s>4)
					{
						ENL();
						break;
					}

					if ( tag_param1 == 0)
					{
						tag_param1 = REG;
						memcpy( p_param1, s, e-s+1 );
						p_param1[e-s] = 0;
					} else
					{
						tag_param2 = REG;
						memcpy( p_param2, s, e-s+1 );
						p_param2[e-s] = 0;
					}

					if ( *p == ' ' || *p == '\t' )
					{
						state = S_SPC;
					} else if ( *p == ',' )
					{
						p++;
						state = S_SPC;
					} else if ( *p == ';' )
					{
						state = S_COMMENT;
					} else {
						ERROR("%c\n",*p);
					}

				}
				break;
			//parse number value
			case S_VAL:
				{
					char *s,*e;
					PRINT("S_VAL\n");

					s = p;
					if ( *p == '$' ) p++;

					while ( isdigit(*p) )
						p++;
					e = p;
					if ( e-s>4 )
					{
						ENL();
						break;
					}
					if ( tag_param1 == 0 )
					{
						tag_param1 = VAL;
						memcpy( p_param1, s, e-s+1);
						p_param1[e-s] = 0;
					} else
					{
						tag_param2 = VAL;
						memcpy( p_param2, s, e-s+1);
						p_param2[e-s] = 0;
					}

					state = S_SPC;

				}
				break;
			//if comment go to end of line
			case S_COMMENT:
				{
					PRINT("S_COMMENT\n");
					while ( *p == '\n' )
					{
						p++;
					}
					state = S_END;
				}
				break;
			//unknown state
			default:
			{
				ERROR("Unknow state\n");
			}
		}
	}
	PRINT("RES: [%s] [%s] [%s]\n", p_cmd, p_param1, p_param2 );
	PRINT("TAGS: [%d] [%d]\n", tag_param1, tag_param2 );

	data[0] = name2instr( p_cmd, tag_param1, tag_param2 );
	if (data[0] == 0xFF)
		return NULL;

	//PNL();
	if ( tag_param1 == REG )
	{
		PNL();
		data[1] = name2reg( p_param1 );
		if ( data[1] == 0xff )
			return NULL;
	}

	//PNL();
	if ( tag_param2 == REG )
	{
		PNL();
		data[2] = name2reg( p_param2 );
		if ( data[2] == 0xFF )
			return NULL;
	}

	//PNL();
	if ( tag_param1 == VAL )
	{
		PNL();
		int tmp = val2int( p_param1+1 );
		if ( tmp == -1 )
			return NULL;
		data[1] = (uint8_t)tmp;
	}

	//PNL();
	if ( tag_param2 == VAL )
	{
		PNL();
		int tmp = val2int( p_param2+1 );
		if ( tmp == -1 )
			return NULL;
		data[2] = (uint8_t)tmp;
	}

	ret = data;
	return ret;
}