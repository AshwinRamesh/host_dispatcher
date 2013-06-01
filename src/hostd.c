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
	PcbPtr process_queue; // the pcb queue
	if (argc != 2) { // ensure that there is only 1 arg provided to hostd
		printf("%s\n", "Usage: hostd <filename>");
		return EXIT_FAILURE;
	}
	char file_name[MAX_INPUT_SIZE];
	strcpy(file_name,argv[1]); // copy the arg to a string
	process_queue = read_file(file_name); // process the input queue from the file
	if (process_queue == NULL) { // error in reading
		return EXIT_FAILURE;
	}
	dispatcher(process_queue); // run the dispatcher
	return 0;
}
