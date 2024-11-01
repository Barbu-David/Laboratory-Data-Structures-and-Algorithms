#include<stdio.h>
#include"minheap.h"
#include<stdlib.h>

struct person{
        char initial;
        int age;
};

void* compare_for_pers(void* a, void* b)
{
        return ((*(struct person*)a).age >= (*(struct person*)b).age) ? a : b;
}

bool check_eperson_arrayuality_for_pers(void* a, void* b)
{
        return ((*(struct person*)a).age == (*(struct person*)b).age);
}

void print_for_pers(void* a)
{
        printf("%c ", (*(struct person*)a).initial);
}

void* compare_for_ints(void* a, void* b)
{
        return *(int*)a >= *(int*)b? a:b;
}

bool check_eperson_arrayuality_for_ints(void* a, void* b)
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
	int a[6];
	a[0]=10;
	a[1]=17;
	a[2]=13;
	a[3]=8;
	a[4]=20;
	a[5]=1;
	
	minheap_insert(heap, &a[0], sizeof(int), compare_for_ints);	
	minheap_insert(heap, &a[1], sizeof(int), compare_for_ints);
	minheap_insert(heap, &a[2], sizeof(int), compare_for_ints);
        minheap_insert(heap, &a[3], sizeof(int), compare_for_ints);
        minheap_insert(heap, &a[4], sizeof(int), compare_for_ints);
        minheap_insert(heap, &a[5], sizeof(int), compare_for_ints);

	minheap_print(heap, print_for_ints);
	printf("\n");	

	free(minheap_extract(heap, compare_for_ints));

	minheap_print(heap, print_for_ints);
	printf("\n");	

	int e=13;

	minheap_delete(heap, &e, sizeof(int), compare_for_ints, check_eperson_arrayuality_for_ints);

	minheap_print(heap, print_for_ints);
	printf("\n");

	minheap_free(heap);

	struct person p[3];
	p[0].age=30;
	p[0].initial='a';

	p[1].age=35;
	p[1].initial='b';

	p[2].age=25;
	p[2].initial='c';

	void** person_array=malloc(sizeof(void*)*4);
	int i;
	for(i=0; i<3; i++) person_array[i]=&p[i];

	minheap_heapify_array(person_array, 3, compare_for_pers);
	
	struct minheap* heap2=minheap_init_from_array(person_array, 3, sizeof(struct person));
	
	minheap_print(heap2, print_for_pers);
	printf("\n");
	minheap_delete(heap2, &p[2], sizeof(struct person),compare_for_pers, check_eperson_arrayuality_for_pers);

	minheap_print(heap2, print_for_pers);
	printf("\nYoungest: %d\n",(*(struct person*)(minheap_findmin(heap2))).age);
	minheap_free(heap2);
	free(person_array);	

	return 0;
}
