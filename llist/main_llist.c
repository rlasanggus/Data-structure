#include "ADT_llist.h"
#include "ADT_tree.h"
#include <stdlib.h>
#include <stdio.h>

#define sample_NUM 10000000

int comparel(void* x, void* y){
	return *((int*)x) - *((int*)y);
}

void printl(void* x){
	int * xp = (int*)x;
	printf(" - int data %d\n", *xp);
}

int main(){
	FILE* fin = fopen("sample.txt", "r");
	int* N = (int*)malloc(sizeof(int)*sample_NUM);
	int* M = (int*)malloc(sizeof(int)*sample_NUM);

	int i, iter, cmp_result;
	int search_num = sample_NUM - 1;
	T_NODE* search;

	LLIST* new_llist = create_list(comparel, printl);
	BST_TREE* new_bst = create_bst_tree();

	for(i=0; i<sample_NUM; i++){
		*M = sample_NUM - i;
		fscanf(fin, "%d", N);
		add_node_at(new_llist, 0, M);
		BST_insert(new_bst, *N);
		N++;
		M++;
	}

	iter = find_data(new_llist, &search_num);
	printf("iter num = %d\n", iter);

	fclose(fin);
	return 0;


}