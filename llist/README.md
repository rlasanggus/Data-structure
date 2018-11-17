# Linsked_List    

![image](https://user-images.githubusercontent.com/43701183/48621190-1f333680-e9e6-11e8-9050-b4e2d603ee7d.png)  
![image](https://user-images.githubusercontent.com/43701183/48621210-28240800-e9e6-11e8-8c29-3a98eb5fdeca.png)  


## <pre>ADT_llist.h</pre>  
```c
typedef struct node{
	void* data_ptr;
	struct node* next;
}NODE;
```  
llist 에서 데이터를 가리키는 포인터값을 저장할 data_ptr, 다음 노드의 주소 값을 가리킬 노드형의 next 를 정의, 구조체 node 를 NODE로 정의(데이터에 어떤 변수가 올 지 모름으로 void* 형으로 정의)  
```c
typedef struct{
	int count;
	NODE* front;
	NODE* rear;
	NODE* pos;
	int(*cmp_func)(void* x, void* y);
	void(*print_func)(void* x);
}LLIST;
```
llist을 쌓기 위해 노드의 개수를 알려줄 count, 현재 맨 앞의 노드 주소를 가리킬 front, 맨 뒤의 노드 주소를 가리킬 rear, llist에서 인덱스 값을 입력받아 그 위치로 이동하기위한 NODE형의 pos을 정의, 이후 LLIST를 만들면서 입력받아 사용할 포인터 함수들을 정의.  
```c
LLIST* create_list(int(*c_func)(void*x, void*y), void(*p_func)(void* x));
bool add_node_at(LLIST* list, unsigned int index, void* in);
bool del_node_at(LLIST* list, unsigned int index);
void* get_data_at(LLIST* list, unsigned int index);
bool change_data_at(LLIST* list, unsigned int index, void* new_data);
int find_data(LLIST* list, void* search_data);
```  
LLIST를 생성할 때 사용할 create_list  
LLIST에 데이터를 추가할 때 사용할 add_node_at  
노드를 삭제할 때 사용할 del_node_at  
노드에 저장된 데이터를 가져올 때 사용할 get_data_at  
노드에 저장된 데이터값을 새로운 데이터로 바꿀때 사용할 chage_data_at  
노드에 저장된 데이터를 찾을 find_data(index값을 return)  


## <pre>ADT_llist.c</pre>  
> [LLIST* create_list(int(*c_func)(void*x, void*y), void(*p_func)(void* x))](https://github.com/rlasanggus/Data-structure/tree/master/llist#llist-create_listintc_funcvoidx-voidy-voidp_funcvoid-x)  
> [bool add_node_at(LLIST* list, unsigned int index, void* in)](https://github.com/rlasanggus/Data-structure/tree/master/llist#bool-add_node_atllist-list-unsigned-int-index-void-in)  
> [bool del_node_at(LLIST* list, unsigned int index)](https://github.com/rlasanggus/Data-structure/tree/master/llist#bool-del_node_atllist-list-unsigned-int-index)  
> [void* get_data_at(LLIST* list, unsigned int index)](https://github.com/rlasanggus/Data-structure/tree/master/llist#void-get_data_atllist-list-unsigned-int-index)  
> [bool change_data_at(LLIST* list, unsigned int index, void* new_data)](https://github.com/rlasanggus/Data-structure/tree/master/llist#bool-change_data_atllist-list-unsigned-int-index-void-new_data)  
> [int find_data(LLIST* list, void* search_data)](https://github.com/rlasanggus/Data-structure/tree/master/llist#int-find_datallist-list-void-search_data)  
```c
#include "ADT_llist.h"
#include <stdlib.h>
```  
ADT_llist.c.에서 참조할 ADT_llist.h.를 불러옴  

#### <code>LLIST* create_list(int(*c_func)(void*x, void*y), void(*p_func)(void* x))</code>  
```c
LLIST* create_list(int(*c_func)(void*x, void*y), void(*p_func)(void* x)){
	LLIST* list = (LLIST*)malloc(sizeof(LLIST));
	if(list){
		list -> front = NULL;
		list -> rear = NULL;
		list -> pos = NULL;
		list -> count = 0;
		list -> cmp_func = c_func;
		list -> print_func = p_func;
		return list;
	}
	return NULL;
  ```  
LLIST형의 메모리를 할당받고, 메모리가 할당된다면 list의 front, rear, pos count 값을 초기화하고, 생성된 리스트에 사용될 cmp_func, print_func 함수포인터값 정의.  

#### <code>bool add_node_at(LLIST* list, unsigned int index, void* in)</code>  
```c
bool add_node_at(LLIST* list, unsigned int index, void* in){
	if((list -> count)<index)
		return false;
	NODE* new_node = (NODE*)malloc(sizeof(NODE));
	if(!new_node) return false;

	new_node -> data_ptr = in;
	new_node -> next = NULL;
```  
리스트에 노드를 추가할 add_node_at 함수의 몸체를 구성  
입력받은 인덱스 값이 리스트의 노드 개수보다 많을 순 없으므로 많다면 false를 리턴(인덱스값은 0~count)  
새로운 노드의 메모리를 할당받고 메모리가 할당되지않으면 false를 리턴  
메모리가 할당된다면 노드의 data_ptr과 next 초기화  
```c
if((list -> count)==0){
		list -> front = new_node;
		list -> rear = new_node;
		(list -> count)++;
		return true;
	}
```  
리스트의 카운터가 0이면 노드추가시 노드가 한 개이므로 front와 rear가 같은 노드를 가리킴으로 같은 노드를 가리키게 한 후 카운터 증가  
```c
	int iter_i = 0;
	if(index == 0){
		new_node -> next = list -> front;
		list -> front = new_node;
		(list -> count)++;
		return true;
	}
```  
인덱스가 0을 가리킨다면 리스트의 맨 앞의 노드값을 가리키는 front값이 변하게 된다. 따라서 노드의 next값에는 front값이 들어가고, front값은 새로운 노드를 가리키게 된다.  
```c
	iter_i ++;
	list -> pos = list -> front;
	while(iter_i != index){
		list->pos = list->pos->next;
		iter_i ++;
	}
	if(iter_i == list -> count){
		list->pos->next = new_node;
		list -> rear = new_node;
		(list -> count)++;
		return true;
	}else{
		new_node -> next = list -> pos -> next;
		list -> pos -> next = new_node;
		(list->count)++;
		return true;
	}
	return false;
```  
pos을 현재 front위치에 위치시킨 후 한칸씩 뒤로 이동시키며 인덱스값의 이전 노드로 이동  
이동한 값이 맨 마지막을 가리킨다면 rear값이 변하게 되므로 그에대한 예외경우를 고려  
아닐경우는 new_node의 next에 현재 pos의 next값 입력 후 pos의 next값에는 new_node의 주소값 입력(pos이 가리키는 노드는 인덱스 바로앞에 위치)  
모든 경우를 고려했지만 끝까지 온다면 위의 코드에서 오류가 발생한 것이므로 false를 리턴  


#### <code>bool del_node_at(LLIST* list, unsigned int index)</code>  
```c
bool del_node_at(LLIST* list, unsigned int index){
	if(list->count == 0) return false;
	else if(index>=list->count) return false;
```  
count 값이 0이라면, 데이터가 없는 list임으로 지울 수 있는 데이터가 없음 false 반환  
```c
if(list -> count == 1){
		free(list->front);
		list -> front = NULL;
		list -> rear = NULL;
		list -> count = 0;
		return true;
	}
```  
count 값이 1이라면 하나의 데이터가 있음으로 그 데이터가 사라지면 모든 값은 초기화시켜야함  
```c
int iter_i = 0;
	list -> pos = list -> front;
	NODE* pre = NULL;
	while(iter_i != index){
		pre = list -> pos;
		list -> pos = list -> pos -> next;
		iter_i++;
	}
```  
지우고자 하는 인덱스 값으로 이동  
```c
	if(index==0){
		list -> front = list -> pos -> next;
		free(list->pos);
		(list -> count)--;
		list -> pos = NULL;
		return true;
	}
```  
index = 0 라면, 현재 front에위치하는 데이터. 따라서 이 데이터가 사라진다면, 현재 index=1의 자리가 fornt가 됨으로 fornt값 최신화  
지구고자 하는 데이터 메모리 반환, count 감소, pos 초기화 true반환 후 함수종료  
```c
	if(index==(list->count - 1)){
		list -> rear = pre;
		pre -> next = NULL;
		free(list -> pos);
		list -> pos = NULL;
		(list -> count)--;
		return true;
```  
index = count - 1 값이라면, 현재 list의 rear에 위치하는 데이터 임으로, rear값을 최신화 후 제거
```c
	}else{
		pre -> next = list->pos->next;
		free(list->pos);
		list -> pos = NULL;
		(list->count)--;
		return true;
	}
```  
index=0, index=count-1이 아니라면  
지우고자 하는 데이터의 앞의 위치의 노드의 next값은 지우고자 하는 데이터의 next값이 되어야 함으로 next값을 최신화  
이후 메모리 반환후 count감소, true값 반환  
```c

	return false;
}
```  
위의 모든 case가 아니라면, 또다른 case는 없으므로 여기까지왔다면 오류가 발생. return false  
#### <code>void* get_data_at(LLIST* list, unsigned int index)</code>  
```c
void* get_data_at(LLIST* list, unsigned int index){
	if(index >= (list -> count))
		return NULL;

	list -> pos = list -> front;
	int iter_i = 0;
	while(list -> pos != NULL){
		if(iter_i == index)
			return list -> pos -> data_ptr;

		list -> pos = list -> pos -> next;
		iter_i ++;
	}
	return NULL;
}
```  
인덱스값이 리스트의 카운터보다 크거나 같으면 NULL리턴(get함수에서의 인덱스는 count보다 작아야한다 0~count-1)  
pos값을 front로 초기화  
pos을 한칸식 이동시키며 index의 위치에 도착하면 pos의 data_ptr을 리턴  
이 코드까지 도착한다면 위의 코드에서 데이터를 반환하지 못했으므로 NULL리턴  

#### <code>bool change_data_at(LLIST* list, unsigned int index, void* new_data)</code>  
```c
bool change_data_at(LLIST* list, unsigned int index, void* new_data){

	if(list -> count == 0)
		return false;
	if(list->count < (index-1))
		return false;

	int iter_i = 0;
	list->pos = list->front;

	while(iter_i != index){
		list -> pos = list -> pos -> next;
		iter_i ++;
	}

	list -> pos -> data_ptr = new_data;

	list -> pos = NULL;

	return true;
}
```  
count값이 0이면 바꿀 데이터가 없으므로 false, index개수는 0~count-1이므로 이 이상이면 false  
pos을 front로 초기화 한 후, 한칸씩 뒤로 이동시키며 index위치로 이동, 이동 후 pos의 데이터주소값을 새로운 데이터주소로 변환  

#### <code>int find_data(LLIST* list, void* search_data)</code>  





