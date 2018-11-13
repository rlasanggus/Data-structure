ADT_queue.o : ADT_queue.c
	g++ -c ADT_queue.c

main.o : main.c
	g++ -c main.c

all : ADT_queue.o main.o
	g++ -o queue main.o ADT_queue.o

run : all
	./queue

clean : 
	rm -rf *.o queue