#!/bin/bash
g++ test.cpp -DONLINE_JUDGE -DSTRESSTEST --std=c++17 -O2 -o fast || { echo 'fast comp failed'; exit 1;}
g++ slow.cpp --std=c++17 -O2 -o slow || { echo 'slow comp failed'; exit 1;}
g++ gen.cpp --std=c++17 -O2 -o gen || { echo 'gen comp failed'; exit 1;}

for((i=1;;++i)); do
	echo $i
	./gen $i > in
	./fast < in > out1 || { echo 'fast run failed'; break;}
	./slow < in > out2 || { echo 'slow run failed'; break;}
	diff -w out1 out2 || break
done
