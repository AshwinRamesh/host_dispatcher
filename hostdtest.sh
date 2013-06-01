#!/bin/bash
# runs all tests in the tests folder.
make
FILES=./tests/*
echo "Starting tests..."
for f in $FILES
do
	echo "************************************** STARTING TEST $f*****************************************************"
	./hostd ./tests/$f
	echo "************************************** DONE TEST ******************************************************"
done
