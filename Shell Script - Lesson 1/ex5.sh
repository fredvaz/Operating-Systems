#!/bin/sh

for file in *; # Vai procurar todo o tipo de ficheiros
do 
	if [[ $1 == '-l' ]]; then
		
		if [ -f $file ]; then
			echo "FILE - $file";
		fi

		if [ -d $file ]; then
			echo "DIR - $file";
		fi
	else
		echo "$file"; # Mostra apens 
	fi

done