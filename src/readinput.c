#include "../inc/pcb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PcbPtr read_file(FILE *file) {

	char buffer[MAX_INPUT_SIZE];

	/* Read each line of the file */
	while(fgets(buffer,sizeof(buffer),file) != NULL) {
		int arg_count = sscanf(buffer,"%d, %d, %d, %d, %d, %d, %d, %d",
				)
	}

}
