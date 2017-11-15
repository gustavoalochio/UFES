COMPILADOR := gcc
LPTHREAD := -lpthread
LMATH := -lm

all: build clean

build:
	@$(COMPILADOR) main.c fila.c sieve.c -c -g $(LPTHREAD) $(LMATH)
	@$(COMPILADOR) *.o -o trab1 -g $(LPTHREAD) $(LMATH)
	
run:
	@./Trabalho $N $M
run-val:
	valgrind --leak-check=full ./Trabalho $arg1 $arg2
clean:
	@rm -f *.o
