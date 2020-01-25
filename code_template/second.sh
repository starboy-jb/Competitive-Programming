#! /bin/bash
# This is something
for ((i = 1; i <= 10; i++)); do
	echo "$(tput setaf 1)$(tput setab 7)Test Case : $i $(tput sgr 0)"
	./gen $i > in
	cat in
	./brute < in > out2
	cat out2
	printf "\n"
done
