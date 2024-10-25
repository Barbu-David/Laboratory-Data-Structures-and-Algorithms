#ifndef MINHEAP_H
#define MINHEAP_H

struct minheap {
		int* values;
		long unsigned size, capacity;
};		

void switch_values(int* a, int* b);
struct minheap* minheap_init();
void minheap_insert(struct minheap* heap, int value);
void minheap_print(struct minheap* heap);
int minheap_extract(struct minheap* heap);
int minheap_findmin(struct minheap* heap);
struct minheap* minheap_heapify(int* future_heap, int size);
void minheap_delete(struct minheap* heap, int value);
void minheap_free(struct minheap* heap);

#endif
