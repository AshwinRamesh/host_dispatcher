#Ashwin Ramesh, 311254012 - Operating Systems Project 2
all: hostdcompile sigtrap

.PHONY: all
.DEFAULT: all

hostdcompile: src/hostd.c inc/hostd.h src/pcb.c inc/pcb.h inc/readinput.h src/readinput.c inc/dispatcher.h src/dispatcher.c inc/mab.h src/mab.c
		gcc -Wall src/hostd.c src/pcb.c src/readinput.c src/dispatcher.c -o hostd

sigtrap:  src/sigtrap.c
		gcc -Wall src/sigtrap.c -o sigtrap
