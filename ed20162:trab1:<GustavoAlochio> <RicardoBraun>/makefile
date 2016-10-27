# Declarando variaveis
compilador = gcc -g
executavel = trabalhoed
pagina = pagina
editor = editor
wiked = wiked
main = main

#Compila o programa
all: compilar

compilar:


	$(compilador) -o $(executavel)  $(wiked).c $(editor).c $(pagina).c $(main).c

#Executa o programa
run:
	./$(executavel)


limpar:

	rm *.o
	rm $(executavel)
	reset

val: compilar
	valgrind --leak-check=full ./$(executavel)
