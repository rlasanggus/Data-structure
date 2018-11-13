#include "ADT_graph.h"
#include <stdio.h>

int main(){
	int i;
	GRAPH* graph = create_graph();

	int vertex[6] = {'A', 'B', 'C', 'D', 'E', 'F'};

	//VERTEX insertion
	for(i=0; i<6; i++){
		if(!g_insert_vertex(graph, vertex[i]))
			printf(" fall insertion %c \n", (char)vertex[i]);
		else
			printf("graph vertex insertion ok : %c\n", (char)vertex[i]);
	}

	printf("\nGraph's Vertex:\n");
	print_vertex_all(graph);
	printf("\n");

	if(!g_insert_vertex(graph, 'C'))
		printf("graph vertex_insertion failed: %c already exist\n", 'C');
	else
		printf("graph vertex insertion ok: %c\n", 'C');

	//ARC insertion
	if(!g_insert_arc(graph, 'A', 'B'))
		printf("graph arc insertion failed: %c -> %c\n", 'A', 'B');
	else
		printf("graph arc insertion ok: %c -> %c\n", 'A', 'B');

	if(!g_insert_arc(graph, 'A', 'B'))
		printf("graph arc insertion failed: %c -> %c\n", 'A', 'B');

	if(!g_insert_arc(graph, 'B', 'A'))
		printf("graph arc insertion failed: %c -> %c\n", 'A', 'B');

	if(!g_insert_arc(graph, 'B', 'C'))
		printf("graph arc insertion failed: %c -> %c\n", 'A', 'B');

	if(!g_insert_arc(graph, 'C', 'B'))
		printf("graph arc insertion failed: %c -> %c\n", 'A', 'B');

	if(!g_insert_arc(graph, 'D', 'C'))
		printf("graph arc insertion failed: %c -> %c\n", 'A', 'B');

	if(!g_insert_arc(graph, 'E', 'B'))
		printf("graph arc insertion failed: %c -> %c\n", 'A', 'B');

	if(!g_insert_arc(graph, 'F', 'C'))
		printf("graph arc insertion failed: %c -> %c\n", 'A', 'B');

	if(!g_insert_arc(graph, 'F', 'E'))
		printf("graph arc insertion failed: %c -> %c\n", 'A', 'B');
	//print ARC in graph
	printf("\nGraph's Arc: \n");
	print_arc_all(graph);
	printf("\n");

	//del VERTEX 'B'
	if(!g_delete_vertex(graph, 'B'))
		printf("graph vertex delete failed: %c\n", 'B');
	else
		printf("graph vertex delete ok: %c\n", 'B');
	printf("\nGraph's Arc:\n");
	print_arc_all(graph);
	printf("\n");

	if(destroy_graph(graph))
		printf("success\n");

}