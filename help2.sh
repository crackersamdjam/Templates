#!/bin/bash
g++ ./test.cpp -DONLINE_JUDGE --std=c++17 -O2 -o fast || { echo 'fast comp failed'; break;}
# g++ ./slow.cpp --std=c++17 -O2 -o slow || { echo 'slow comp failed'; break;}
# g++ ./gen.cpp --std=c++17 -O2 -o gen || { echo 'gen comp failed'; break;}

# for((i=1;;i++)); do
#     echo $i
#     ./gen $i > in
#     ./fast < in > out1 || { echo 'fast run failed'; break;}
#     ./slow < in > out2 || { echo 'slow run failed'; break;}
#     diff -w out1 out2 || break
# done

for i in data/*in; do
	echo $i
	j=${i%.in}.out
	echo $j
	./fast < $i > out
	diff -w out $j || break;
	#diff -w out $j || { subl $i $j; break;}
done