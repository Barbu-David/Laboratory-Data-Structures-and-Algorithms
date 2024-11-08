#ifndef SPLAY_H
#define SPLAY_H

#include<stddef.h>
#include<stdbool.h>

struct splay_node { 
        struct  splay_node *right;
        struct  splay_node *left;
        void* value;
};

struct splay_node* splay_init(void* value, size_t size); 

void splay_push(struct splay_node** root, void* value, size_t size, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*));
void splay_pop(struct splay_node** root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*));

void splay_preorder_print(struct splay_node* root, void (*print)(void*));
void splay_inorder_print(struct splay_node* root, void (*print)(void*));
void splay_postorder_print(struct splay_node* root, void (*print)(void*));

int splay_size(struct splay_node* root); 
int splay_levels(struct splay_node* root); 
void* splay_min(struct splay_node* root); 
void* splay_max(struct splay_node* root); 

struct splay_node* splay_search_child_with_value(struct splay_node* root, void* value, bool (*check_equality)(void*, void*)); 
struct splay_node* splay_search_parent(struct splay_node* root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*));
struct splay_node* splay_search(struct splay_node** root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*)); 

struct splay_node* splay_successor_parent(struct splay_node* root);
struct splay_node* splay_predecessor_parent(struct splay_node* root);
struct splay_node* splay_successor(struct splay_node* root);
struct splay_node* splay_predecessor(struct splay_node* root);

void splay_free(struct splay_node** root); 

#endif
