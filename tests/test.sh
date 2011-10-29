#!/bin/bash

PROGRAM=../wordcount
DIFF="diff -q"

for i in *.in
do
	echo Running test: $i
	time $PROGRAM $i ${i/.in/.try}
	$DIFF ${i/.in/.out} ${i/.in/.try}
	echo
done

