#ifndef BST_H
#define BST_H

struct bst_node {    
        struct  bst_node *right;
        struct  bst_node *left;
        int value;
};

struct bst_node* bst_init(int value); 
void bst_push(struct bst_node* root, int value);
void bst_pop(struct bst_node** root, int value);
void bst_preorder_print(struct bst_node* root);
void bst_inorder_print(struct bst_node* root);
void bst_postorder_print(struct bst_node* root);
int bst_size(struct bst_node* root); 
int bst_levels(struct bst_node* root); 
int bst_min(struct bst_node* root); 
int bst_max(struct bst_node* root); 
struct bst_node* bst_search(struct bst_node* root, int value); 
struct bst_node* bst_search_parent(struct bst_node* root, int value); 
void bst_free(struct bst_node** root); 

#endif
