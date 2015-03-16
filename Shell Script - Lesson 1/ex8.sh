#!/bin/sh

while [[ true ]]; do
	
	var=$(ps -fe | wc -l)
	#users=$(who -u)

	echo "Nº de processos:" $var
	#echo "Nº de users:" $users


	sleep 10 # 10 segundos
done