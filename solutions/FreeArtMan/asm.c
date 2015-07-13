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

void asm_help()
{
	printf("\
Usage: sim [OPTIONS] ...\n\
-i [FILE]   compile choosen file\n\
-o [FILE]   output binary file\n\
\n");
}

//count until NULL
int count_nl( char *p )
{
	int ret = 0;

	if ( p == NULL )
		return -1;

	while ( *p != 0 )
	{
		if (*p == '\n') ret++;
		p++;
	}
	return ret;
}

//return array of ints showing where all newlines are located
int *array_nl( char *p )
{
	int num = -1;
	int *ret = NULL;
	int i;
	char *c;

	if ( p == NULL)
		return NULL;

	num = count_nl( p );
	if (num < 1)
		return NULL;
	//for extrac 0 at begining of array, for easy calc 
	num += 1;

	ret = malloc( sizeof(int)*num );
	
	i = 1; //first one is null
	c = p;
	while ( *c != 0 )
	{
		if ( *c == '\n' )
		{
			ret[i] = c-p;
			i++; 
		}
		c++;
	}
	ret[0] = -1;

	return ret;
}

//get one line and return representation
uint8_t* parse_line( char *buf, int line, int pos, int size )
{
	uint8_t *ret = NULL;

	char *str = NULL;
	uint8_t *inst=NULL;
	
	str = malloc(size+1);
	if ( str == NULL )
	{
		ENL();
		return NULL;
	}

	memcpy( str, &buf[pos], size );
	str[size-1] = 0; //BUG: could be something with line ending

	printf("%d %s\n", line, str);
	inst = str2instr( str );
	if ( inst == NULL )
	{
		ENL();
		return NULL;
	}

	PRINT("%02X %02X %02X\n", inst[0], inst[1], inst[2]);

	ret = inst;
	return ret;
}

int main( int argc, char **argv )
{
	size_t buf_size = 0;
	char *buf = NULL;
	int *nl_arr = NULL, nl_num;
	struct stat fstat;

	char *fname_in = NULL, *fname_out = NULL;
	FILE *f = NULL, *f_out = NULL;
	int c,i,j,cnt;

	while ((c = getopt (argc, argv, "i:o:h")) != -1)
	{
		switch( c )
		{
			case 'i':
				fname_in = optarg;
				break;
			case 'o':
				fname_out = optarg;
				break;
			case 'h':
				{
					asm_help();
					return -1;
				}
			default:
				ENL();
		}
	}

	if ( fname_in == NULL )
	{
		ERROR("Need to set flag -i\n");
		return -1;
	}

	
	if ( fname_out == NULL )
	{
		ERROR("Need to set flag -o\n");
		return -1;
	}
	

	if ( stat( fname_in, &fstat ) == -1 )
	{
		ERROR("Cannot stat file\n")
		return -1;
	}

	f = fopen( fname_in, "r");
	if ( f == NULL )
	{
		ERROR("Cannot open file %s\n", fname_in);
		return -1;
	}

	buf_size = fstat.st_size;
	buf = malloc( buf_size+1 );

	fread( buf, 1, buf_size, f );
	buf[buf_size] = 0;
	fclose( f ); f = NULL;

	f_out = fopen( fname_out, "w" );
	if ( f_out == NULL )
	{
		ERROR("Cannot open file %s\n", fname_out );
		return -1;
	}

	nl_num = count_nl( buf );
	nl_arr = array_nl( buf );

	//could be error with end of file line
	for ( i=0; i<nl_num; i++ )
	{
		uint8_t *instr = NULL ;
		instr = parse_line( buf, i, nl_arr[i]+1, nl_arr[i+1]-nl_arr[i] );
		if ( instr != NULL )
		{
			fwrite( instr, 1, 3, f_out );

			free( instr );
			instr = NULL;
		}
		
	}

	fclose( f_out );

	return 0;
}