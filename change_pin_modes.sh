#!/bin/bash

COUNTER=7 
while [ $COUNTER -lt 14 ]; do
	gpio mode $i in
	let COUNTER=COUNTER+1
done
