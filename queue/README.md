# Queue  
![image](https://user-images.githubusercontent.com/43701183/48624026-c61bd080-e9ee-11e8-96cb-6e2186c41d81.png)  
![image](https://user-images.githubusercontent.com/43701183/48624053-d338bf80-e9ee-11e8-9ddd-5a818672e2c1.png)  


## <pre>ADT_queue.h</pre>  
```c
typedef struct node{
	void* data_ptr;
	struct node* next;
}QUEUE_NODE;
```  
queue에서 데이터의 메모리주소를 저장할 data_ptr, 다음 노드 주소값을 저장할 next 정의, 구조체 node를 QUEUE_NODE로 정의  
```c
typedef struct{
	int count;
	QUEUE_NODE* front;
	QUEUE_NODE* rear;
}QUEUE;
```  
queue를 쌓기위해 노드의 개수를 알려줄count, 현재 맨 앞의 노드 주소를 가리킬 front, 맨 뒤의 주소를 가리킬 rear 정의  
```c
QUEUE* create_queue();
bool enqueue(QUEUE* queue, void* in);
void* dequeue(QUEUE* queue);
void* queue_hook_front(QUEUE* queue);
void* queue_hook_rear(QUEUE* queue);
void destroy_queue(QUEUE* queue);
```  
queue를 생성할 때 사용할 create_queue  
queue에 데이터를 넣을 enqueue  
queue에서 데이터를 꺼낼 dequeue  
queue의 front의 데이터를 읽어오는 queue_hook_front  
queue의 rear의 데이터를 읽어오는 queue_hook_rear  
queue를 삭제하는 destroy_queue  



## <pre>ADT_queue.c</pre>  
> [QUEUE* create_queue()](https://github.com/rlasanggus/Data-structure/tree/master/queue#queue-create_queue)  
> [bool enqueue(QUEUE* queue, void* in)](https://github.com/rlasanggus/Data-structure/tree/master/queue#bool-enqueuequeue-queue-void-in)  
> [void* dequeue(QUEUE* queue)](https://github.com/rlasanggus/Data-structure/tree/master/queue#void-dequeuequeue-queue)  
> [void* queue_hook_front(QUEUE* queue)](https://github.com/rlasanggus/Data-structure/tree/master/queue#void-queue_hook_frontqueue-queue)  
> [void* queue_hook_rear(QUEUE* queue)](https://github.com/rlasanggus/Data-structure/tree/master/queue#void-queue_hook_rearqueue-queue)  
> [void destroy_queue(QUEUE* queue)](https://github.com/rlasanggus/Data-structure/tree/master/queue#void-destroy_queuequeue-queue)  
#### <code>QUEUE* create_queue()</code>  
```c
QUEUE* create_queue(){
	QUEUE* queue;
	queue = (QUEUE*)malloc(sizeof(QUEUE));
	if(queue){
		queue -> front = NULL;
		queue -> rear = NULL;
		queue -> count = 0;
		return queue;
	}
	else
		return NULL;
}
```  
QUEUE형의 메모리를 할당받고, 메모리가 할당되면, front, rear, count값을 초기화.  
생성된 queue를 return  
queue에 메모리가 할당되지 않았으면 오류. NULL값 return  

#### <code>bool enqueue(QUEUE* queue, void* in)()</code>  
```c
bool enqueue(QUEUE* queue, void* in){
	QUEUE_NODE* new_node;
	new_node = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE));
	if(new_node==NULL)
		return false;
		
	new_node -> data_ptr = in;
	new_node -> next = NULL;
```  
QUEUE_NODE형의 메모리를 할당받음  
메모리 할당받지 못했으면 오류. false값 return  
메모리를 할당받았다면 data_ptr엔 전달받은 데이터값을 입력  
queue는 방향성을 가지고 있음으로 next는 항상 NULL  
```c
if(queue -> count == 0){
		queue -> front = new_node;
	}
	else{
		queue -> rear -> next = new_node;
	}
	(queue -> count)++;
	queue -> rear = new_node;

	return true;
}
```  
count == 0라면, 첫번째 node임으로 front node가 됨  
아니라면, 현재 queue의 rear가 새로운 노드로 대체  
count값을 1 증가  
#### <code>void* dequeue(QUEUE* queue)</code>  
```c
void* dequeue(QUEUE* queue){
	if(queue -> count == 0)
		return NULL;
```  
count 값이 0이라면, 꺼낼수 있는 node가 없으므로 NULL값 반환  
```c
QUEUE_NODE* deleted_node;
deleted_node = queue -> front;
void* item_ptr = queue -> front -> data_ptr;
```  
deleted_node를 정의하고, deleted_node를 queue의 front node값으로.(queue는 방향성)  
반환해줄 front의 데이터값은 itemp_ptr에 저장  
```c
	if(queue -> count ==1){
		queue -> front = NULL;
		queue -> rear = NULL;
	}else{
		queue -> front = queue -> front -> next;
	}
```  
count == 1 이라면, deque이후엔 queue에 들어있는 node가 없으므로 초기화  
아니라면 front의 다음 노드가 front 노드로 업데이트  
```c
	(queue -> count)--;
	free(deleted_node);
	return item_ptr;
}
```  
count를 1만큼 감소시카고, 메모리 반환, front의 데이터 item_ptr 반환  

#### <code>void* queue_hook_front(QUEUE* queue)</code>  
```c
void* queue_hook_front(QUEUE* queue){
	if(queue -> count == 0)
		return NULL;
	else{
		return queue-> front -> data_ptr;
	}
}
```  
count == 0 라면, queue에 들어있는 node 없음 NULL  
아니라면, 현재 front의 데이터 읽어옴(deque와는 다르게 front노드 제거 안함)  
#### <code>void* queue_hook_rear(QUEUE* queue)</code>  
```c
void* queue_hook_rear(QUEUE* queue){
	if(queue -> count == 0)
		return NULL;
	else{
		return queue -> rear -> data_ptr;
	}
}
```  
count == 0 라면, queue에 들어있는 node 없음 NULL  
아니라면, 현재 rear의 데이터 읽어옴  
#### <code>void destroy_queue(QUEUE* queue)</code>  
```c
void destroy_queue(QUEUE* queue){
	if(queue != NULL){
		while(queue -> count != 0){
			free(queue -> front -> data_ptr);
			dequeue(queue);
		}
	}

}
```  
queue안에있는 모든 node에 할당된 메모리 반환후 queue의 메모리 반환  
node메모리 반환 하지 않고 queue를 제거하면 queue의 틀만 제거될 뿐 내부의 node 메모리는 제거가 안됨으로 메모리 낭비가됨   
