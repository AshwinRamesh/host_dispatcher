#!/bin/bash

make
./hostd tests/rr_test.txt > output.txt &
echo "running $!"
p_id=$!
sleep 6
kill $p_id
date > output_small.txt
head -n 300 output.txt >> output_small.txt
rm output.txt
