# Stack_ADT(Absract Data Type)  

![image](https://user-images.githubusercontent.com/43701183/48619684-a2518e00-e9e0-11e8-9bfd-0d7cd056020e.png)  
![image](https://user-images.githubusercontent.com/43701183/48620019-d8434200-e9e1-11e8-9b89-d1387fa7dcce.png)  



## <pre>ADT_stack.h</pre>  
```c
typedef struct node{
	void* data_ptr;
	struct node* link;

} STACK_NODE;
```  
stack 에서 데이터를 가리키는 포인터값을 저장할 data_ptr, 다음 노드의 주소 값을 가리킬 링크 값을 저장할 link 를 정의, 구조체 node 를 STACK_NODE로 정의(데이터에 어떤 변수가 올 지 모름으로 void* 형으로 정의)  
```c
typedef struct {

	int count;
	STACK_NODE* top;

} STACK;
```  
stack을 쌓기 위해 노드의 개수를 알려줄 count, 현재 맨 위 노드의 주소 값을 가리킬 top을 가지는 구조체를 STACK으로 정의  
```c
STACK* create_stack();
bool push(STACK* stack, void* in);
void* pop(STACK* stack);
```  
stack을 생성할 때 사용할 create_stack(), 스택을 쌓을 때 사용할 push, 데이터를 꺼내고 stack을 지우가 위한 pop 을 정의 => ADT_stack.c 파일에서 함수를 정의  

## <pre>ADT_stack.c</pre>  
> [STACK* create_stack()](https://github.com/rlasanggus/Data-structure/tree/master/stack#stack-create_stack)
> [bool push(STACK* stack, void* in)](https://github.com/rlasanggus/Data-structure/tree/master/stack#bool-pushstack-stack-void-in)
> [void* pop(STACK* stack)](https://github.com/rlasanggus/Data-structure/tree/master/stack#void-popstack-stack)

#### <code>STACK* create_stack()</code>  
```c
STACK*
create_stack() {

	STACK* stack = (STACK*)malloc(sizeof(STACK));
	if(!stack)
		return NULL;

	stack->count = 0;
	stack->top = NULL;

	return stack;
}
```  
stack을 쌓기 위해 STACK크기만큼의 메모리를 할당  
메모리를 할당 받지 못하며 NULL을 리턴하고 종료  
메모리를 할당 받으면 count값과 top 값을 초기화 하고 STACK의 주소값인 stack 을 반환  
#### <code>bool push(STACK* stack, void* in)</code>  
```c
bool
push(STACK* stack, void* in){

	STACK_NODE* node = (STACK_NODE*)malloc(sizeof(STACK_NODE));
	if(node == NULL)
		return false;

	node->data_ptr = in;
	node->link = stack->top; // new node's next in previous top
	stack->top = node;
	(stack->count)++;

	return true;
  ```  
STACK_NODE 만큼의 메모리를 할당  
메모리를 받지 못하면 false를 반환  
node의 data_ptr에 입력받은 데이터의 주소값을 저장  
node 의 link에 현재 맨 위에있는 노드의 top값을 저장  
현재 맨 위에 쌓여있는 노드의 주소값을 쌓을 stack의 link 값에다 저장  
stack의 개수를 한 개 늘림  
true 값을 반환  
#### <code>void* pop(STACK* stack)</code>  
```c
void* pop(STACK* stack){
	if(stack -> count=0)
		return NULL;
	else{
		STACK_NODE* temp = stack -> top;
		void* data_out = stack->top->data_ptr;
		stack->top = stack->top->link;
		free(temp);
		(stack->count)--;
		return data_out;
	}
}
```  
현재 stack의 개수가 0개면 NULL값을 반환(더 이상 꺼낼 데이터가 없기 때문에)  
temp에 현재 top 값(맨위 노드가 가리키는 바로 밑 노드의 주소값)을 저장  
data_out 값에 현재 stack에 저장되어있는 데이터의 주소값을 저장  
현재의 top에 밑의 stack의 link 값을 저장  
맨 위 stack 의 주소값을 반환(stack 이 사라짐)  
맨 위 satck 한 개가 사라졌으므로 stack의 개수를 한개 줄임  
맨 위 stack에 저장되어 있던 데이터의 주소값을 반환  



