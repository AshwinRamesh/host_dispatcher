#Ashwin Ramesh, 311254012 - Operating Systems Project 2
all: hostdcompile sigtrap

.PHONY: all
.DEFAULT: all

hostdcompile: src/hostd.c src/pcb.c inc/pcb.h inc/readinput.h src/readinput.c inc/dispatcher.h src/dispatcher.c inc/mab.h src/mab.c inc/resources.h src/resources.c
		gcc -Wall src/hostd.c src/pcb.c src/readinput.c src/dispatcher.c src/resources.c src/mab.c -o hostd

sigtrap:  src/sigtrap.c
		gcc -Wall src/sigtrap.c -o sigtrap

clang: src/hostd.c src/pcb.c inc/pcb.h inc/readinput.h src/readinput.c inc/dispatcher.h src/dispatcher.c inc/mab.h src/mab.c inc/resources.h src/resources.c
		clang src/hostd.c src/pcb.c src/readinput.c src/dispatcher.c src/resources.c src/mab.c -o hostd

