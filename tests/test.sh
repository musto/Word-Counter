#!/bin/bash

PROGRAM=../wordcount
DIFF="diff -q"

for i in *.in
do
	echo -n Running test: $i
	time $PROGRAM $i testoutput
	$DIFF ${i/.in/.out} testoutput
	echo
done

