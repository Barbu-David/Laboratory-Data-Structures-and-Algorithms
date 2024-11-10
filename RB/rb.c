#include"rb.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<stdbool.h>

struct rb_node* rb_init(void* value, size_t size)
{	
	assert(value!=NULL);

	struct rb_node* node=malloc(sizeof(struct rb_node));
	assert(node!=NULL);	

	void* new_value=malloc(size);
	assert(new_value!=NULL);

	memcpy(new_value, value, size);

	node->value=new_value;
	node->left=NULL;
	node->right=NULL;
	node->color=BLACK;
	return node;
}

int rb_levels(struct rb_node* root)
{
	if(root==NULL) return 0;

	int levels_left=1+rb_levels(root->left), levels_right=1+rb_levels(root->right);

	return (levels_right>levels_left)? levels_right:levels_left;
}

struct rb_node* rb_right_rotate(struct rb_node* root)
{
	if(root==NULL) return NULL;

	struct rb_node* new_root=root->left;

	if(new_root==NULL) return root; 

	root->left=new_root->right;
	new_root->right=root;

	return new_root;
}

struct rb_node* rb_left_rotate(struct rb_node* root)
{
	if(root==NULL) return NULL;

	struct rb_node* new_root=root->right;

	if(new_root==NULL) return root; 

	root->right=new_root->left;
	new_root->left=root;

	return new_root;
}


struct rb_node* rb_right_left_rotate(struct rb_node* root)
{	
	if(root==NULL) return NULL;

	root->right=rb_right_rotate(root->right);
	return rb_left_rotate(root);
}

struct rb_node* rb_left_right_rotate(struct rb_node* root)
{	
	if(root==NULL) return NULL;

	root->left=rb_left_rotate(root->left);
	return rb_right_rotate(root);
}

void rb_inorder_print(struct rb_node* root, void (*print)(void*))
{
	if(root==NULL)	return;

	rb_inorder_print(root->left, print);
	print(root->value);
	rb_inorder_print(root->right, print);

}

void rb_preorder_print(struct rb_node* root, void (*print)(void*))
{
	if(root==NULL)	return;

	print(root->value);
	rb_preorder_print(root->left, print);
	rb_preorder_print(root->right, print);

}

void rb_postorder_print(struct rb_node* root, void (*print)(void*))
{
	if(root==NULL)	return;

	rb_postorder_print(root->left, print);
	rb_postorder_print(root->right, print);
	print(root->value);
}

int rb_size(struct rb_node* root)
{	
	if(root==NULL) return 0;
	return 1+rb_size(root->right)+rb_size(root->left);
}

void* rb_min(struct rb_node* root)
{	
	if(root==NULL){
		fprintf(stderr, "Min requested for empty tree\n");
		return NULL;
	}

	while(root->left!=NULL) root=root->left;
	return root->value;
}

void* rb_max(struct rb_node* root)
{
	if(root==NULL){
		fprintf(stderr, "Max requested for empty tree\n");
		return NULL;
	}

	while(root->right!=NULL) root=root->right;
	return root->value;
}

struct rb_node* rb_search_parent(struct rb_node* root, void* value, bool (*check_equality)(void* a, void* b), void* (*compare)(void*, void*))
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

struct rb_node* rb_search_grand_parent(struct rb_node* root, void* value, bool (*check_equality)(void* a, void* b), void* (*compare)(void*, void*))
{
	assert(value!=NULL);

	void* parent_value=rb_search_parent(root, value, check_equality, compare)->value;
	root=rb_search_parent(root, parent_value, check_equality, compare);


	return root;
}


struct rb_node* rb_search_child_with_value(struct rb_node* root, void* value, bool (*check_equality)(void*, void*))
{
	assert(value!=NULL);

	if(root==NULL) return root;

	if(root->right!=NULL)
		if(check_equality(value,root->right->value)) return root->right;

	return root->left;
}


struct rb_node* rb_successor_parent(struct rb_node* root)
{
	if(root==NULL) return root;
	if(root->right==NULL) return root;
	if(root->right->left==NULL) return root;

	root = root->right;

	while (root->left->left != NULL) root = root->left;

	return root;

}

struct rb_node* rb_predecessor_parent(struct rb_node* root)
{
	if(root==NULL) return root;
	if(root->left==NULL) return root;
	if(root->left->right==NULL) return root;

	root = root->left;

	while (root->right->right != NULL) root = root->right;

	return root;
}


struct rb_node* rb_search(struct rb_node* root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*))
{
	assert(value!=NULL);

	if(check_equality(value, root->value)) return root;
	return rb_search_child_with_value(rb_search_parent(root,value,check_equality,compare), value, check_equality);
}


void rb_push_no_fix(struct rb_node** root, void* value, size_t size, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*))
{	
	if(*root==NULL) { 
		fprintf(stderr,"Pushed to uninitialized tree\n");
		return;	
	}

	assert(value!=NULL);

	if(compare(value,(*root)->value)==(*root)->value){
		if((*root)->left!=NULL) rb_push(&((*root)->left), value, size, check_equality, compare);
		else {
			(*root)->left=rb_init(value, size);	
			(*root)->left->color=RED;
		}
	}
	else if((*root)->right!=NULL) rb_push(&((*root)->right), value, size, check_equality, compare);
	else {
	(*root)->right=rb_init(value, size);
	(*root)->right->color=RED;
	}

}

void rb_fix(struct rb_node** root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*))
{
	struct rb_node* parent=rb_search_parent(*root, value, check_equality, compare);
	if(parent->color==BLACK) return;

	struct rb_node* grand=rb_search_grand_parent(*root, value, check_equality, compare);
	struct rb_node* uncle;
	if(rb_search_child_with_value(grand, parent->value, check_equality)==grand->left) uncle=grand->right;
	else uncle=grand->left;

	if(uncle==NULL) {
		parent->color=BLACK;
		grand->color=RED;
		rb_fix(root, value, check_equality, compare);
		return;
	}
	else if(uncle->color==BLACK) {	
		parent->color=BLACK;
		uncle->color=BLACK;
		grand->color=RED;
		rb_fix(root, value, check_equality, compare);
		return;
	}

}

void rb_push(struct rb_node** root, void* value, size_t size, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*))
{	
	rb_push_no_fix(root, value, size, check_equality, compare);
	rb_fix(root, value, check_equality, compare);
}

struct rb_node* rb_successor(struct rb_node* root)
{
	root=rb_successor_parent(root);
	if(root->left==NULL) return root;
	return root->left;
}

struct rb_node* rb_predecessor(struct rb_node* root)
{
	root=rb_predecessor_parent(root);
	if(root->right==NULL) return root;
	return root->right;
}

void rb_pop(struct rb_node** root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*))  {

	assert(value!=NULL);

	struct rb_node* target = *root;

	struct rb_node* parent = rb_search_parent(target, value, check_equality, compare);

	if(parent!=NULL) target = rb_search_child_with_value(target, value, check_equality);	

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

	struct rb_node* successor_parent = rb_successor_parent(target);
	struct rb_node* successor = (successor_parent->left==NULL)? successor_parent:successor_parent->left;

	void* stored_target_value=target->value;

	target->value = successor->value;

	if (successor_parent->left == successor) successor_parent->left = successor->right;
	else successor_parent->right = successor->right;

	free(stored_target_value);
	free(successor);
}

void rb_free(struct rb_node** root)
{
	if((*root)==NULL) return;
	rb_free(&(*root)->left);
	rb_free(&(*root)->right);
	free((*root)->value);
	free((*root));
	(*root)=NULL;
}
