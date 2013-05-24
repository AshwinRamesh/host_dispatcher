#Ashwin Ramesh, 311254012 - Operating Systems Project 2
all: hostd sigtrap

.PHONY: all
.DEFAULT: all

hostd: src/hostd.c inc/hostd.h
		gcc -Wall src/hostd.c src/pcb.c src/readinput.c -o hostd

sigtrap:  src/sigtrap.c
		gcc -Wall src/sigtrap.c -o sigtrap
