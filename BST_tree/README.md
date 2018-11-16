# BST_Tree(Binary Search Tree)  

![image](https://user-images.githubusercontent.com/43701183/48622083-fd877e80-e9e8-11e8-947a-286c56b3e293.png)  
![image](https://user-images.githubusercontent.com/43701183/48622232-75ee3f80-e9e9-11e8-9da2-6e33c34450ec.png)
![image](https://user-images.githubusercontent.com/43701183/48622253-830b2e80-e9e9-11e8-9dbb-ade3279f918d.png)  


## <pre>ADT_tree.h</pre>  
```c
typedef struct node{
	int data;
	struct node* left;
	struct node* right;
}T_NODE;
```  
tree 에서 사용할 node를 정의 node 안에는 int형의 데이터를 저장할 data와 tree에서 자식을 가리킬 left와 right를 정의 이 구조체를 T_NODE로 재정의  
```c
typedef struct{
	int count;
	T_NODE* root;
}BST_TREE;
```  
tree에서 노드의 개수를 저장할 count와 노드를 가리킬 root 정의 이 구조체를 BST_TREE로 재정의  
```c
BST_TREE* create_bst_tree();
T_NODE* find_smallest_node(T_NODE* root);
T_NODE* find_largest_node(T_NODE* root);
T_NODE* search_bst(T_NODE* root, int key);
T_NODE* add_bst(T_NODE* root, int data);
T_NODE* delete_bst(T_NODE* root, int data, bool* success);

void traverse_inorder(T_NODE* root);
void traverse_postorder(T_NODE* root);
void traverse_preorder(T_NODE* root);

bool BST_insert(BST_TREE* tree, int data);
bool BST_delete(BST_TREE* tree, int data);
void BST_print(BST_TREE* tree, int method);
```  
위에서부터 차례대로 트리를 생성, 가장 작은 데이터를 가질 노드 검색, 가장 큰 데이터를 가진 노드 검색, 데이터를 찾는 함수, 노드를 추가하는 함수(BST_insert 안에서 사용), 노드를 삭제하는 함수  
traverse 함수 세개  
노드 추가, 삭제, 출력하는 함수  

## <pre>ADT_tree.c</pre>  
```c
#include "ADT_tree.h"
```  
ADT_tree.c 에서 참조할 ADT_tree.h 를 불러옴  

#### <code>BST_TREE* create_bst_tree()</code>  
```c
BST_TREE* create_bst_tree(){

	BST_TREE* tree = (BST_TREE*)malloc(sizeof(BST_TREE));

	tree -> count = 0;
	tree -> root = NULL;

	return tree;
}
```  
BST_TREE 만큼의 메모리를 할당 받은 수 BST_TREE* 형태로 형변환하여 tree에 저장, tree 의 count 와 root 를 초기화 한 수 반환  

#### <code>T_NODE* find_smallest_node(T_NODE* root)</code>  
```c
T_NODE* find_smallest_node(T_NODE* root){
	if(root -> left == NULL)
		return root;
	else
		return find_smallest_node(root -> left);
}
```  
root -> left 가 NULL 이라면, 가장 작은 데이터를 가지는 root에 도착했으므로 root 값을 반환하고, 아니라면 다시 find_smallest_node에 root -> left 을 넣어 실행 (재귀함수)  

#### <code>T_NODE* find_largest_node(T_NODE* root)</code>  
```c
T_NODE* find_largest_node(T_NODE* root){
	if(root -> right == NULL)
		return root;
	else
		return find_largest_node(root -> right);
}
```  
가장 큰 값을 가지는 node를 검색하려면 가장 오른쪽 밑의 node로 가면 되므로 root -> left 대신에 root -> right를 넣음  

#### <code>T_NODE* search_bst(T_NODE* root, int key)</code>  
```c
_NODE* search_bst(T_NODE* root, int key){
	if(root == NULL)
		return NULL;
	if(key < (root -> data)){
		return search_bst(root -> left, key);
	}
	else if(key > (root -> data)){
		return search_bst(root -> right, key);
	}
	else
		return root;
}
```  
root == NULL 이라면 비어있는 root가 비어 있으므로 검색할 데이터가 없다 따라서NULL을 반환, 만약 검색하고자 하는 데이터 값인 key값이 root -> data값 보다 작다면 현재 root 의 left 쪽 밑에 있으므로 재귀 함수로 root -> left 넣음, 마찬가지로 key값이 root -> data 보다 크다면 오른쪽에 위치함으로 root -> right를 넣어 재귀함수사용, 만약 두 경우가 모두 아니라면 현재 key 값과 현재 root의 data 값이 일치하므로 현재 root 값을 반환  

#### <code>T_NODE* add_bst(T_NODE* root, int data)</code>  
```c
T_NODE* add_bst(T_NODE* root, int data){
	if(root == NULL){
		T_NODE* new_node = (T_NODE*)malloc(sizeof(T_NODE));

		if(!new_node)
			return NULL;
		new_node -> left = NULL;
		new_node -> right = NULL;
		new_node -> data = data;

		return new_node;
	}

	if(data < (root -> data)){
		root -> left = add_bst(root -> left, data);

		return root;
	}
	else{
		root -> right = add_bst(root -> right, data);

		return root;
	}
}
```  
T_NODE의 크기만큼 동적할당 후 T_NODE*형으로 형변환 한 값을 new_node에 저장, 만약 메모리가 할당되지않으면 NULL을 반환, 할당이 됬다면 left와 right값을 초기화 하고, new_node의 data값에 추가하고자 하는 data값을 넣음  
data값과 root -> data 값을 비교하며 새로운 data가 들어갈 위치까지 내려간 후 저장(if, else 내부의 add_bst 재귀함수에서 tree의 맨 밑까지 내려갔다면 root -> right 와 left는 NULL이므로 new_node를 반환하게 되고, 그 값이 root의 left나 right 값으로 들어가게됨)  

#### <code>T_NODE* delete_bst(T_NODE* root, int data, bool* success)</code>  
```c
T_NODE* delete_bst(T_NODE* root, int data, bool* success){
	T_NODE* new_root;
	T_NODE* deleted_node;
	T_NODE* search;

	if(root == NULL){
		*success = false;
		return NULL;
	}

	if(data < (root -> data)){
		root -> left = delete_bst(root -> left, data, success);
	}else if(data > (root -> data)){
		root -> right = delete_bst(root -> right, data, success);
	}else{
		deleted_node = root;
		if(root -> left == NULL){
			new_root = root -> right;
			free(deleted_node);
			*success = true;
			return new_root;
		}else{
			if(root -> right == NULL){
				new_root = root -> left;
				free(deleted_node);
				*success = true;
				return new_root;
			}else{
				search = root -> left;
				while(search -> right != NULL)
					search = search -> right;

				root -> data = search -> data;
				root -> left = delete_bst(root -> left, search -> data, success);
			}
		}
	}
	return root;
}
```  
delete_bst 함수에서 사용할 변수들을 정의  
root == NULL 이라면 delete 할 노드가 없으므로 *success에는 false 를 넣고 NULL 반환  
data값과 root -> data값을 비교하며 지우고자 하는 data값이 있는 위치로 찾아가는 과정(T_NODE* search_bst(T_NODE* root, int key) 함수에서 설명), 그리고 left와 right를 재정의 하는 과정  
위의 경우가 모두 아니라면 data = root -> data 이므로 지우고자 하는 노드에 도착  
지우고자 하는 root 를 deleted_node 에 저장  
만약 지우고자 하는 root -> left == NULL 이라면, 현재 root 의 right 값만 부모 노드의 left나 right 값으로 정의 해주면 된다, 이때 left나 right가 결정되는 기준은 이 else 구문이 실행되기 바로 위의 재귀함수에서 data < root -> data 인 경우인지 data > root -> data인 경우인지에 의해 판단.  
마찬가지로 현재 root의 left값만 부모 노드의 left나 right 값으로 정의해주면 됨  
두가지 경우 실행 후 *success에 true 값을 넣고, free를 호출해 지움  
search 에 root -> left 로 하고, search를 초기 search의 하위 tree 에서 가장 큰 데이터 값을가지도록 위치를 옮김  
root -> data 값에 search -> data값을 입력하고 재귀함수 호출(root -> left값 넣어서)  
root 값 반환  

#### <code>void traverse_inorder(T_NODE* root)</code>  
```c
void traverse_inorder(T_NODE* root){
	if(root != NULL){
		traverse_inorder(root -> left);
		printf("%d", root -> data);
		traverse_inorder(root -> right);
	}
}
```  
preorder은 root => left => right순으로 출력이므로 먼저 root를 print한 후 left, right 순으로 이동하며 출력  
#### <code>void traverse_postorder(T_NODE* root)</code>  
```c
void traverse_postorder(T_NODE* root){
	if(root != NULL){
		traverse_postorder(root -> left);
		traverse_postorder(root -> right);
		printf("%d", root -> data);
	}
}
```  
postorder은 left => right => root 순으로 출력이므로 왼쪽 가장 밑의 left부터 시작하여 left, right, root 순으로 출력  

#### <code>void traverse_preorder(T_NODE* root)</code>  
```c
void traverse_preorder(T_NODE* root){
	if(root != NULL){
		printf("%d", root -> data);
		traverse_preorder(root -> left);
		traverse_preorder(root -> right);
	}
}
```  
inorder은 left => root => right 순으로 출력이므로 왼쪽 가장 밑의 left부터 시작하여 left, root, right를 돌며 출력  

#### <code>bool BST_insert(BST_TREE* tree, int data)</code>  
```c
bool BST_insert(BST_TREE* tree, int data){

	T_NODE* new_root;
	new_root = add_bst(tree->root, data);

	if(new_root == NULL)
		return false;
	else{
		tree -> root = new_root;
		(tree -> count)++;
		return true;
	}

}
```  
T_NODE* 형의 new_root 를 정의한 후 add_bst함수를 이용해 data를 삽입한 것을 저장  
new_root == NULL 이라면 삽입이 제데로 이루어지지 않았으므로 false를 반환, 아니라면 tree -> root에 new_root를 저장하고 데이터가 삽입되었으므로 count를 증가, true를 반환  

#### <code>bool BST_delete(BST_TREE* tree, int data);</code>  
```c
bool BST_delete(BST_TREE* tree, int data){
	bool success;
	T_NODE* new_root;
	new_root = delete_bst(tree -> root, data, &success);

	if(success){
		tree -> root = new_root;
		(tree -> count)--;
		if(tree -> count == 0)
			tree -> root = NULL;
	}
	return success;
}
```  
bool 형의 success를 정의, T_NODE*형의 new_root 정의 후 delete_bst함수의 반환값 저장(delte_bst함수에 success의 주소값을 넘겨줌으로써 T_NODE*가 반환형이 delete_bst함수 내부의 true false 값을 success의 주소로 접근함으로써 알수있음)  
success가 true 라면 tree -> root 에 new_root를 저장하고 노드를 하나 지웠으므로 count를줄인다   
만약 tree -> count == 0 이면 빈 tree 이므로 root 값을 NULL로 초기화  
success 값을 반환  

#### <code>void BST_print(BST_TREE* tree, int method);</code>  
```c
void BST_print(BST_TREE* tree, int method){
	printf("BST_TREE\n");
	printf("size : %d\n", tree -> count);
	printf("data : ");

	if(method == 0)
		traverse_preorder(tree -> root);
	else if(method == 1)
		traverse_inorder(tree -> root);
	else if(method == 2)
		traverse_postorder(tree -> root);
	else
		printf("type error");

	printf("\n");
}
```  
method값으로 0 1 2 를 입력받아 traverse 방법을 정한 후 트리의 크기와 data 값을 출력  
