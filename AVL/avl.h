#ifndef BST_H
#define BST_H

#include<stddef.h>
#include<stdbool.h>

struct avl_node { 
        struct  avl_node *right;
        struct  avl_node *left;
	unsigned long balance_factor;
        void* value;
};

struct avl_node* bst_init(void* value, size_t size); 

void avl_push(struct avl_node* root, void* value, size_t size, void* (*compare)(void*, void*));
void avl_pop(struct avl_node** root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*));

void avl_preorder_print(struct avl_node* root, void (*print)(void*));
void avl_inorder_print(struct avl_node* root, void (*print)(void*));
void avl_postorder_print(struct avl_node* root, void (*print)(void*));

int avl_size(struct avl_node* root); 
int avl_levels(struct avl_node* root); 
void* avl_min(struct avl_node* root); 
void* avl_max(struct avl_node* root); 

struct avl_node* bst_search_child_with_value(struct avl_node* root, void* value, bool (*check_equality)(void*, void*)); 
struct avl_node* bst_search_parent(struct avl_node* root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*));
struct avl_node* bst_search(struct avl_node* root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*)); 

struct avl_node* bst_successor_parent(struct avl_node* root);
struct avl_node* bst_predecessor_parent(struct avl_node* root);
struct avl_node* bst_successor(struct avl_node* root);
struct avl_node* bst_predecessor(struct avl_node* root);

void avl_free(struct avl_node** root); 

#endif
