#ifndef MINHEAP_H
#define MINHEAP_H

#include<stddef.h>
#include<stdbool.h>

struct binaryheap {
		void** values;
		long unsigned occupied_capacity, capacity;
};	


struct binaryheap* binaryheap_init();
struct binaryheap* binaryheap_init_from_array(void** values, long unsigned number_of_elements, size_t size);

void binaryheap_insert(struct binaryheap* heap, void* value, size_t size, void* (*compare)(void*, void*));

void binaryheap_print(struct binaryheap* heap, void (*print)(void*));

void* binaryheap_extract(struct binaryheap* heap, void* (*compare)(void*, void*));
void binaryheap_delete(struct binaryheap* heap, void* value, size_t size, void* (*compare)(void*, void*), bool (*check_equality)(void*, void*)); 

void* binaryheap_findmin(struct binaryheap* heap);

void binaryheap_free(struct binaryheap* heap);

void binaryheap_heapify_array(void** future_heap, unsigned long number_of_elements, void* (*compare)(void*, void*));

#endif
