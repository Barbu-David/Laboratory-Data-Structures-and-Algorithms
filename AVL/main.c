#include<stdio.h>
#include"avl.h"

struct person{
	char initial;
	int age;
};

void* compare_for_pers(void* a, void* b) 
{
	return ((*(struct person*)a).age >= (*(struct person*)b).age) ? a : b;
}

bool check_equality_for_pers(void* a, void* b) 
{
	return ((*(struct person*)a).age == (*(struct person*)b).age); 
}

void print_for_pers(void* a)
{
	printf("%c ", (*(struct person*)a).initial);
}


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
	int a=30;
	struct avl_node* avl = avl_init(&a, sizeof(int));
	
	a=20;
	avl_push(&avl, &a, sizeof(int), compare_for_ints);

	a=10;
	avl_push(&avl, &a, sizeof(int), compare_for_ints);

	avl_preorder_print(avl, print_for_ints);
	printf("\n");

	a=40;
	avl_push(&avl, &a, sizeof(int), compare_for_ints);

	a=50;
	avl_push(&avl, &a, sizeof(int), compare_for_ints);

	avl_preorder_print(avl, print_for_ints);
	printf("\n");

	a=25;
	avl_push(&avl, &a, sizeof(int), compare_for_ints);

	avl_preorder_print(avl, print_for_ints);
	printf("\n");

	a=35;
	avl_push(&avl, &a, sizeof(int), compare_for_ints);

	avl_preorder_print(avl, print_for_ints);
	printf("\n");

	avl_pop(&avl, &a, check_equality_for_ints, compare_for_ints);
	
	avl_preorder_print(avl, print_for_ints);
	printf("\n");

	avl_free(&avl);

	return 0;
}
