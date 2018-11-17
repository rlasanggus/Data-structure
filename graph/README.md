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

bool g_insert_vertex(GRAPH* graph, int data);
int compare_vertex(void* x, void*y);
void print_vertex(void* x);
void print_vertex_all(GRAPH* graph);
bool g_delete_vertex(GRAPH* graph, int data);

bool g_insert_arc(GRAPH* graph, int from, int to);
int compare_arc(void* x, void* y);
void print_arc(void* x);
void print_arc_all(GRAPH* graph);

bool destroy_graph(GRAPH* graph);
```
GRAPH를 생성할 때 사용할 create_graph  
vertex를 추가할 때 사용할 g_insert_vertex  
vertex두개를 비교할 compare_vertex  
vertex값을 출력할 print_vertex  
vertex들의 값을 모두 출력할 print_vertex_all  
vertex를 삭제할 g_delete_vertex  
arc를 추가할 때 사용할 g_insert_arc  
arc두개를 비교할 compare_arc  
arc값을 출력할 print_arc  
arc들의 값을 출력할 print_arc_all  
GRAPH를 삭제할 destroy_graph  


## <pre>ADT_graph.c</pre>  
>>[ADT_llist.c](https://github.com/rlasanggus/Data-structure/tree/master/llist)   


[GRAPH* create_graph()](https://github.com/rlasanggus/Data-structure/tree/master/graph#graph-create_graph)  

[bool g_insert_vertex(GRAPH* graph, int data)](https://github.com/rlasanggus/Data-structure/tree/master/graph#bool-g_insert_vertexgraph-graph-int-data)  
[int compare_vertex(void* x, void*y)](https://github.com/rlasanggus/Data-structure/tree/master/graph#int-compare_vertexvoid-x-voidy)  
[void print_vertex(void* x)](https://github.com/rlasanggus/Data-structure/tree/master/graph#void-print_vertexvoid-x)  
[void print_vertex_all(GRAPH* graph)](https://github.com/rlasanggus/Data-structure/tree/master/graph#void-print_vertex_allgraph-graph)  
[bool g_delete_vertex(GRAPH* graph, int data)](https://github.com/rlasanggus/Data-structure/tree/master/graph#bool-g_delete_vertexgraph-graph-int-data)  

[bool g_insert_arc(GRAPH* graph, int from, int to)](https://github.com/rlasanggus/Data-structure/tree/master/graph#bool-g_insert_arcgraph-graph-int-from-int-to)  
[int compare_arc(void* x, void* y)](https://github.com/rlasanggus/Data-structure/tree/master/graph#int-compare_arcvoid-x-void-y)  
[void print_arc(void* x)](https://github.com/rlasanggus/Data-structure/tree/master/graph#void-print_arcvoid-x)    
[void print_arc_all(GRAPH* graph)](https://github.com/rlasanggus/Data-structure/tree/master/graph#void-print_arc_allgraph-graph)  

[bool destroy_graph(GRAPH* graph)](https://github.com/rlasanggus/Data-structure/tree/master/graph#bool-destroy_graphgraph-graph)

#### <code>GRAPH* create_graph()</code>  
```c
GRAPH* create_graph(){
	GRAPH* graph = (GRAPH*)malloc(sizeof(GRAPH));
	graph -> vertex_list = create_list(compare_vertex, print_vertex);
	return graph;
}
```
GRAPH형의 메모리를 할당받고, graph의 vertex_list에 Linked_list를 create해서 넣음(vertex들을 list로 저장)  

#### <code>bool g_insert_vertex(GRAPH* graph, int data)</code>  
```c
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
```  
vertex에는 arc들을 저장할 arc_list가 필요함으로 vertex의 arc_list에 Linked_list를 create해서 넣음  
Linksed_list의 find함수를 이용하여 graph에 vertex가 이미 있는지 확인 
만약 -1이 반환되면, 이미 존재하는 vertex임으로 메모리를 반환(반환하지않으면 메모리가 찌꺼기가되어 남음)  
아니라면 list에 연결  

#### <code>int compare_vertex(void* x, void*y)</code>  
```c
int compare_vertex(void* x, void* y){
	VERTEX* left = (VERTEX*)x;
	VERTEX* right = (VERTEX*)y;
	return (left -> data) - (right -> data);
}
```
list의 find data와 비슷한 형식으로, 하나의 vertex를 left에 또다른 하나의 vertex를 right에 저장 후 left의 데이터에서 right의 데이터를 뺌. 만약 같다면 0이 반환될것이고 다르다면 0이 아닌 값을 반환  
#### <code>void print_vertex(void* x)</code>  
```c
void print_vertex(void* x){
	VERTEX* vertex = (VERTEX*)x;
	printf(" - vertex : %c\n", (char)(vertex -> data));
}
```  
vertex의 data를 출력  
#### <code>void print_vertex_all(GRAPH* graph)</code>  
```c
void print_vertex_all(GRAPH* graph){
	NODE* pos = graph -> vertex_list -> front;
	while(pos != NULL){
		print_vertex(pos -> data_ptr);
		pos = pos -> next;
	}
}
```  
vertex는 graph에 list 형태로 저장되어 있음으로 list의 처음부터 끝까지 지나가며 그 값들을 print_vertex함수를 이용하여 출력  
#### <code>bool g_delete_vertex(GRAPH* graph, int data)</code>  


#### <code>bool g_insert_arc(GRAPH* graph, int from, int to)</code>  

#### <code>int compare_arc(void* x, void* y)</code>  
#### <code>void print_arc(void* x)</code>  
#### <code>void print_arc_all(GRAPH* graph)</code>  

#### <code>bool destroy_graph(GRAPH* graph)</code>  
