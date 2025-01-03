#include"b.h"
#include<stdlib.h>
#include<assert.h>
#include<string.h>

struct b_node* b_init(void* value, size_t size) 
{	
	assert(value!=NULL);

	struct b_node* new_node = malloc(sizeof(struct b_node));
	assert(new_node!=NULL);

	void* new_value=malloc(size);
	memcpy(new_value, value, size);

	new_node->leaf=true;
	new_node->values=malloc(sizeof(void*) * (2*T-1));
	new_node->children=malloc(sizeof(struct b_node*) * (2*T));
	
	assert(new_node->values!=NULL && new_node->children!=NULL);

	new_node->numb_v=1; //numb_v is a true counter, so for indexing it's off by one
	new_node->values[0]=new_value;

	return new_node;
}

//splits a full child into two nodes
void b_split_child(struct b_node* root, int full_child_index)
{
	struct b_node* child =root->children[full_child_index];
	struct b_node* sibling = malloc(sizeof(struct b_node)); //new node
	sibling->values=malloc(sizeof(void*) * (2*T-1));
	sibling->children=malloc(sizeof(struct b_node*) * (2*T));
	
	assert(sibling!=NULL && sibling->values!=NULL && sibling->children!=NULL);

	sibling->leaf=child->leaf; //they have the same leaf value
	
	
	int index;
	//the sibling gets the large values
	for(index=0; index<T-1; index++) 
		sibling->values[index]=child->values[index+T];
	
	//and the children, if they are exist
	if(!child->leaf) 
		for(index=0; index<T; index++) 
			sibling->children[index]=child->children[index+T];

	child->numb_v=T-1; //the child keeps T-1 values. 
	//Setting the rest of the childs values and children to null isn't necessary due to the presence of numb_v


	//shift children of root to make room for the sibling
	for(index=root->numb_v-1; index>full_child_index+1; index--)	//reverse order necessary
		root->children[index+1]=root->children[index];
	root->children[full_child_index+1]=sibling;

	//shift values of root to make room for median value
	for(index=root->numb_v-2; index>full_child_index;index--)
		root->values[index+1]=&root->values[index];
	root->numb_v++;
	root->values[full_child_index]=child->values[T];

}

/*
void b_split_root(struct b_node** root, void* value, size_t size, bool (*check_equalty)(void*, void*), void* (*compare)(void*, void*))
{

}



void b_merge_siblings(struct b_node** root, void* value, size_t size, bool (*check_equalty)(void*, void*), void* (*compare)(void*, void*))
{

}

void b_push_not_full(struct b_node** root, void* value, size_t size, bool (*check_equalty)(void*, void*), void* (*compare)(void*, void*))
{

}

void b_push(struct b_node** root, void* value, size_t size, bool (*check_equalty)(void*, void*), void* (*compare)(void*, void*))
{

}
void b_pop(struct b_node** root, void* value, size_t size, bool (*check_equaliy)(void*, void*), void* (*compare)(void*, void*))
{

}

struct b_node_value b_search(struct b_node* root, void* value) 
{

}

void b_free(struct b_node* root)
{

}*/
