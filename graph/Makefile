help :
	@echo "make help"
	@echo "make all"

ADT_graph.o : ADT_graph.c
	g++ -c ADT_graph.c

ADT_llist.o : ADT_llist.c
	g++ -c ADT_llist.c

main.o : main.c
	g++ -c main.c

all : ADT_graph.o ADT_llist.o main.o
	g++ -o graph main.o ADT_graph.o ADT_llist.o

run : all
	./graph

clean :
	rm *.o graph