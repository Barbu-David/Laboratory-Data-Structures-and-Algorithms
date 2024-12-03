#include<stdio.h>
#include"splay.h"


///broken, work in progress

void* compare_for_ints(void* a, void* b)
{
	return *(int*)a >= *(int*)b? a:b;
}

bool check_equality_for_ints(void* a, void* b)
{
	return *(int*)a == *(int*)b;
}

void print_for_ints(void* a)
{
	printf("%d ", *(int*)a);
}

int main(void)
{	
	int a=10;
	struct splay_node* sp =splay_init(&a, sizeof(int));
	splay_preorder_print(sp, print_for_ints);
	printf("\n");

	a=8;
	splay_push(&sp, &a, sizeof(int), check_equality_for_ints, compare_for_ints);
	splay_preorder_print(sp, print_for_ints);	
	printf("\n");

	a=9;
	splay_push(&sp, &a, sizeof(int), check_equality_for_ints, compare_for_ints);
	splay_preorder_print(sp, print_for_ints);	
	printf("\n");

	a=5;
	splay_push(&sp, &a, sizeof(int), check_equality_for_ints, compare_for_ints);
	splay_preorder_print(sp, print_for_ints);	
	printf("\n");

	a=7;
	splay_push(&sp, &a, sizeof(int), check_equality_for_ints, compare_for_ints);
	splay_preorder_print(sp, print_for_ints);	
	printf("\n");
	splay_inorder_print(sp, print_for_ints);	
	
	splay_free(&sp);

	return 0;
}
