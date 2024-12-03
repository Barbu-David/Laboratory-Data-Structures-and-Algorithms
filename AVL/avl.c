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
	node->balance_factor=0;
	return node;
}

int avl_levels(struct avl_node* root)
{
	if(root==NULL) return 0;

	int levels_left=1+avl_levels(root->left), levels_right=1+avl_levels(root->right);

	return (levels_right>levels_left)? levels_right:levels_left;
}

int avl_node_balance_factor(struct avl_node* root)
{
	if(root==NULL) 	return 0;	

	root->balance_factor=avl_levels(root->left)-avl_levels(root->right);
	return root->balance_factor;

}

struct avl_node* avl_right_rotate(struct avl_node* root)
{
	if(root==NULL) return NULL;
	
	struct avl_node* new_root=root->left;

	if(new_root==NULL) return root; 

	root->left=new_root->right;
	new_root->right=root;

	avl_node_balance_factor(root);
	avl_node_balance_factor(new_root);

	return new_root;
}

struct avl_node* avl_left_rotate(struct avl_node* root)
{
	if(root==NULL) return NULL;

	struct avl_node* new_root=root->right;

	if(new_root==NULL) return root; 

	root->right=new_root->left;
	new_root->left=root;
	avl_node_balance_factor(root);
	avl_node_balance_factor(new_root);

	return new_root;
}

struct avl_node* avl_right_left_rotate(struct avl_node* root)
{	
	if(root==NULL) return NULL;

	root->right=avl_right_rotate(root->right);
	return avl_left_rotate(root);

}

struct avl_node* avl_left_right_rotate(struct avl_node* root)
{	
	if(root==NULL) return NULL;

	root->left=avl_left_rotate(root->left);
	return avl_right_rotate(root);
}

struct avl_node* avl_balance(struct avl_node* root)
{
	if(root==NULL) return NULL;

	if(root->balance_factor>1) { //Left cases

		int left_right_factor, left_left_factor;
		if(root->left==NULL) {	
			left_right_factor=0;
			left_left_factor=0;
		}
		else {
			if(root->left->left!=NULL) left_left_factor=root->left->left->balance_factor;
			else left_left_factor=0;
			if(root->left->right!=NULL) left_right_factor=root->left->right->balance_factor;
			else left_right_factor=0;
		}T

		if(left_left_factor>=left_right_factor) 
			return avl_right_rotate(root);
		else return avl_left_right_rotate(root);

	}
	else if(root->balance_factor<-1){ //Right cases

		int right_right_factor, right_left_factor;
		if(root->right==NULL) {	
			right_right_factor=0;
			right_left_factor=0;
		}
		else {
			if(root->right->left!=NULL) right_left_factor=root->right->left->balance_factor;
			else right_left_factor=0;
			if(root->right->right!=NULL) right_right_factor=root->right->right->balance_factor;
			else right_right_factor=0;
		}

		if(right_left_factor<right_right_factor) 
			return avl_left_rotate(root);
		else return avl_right_left_rotate(root);

	}

	return root;	
}

void avl_push(struct avl_node** root, void* value, size_t size, bool (*check_equality) (void*, void*) ,void* (*compare)(void*, void*))
{
	assert(root!=NULL);	
	assert(value!=NULL);

        bool pushed=false;
        while(!pushed)
        {
                if(check_equality(value, (*root)->value)) return;
                if(compare(value,(*root)->value)==(*root)->value){
                        if((*root)->left!=NULL) *root=(*root)->left;
                        else {
                                (*root)->left=avl_init(value, size);    
                                pushed=true;
                        }
                }
                else if((*root)->right!=NULL) *root=(*root)->right;
                else {
                        (*root)->right=avl_init(value, size);
                        pushed=true;
                }

        }

	avl_node_balance_factor(*root);
	*root=avl_balance(*root);
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

	if(check_equality(value, root->value)) return root;
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

	if (target->left == NULL && target->right == NULL) {
		if (parent != NULL) {
			if (target == parent->left) parent->left = NULL;
			else if (target == parent->right) parent->right = NULL;
			avl_node_balance_factor(parent);
			parent=avl_balance(parent);
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
			avl_node_balance_factor(parent);
			parent=avl_balance(parent);
		} 
		else *root = target->left;

		free(target->value);
		free(target);
		return;
	}

	if (target->left == NULL) {
		if (parent != NULL) {
			if (parent->right == target) parent->right = target->right;
			else parent->left = target->right;
			avl_node_balance_factor(parent);
			parent=avl_balance(parent);
		} 	
		else *root = target->right;

		free(target->value);
		free(target);
		return;
	}

	struct avl_node* successor_parent = avl_successor_parent(target);
	struct avl_node* successor = (successor_parent->left==NULL)? successor_parent:successor_parent->left;

	void* stored_target_value=target->value;

	target->value = successor->value;

	if (successor_parent->left == successor) successor_parent->left = successor->right;
	else successor_parent->right = successor->right;

	avl_node_balance_factor(successor_parent);
	successor_parent=avl_balance(successor_parent);

	free(stored_target_value);
	free(successor);
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
