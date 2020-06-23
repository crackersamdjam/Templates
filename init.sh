#!/bin/bash

if [ $1 = "help" ]; then
	echo "usage: ./init.sh cf 123 E --> {cf123A.cpp ... cf123E.cpp}"
	echo "or ./init.sh cco20 3 --> {cco20p1.cpp ... cco20p3.cpp}"
elif [ $1 = "cf" ]; then
	echo "Letter"
	chars=({A..Z})
	for ((i=0; i<$3; i++))
	do
	  echo "cf$2${chars[i]}.cpp"
	  echo "import_safe" > "cf$2${chars[i]}.cpp"
	done

else
    echo "Number"
    for ((i=1; i<=$2; i++))
	do
	  echo "$1p$i.cpp"
	  echo "import_f" > "$1p$i.cpp"
	done
fi
