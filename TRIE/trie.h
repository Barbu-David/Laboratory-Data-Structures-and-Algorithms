#ifndef TRIE_H
#define TRIE_H

#define ALPHABET_SIZE 27
#define SPACE_INDEX 26
#include<stdbool.h>

struct trie_node {
	
	struct trie_node* children[ALPHABET_SIZE];
	bool end_flag;
};

struct trie_node* trie_init(void);

bool trie_search(struct trie_node* root, char* word, int word_size);
void trie_insert(struct trie_node* root, char* word, int word_size);
void trie_delete(struct trie_node* root, char* word, int word_size, int depth);

bool trie_empty(struct trie_node* root);
void trie_print(struct trie_node* root);

void trie_free(struct trie_node* root);

#endif
