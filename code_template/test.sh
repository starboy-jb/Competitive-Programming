#! /bin/bash
# This is something
for ((i = 1; ; i++)); do
	echo $i
	./gen $i > in
	./main < in > out1
	./brute < in > out2
	diff -w out1 out2 || break
done
