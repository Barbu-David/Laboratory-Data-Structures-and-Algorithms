#include<stdio.h>
#include"bst.h"

int main(void)
{
	struct bst_node* bst = bst_init(10);
	bst_push(bst, 2);
	bst_push(bst, 25);
	bst_push(bst, 14);
	bst_push(bst, 55);
	bst_push(bst, 1);
	bst_push(bst, 11);
	bst_push(bst, 2);

	bst_inorder_print(bst);
	printf("\n");
	bst_preorder_print(bst);
	printf("\n");
	bst_postorder_print(bst);

	printf("\n size %d",bst_size(bst));
	printf("\n levels %d",bst_levels(bst));
	printf("\n min %d",bst_min(bst));
	printf("\n max %d",bst_max(bst));

	bst_pop(&bst,10);

	printf("\n size %d\n",bst_size(bst));

	bst_inorder_print(bst);

	bst_pop(&bst,2);
	printf("\n size %d\n",bst_size(bst));
	bst_inorder_print(bst);

	bst_pop(&bst,25);
	printf("\n size %d\n",bst_size(bst));
	bst_inorder_print(bst);

	bst_free(&bst);

	return 0;
}
