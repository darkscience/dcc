#ifndef __RB_DEBUG_UTILS_H
#define __RB_DEBUG_UTILS_H

//what about kprintf?

//config options
#define PRINTF printf
#define COLORIZE
#define PRINT_LINENUM
#define PRINT_FILENAME
#define PRINT_DEBUG


//use color
#ifdef COLORIZE
	#define D_COLOR "1;32m"
	#define D_COLOR_S "\033[" D_COLOR
	#define D_COLOR_E "\033[0m"
	#define E_COLOR "1;31m"
	#define E_COLOR_S "\033[" E_COLOR
	#define E_COLOR_E "\033[0m"
#else
	#define D_COLOR
	#define D_COLOR_S
	#define D_COLOR_E
	#define E_COLOR
	#define E_COLOR_S
	#define E_COLOR_E
#endif

//print debug line
#ifdef PRINT_LINENUM
	#define PRINT_LINE_F "LINE:%d "
	#define PRINT_LINE_D __LINE__
#else
	#define PRINT_LINE_F ""
	#define PRINT_LINE_D ""
#endif

//print
#ifdef PRINT_FILENAME
	#define PRINT_FILE_F "FILE:%s "
	#define PRINT_FILE_D __FILE__
#else
	#define PRINT_FILE_F ""
	#define PRINT_FILE_D ""
#endif

//print debug string
#ifdef PRINT_DEBUG
	#define PRINT_DEBUG_F "Debug: "
#else
	#define PRINT_DEBUG_F ""
#endif

#define PRINT( format, args ... ) PRINTF( D_COLOR_S PRINT_DEBUG_F \
	PRINT_FILE_F PRINT_LINE_F format D_COLOR_E, PRINT_FILE_D, \
	PRINT_LINE_D, ##args);

#define ERROR( format, args ... ) PRINTF( E_COLOR_S PRINT_DEBUG_F \
	PRINT_FILE_F PRINT_LINE_F format E_COLOR_E, PRINT_FILE_D, \
	PRINT_LINE_D, ##args);

#define PNL() PRINT("\n");

#define ENL() ERROR("\n");


#endif
