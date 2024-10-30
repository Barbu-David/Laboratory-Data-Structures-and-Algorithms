#include"avl.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<stdbool.h>
	
struct avl_node* avl_init(void* value, size_t size)
{	
	assert(value!=NULL);

	struct avl_node* node=malloc(sizeof(struct avl_node));
	assert(node!=NULL);	

	void* new_value=malloc(size);
	assert(new_value!=NULL);

	memcpy(new_value, value, size);

	node->value=new_value;
	node->left=NULL;
	node->right=NULL;

	return node;
}

void avl_push(struct avl_node* root, void* value, size_t size, void* (*compare)(void*, void*))
{	
	if(root==NULL) { 
		fprintf(stderr,"Pushed to uninitialized tree\n");
		return;	
	}

	assert(value!=NULL);
	
	//to do
}

void avl_inorder_print(struct avl_node* root, void (*print)(void*))
{
	if(root==NULL)	return;

	avl_inorder_print(root->left, print);
	print(root->value);
	avl_inorder_print(root->right, print);

}

void avl_preorder_print(struct avl_node* root, void (*print)(void*))
{
	if(root==NULL)	return;

	print(root->value);
	avl_preorder_print(root->left, print);
	avl_preorder_print(root->right, print);

}

void avl_postorder_print(struct avl_node* root, void (*print)(void*))
{
	if(root==NULL)	return;

	avl_postorder_print(root->left, print);
	avl_postorder_print(root->right, print);
	print(root->value);
}

int avl_size(struct avl_node* root)
{	
	if(root==NULL) return 0;
	return 1+avl_size(root->right)+avl_size(root->left);
}

int avl_levels(struct avl_node* root)
{
	if(root==NULL) return 0;

	int levels_left=1+avl_levels(root->left), levels_right=1+avl_levels(root->right);

	return (levels_right>levels_left)? levels_right:levels_left;

}

void* avl_min(struct avl_node* root)
{	
	if(root==NULL){
		fprintf(stderr, "Min requested for empty tree\n");
		return NULL;
	}

	while(root->left!=NULL) root=root->left;
	return root->value;
}

void* avl_max(struct avl_node* root)
{
	if(root==NULL){
		fprintf(stderr, "Max requested for empty tree\n");
		return NULL;
	}

	while(root->right!=NULL) root=root->right;
	return root->value;
}


struct avl_node* avl_search_parent(struct avl_node* root, void* value, bool (*check_equality)(void* a, void* b), void* (*compare)(void*, void*))
{
	assert(value!=NULL);

	while(root!=NULL) {
		if(root->left!=NULL)
			if(check_equality(value, root->left->value)) return root;

		if(root->right!=NULL)
			if(check_equality(value, root->right->value)) return root;

		if(compare(value, root->value)==value) root=root->left;
		else root=root->right;
	}

	return root;
}

struct avl_node* avl_search_child_with_value(struct avl_node* root, void* value, bool (*check_equality)(void*, void*))
{
	assert(value!=NULL);

	if(root==NULL) return root;

	if(root->right!=NULL)
		if(check_equality(value,root->right->value)) return root->right;

	return root->left;
}

struct avl_node* avl_successor_parent(struct avl_node* root)
{
	if(root==NULL) return root;
	if(root->right==NULL) return root;
	if(root->right->left==NULL) return root;

	root = root->right;

	while (root->left->left != NULL) root = root->left;

	return root;

}

struct avl_node* avl_predecessor_parent(struct avl_node* root)
{
	if(root==NULL) return root;
	if(root->left==NULL) return root;
	if(root->left->right==NULL) return root;

	root = root->left;

	while (root->right->right != NULL) root = root->right;

	return root;
}

struct avl_node* avl_search(struct avl_node* root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*))
{
	assert(value!=NULL);

	if(check_equality(root, root->value)) return root;
	return avl_search_child_with_value(avl_search_parent(root,value,check_equality,compare), value, check_equality);
}


struct avl_node* avl_successor(struct avl_node* root)
{
	root=avl_successor_parent(root);
	if(root->left==NULL) return root;
	return root->left;
}

struct avl_node* avl_predecessor(struct avl_node* root)
{
	root=avl_predecessor_parent(root);
	if(root->right==NULL) return root;
	return root->right;
}

void avl_pop(struct avl_node** root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*))  {

        assert(value!=NULL);

	struct avl_node* target = *root;

	struct avl_node* parent = avl_search_parent(target, value, check_equality, compare);

		
	if(parent!=NULL) target = avl_search_child_with_value(target, value, check_equality);	

	if (target == NULL) return; 
	
	//to do
}

void avl_free(struct avl_node** root)
{
	if((*root)==NULL) return;
	avl_free(&(*root)->left);
	avl_free(&(*root)->right);
	free((*root)->value);
	free((*root));
	(*root)=NULL;
}
