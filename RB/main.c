#include<stdio.h>
#include"rb.h"

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
	struct rb_node* rb = rb_init(&a, sizeof(int));
	
	a=8;
	rb_push(&rb, &a, sizeof(int), check_equality_for_ints, compare_for_ints);

	rb_preorder_print(rb, print_for_ints);
	printf("\n");

	a=5;
	rb_push(&rb, &a, sizeof(int), check_equality_for_ints, compare_for_ints);

	rb_preorder_print(rb, print_for_ints);

	rb_free(&rb);
	
	return 0;
}
