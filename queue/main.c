#include "ADT_queue.h"
#include <stdio.h>

int main(){
	QUEUE* queue;
	queue = create_queue();

	int data = 10;
	if(enqueue(queue, &data))
		printf("enqueue : ok\n");
	else
		printf("enqueue : fail\n");

	printf("count : %d\n", queue->count);
	printf("data : %d\n", *((int*)(queue->front->data_ptr)));
}