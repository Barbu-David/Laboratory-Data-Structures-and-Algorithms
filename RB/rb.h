#ifndef RB_H
#define RB_H

#include<stddef.h>
#include<stdbool.h>
#define RED true
#define BLACK false


struct rb_node { 
        struct  rb_node *right;
        struct  rb_node *left;
        void* value;
	bool color;
};

struct rb_node* rb_init(void* value, size_t size); 

void rb_push(struct rb_node** root, void* value, size_t size, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*));
void rb_pop(struct rb_node** root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*));

void rb_preorder_print(struct rb_node* root, void (*print)(void*));
void rb_inorder_print(struct rb_node* root, void (*print)(void*));
void rb_postorder_print(struct rb_node* root, void (*print)(void*));

int rb_size(struct rb_node* root); 
int rb_levels(struct rb_node* root); 
void* rb_min(struct rb_node* root); 
void* rb_max(struct rb_node* root); 

struct rb_node* rb_search(struct rb_node* root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*)); 

struct rb_node* rb_successor_parent(struct rb_node* root);
struct rb_node* rb_predecessor_parent(struct rb_node* root);
struct rb_node* rb_successor(struct rb_node* root);
struct rb_node* rb_predecessor(struct rb_node* root);

void rb_free(struct rb_node** root); 

#endif
