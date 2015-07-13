#ifndef __TGS_CPU_H
#define __TGS_CPU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "tgs.h"

//just exit if this flag is set
#define TRACE_NONE 0

//just trace in default manner
#define TRACE_NORMAL 1

//continue every instruction, if there is branch dont fallow branch
#define TRACE_STREAM 2

//fallow all branches
#define TRACE_BRANCH 3

//run and if there is used BA,BB registers stop and ask to input theirs values
#define TRACE_GUIDED 4

//when compare is made you need to save cmp value
#define CMP_NONE 0 
#define CMP_E    1 //equal
#define CMP_NE   2 //not equal
#define CMP_G    3 //greater
#define CMP_L    4 //lower

//7-segment dispay
typedef enum display_segments
{
	A=0,
	B,
	C,
	D,
	E,
	F,
	G
} display_segments;

typedef struct display_t
{
	uint8_t segments[7];
} display_t;

#define REG(X,Y) ((X)->regs[##Y])
#define DSP(X,Y) ((X)->segments[##Y])

#define DSPLY_SIZE 4
typedef struct tgs_cpu
{
	//just array some values could be empty
	uint8_t regs[LAST_REG];
	display_t display[DSPLY_SIZE];
	uint8_t cmp_flag;
} tgs_cpu;

tgs_cpu* tgs_alloc();
void tgs_free( tgs_cpu *tgs );


//non-defence programming
//dont check params, becouse they should be allready safe
//otherwise dont use this API
int tgs_init( tgs_cpu *tgs );
int tgs_nextstep( tgs_cpu *tgs, uint8_t *execdata, uint8_t flags );
int tgs_print( tgs_cpu *tgs );
int tgs_print_dsp( tgs_cpu *tgs );

//per instruction functions

//go to next instuction, PC+=1
void pc_inc( tgs_cpu *tgs );

//ask to set BA,BB
void tgs_set_display( tgs_cpu *tgs );

#endif