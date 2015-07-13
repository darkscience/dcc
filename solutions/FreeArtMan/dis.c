#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


#include "debug.h"
#include "tgs.h"



int main( int argc, char **argv )
{
	char *fname = NULL;
	FILE *f = NULL;
	struct stat fstat;
	int binbuf_size = -1;
	uint8_t *binbuf=NULL;
	int fret;

	int i,c;
	
	while ((c = getopt (argc, argv, "f:")) != -1)
	{
		switch( c )
		{
			case 'f':
				fname = optarg;
				break;
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

	for (i=0; i<binbuf_size; i+=3)
	{
		char *dec_instr = inst2str( &binbuf[i] );
		if ( dec_instr != NULL )
		{
			printf( "%02d %s\n", i/3, dec_instr );
			free( dec_instr );
		} else
		{
			ERROR("Unknow instruction\n");
		}
	}

	free( binbuf );

	return 0;
}

