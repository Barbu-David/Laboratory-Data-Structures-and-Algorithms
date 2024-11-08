#include<stdio.h>
#include"splay.h"

struct person{
	char initial;
	int age;
};

void* compare_for_pers(void* a, void* b) 
{
	return ((*(struct person*)a).age >= (*(struct person*)b).age) ? a : b;
}

bool check_equality_for_pers(void* a, void* b) 
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
	return 0;
}
