#Ashwin Ramesh, 311254012 - Operating Systems Project 2
all: hostd sigtrap

.PHONY: all
.DEFAULT: all

hostd: src/hostd.c inc/hostd.h
		gcc src/hostd.c -o hostd

sigtrap:  src/sigtrap.c
		gcc src/sigtrap.c -o sigtrap
