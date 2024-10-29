#include<stdio.h>
#include"minheap.h"
#include"stdlib.h"

void* compare_for_ints(void* a, void* b)
{
        return *(int*)a >= *(int*)b? a:b;
}

bool check_equality_for_ints(void* a, void* b)
{
        return *(int*)a == *(int*)b;
}

void print_for_ints(void* a)
{
        printf("%d ", *(int*)a);
}

int main(void)
{

	struct minheap* heap=minheap_init();
	int a=5;
	int b=15;
	int c=19;
	int d =17;

	minheap_insert(heap, &a, sizeof(int), compare_for_ints);	
	minheap_insert(heap, &b, sizeof(int), compare_for_ints);
	minheap_insert(heap, &c, sizeof(int), compare_for_ints);
        minheap_insert(heap, &d, sizeof(int), compare_for_ints);

	minheap_print(heap, print_for_ints);
	printf("\n");	

	minheap_extract(heap, compare_for_ints);

	minheap_print(heap, print_for_ints);
	printf("\n");	

	int e=19;

	minheap_delete(heap, &e, compare_for_ints, check_equality_for_ints);

	minheap_print(heap, print_for_ints);

	minheap_free(heap);

	return 0;
}
