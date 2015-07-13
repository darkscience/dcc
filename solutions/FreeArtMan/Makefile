CC=gcc
CFLAGS=-g3 -O2

dbg: 
	$(CC) $(CFLAGS) -c tgs_cpu.c
	$(CC) $(CFLAGS) -c tgs.c
	$(CC) tgs_cpu.o tgs.o dbg.c -o dbg

sim:
	$(CC) $(CFLAGS) -c tgs_cpu.c
	$(CC) $(CFLAGS) -c tgs.c
	$(CC) $(CFLAGS) tgs_cpu.o tgs.o sim.c -o sim

dis:
	$(CC) $(CFLAGS) -c tgs_cpu.c
	$(CC) $(CFLAGS) -c tgs.c
	$(CC) $(CFLAGS) tgs.o tgs_cpu.o dis.c -o dis

asm:
	$(CC) $(CFLAGS) -c tgs_cpu.c
	$(CC) $(CFLAGS) -c tgs.c
	$(CC) $(CFLAGS) tgs.o tgs_cpu.o asm.c -o asm

clean:
	rm -f *.o
	rm -f asm
