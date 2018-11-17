# ADT_Graph  
![image](https://user-images.githubusercontent.com/43701183/48654149-e3cc5280-ea4d-11e8-9cec-972a719d60aa.png)  
![image](https://user-images.githubusercontent.com/43701183/48654156-ec248d80-ea4d-11e8-8c87-df3e674f72f8.png)
![image](https://user-images.githubusercontent.com/43701183/48654162-f3e43200-ea4d-11e8-9d25-04d051aaba94.png)  



## <pre>ADT_graph.h</pre>  
>>[ADT_llist.h](https://github.com/rlasanggus/Data-structure/tree/master/llist)  
```c
typedef struct vertex{
	int data;
	LLIST* arc_list;
}VERTEX;
```
VERTEX에서 다른 vertex로 연결되는 길인 arc들을  list로 저장.  
```c
typedef struct arc{
	VERTEX* to_vertex;
}ARC;
```  
arc의 구조체 정의. arc는 목적지가 되는 vertex의 주소를 가져야함.  
출발지 vertex의 arc_list안에 arc가 저장되기때문에 출발지의 정보는 출발지 vertex가 가지고있음  
```c
typedef struct{
	LLIST* vertex_list;	
}GRAPH;
```  
GRAPH는 vertex들의 정보를 가져야함.  
linked_list를 이용하여 vertex를 list로 저장  
```c
GRAPH* create_graph();

int compare_vertex(void* x, void*y);
void print_vertex(void* x);

int compare_arc(void* x, void* y);
void print_arc(void* x);

bool g_insert_vertex(GRAPH* graph, int data);
void print_vertex_all(GRAPH* graph);

bool g_insert_arc(GRAPH* graph, int from, int to);
void print_arc_all(GRAPH* graph);

bool g_delete_vertex(GRAPH* graph, int data);
bool destroy_graph(GRAPH* graph);
```
* [GRAPH* create_graph()](https://github.com/rlasanggus/Data-structure/tree/master/graph#graph-create_graph)  
	* sdf
* [int compare_vertex(void* x, void*y)](https://github.com/rlasanggus/Data-structure/tree/master/graph#int-compare_vertexvoid-x-voidy)  
* [void print_vertex(void* x)](https://github.com/rlasanggus/Data-structure/tree/master/graph#void-print_vertexvoid-x)  
* [int compare_arc(void* x, void* y)](https://github.com/rlasanggus/Data-structure/tree/master/graph#int-compare_arcvoid-x-void-y)  
* [void print_arc(void* x)](https://github.com/rlasanggus/Data-structure/tree/master/graph#void-print_arcvoid-x)    
* [bool g_insert_vertex(GRAPH* graph, int data)](https://github.com/rlasanggus/Data-structure/tree/master/graph#bool-g_insert_vertexgraph-graph-int-data)  
* [void print_vertex_all(GRAPH* graph)](https://github.com/rlasanggus/Data-structure/tree/master/graph#void-print_vertex_allgraph-graph)  
* [bool g_insert_arc(GRAPH* graph, int from, int to)](https://github.com/rlasanggus/Data-structure/tree/master/graph#bool-g_insert_arcgraph-graph-int-from-int-to)  
* [void print_arc_all(GRAPH* graph)](https://github.com/rlasanggus/Data-structure/tree/master/graph#void-print_arc_allgraph-graph)  
* [bool g_delete_vertex(GRAPH* graph, int data)](https://github.com/rlasanggus/Data-structure/tree/master/graph#bool-g_delete_vertexgraph-graph-int-data)  
* [bool destroy_graph(GRAPH* graph)](https://github.com/rlasanggus/Data-structure/tree/master/graph#bool-destroy_graphgraph-graph) 




## <pre>ADT_graph.c</pre>  
>>[ADT_llist.c](https://github.com/rlasanggus/Data-structure/tree/master/llist)   


#### <code>int compare_vertex(void* x, void*y)</code>  
#### <code>void print_vertex(void* x)</code>  
#### <code>int compare_arc(void* x, void* y)</code>  
#### <code>void print_arc(void* x)</code>  
#### <code>GRAPH* create_graph()</code>  
#### <code>bool g_insert_vertex(GRAPH* graph, int data)</code>  
#### <code>void print_vertex_all(GRAPH* graph)</code>  
#### <code>bool g_insert_arc(GRAPH* graph, int from, int to)</code>  
#### <code>void print_arc_all(GRAPH* graph)</code>  
#### <code>bool g_delete_vertex(GRAPH* graph, int data)</code>  
#### <code>bool destroy_graph(GRAPH* graph)</code>  
