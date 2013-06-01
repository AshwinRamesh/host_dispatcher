#include "../inc/pcb.h"
#include "../inc/readinput.h"
#include "../inc/dispatcher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char const *argv[]){
	/*Initialise Variables*/
	PcbPtr process_queue; // the pcb queue
	/* Validating Program Arguments */
	if (argc != 2) {
		printf("%s\n", "Usage: hostd <filename>");
		return EXIT_FAILURE;
	}
	char file_name[MAX_INPUT_SIZE];
	strcpy(file_name,argv[1]);
	process_queue = read_file(file_name);
	if (process_queue == NULL) { // error in reading
		return EXIT_FAILURE;
	}
	dispatcher(process_queue);
	return 0;
}
