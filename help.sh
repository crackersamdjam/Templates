#!/bin/bash
g++ ./fast.cpp --std=c++14 -O2 -o fast
g++ ./slow.cpp --std=c++14 -O2 -o slow
g++ ./gen.cpp --std=c++14 -O2 -o gen

for((i=1;i<=1000;++i)); do
    echo $i
    ./gen $i > stressin
    ./fast < stressin > out1
    ./slow < stressin > out2
    diff -w out1 out2 || break
done
