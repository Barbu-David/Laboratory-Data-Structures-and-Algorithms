#include"minheap.h"
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

void switch_values(int* a, int* b)
{
	int tmp=*a;
	*a=*b;
	*b=tmp;

}

struct minheap* minheap_init()
{
	struct minheap* heap = malloc(sizeof(struct minheap));
	assert(heap!=NULL);

	heap->size=0;
	heap->capacity=4;	

	heap->values = malloc(sizeof(int)*heap->capacity);
	assert(heap->values!=NULL);

	return heap;
}

void minheap_insert(struct minheap* heap, int value)
{
	assert(heap!=NULL);
	heap->size++;

	if(heap->size>=heap->capacity){ 
		heap->capacity*=2;
		heap->values=realloc(heap->values,sizeof(int)*heap->capacity);
	}

	int index=heap->size-1;
	heap->values[index]=value;

	while(index>0 && heap->values[(index-1)/2] > heap->values[index]) {
		switch_values(&heap->values[(index-1)/2],&heap->values[index]);
		index=(index-1)/2;
	}	
}

void minheap_print(struct minheap* heap)
{
	assert(heap!=NULL);

	for(unsigned long i=0;i < heap->size;i++) 
		printf("%d, ",heap->values[i]);
	printf("\n");
}



int minheap_extract(struct minheap* heap)
{	
	assert(heap!=NULL);

	int r=heap->values[0];

	heap->values[0]=heap->values[heap->size-1];
	heap->size--;

	if(heap->size==1) return r;
	else if(heap->size==2) {
		if(heap->values[1]<heap->values[0]) switch_values(&heap->values[0],&heap->values[1]);
		return r;
	}


	int index=0;
	int index_left=1;
	int index_right=2;
	int smallest;

	if(heap->values[index]<=heap->values[index_right] && heap->values[index]<=heap->values[index_left])
		smallest=index;
	else if(heap->values[index_right]<=heap->values[index_left])
		smallest=index_right;
	else smallest=index_left;


	while(smallest!=index){

		switch_values(&heap->values[index],&heap->values[smallest]);
		index=smallest;
		index_right=smallest*2+1;
		index_left=smallest*2;

		if(index_right>(int)heap->size)
		{
			if(index_left==(int)heap->size)
				smallest=index_left;
			else smallest=index;
		}
		else if((heap->values[index]<=heap->values[index_right] && heap->values[index]<=heap->values[index_left]))
			smallest=index;
		else if(heap->values[index_right]<=heap->values[index_left])
			smallest=index_right;
		else smallest=index_left;

	}

	return r;


}

int minheap_findmin(struct minheap* heap)
{	
	assert(heap!=NULL);
	return heap->values[0];
}

struct minheap* minheap_heapify(int* future_heap, int size)
{
	int i=0;
	struct minheap* heap = minheap_init();
	for(i=0;i<size;i++)
		minheap_insert(heap, future_heap[i]);
	return heap;

}

void minheap_free(struct minheap* heap)
{
	free(heap->values);
	free(heap);
}

void minheap_delete(struct minheap* heap, int value)
{
	assert(heap!=NULL);	

	for(int i=0;i<(int)heap->size;i++)
		if(heap->values[i]==value){
			switch_values(&heap->values[i], &heap->values[0]);	
			switch_values(&heap->values[i], &heap->values[heap->size-1]);	
			minheap_extract(heap);
			return;
		}
}

void heapsort(int* arr, int size)
{
	struct minheap* heap=minheap_heapify(arr,size);
	int i=0;
	while(heap->size){
		arr[i]=minheap_extract(heap);
		i++;
	}
	minheap_free(heap);
}

