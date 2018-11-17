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
```c
bool g_delete_vertex(GRAPH* graph, int data){
	if(graph -> vertex_list -> count == 0)
		return false;
```
graph의 vertex_list의 count 즉 graph에 저장되어있는 vertex개수가 0개라면 vertex를 지우겠다는것이 모순임으로 false 반환  
```c
	bool flag = false;

	VERTEX del_vertex;
	del_vertex.data = data;
	del_vertex.arc_list = NULL;
	int del_index = find_data(graph -> vertex_list, &del_vertex);
	if(del_index == -1)
		return flag;
```  
flag에 false를 저장  
del_vertex를 정의  
Linked_list의 find data를 이용 graph의 vertex_list안에 해당 데이터가 있는지 확인  
없다면 -1반환됨으로 flag(false)값 반환  
```c
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
```  
만약 있다면, 해당 vertex와 연결되어있는 arc들을 모두 제거해줘야함으로 find_data를 이용하여 graph의 모든 vertex를 지나가며 지우고자 하는 vertex와 연결되어있는 arc가 있는지 검색 후 있다면 해당 arc들을 삭제  

#### <code>bool g_insert_arc(GRAPH* graph, int from, int to)</code>  
```c
bool g_insert_arc(GRAPH* graph, int from, int to){
	VERTEX tmp_vertex1;
	tmp_vertex1.data = from;
	tmp_vertex1.arc_list = NULL;

	int vertex_loc = find_data(graph -> vertex_list, &tmp_vertex1);
	if(vertex_loc == -1){
		printf("from_vertex %c: not found\n", (char)from);
	}
	
	VERTEX* from_vertex = (VERTEX*)get_data_at(graph -> vertex_list, vertex_loc);
```  
from vertex를 저장할 vertex1을 정의  
from vertex가 graph안에 존재하는지 find_data함수를 이용하여 검색 
없다면 find_data가 -1을 반환  
존재한다면 from_vertex의 정보를 Linked_list의 get_data_at을 사용하여 가져옴  

```c
	VERTEX tmp_vertex2;
	tmp_vertex2.data = to;
	tmp_vertex2.arc_list = NULL;

	vertex_loc = find_data(graph -> vertex_list, &tmp_vertex2);
	if(vertex_loc == -1){
		printf("to_vertex %c: not fonund\n", (char)to);
		return false;
	}
	
	VERTEX* to_vertex = (VERTEX*)get_data_at(graph -> vertex_list, vertex_loc);
```
to vertex를 저장할 vertex2를 정의
to vertex가 graph안에 존재하는지 find_data함수를 이용하여 검색  
없다면 find_data가 -1을 반환  
존재한다면 to_vertex의 정보를 Linked_list의 get_data_at을 사용하여 가져옴  

```c
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
```
from vertex와 to vertex가 모두 존재했음으로 그 사이를 연결할 arc를 정의  
arc는 to vertex값을 가짐  
from vertex의 arc_list로부터 to vertex와 연결되어있는 arc가 있는지 검색  
존재한다면 연결할 필요없으므로 false 반환  
존재하지 않는다면 from vertex의 arc list에 Linked_list의 add_node_at 함수를 사용 새로운 arc를 추가  
#### <code>int compare_arc(void* x, void* y)</code>  
```c
int compare_arc(void* x, void* y){
	ARC* left = (ARC*)x;
	ARC* right = (ARC*)y;
	return compare_vertex(left -> to_vertex, right -> to_vertex);
}
```  
list의 find data와 비슷한 형식으로, 하나의 arc를 left에 또다른 하나의 arc를 right에 저장 후 left의 데이터에서 right의 데이터를 뺌. 만약 같다면 0이 반환될것이고 다르다면 0이 아닌 값을 반환  
#### <code>void print_arc(void* x)</code>  
```c
void print_arc(void* x){
	ARC* arc = (ARC*)x;
	printf("		-> : %c\n", (char)(arc -> to_vertex -> data));
}
```
해당 arc에 저장되어있는 to vertex값을 출력  
#### <code>void print_arc_all(GRAPH* graph)</code>  

#### <code>bool destroy_graph(GRAPH* graph)</code>  
