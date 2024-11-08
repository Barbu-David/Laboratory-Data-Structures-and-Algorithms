#include"trie.h"
#include<stdlib.h>
#include<stdio.h>

struct trie_node* trie_init(void)
{
	struct trie_node* new_node=malloc(sizeof(struct trie_node));
	for(int i=0; i<ALPHABET_SIZE; i++) new_node->children[i]=NULL;
	new_node->end_flag=false;

	return new_node;
}

bool trie_empty(struct trie_node* root)
{
	for(int i=0;i<ALPHABET_SIZE;i++)
		if(root->children[i]!=NULL) return false;

	return true;
}

void trie_print_word(struct trie_node* root, char* word, int word_size)
{
	char* new_word;
	if(word_size==0) {
		new_word=malloc(sizeof(char));
	}
	else {
		new_word=malloc(sizeof(char)*(word_size+1));
		for(int i=0; i<word_size; i++) new_word[i]=word[i];
	}

	
	for(int j=0; j<ALPHABET_SIZE; j++) {
		
		if(root->children[j]!=NULL) {
			
			(j==SPACE_INDEX)? (new_word[word_size]=' ') : (new_word[word_size]=(char)('a'+j));	
			if(root->children[j]->end_flag) {
				for(int k=0; k<=word_size; k++) printf("%c",new_word[k]);
				printf("\n");
			}
			trie_print_word(root->children[j], new_word, word_size+1);
		}
			
	}

	free(new_word);	

}
void trie_print(struct trie_node* root)
{
	trie_print_word(root, NULL, 0);	
}

bool trie_search(struct trie_node* root, char* word, int word_size)
{
	for(int i=0; i<word_size; i++) {
		int index;
		if(word[i]==' ') index=SPACE_INDEX;
		else index=word[i]-'a';

		if(root->children[index]==NULL) return false;

		root=root->children[index];
	}

	return root->end_flag;
	
}

void trie_insert(struct trie_node* root, char* word, int word_size)
{
	for(int i=0; i<word_size; i++) {
		int index;
		if(word[i]==' ') index=SPACE_INDEX;
		else index=word[i]-'a';

		if(root->children[index]==NULL) root->children[index]=trie_init();

		root=root->children[index];
	}
	
	root->end_flag=true;
}

void trie_delete(struct trie_node* root, char* word, int word_size, int depth)
{

}

void trie_free(struct trie_node* root)
{
	if(root!=NULL) {
		for(int i=0; i<ALPHABET_SIZE; i++) trie_free(root->children[i]);
		free(root);
		root=NULL;
	}
}
