#!/bin/sh

while [ $# -gt 0 ] 
do
	echo $1
	shift # muda $1 $2 etc
done