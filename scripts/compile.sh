#!/usr/bin/env bash
# first command line argument is the compile command, following arguments are
# the files to compile
declare -i total=0
declare -i pass=0
declare -i fail=0
fails="Failed files:"
for i in $(seq 2 $#); do
	test=${!i}
	total++
	echo ""
	echo "$test:"
	$1 $test
	retCode=$?
	if (($retCode == 0)); then
		echo "Compilation Successful"
		pass++
	else
		echo "Compilation Failed ($test)"
		fail++
		fails+=" $test"
	fi
done

echo ""
echo "$total files(s) compiled"
echo "$pass successful"
echo "$fail failed"

if (($fail != 0)); then
	echo $fails
	exit 1
fi