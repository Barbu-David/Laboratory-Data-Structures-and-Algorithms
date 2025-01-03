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
}


int main(void)
{	
	int a =17;
	struct b_node* root=b_init(&a, sizeof(int));
	b_print(root);
	printf("\n");

	a=5;
	b_push(&root, &a, sizeof(int), check_equality_for_ints, compare_for_ints);
	b_print(root);
	printf("\n");

	a=21;
	b_push(&root, &a, sizeof(int), check_equality_for_ints, compare_for_ints);
	b_print(root);
	printf("\n");

	a=10;
	b_push(&root, &a, sizeof(int), check_equality_for_ints, compare_for_ints);
	b_print(root);
	printf("\n");

	a=32;
	b_push(&root, &a, sizeof(int), check_equality_for_ints, compare_for_ints);
	b_print(root);
	printf("\n");

	a=79;
	b_push(&root, &a, sizeof(int), check_equality_for_ints, compare_for_ints);
	b_print(root);
	printf("\n");

	a=8;
	b_push(&root, &a, sizeof(int), check_equality_for_ints, compare_for_ints);
	b_print(root);
	printf("\n");

	a=16;
	b_push(&root, &a, sizeof(int), check_equality_for_ints, compare_for_ints);
	b_print(root);
	printf("\n");

	a=7;
	b_push(&root, &a, sizeof(int), check_equality_for_ints, compare_for_ints);
	b_print(root);
	printf("\n");

	a=6;
	b_push(&root, &a, sizeof(int), check_equality_for_ints, compare_for_ints);
	b_print(root);
	printf("\n");


	a=20;
	b_push(&root, &a, sizeof(int), check_equality_for_ints, compare_for_ints);
	b_print(root);
	printf("\n");

	a=14;
	b_push(&root, &a, sizeof(int), check_equality_for_ints, compare_for_ints);
	b_print(root);
	printf("\n");


	return 0;
}
