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
/*	
	int a=24;

	struct bst_node* bst = bst_init(&a, sizeof(int));
	bst_inorder_print(bst, print_for_ints);
	printf("\n");	

	a=23;
	bst_push(bst, &a, sizeof(int), compare_for_ints);


	a=25;
	bst_push(bst, &a, sizeof(int), compare_for_ints);

	a=27;
	bst_push(bst, &a, sizeof(int), compare_for_ints);

	bst_inorder_print(bst, print_for_ints);
	printf("\n");
	bst_preorder_print(bst, print_for_ints);
	printf("\n");
	bst_postorder_print(bst, print_for_ints);

	printf("\n size %d",bst_size(bst));
	printf("\n levels %d",bst_levels(bst));
	printf("\n min %d",*(int*)bst_min(bst));
	printf("\n max %d",*(int*)bst_max(bst));

	int b=27;
	bst_pop(&bst, &b, check_equality_for_ints, compare_for_ints);
	printf("\n size %d\n",bst_size(bst));
	bst_inorder_print(bst, print_for_ints);

	struct person pers, persA;

	pers.age=24;
	pers.initial='A';
	persA=pers;

	struct bst_node* bst2 = bst_init(&pers, sizeof(struct person));

	pers.age=23;
	pers.initial='B';
	bst_push(bst2, &pers, sizeof(struct person), compare_for_pers);

	pers.age=25;
	pers.initial='C';
	bst_push(bst2, &pers, sizeof(struct person), compare_for_pers);

	pers.age=27;
	pers.initial='D';
	bst_push(bst2, &pers, sizeof(struct person), compare_for_pers);

	bst_inorder_print(bst2, print_for_pers);	
	bst_pop(&bst2, &persA, check_equality_for_pers, compare_for_pers);

	printf("\n");
	bst_inorder_print(bst2, print_for_pers);	

	bst_free(&bst);
	bst_free(&bst2);
*/
	return 0;
}
