#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>


int main(int argc, char const *argv[])
{
	FILE * inputFile;
	if (argc != 2) { // Too many arguments given
		printf("%s\n", "Usage: hostd <filename>");
		return EXIT_FAILURE;
	}
	else if (!(inputFile = fopen(argv[1],"r"))) { // The input file given does not exist
		printf("%s\n", "Error: Unable to open file.");
		return EXIT_FAILURE;
	}
	else{
		printf("Test\n");
	}
		return EXIT_SUCCESS;
}
