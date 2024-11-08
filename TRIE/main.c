#include"trie.h"
#include<stdio.h>

int main(void)
{
	struct trie_node* trie=trie_init();

	if(trie_empty(trie)) printf("Empty trie\n");

	char dog[3];
 	dog[0]='d';
	dog[1]='o';
	dog[2]='g';

	trie_insert(trie, dog, 3);
	if(trie_search(trie, dog, 3)) printf("dog inserted\n");

	char cut[7];
 	cut[0]='c';
	cut[1]='u';
	cut[2]='t';
	cut[3]='t';
	cut[4]='i';
	cut[5]='n';
	cut[6]='g';	

	trie_insert(trie, cut, 3);
	if(trie_search(trie, cut, 3)) printf("cut inserted\n");

	trie_insert(trie, cut, 7);
	if(trie_search(trie, cut, 7)) printf("cutting inserted\n");

	cut[4]='e';
	cut[5]='r';	

	trie_insert(trie, cut, 6);
	if(trie_search(trie, cut, 6)) printf("cutter inserted\n");

	trie_print(trie);

	trie_delete(trie, cut, 3, 0);
	if(!trie_search(trie, cut, 3)) printf("cut deleted\n");
	trie_print(trie);

	trie_delete(trie, cut, 6, 0);
	if(!trie_search(trie, cut, 6)) printf("cutter deleted\n");
	trie_print(trie);

	trie_free(trie);

	return 0;
}
