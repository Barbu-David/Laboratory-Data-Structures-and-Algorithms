#include"minheap.h"
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void switch_values(void** a, void** b)
{
	void* tmp=*a;
	*a=*b;
	*b=tmp;
}

struct minheap* minheap_init()
{
	struct minheap* heap = malloc(sizeof(struct minheap));
	assert(heap!=NULL);

	heap->occupied_capacity=0;
	heap->capacity=4;	

	heap->values = malloc(sizeof(void*)*heap->capacity);
	assert(heap->values!=NULL);

	return heap;
}

struct minheap* minheap_init_from_array(void** values, long unsigned number_of_elements, size_t size)
{
	struct minheap* heap = malloc(sizeof(struct minheap));
	assert(heap!=NULL);
	assert(values!=NULL);

	heap->occupied_capacity=number_of_elements;
	heap->capacity=number_of_elements+1;	

	heap->values=malloc(sizeof(void*)*number_of_elements);

	for(unsigned long index=0; index<number_of_elements; index++){
		heap->values[index]=malloc(size);
		assert(heap->values[index]!=NULL);
		memcpy(heap->values[index], values[index], size);
	}

	return heap;
}


void minheap_heapify_up(void** values, long unsigned index, void* (*compare)(void*, void*))
{
	while(index>0 && compare(values[(index-1)/2], values[index])==values[(index-1)/2]) {
		switch_values(&values[(index-1)/2],&values[index]);
		index=(index-1)/2;
	}	
}

void minheap_heapify_down(void** values, unsigned long number_of_elements, unsigned long index, void* (*compare)(void*, void*)) 
{
	unsigned long index_left = index * 2 + 1;
	unsigned long index_right = index * 2 + 2;
	unsigned long smallest = index;

	if(index_left < number_of_elements) 
		if(compare(values[smallest], values[index_left]) == values[smallest]) 
			smallest = index_left;

	if(index_right < number_of_elements) 
		if(compare(values[smallest], values[index_right]) == values[smallest]) 
			smallest = index_right;

	if(smallest != index) {
		switch_values(&values[index], &values[smallest]);
		minheap_heapify_down(values, number_of_elements, smallest, compare);   
	}
}

void minheap_insert(struct minheap* heap, void* value, size_t size, void* (*compare)(void*, void*))
{
	assert(heap!=NULL);
	assert(value!=NULL);

	heap->occupied_capacity++;

	if(heap->occupied_capacity>=heap->capacity){ 
		heap->capacity*=2;
		heap->values=realloc(heap->values,sizeof(void*)*heap->capacity);
		assert(heap->values!=NULL);
	}

	void* new_value=malloc(size);
	assert(new_value!=NULL);

	memcpy(new_value, value, size);

	unsigned long index=heap->occupied_capacity-1;
	heap->values[index]=new_value;

	minheap_heapify_up(heap->values, index, compare);
}

void minheap_print(struct minheap* heap, void (*print)(void*))
{
	assert(heap!=NULL);

	for(unsigned long i=0;i < heap->occupied_capacity;i++) 
		print(heap->values[i]);
}

void* minheap_extract(struct minheap* heap, void* (*compare)(void*, void*))
{	
	assert(heap!=NULL);

	void* return_value=heap->values[0];
	heap->values[0]=heap->values[heap->occupied_capacity-1];
	heap->occupied_capacity--;

	minheap_heapify_down(heap->values, heap->occupied_capacity, 0, compare);	

	return return_value;
}

void* minheap_findmin(struct minheap* heap)
{	
	assert(heap!=NULL);
	return heap->values[0];
}

void minheap_heapify_array(void** future_heap, unsigned long number_of_elements, void* (*compare)(void*, void*))
{
	unsigned long index;
	for(index = (number_of_elements-1)/2; index>0; index--)
		minheap_heapify_down(future_heap,number_of_elements, index, compare);
	minheap_heapify_down(future_heap,number_of_elements, 0, compare);
}

void minheap_free(struct minheap* heap)
{
	assert(heap!=NULL);

	for(unsigned long i=0; i<heap->occupied_capacity; i++) free(heap->values[i]);
	free(heap->values);
	free(heap);
	heap=NULL;
}

void minheap_delete(struct minheap* heap, void* value, size_t size, void* (*compare)(void*, void*), bool (*check_equality)(void*, void*))
{
	assert(heap!=NULL);	

	for(unsigned long i=0;i<heap->occupied_capacity;i++)
		if(check_equality(heap->values[i],value)){
			memcpy(heap->values[i], heap->values[0], size);
			minheap_heapify_up(heap->values, i, compare);
			free(minheap_extract(heap, compare));			
			return;
		}
}
