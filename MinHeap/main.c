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
	

	minheap_extract(heap);	
	minheap_delete(heap, 12);

	minheap_print(heap);

	minheap_free(heap);

	return 0;
}
