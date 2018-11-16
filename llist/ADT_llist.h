#include <stdio.h>

typedef struct node{
	void* data_ptr;
	struct node* next;
}NODE;

typedef struct{
	int count;
	NODE* front;
	NODE* rear;
	NODE* pos;
	int(*cmp_func)(void* x, void* y);
	void(*print_func)(void* x);
}LLIST;

LLIST* create_list(int(*c_func)(void*x, void*y), void(*p_func)(void* x));
bool add_node_at(LLIST* list, unsigned int index, void* in);
bool del_node_at(LLIST* list, unsigned int index);
void* get_data_at(LLIST* list, unsigned int index);
bool change_data_at(LLIST* list, unsigned int index, void* new_data);
int find_data(LLIST* list, void* search_data);
