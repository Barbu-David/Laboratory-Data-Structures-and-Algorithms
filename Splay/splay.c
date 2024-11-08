#include"splay.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<stdbool.h>

struct splay_node* splay_init(void* value, size_t size)
{	
	assert(value!=NULL);

	struct splay_node* node=malloc(sizeof(struct splay_node));
	assert(node!=NULL);	

	void* new_value=malloc(size);
	assert(new_value!=NULL);

	memcpy(new_value, value, size);

	node->value=new_value;
	node->left=NULL;
	node->right=NULL;
	return node;
}

int splay_levels(struct splay_node* root)
{
	if(root==NULL) return 0;

	int levels_left=1+splay_levels(root->left), levels_right=1+splay_levels(root->right);

	return (levels_right>levels_left)? levels_right:levels_left;
}

struct splay_node* splay_right_rotate(struct splay_node* root)
{
	if(root==NULL) return NULL;
	
	struct splay_node* new_root=root->left;

	if(new_root==NULL) return root; 

	root->left=new_root->right;
	new_root->right=root;

	return new_root;
}

struct splay_node* splay_left_rotate(struct splay_node* root)
{
	if(root==NULL) return NULL;

	struct splay_node* new_root=root->right;

	if(new_root==NULL) return root; 

	root->right=new_root->left;
	new_root->left=root;

	return new_root;
}

struct splay_node* splay_right_left_rotate(struct splay_node* root)
{	
	if(root==NULL) return NULL;

	root->right=splay_right_rotate(root->right);
	return splay_left_rotate(root);

}

struct splay_node* splay_left_right_rotate(struct splay_node* root)
{	
	if(root==NULL) return NULL;

	root->left=splay_left_rotate(root->left);
	return splay_right_rotate(root);
}

struct splay_node* splay_splay(struct splay_node* root, void* value)
{
	return NULL;
}

void splay_inorder_print(struct splay_node* root, void (*print)(void*))
{
	if(root==NULL)	return;

	splay_inorder_print(root->left, print);
	print(root->value);
	splay_inorder_print(root->right, print);

}

void splay_preorder_print(struct splay_node* root, void (*print)(void*))
{
	if(root==NULL)	return;

	print(root->value);
	splay_preorder_print(root->left, print);
	splay_preorder_print(root->right, print);

}

void splay_postorder_print(struct splay_node* root, void (*print)(void*))
{
	if(root==NULL)	return;

	splay_postorder_print(root->left, print);
	splay_postorder_print(root->right, print);
	print(root->value);
}

int splay_size(struct splay_node* root)
{	
	if(root==NULL) return 0;
	return 1+splay_size(root->right)+splay_size(root->left);
}

void* splay_min(struct splay_node* root)
{	
	if(root==NULL){
		fprintf(stderr, "Min requested for empty tree\n");
		return NULL;
	}

	while(root->left!=NULL) root=root->left;
	return root->value;
}

void* splay_max(struct splay_node* root)
{
	if(root==NULL){
		fprintf(stderr, "Max requested for empty tree\n");
		return NULL;
	}

	while(root->right!=NULL) root=root->right;
	return root->value;
}

struct splay_node* splay_search_parent(struct splay_node* root, void* value, bool (*check_equality)(void* a, void* b), void* (*compare)(void*, void*))
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

struct splay_node* splay_search_child_with_value(struct splay_node* root, void* value, bool (*check_equality)(void*, void*))
{
	assert(value!=NULL);

	if(root==NULL) return root;

	if(root->right!=NULL)
		if(check_equality(value,root->right->value)) return root->right;

	return root->left;
}

struct splay_node* splay_successor_parent(struct splay_node* root)
{
	if(root==NULL) return root;
	if(root->right==NULL) return root;
	if(root->right->left==NULL) return root;

	root = root->right;

	while (root->left->left != NULL) root = root->left;

	return root;

}

struct splay_node* splay_predecessor_parent(struct splay_node* root)
{
	if(root==NULL) return root;
	if(root->left==NULL) return root;
	if(root->left->right==NULL) return root;

	root = root->left;

	while (root->right->right != NULL) root = root->right;

	return root;
}

struct splay_node* splay_search(struct splay_node** root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*))
{
	assert(value!=NULL);

	if(check_equality(value, (*root)->value)) return *root;
	struct splay_node* sp = splay_search_child_with_value(splay_search_parent(*root,value,check_equality,compare), value, check_equality);

	if(sp!=NULL) *root=splay_splay(*root, sp->value);
		
	return sp;
}


void splay_push(struct splay_node** root, void* value, size_t size, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*))
{	
	if(*root==NULL) { 
		fprintf(stderr,"Pushed to uninitialized tree\n");
		return;	
	}

	assert(value!=NULL);

	if(compare(value,(*root)->value)==(*root)->value){
		if((*root)->left!=NULL)
			splay_push(&((*root)->left), value, size, check_equality, compare);
		else (*root)->left=splay_init(value, size);	
	}
	else if((*root)->right!=NULL) splay_push(&((*root)->right), value, size, check_equality, compare);
	else (*root)->right=splay_init(value, size);

	*root=splay_search(root, value, check_equality, compare);

}

struct splay_node* splay_successor(struct splay_node* root)
{
	root=splay_successor_parent(root);
	if(root->left==NULL) return root;
	return root->left;
}

struct splay_node* splay_predecessor(struct splay_node* root)
{
	root=splay_predecessor_parent(root);
	if(root->right==NULL) return root;
	return root->right;
}

void splay_pop(struct splay_node** root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*))  {

	assert(value!=NULL);

	struct splay_node* target = *root;

	struct splay_node* parent = splay_search_parent(target, value, check_equality, compare);

	if(parent!=NULL) target = splay_search_child_with_value(target, value, check_equality);	

	if (target == NULL) return; 

	if (target->left == NULL && target->right == NULL) {
		if (parent != NULL) {
			if (target == parent->left) parent->left = NULL;
			else if (target == parent->right) parent->right = NULL;
			*root=splay_search(root, parent->value, check_equality, compare);	
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
			*root=splay_search(root, parent->value, check_equality, compare);	
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
			*root=splay_search(root, parent->value, check_equality, compare);	
		} 	
		else *root = NULL;

		free(target->value);
		free(target);
		return;
	}

	struct splay_node* successor_parent = splay_successor_parent(target);
	struct splay_node* successor = (successor_parent->left==NULL)? successor_parent:successor_parent->left;

	void* stored_target_value=target->value;

	target->value = successor->value;

	if (successor_parent->left == successor) successor_parent->left = successor->right;
	else successor_parent->right = successor->right;

	*root=splay_search(root, successor_parent->value, check_equality, compare);	

	free(stored_target_value);
	free(successor);
}

void splay_free(struct splay_node** root)
{
	if((*root)==NULL) return;
	splay_free(&(*root)->left);
	splay_free(&(*root)->right);
	free((*root)->value);
	free((*root));
	(*root)=NULL;
}
