#!/bin/sh

while [[ true ]]; do # executa até fazer quit basta um break ou boolean
	
	echo "MENU"
	echo "========================================"
	echo "1 - List the files of the HOME directory"
	echo "2 - Show text file"
	echo "3 - Edit file"
	echo "4 - Quit"

	read comando file

	case $comando in # Usar $ para acender ao contéudo da variável comando
		1)
			ls ;; # Vamos usar o comando da shell mas poderiamos ler a directoria
		2)
			less $file ;; # leitor
		3)
			nano $file ;; # editor
		4)
			break ;; # quit
		*) # default, ou seja, outras entradas como comando
			echo "Opção não valida ! Escolha de 1 a 4." ;;
	esac

done