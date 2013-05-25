#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../inc/dispatcher.h"

int clock_time;

void dispatcher(PcbPtr queue) {

	printf("%s\n", "stub");
	clock_time = 0;
	while (queue != NULL) {
		// check running processes
			// decrement remaining cputime
				// if times up terminate and free memory
		// for each item in the queue start anything where the clock time >= arrival time
			//deque and fork
			// set it as running. ?? make a new variable
		sleep(1);
		clock_time = clock_time+1;
	}
}
