#!/bin/sh

for file in *.old
do
	newf=`basename $file .old` 
	cp $file $newf.new
done