#ifndef BST_H
#define BST_H

#include<stddef.h>
#include<stdbool.h>

struct bst_node { 
        struct  bst_node *right;
        struct  bst_node *left;
        void* value;
};

struct bst_node* bst_init(void* value, size_t size); 

void bst_push(struct bst_node* root, void* value, size_t size, void* (*compare)(void*, void*));
void bst_pop(struct bst_node** root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*));

void bst_preorder_print(struct bst_node* root, void (*print)(void*));
void bst_inorder_print(struct bst_node* root, void (*print)(void*));
void bst_postorder_print(struct bst_node* root, void (*print)(void*));

int bst_size(struct bst_node* root); 
int bst_levels(struct bst_node* root); 
void* bst_min(struct bst_node* root); 
void* bst_max(struct bst_node* root); 

struct bst_node* bst_search_child_with_value(struct bst_node* root, void* value, bool (*check_equality)(void*, void*)); 
struct bst_node* bst_search_parent(struct bst_node* root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*));
struct bst_node* bst_search(struct bst_node* root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*)); 

struct bst_node* bst_successor_parent(struct bst_node* root);
struct bst_node* bst_predecessor_parent(struct bst_node* root);
struct bst_node* bst_successor(struct bst_node* root);
struct bst_node* bst_predecessor(struct bst_node* root);

void bst_free(struct bst_node** root); 

#endif
