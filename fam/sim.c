#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>


#include "tgs.h"
#include "tgs_cpu.h"

#include "debug.h"

void sim_help()
{
	printf("\
Usage: sim [OPTIONS] ...\n\
-f [FILE]   run choosen file\n\
-s [NUM]    instruction number to run\n\
-r          show register values on each step\n\
-u [DELAY]  delay for usecs between each instruction execution\n\
\n");
}

int main( int argc, char **argv )
{
	struct stat fstat;
	int binbuf_size = -1;
	uint8_t *binbuf=NULL;
	FILE *f = NULL;
	int i,c;

	//setting up with flags
	//file name
	char *fname = NULL;
	//delay between instuction execution
	unsigned int usec=0;
	//how many steps to run
	unsigned int steps=10;
	//show CPU register state
	unsigned int show_reg=0;

	tgs_cpu *cpu=NULL;

	while ((c = getopt (argc, argv, "f:u:s:rh")) != -1)
	{
		switch( c )
		{
			case 'f':
				fname = optarg;
				break;
			case 'u':
				usec = atoi( optarg );
				break;
			case 's':
				steps = atoi( optarg );
				break;
			case 'r':
				show_reg = 1;
				break;
			case 'h':
				{
					sim_help();
					return -1;
				}
			default:
				ENL();
		}
	}

	//if no fname set then exit
	if ( fname == NULL )
	{
		ERROR("We need file as -f [FILE] param\n");
		exit(1);
	}

	if ( stat( fname, &fstat ) == -1 )
	{
		ERROR("Cannot stat file %s\n", fname );
		exit(1);
	}


	f = fopen( fname, "r" );
	if ( f == NULL )
	{
		ERROR("Cannot open file %s \n", fname);
		exit(1);
	}

	binbuf_size  = fstat.st_size;
	binbuf = malloc( binbuf_size );
	fread( binbuf, 1, binbuf_size, f );


	//CORE CODE
	printf("\
+++++++++++++++++++++++++++++++++++\n\
+ TGS CPU INITIAL STATE           +\n\
+++++++++++++++++++++++++++++++++++\n\
");


	cpu = tgs_alloc();
	tgs_init( cpu );


	tgs_print( cpu );
	for (i=0; i<steps; i++)
	{
		uint8_t *cur_inst = &binbuf[cpu->regs[PC]*3];

		char *dec_instr = inst2str( cur_inst );
		if ( dec_instr != NULL )
		{
			printf( "STEP:%02d PC:%02x %s \n", i, cpu->regs[PC], dec_instr );
			free( dec_instr );

			tgs_nextstep( cpu, binbuf, TRACE_NORMAL );
			if ( show_reg == 1 )
				tgs_print( cpu );
			usleep( usec );
			
		} else
		{
			ERROR("Unknow instruction\n");
		}
	}

	//tgs_free( cpu );


	//free( binbuf );

	return 0;
}