/* Header for readinput.c */

#ifndef READINPUT_H_
#define READINPUT_H_

#define MAX_INPUT_LINES 1000	// maximum file size

#include  "pcb.h"
#include <stdio.h>

int count_file_lines(char* file_name) ;
int validate_input_line(int arrival_time, int priority, int processor_time, int mbytes, int num_printers, int num_scanners, int num_modems, int num_cds);
PcbPtr read_file(char * file_name);
#endif
