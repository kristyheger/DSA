#!/usr/bin/env bash
rm -f out check.out MAX MAXTIME log ans my

[ -n "$2" ] && export L="-D$2"

if [ -z "$1" ]; then
	make || exit 1
	run="make run -s"
else
	export VER=$1
	make ver || exit 1
	run="make runv -s"
fi

if [ -f check2.cpp ]; then
	g++ -O2 check.cpp -o check.out
elif ! [ -f check2.out ] ;then
    wget -q https://www.csie.ntu.edu.tw/~b04902103/files/check2.out
fi
chmod +x check2.out
rm -f record$1
touch MAX
touch MAXTIME
echo "0.0" > MAX
echo "0m0.0s" > MAXTIME
########################################################################
for (( i = 1; i < 49; i++ )); do
	N="${i}"
	if [[ $i -lt 10 ]]; then
		N="0${i}"
	fi
	printf "Test Case $N: "
	if [ $i -gt 9 ]; then
		printf "data$i: " >> record$1
	else
		printf "data$i:  " >> record$1
	fi
	curl -s  "http://mirlab.org/jang/courses/dsa/homework/2016/hw06/testSet/${N}_input.txt" | ( time $run > out ) 2>log
	curl -s "http://mirlab.org/jang/courses/dsa/homework/2016/hw06/testSet/${N}_output.txt" | head -n 1 > ans
	head -n 1 out > my
	./check2.out
	cat log >> record$1
	echo >> record$1
	rm -f log
done
echo
printf "MAX DEVIATION: "
cat MAX
echo
printf "MAX TIME: "
cat MAXTIME
echo
rm -f out check2.out MAX MAXTIME log ans my
