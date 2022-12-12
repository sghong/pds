#!/bin/bash

for entry in `ls -d $1/*`; do
	echo $entry;
	for entry2 in `ls $entry/*`; do 
		echo $entry2;
	done
done
