#include "ADT_graph.h"
#include <stdlib.h>

int compare_vertex(void* x, void* y){
	VERTEX* left = (VERTEX*)x;
	VERTEX* right = (VERTEX*)y;
	return (left -> data) - (right -> data);
}

void print_vertex(void* x){
	VERTEX* vertex = (VERTEX*)x;
	printf(" - vertex : %c\n", (char)(vertex -> data));
}

int compare_arc(void* x, void* y){
	ARC* left = (ARC*)x;
	ARC* right = (ARC*)y;
	return compare_vertex(left -> to_vertex, right -> to_vertex);
}

void print_arc(void* x){
	ARC* arc = (ARC*)x;
	printf("		-> : %c\n", (char)(arc -> to_vertex -> data));
};


GRAPH* create_graph(){
	GRAPH* graph = (GRAPH*)malloc(sizeof(GRAPH));
	graph -> vertex_list = create_list(compare_vertex, print_vertex);
	return graph;
}

bool g_insert_vertex(GRAPH* graph, int data){
	VERTEX* new_vertex = (VERTEX*)malloc(sizeof(VERTEX));
	new_vertex -> data = data;
	new_vertex -> arc_list = create_list(compare_arc, print_arc);

	int vertex_loc = find_data(graph -> vertex_list, new_vertex);
	if(vertex_loc != -1){
		free(new_vertex);
		return false;//there already exists
	}
	return add_node_at(graph -> vertex_list, graph -> vertex_list -> count, new_vertex);
}

void print_vertex_all(GRAPH* graph){
	NODE* pos = graph -> vertex_list -> front;
	while(pos != NULL){
		print_vertex(pos -> data_ptr);
		pos = pos -> next;
	}
}

bool g_insert_arc(GRAPH* graph, int from, int to){
	VERTEX tmp_vertex1;
	tmp_vertex1.data = from;
	tmp_vertex1.arc_list = NULL;

	int vertex_loc = find_data(graph -> vertex_list, &tmp_vertex1);
	if(vertex_loc == -1){
		printf("from_vertex %c: not found\n", (char)from);
	}

	VERTEX* from_vertex = (VERTEX*)get_data_at(graph -> vertex_list, vertex_loc);

	VERTEX tmp_vertex2;
	tmp_vertex2.data = to;
	tmp_vertex2.arc_list = NULL;

	vertex_loc = find_data(graph -> vertex_list, &tmp_vertex2);
	if(vertex_loc == -1){
		printf("to_vertex %c: not fonund\n", (char)to);
		return false;
	}
	VERTEX* to_vertex = (VERTEX*)get_data_at(graph -> vertex_list, vertex_loc);

	ARC* new_arc = (ARC*)malloc(sizeof(ARC));
	new_arc -> to_vertex = to_vertex;

	int arc_loc = find_data(from_vertex -> arc_list, new_arc);
	if(arc_loc != -1){
		free(new_arc);
		return false;
	}

	return add_node_at(
		from_vertex -> arc_list, 
		from_vertex -> arc_list -> count, 
		new_arc);
}

void print_arc_all(GRAPH* graph){
	NODE* vertex_cur = graph -> vertex_list -> front;
	while(vertex_cur != NULL){
		printf("vertex: %d\n", (char)((VERTEX*)vertex_cur -> data_ptr)->data);
		NODE* pos_arc = ((VERTEX*)(vertex_cur -> data_ptr)) -> arc_list -> front;

		while(pos_arc != NULL){
			print_arc(pos_arc -> data_ptr);
			pos_arc = pos_arc -> next;
		}
		vertex_cur = vertex_cur -> next;
	}
}

bool g_delete_vertex(GRAPH* graph, int data){
	if(graph -> vertex_list -> count == 0)
		return false;

	bool flag = false;

	VERTEX del_vertex;
	del_vertex.data = data;
	del_vertex.arc_list = NULL;
	int del_index = find_data(graph -> vertex_list, &del_vertex);
	if(del_index == -1)
		return flag;

	flag = del_node_at(graph -> vertex_list, del_index);

	ARC del_arc;
	del_arc.to_vertex = &del_vertex;
	NODE* pos_vertex = graph -> vertex_list -> front;

	while(pos_vertex != NULL){
		del_index = find_data(((VERTEX*)(pos_vertex -> data_ptr)) -> arc_list, &del_arc);//error return -1
		if(del_index != -1)
			flag = del_node_at(((VERTEX*)(pos_vertex -> data_ptr)) -> arc_list, del_index);
		pos_vertex = pos_vertex -> next;
	}
	return flag;
}


bool destroy_graph(GRAPH* graph){
	if(graph == NULL){
		printf("graph is empty graph\n");
		return false;
	}

	LLIST* del_vertex = graph -> vertex_list;
	LLIST* del_arc;

	while(get_data_at(del_vertex, 0) != NULL){
		del_arc = ((VERTEX*)get_data_at(del_vertex, 0)) -> arc_list;

		while(get_data_at(del_arc, 0) != NULL){
			del_node_at(del_arc, 0);
		}

		del_node_at(del_vertex, 0);
	}

	return true;
}