#ifndef MINHEAP_H
#define MINHEAP_H

#include<stddef.h>
#include<stdbool.h>

struct minheap {
		void** values;
		long unsigned occupied_capacity, capacity;
};		


struct minheap* minheap_init();

void minheap_insert(struct minheap* heap, void* value, size_t size, void* (*compare)(void*, void*));

void minheap_print(struct minheap* heap, void (*print)(void*));

void* minheap_extract(struct minheap* heap, void* (*compare)(void*, void*));
void minheap_delete(struct minheap* heap, void* value, void* (*compare)(void*, void*), bool (*check_equality)(void*, void*));

void* minheap_findmin(struct minheap* heap);

struct minheap* minheap_heapify(void** future_heap, unsigned long number_of_elements, size_t size, void* (*compare)(void*, void*));

void minheap_free(struct minheap* heap);

void switch_values(void** a, void** b);

#endif
