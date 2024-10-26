#include<stdio.h>
#include"minheap.h"
#include"stdlib.h"

int main(void)
{
	struct minheap* heap=minheap_init();
	minheap_insert(heap,10);
	minheap_insert(heap,9);
	minheap_insert(heap,3);
	minheap_insert(heap,12);
	minheap_insert(heap,55);
	minheap_insert(heap,5);
	minheap_insert(heap,11);
	minheap_insert(heap,13);
	minheap_insert(heap,19);
	minheap_insert(heap,81);
	minheap_insert(heap,33);
	minheap_insert(heap,44);
	minheap_insert(heap,36);
	minheap_insert(heap,665);
	minheap_insert(heap,212);
	minheap_insert(heap,70);
	minheap_insert(heap,8);
	minheap_insert(heap,2);
	
	minheap_print(heap);

	printf("minheap: %d \n",minheap_extract(heap));

	minheap_print(heap);

	printf("min: %d\n", minheap_findmin(heap));

	int* arr=malloc(sizeof(int)*5);
	arr[0]=10;
	arr[1]=9;
	arr[2]=8;
	arr[3]=7;
	arr[4]=6;

	struct minheap* heap2 = minheap_heapify(arr, 5);
	minheap_print(heap2);
	
	minheap_delete(heap, 12);
	minheap_print(heap);

	heapsort(heap->values,heap->size);
	minheap_print(heap);

	minheap_free(heap);
	minheap_free(heap2);
	free(arr);

	return 0;
}
