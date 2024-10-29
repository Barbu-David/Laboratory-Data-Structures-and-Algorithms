#include"bst.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<stdbool.h>
	
struct bst_node* bst_init(void* value, size_t size)
{	
	assert(value!=NULL);

	struct bst_node* node=malloc(sizeof(struct bst_node));
	assert(node!=NULL);	

	void* new_value=malloc(size);
	assert(new_value!=NULL);

	memcpy(new_value, value, size);

	node->value=new_value;
	node->left=NULL;
	node->right=NULL;

	return node;
}

void bst_push(struct bst_node* root, void* value, size_t size, void* (*compare)(void*, void*))
{	
	if(root==NULL) { 
		fprintf(stderr,"Pushed to uninitialized tree\n");
		return;	
	}

	assert(value!=NULL);

	if(compare(value,root->value)==root->value){
		if(root->left!=NULL)
			bst_push(root->left, value, size, compare);
		else root->left=bst_init(value, size);	
	}
	else if(root->right!=NULL) bst_push(root->right, value, size, compare);
	else root->right=bst_init(value, size);
}

void bst_inorder_print(struct bst_node* root, void (*print)(void*))
{
	if(root==NULL)	return;

	bst_inorder_print(root->left, print);
	print(root->value);
	bst_inorder_print(root->right, print);

}

void bst_preorder_print(struct bst_node* root, void (*print)(void*))
{
	if(root==NULL)	return;

	print(root->value);
	bst_preorder_print(root->left, print);
	bst_preorder_print(root->right, print);

}

void bst_postorder_print(struct bst_node* root, void (*print)(void*))
{
	if(root==NULL)	return;

	bst_postorder_print(root->left, print);
	bst_postorder_print(root->right, print);
	print(root->value);
}

int bst_size(struct bst_node* root)
{	
	if(root==NULL) return 0;
	return 1+bst_size(root->right)+bst_size(root->left);
}

int bst_levels(struct bst_node* root)
{
	if(root==NULL) return 0;

	int levels_left=1+bst_levels(root->left), levels_right=1+bst_levels(root->right);

	return (levels_right>levels_left)? levels_right:levels_left;

}

void* bst_min(struct bst_node* root)
{	
	if(root==NULL){
		fprintf(stderr, "Min requested for empty tree\n");
		return NULL;
	}

	while(root->left!=NULL) root=root->left;
	return root->value;
}

void* bst_max(struct bst_node* root)
{
	if(root==NULL){
		fprintf(stderr, "Max requested for empty tree\n");
		return NULL;
	}

	while(root->right!=NULL) root=root->right;
	return root->value;
}


struct bst_node* bst_search_parent(struct bst_node* root, void* value, bool (*check_equality)(void* a, void* b), void* (*compare)(void*, void*))
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

struct bst_node* bst_search_child_with_value(struct bst_node* root, void* value, bool (*check_equality)(void*, void*))
{
	assert(value!=NULL);

	if(root==NULL) return root;

	if(root->right!=NULL)
		if(check_equality(value,root->right->value)) return root->right;

	return root->left;
}

struct bst_node* bst_successor_parent(struct bst_node* root)
{
	if(root==NULL) return root;
	if(root->right==NULL) return root;
	if(root->right->left==NULL) return root;

	root = root->right;

	while (root->left->left != NULL) root = root->left;

	return root;

}

struct bst_node* bst_predecessor_parent(struct bst_node* root)
{
	if(root==NULL) return root;
	if(root->left==NULL) return root;
	if(root->left->right==NULL) return root;

	root = root->left;

	while (root->right->right != NULL) root = root->right;

	return root;
}

struct bst_node* bst_search(struct bst_node* root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*))
{
	assert(value!=NULL);

	if(check_equality(root, root->value)) return root;
	return bst_search_child_with_value(bst_search_parent(root,value,check_equality,compare), value, check_equality);
}


struct bst_node* bst_successor(struct bst_node* root)
{
	root=bst_successor_parent(root);
	if(root->left==NULL) return root;
	return root->left;
}

struct bst_node* bst_predecessor(struct bst_node* root)
{
	root=bst_predecessor_parent(root);
	if(root->right==NULL) return root;
	return root->right;
}

void bst_pop(struct bst_node** root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*))  {

        assert(value!=NULL);

	struct bst_node* target = *root;

	struct bst_node* parent = bst_search_parent(target, value, check_equality, compare);

		
	if(parent!=NULL) target = bst_search_child_with_value(target, value, check_equality);	

	if (target == NULL) return; 

	if (target->left == NULL && target->right == NULL) {
		if (parent != NULL) {
			if (target == parent->left) parent->left = NULL;
			else if (target == parent->right) parent->right = NULL;
		} 
		else *root = NULL;
		
		free(target->value);
		free(target);

		return;
	}

	if (target->right == NULL) {
		if (parent != NULL) {
			if (parent->right == target) parent->right = target->left;
			else parent->left = target->left;
		} 
		else *root = NULL;
		
		free(target->value);
		free(target);
		return;
	}

	if (target->left == NULL) {
		if (parent != NULL) {
			if (parent->right == target) parent->right = target->right;
			else parent->left = target->right;
		} 	
		else *root = NULL;

		free(target->value);
		free(target);
		return;
	}

	struct bst_node* successor_parent = bst_successor_parent(target);
	struct bst_node* successor = (successor_parent->left==NULL)? successor_parent:successor_parent->left;
	
	void* stored_target_value=target->value;

	target->value = successor->value;

	if (successor_parent->left == successor) successor_parent->left = successor->right;
	else successor_parent->right = successor->right;
	
	free(stored_target_value);
	free(successor);
}

void bst_free(struct bst_node** root)
{
	if((*root)==NULL) return;
	bst_free(&(*root)->left);
	bst_free(&(*root)->right);
	free((*root)->value);
	free((*root));
	(*root)=NULL;
}
