#ifndef B_H
#define B_H

#define T 2

#include<stdbool.h>
#include<stddef.h>


//Struct declaration
struct b_node {
	int numb_v; //number of values currently stored
	void** values;
	bool leaf;
	struct b_node** children;
};

//Return type for values in the B tree
struct b_node_value {
	int index;
	struct b_node* node;
};

//Intialization

struct b_node* b_init(void* value, size_t size);

//Pushing and popping
void b_push(struct b_node** root, void* value, size_t size, void* (*compare)(void*, void*));
void b_pop(struct b_node** root, void* value, size_t size, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*));

//Searching
struct b_node_value b_search(struct b_node* root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*));

//Freeing
void b_free(struct b_node* root);

#endif
