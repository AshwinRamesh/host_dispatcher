#!/bin/bash
# runs all tests in the tests folder.
make
FILES=./tests/*
echo "Starting tests..."
for f in $FILES
do
	echo "************************************** STARTING TEST $f *****************************************************"
	#echo "Command: ./hostd $f"
	./hostd $f
	echo "************************************** DONE TEST ******************************************************\n"
done
# run a test on non existing file
echo "************************************** STARTING TEST ./tests/no_file_here.txt  *****************************************************"
./hostd ./tests/no_file_here.txt
echo "************************************** DONE TEST ******************************************************\n"
echo "Tests Complete"
