#!/bin/bash
g++ oly19practice27.cpp --std=c++14 -O2 -o fast || { echo 'fast comp failed'; exit 1;}
g++ slow.cpp --std=c++14 -w -O2 -o slow || { echo 'slow comp failed'; exit 1;}
g++ gen.cpp --std=c++14 -O2 -o gen || { echo 'gen comp failed'; exit 1;}

for((i=1;i<=100;++i)); do
    echo $i
    ./gen $i > stressin
    ./fast < stressin > out1
    ./slow < stressin > out2
    diff -w out1 out2 || break
done
