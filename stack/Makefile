ADT_stack.o : ADT_stack.c
	g++ -c ADT_stack.c

main.o : main.c
	g++ -c main.c

all : main.o ADT_stack.o
	g++ -o stack main.o ADT_stack.o

	./stack

clean : 
	rm -rf *.o stack

