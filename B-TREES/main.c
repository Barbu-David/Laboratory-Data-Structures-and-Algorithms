#include<stdio.h>
#include"b.h"

void* compare_for_ints(void* a, void* b)
{
        return *(int*)a >= *(int*)b? a:b;
}

bool check_equality_for_ints(void* a, void* b)
{
        return *(int*)a == *(int*)b;
}

void b_print(struct b_node* root)
{	
	int index;
	for(index=0; index<=(root->numb_v)-1; index++)
		printf("%d ", *((int*)(root->values[index])));
	if(!root->leaf)
		for(index=0; index<=(root->numb_v); index++) {
			printf(" | ");
			b_print(root->children[index]);
	} 
	else printf("leaf");
}


int main(void)
{	
	int a =17;
	struct b_node* root=b_init(&a, sizeof(int));
	b_print(root);
	printf("\n");

	a=5;
	b_push(&root, &a, sizeof(int),  compare_for_ints);
	b_print(root);
	printf("\n");

	a=21;
	b_push(&root, &a, sizeof(int),  compare_for_ints);
	b_print(root);
	printf("\n");

	a=10;
	b_push(&root, &a, sizeof(int),  compare_for_ints);
	b_print(root);
	printf("\n");

	a=32;
	b_push(&root, &a, sizeof(int),  compare_for_ints);
	b_print(root);
	printf("\n");

	a=79;
	b_push(&root, &a, sizeof(int),  compare_for_ints);
	b_print(root);
	printf("\n");

	a=8;
	b_push(&root, &a, sizeof(int),  compare_for_ints);
	b_print(root);
	printf("\n");

	a=16;
	b_push(&root, &a, sizeof(int),  compare_for_ints);
	b_print(root);
	printf("\n");

	a=7;
	b_push(&root, &a, sizeof(int),  compare_for_ints);
	b_print(root);
	printf("\n");

	a=6;
	b_push(&root, &a, sizeof(int),  compare_for_ints);
	b_print(root);
	printf("\n");

	a=11;
	b_push(&root, &a, sizeof(int),  compare_for_ints);
	b_print(root);
	printf("\n");

	a=14;
	b_push(&root, &a, sizeof(int),  compare_for_ints);
	b_print(root);
	printf("\n");

	a=1;
	b_push(&root, &a, sizeof(int),  compare_for_ints);
	b_print(root);
	printf("\n");

	a=2;
	b_push(&root, &a, sizeof(int),  compare_for_ints);
	b_print(root);
	printf("\n");

	a=33;
	b_push(&root, &a, sizeof(int),  compare_for_ints);
	b_print(root);
	printf("\n");

	a=34;
	b_push(&root, &a, sizeof(int),  compare_for_ints);
	b_print(root);
	printf("\n");

	a=32;
	struct b_node_value n=b_search(root, &a, check_equality_for_ints, compare_for_ints);
	
	if(n.node==NULL) printf("32 not found \n");
	else printf("32 found\n");

	a=33;
	n=b_search(root, &a, check_equality_for_ints, compare_for_ints);
	
	if(n.node==NULL) printf("33 not found \n");
	else printf("33 found\n");

	a=11;
	n=b_search(root, &a, check_equality_for_ints, compare_for_ints);
	
	if(n.node==NULL) printf("11 not found \n");
	else printf("11 found\n");

	a=6;
	n=b_search(root, &a, check_equality_for_ints, compare_for_ints);
	
	if(n.node==NULL) printf("6 not found \n");
	else printf("6 found\n");

	a=5;
	n=b_search(root, &a, check_equality_for_ints, compare_for_ints);
	
	if(n.node==NULL) printf("5 not found \n");
	else printf("5 found\n");


	a=4;
	n=b_search(root, &a, check_equality_for_ints, compare_for_ints);
	
	if(n.node==NULL) printf("4 not found \n");
	else printf("4 found\n");




	return 0;
}
