#!/bin/bash
g++ gen.cpp --std=c++14 -O2 -o gen || { echo 'gen comp failed'; exit 1;}

echo 'custom_judge: grader.py
unbuffered: true
archive: data.zip
test_cases:' > init.yml

# small cases
echo '- batched:' >> init.yml

for((i=1;i<=20;i++)); do
	v=$((i+2>20 ? 20 : i+2))
    echo $i
	echo "v $v"
    ./gen $v > data/$i.in || { echo 'gen run failed'; exit 1;}
	#cat data/$i.in
	echo "  - {in: data/$i.in}" >> init.yml
done

echo '  points: 30' >> init.yml


# 2^n-1 cases
echo '- batched:' >> init.yml

for((i=21;i<=30;i++)); do
	v=$(((1<<($i-19))-1)) || { echo 'reee'; exit 1;}
	echo $i
	echo "v $v"
	./gen $v > data/$i.in || { echo 'gen run failed'; exit 1;}
	#cat data/$i.in
	echo "  - {in: data/$i.in}" >> init.yml
done

echo '  points: 30' >> init.yml

# main tests
echo '- batched:' >> init.yml

for((i=40;i<=70;i++)); do
    v=$((2048-70+$i))
    echo $i
    echo "v $v"
    ./gen $v > data/$i.in || { echo 'gen run failed'; exit 1;}
    #cat data/$i.in
    echo "  - {in: data/$i.in}" >> init.yml
done

echo '  points: 40' >> init.yml


zip -r data.zip data/*

