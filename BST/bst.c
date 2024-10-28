#include"bst.h"
#include"stdio.h"
#include"stdlib.h"
#include<assert.h>
#include <limits.h>
	
struct bst_node* bst_init(int value)
{
	struct bst_node* node=malloc(sizeof(struct bst_node));
	
	if(node==NULL)	fprintf(stderr,"Memory allocation failed\n");
		
	node->value=value;
	node->left=NULL;
	node->right=NULL;

	return node;
}

void bst_push(struct bst_node* root, int value)
{	
	if(root==NULL) fprintf(stderr,"Pushed to uninitialized tree\n");

	if(value<root->value){
		if(root->left!=NULL)
			bst_push(root->left, value);
		else root->left=bst_init(value);	
	}
	else if(root->right!=NULL) bst_push(root->right, value);
	else root->right=bst_init(value);
}

void bst_inorder_print(struct bst_node* root)
{
	if(root==NULL)	return;

	bst_inorder_print(root->left);
	printf("%d ",root->value);
	bst_inorder_print(root->right);

}

void bst_preorder_print(struct bst_node* root)
{
	if(root==NULL)	return;

	printf("%d ",root->value);
	bst_preorder_print(root->left);
	bst_preorder_print(root->right);

}

void bst_postorder_print(struct bst_node* root)
{
	if(root==NULL)	return;

	bst_postorder_print(root->left);
	bst_postorder_print(root->right);
	printf("%d ",root->value);
}

int bst_size(struct bst_node* root)
{	
	if(root==NULL) return 0;
	return 1+bst_size(root->right)+bst_size(root->left);
}

int bst_levels(struct bst_node* root)
{
	if(root==NULL) return 0;

	int levels_left=1, levels_right=1;
	levels_left+=bst_levels(root->left);
	levels_right+=bst_levels(root->right);

	return (levels_right>levels_left)? levels_right:levels_left;

}

int bst_min(struct bst_node* root)
{	
	if(root==NULL) return INT_MIN;
	while(root->left!=NULL) root=root->left;
	return root->value;
}

int bst_max(struct bst_node* root)
{
	if(root==NULL) return INT_MIN;
	while(root->right!=NULL) root=root->right;
	return root->value;
}


struct bst_node* bst_search_parent(struct bst_node* root, int value)
{

	while(root!=NULL) {
		if(root->left!=NULL)
			if(root->left->value==value) return root;
		

		if(root->right!=NULL)
			if(root->right->value==value) return root;
		

		if(value<root->value) root=root->left;
		else root=root->right;
	}

	return root;
}

struct bst_node* bst_search_child_value(struct bst_node* root, int value)
{
	if(root==NULL) return root;

	if(root->right!=NULL)
		if(root->right->value==value) return root->right;

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

struct bst_node* bst_search(struct bst_node* root, int value)
{
	if(root->value==value) return root;
	return bst_search_child_value(bst_search_parent(root,value),value);
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

void bst_pop(struct bst_node** big_root, int value) {

	struct bst_node* root = *big_root;
	struct bst_node* parent = bst_search_parent(root, value);
	
	if(parent!=NULL) root = bst_search_child_value(root, value);

	if (root == NULL) return; 

	if (root->left == NULL && root->right == NULL) {
		if (parent != NULL) {
			if (root == parent->left) parent->left = NULL;
			else if (root == parent->right) parent->right = NULL;
		} 
		else *big_root = NULL;
		
		free(root);
		return;
	}

	if (root->right == NULL) {
		if (parent != NULL) {
			if (parent->right == root) parent->right = root->left;
			else parent->left = root->left;
		} 
		else *big_root = root->left;
		
		free(root);
		return;
	}

	if (root->left == NULL) {
		if (parent != NULL) {
			if (parent->right == root) parent->right = root->right;
			else parent->left = root->right;
		} 	
		else *big_root = root->right;

		free(root);
		return;
	}

	struct bst_node* successor_parent = bst_successor_parent(root);
	struct bst_node* successor = (successor_parent->left==NULL)? successor_parent:successor_parent->left;
	
	root->value = successor->value;

	if (successor_parent->left == successor) successor_parent->left = successor->right;
	else successor_parent->right = successor->right;
	
	free(successor);
}

void bst_free(struct bst_node** root)
{
	if((*root)==NULL) return;
	bst_free(&(*root)->left);
	bst_free(&(*root)->right);
	free((*root));
	(*root)=NULL;
}
