#include<stdio.h>
#include"bst.h"

void* compare_for_ints(void* a, void* b)
{
	return *(int*)a >= *(int*)b? a:b;
}

bool check_equality(void* a, void* b)
{
	return *(int*)a == *(int*)b? true:false;
}


void print_for_ints(void* a)
{
	printf("%d ", *(int*)a);
}

int main(void)
{	
	int a=10;

	struct bst_node* bst = bst_init(&a, sizeof(int));
	bst_inorder_print(bst, print_for_ints);
	printf("\n");	

	a=2;
	bst_push(bst, &a, sizeof(int), compare_for_ints);


	a=25;
	bst_push(bst, &a, sizeof(int), compare_for_ints);
	
	a=14;
	bst_push(bst, &a, sizeof(int), compare_for_ints);

	a=55;
	bst_push(bst, &a, sizeof(int), compare_for_ints);

	a=1;
	bst_push(bst, &a, sizeof(int), compare_for_ints);

	a=11;
	bst_push(bst, &a, sizeof(int), compare_for_ints);

	a=2;
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

	int b=10;
	bst_pop(&bst, &b, check_equality, compare_for_ints);
	printf("\n size %d\n",bst_size(bst));
	bst_inorder_print(bst, print_for_ints);
	
	b=2;
	bst_pop(&bst,&b, check_equality, compare_for_ints);
	printf("\n size %d\n",bst_size(bst));
	bst_inorder_print(bst, print_for_ints);

	b=25;
	bst_pop(&bst, &b, check_equality, compare_for_ints);
	printf("\n size %d\n",bst_size(bst));
	bst_inorder_print(bst, print_for_ints);

	bst_free(&bst);

	return 0;
}
