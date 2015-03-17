#!/bin/sh

a=10

while [ $a -ge 10 ]
do
   echo $a
   a=`expr $a + 1`
done
