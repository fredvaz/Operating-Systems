#!/bin/sh

until [ $# -eq 0 ] # == igual -eq 
do
	echo $1
	shift # \n mudança de linha
done

# nota: não podia usar -lt (<) porque valor de 
#argumentos nunca passaria por 0 e nunca é seria 
#negativo