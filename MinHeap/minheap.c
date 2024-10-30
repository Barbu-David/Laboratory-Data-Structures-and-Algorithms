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

	while(index>0 && compare(heap->values[(index-1)/2], heap->values[index])==heap->values[(index-1)/2]) {
		switch_values(&heap->values[(index-1)/2],&heap->values[index]);
		index=(index-1)/2;
	}	
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
	free(heap->values[0]);
	heap->values[0]=heap->values[heap->occupied_capacity-1];
	heap->occupied_capacity--;

	if(heap->occupied_capacity==1) return return_value;
	else if(heap->occupied_capacity==2) {
		if(compare(heap->values[1],heap->values[0])==heap->values[0]) switch_values(&heap->values[0],&heap->values[1]);
		return return_value;
	}


	unsigned long index=0, index_left=1, index_right=2, smallest;

	if(compare(heap->values[index],heap->values[index_right]) == heap->values[index_right] && compare(heap->values[index],heap->values[index_left])==heap->values[index_left])
		smallest=index;
	else if(compare(heap->values[index_right],heap->values[index_left]) == heap->values[index_left])
		smallest=index_right;
	else smallest=index_left;


	while(smallest!=index){

		switch_values(&heap->values[index],&heap->values[smallest]);
		index=smallest;
		index_right=smallest*2+2;
		index_left=smallest*2+1;

		if(index_right>heap->occupied_capacity)
		{
			if(index_left==heap->occupied_capacity)
				smallest=index_left;
			else smallest=index;
		}
		else if(compare(heap->values[index],heap->values[index_right]) == heap->values[index_right] && compare(heap->values[index],heap->values[index_left])==heap->values[index_left])
		smallest=index;
		else if(compare(heap->values[index_right],heap->values[index_left]) == heap->values[index_left])
		smallest=index_right;
		else smallest=index_left;

	
	}

	return return_value;
}

void* minheap_findmin(struct minheap* heap)
{	
	assert(heap!=NULL);
	return heap->values[0];
}

struct minheap* minheap_heapify(void** future_heap, unsigned long number_of_elements, size_t size, void* (*compare)(void*, void*))
{
	unsigned long i=0;
	struct minheap* heap = minheap_init(size);
	for(i=0;i<number_of_elements;i++)
		minheap_insert(heap, future_heap[i], size, compare);
	return heap;

}

void minheap_free(struct minheap* heap)
{
	assert(heap!=NULL);

	for(unsigned long i=0; i<heap->occupied_capacity; i++) free(heap->values[i]);
	free(heap->values);
	free(heap);
	heap=NULL;
}

void minheap_delete(struct minheap* heap, void* value, void* (*compare)(void*, void*), bool (*check_equality)(void*, void*))
{
	assert(heap!=NULL);	

	for(unsigned long i=0;i<heap->occupied_capacity;i++)
		if(check_equality(heap->values[i],value)){
			switch_values(&heap->values[i], &heap->values[0]);	
			switch_values(&heap->values[i], &heap->values[heap->occupied_capacity-1]);	
			minheap_extract(heap, compare);
			return;
		}
}

