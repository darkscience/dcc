#include "tgs_cpu.h"

tgs_cpu* tgs_alloc()
{
	tgs_cpu *tgs = NULL;

	tgs = malloc( sizeof(tgs_cpu) );
	if ( tgs == NULL )
	{
		ENL();
		return NULL;
	}

	memset( tgs, 0, sizeof(tgs_cpu) );

	return tgs;
}


void tgs_free( tgs_cpu *tgs )
{
	if ( tgs != NULL )
		free( tgs );
}


int tgs_init( tgs_cpu *tgs )
{
	int ret=0;
	int i = 0;

	memset(tgs, 0, sizeof(tgs) );

	return ret;
}


int tgs_nextstep( tgs_cpu *tgs, uint8_t *execdata, uint8_t flags )
{
	int ret = 0;
	
	uint8_t *data = &execdata[ tgs->regs[PC]*3 ]; 
	int opcode = data[0];

	if ( flags == TRACE_NONE )
		return ret;

	switch ( opcode )
	{
			case I_ADD_RR:
				{
					tgs->regs[data[1]] = tgs->regs[data[1]] + tgs->regs[data[2]];
					pc_inc( tgs );
				}
				break;
			case I_ADD_RV:
				{
					tgs->regs[data[1]] = tgs->regs[data[1]] + data[2];
					pc_inc( tgs );
				}
				break;
			case I_SUB_RR:
				{

				}
				break;
			case I_SUB_RV:
				{

				}
				break;
			case I_LSH_RR:
				{

				}
				break;
			case I_LSH_RV:
				{

				}
				break;
			case I_RSH_RR:
				{

				}
				break;
			case I_RSH_RV:
				{

				}
				break;
			case I_AND_RR:
				{

				}
				break;
			case I_AND_RV:
				{

				}
				break;
			case I_OR_RR:
				{

				}
				break;
			case I_OR_RV:
				{

				}
				break;
			case I_XOR_RR:
				{

				}
				break;
			case I_XOR_RV:
				{

				}
				break;
			case I_CMP_RR:
				{

				}
				break;
			case I_CMP_RV:
				{
					uint8_t val1 = tgs->regs[data[1]];
					uint8_t val2 = data[2];
					if ( val1 == val2 )
					{
						tgs->cmp_flag = CMP_E;
					} else if ( val1 != val2 )
					{
						tgs->cmp_flag = CMP_NE;
					} else if ( val1 > val2 )
					{
						tgs->cmp_flag = CMP_L;
					} else if ( val1 < val2 )
					{
						tgs->cmp_flag = CMP_G;
					} else
					{
						ERROR("How that possible?");
					}
					pc_inc( tgs );
				}
				break;
			case I_BR:
				{
					tgs->regs[PC] = data[1];
				}
				break;
			case I_BE:
				{

				}
				break;
			case I_BNE:
				{
					if ( tgs->cmp_flag == CMP_NE )
					{
						tgs->regs[PC] = data[1];
					} else
					{
						pc_inc( tgs );
					}
				}
				break;
			case I_BG:
				{

				}
				break;
			case I_BL:
				{

				}
				break;
			case I_MOV_RR:
				{
					//PNL();
					//PRINT("%d %d\n", data[1], data[2])
					tgs->regs[data[1]] = tgs->regs[data[2]];
					pc_inc( tgs );
				}
				break;
			case I_MOV_RV:
				{
					//PNL();
					//PRINT("%d %d\n", data[1], data[2])
					tgs->regs[data[1]] = data[2];
					pc_inc( tgs );

				}
				break;
			default:
				ERROR("Unknow opcode\n");
	}
	return ret;
}


int tgs_print( tgs_cpu *tgs )
{
	static uint8_t old_register_state[LAST_REG];

	int i;
	int empty_output = 1;


	//printf("CPU state:\n");

	//print registers
	i = 0;
	while ( reg_names[i].name != 0 )
	{
		if ( old_register_state[reg_names[i].reg] 
			!= tgs->regs[reg_names[i].reg])
		{
			if ( reg_names[i].reg != PC )
				printf("%s:%02x", reg_names[i].name, tgs->regs[reg_names[i].reg]);
			if ( empty_output == 1 )
				empty_output == 0;
		}

		i += 1;
	}
	if ( !empty_output )
		printf("\n");

	memcpy( old_register_state, tgs->regs, LAST_REG );

	//print display
	return 0;
}


int tgs_print_dsp( tgs_cpu *tgs )
{
	int i,j;
	char buf[4][16];
	
	memset( buf, 0, sizeof(buf) );

	for ( i=0; i < DSPLY_SIZE; i++ )
	{
		//segments
		for (j=0; j<7;j++)
		{

		}
	}

}

void pc_inc( tgs_cpu *tgs )
{
	tgs->regs[PC] += 1;
}


void tgs_set_display( tgs_cpu *tgs )
{
	
}