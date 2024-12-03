# **David's Algorithms and Data Structures Library (dads_lib)**

This library was made for UCV's Data Structures and Algorithms course. It aims to implement popular algorithms and data structures in C in a highly optimized and bug-free manner using generic data types.

## **Contents**

### **Part 0**
- 0.1 The void* data type
- 0.2 Memory management
- 0.3 Generic functions

### **Part 1: Trees**
- 1.1 Binary Search Trees
- 1.2 Binary Heap
- 1.3 Height Balanced Trees
  - 1.3.1 AVL Trees
  - 1.3.2 Red-Black Trees
- 1.4 Splay Trees
- 1.5 Trie Trees
- 1.6 B-Trees

### **Part 2: Graphs**
- (Coming Soon)

## **0.1 The ` void* ` data type**

The best way to program generics in C is probably the `void*`. It is a pointer that doesn't know what data it is pointing to. Unlike normal pointers, `void*` can not be dereferenced directly. Instead, it must be cast to another pointer type first.
 Since `void*` doesn't know the type of data it is pointing to, for most functions to be useful, the size of the data block must be provided. One example of` void*` being used in such a manner is the `qsort()` function from stdlib. This data type is also used for most of the implementations here, except special cases like the trie tree.

## **0.2 Memory management**

This library aims to not interfere with your memory management. Even though you need to provide pointers to the data you want to manage, you don't need to preserve that data in any way after providing it. The data structures store their own deep copy of the data, and do not affect yours. Each data structure must be initialized before use, and freed after use, using their own init and free functions. However, in some special cases, like extracting from a binary heap, the data structure will provide you with a pointer that you have to manage, since the local copy has been handed over to you.

## **0.3 Generic functions**

For managing your generic data, you will be asked to provide generic functions comparing, printing, and checking equality.
The comparison function works in a non standard way. Instead of returning an integer like standard c comparison functions, it should return the pointer to the value considered larger or equal. This function doesn't check strict equality, that job goes to another function. 
This approach deviates from the norm of returning 1, 0 or -1. The reason for this change is the existence of data types where two instances with the same value may be considered distinct from each other. (For example you may use a persons age for comparison, but if they have the same age, that doesn't mean they are the same person).

Here is an example:
```c

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


```
## **1.1 Binary Search Tree**

### **Introduction**
The binary tree is one of the most known tree data structures, where each node has at most two children.
The binary search tree adds one more rule: all of the right subtree values must be higher than the root, and the left smaller.  This means that the tree can't store duplicate values.

All of the binary search tree related functions start with bst_
### **Struct Definition**

```c
struct bst_node { 
        struct  bst_node* right;
        struct  bst_node* left;
        void* value;
};
```

The node stores pointers to its children and its generic value;

### **Initialization Function**

`struct bst_node* bst_init(void* value, size_t size)`

#### Usage
When declaring a new binary tree, you should type something like `struct bst_node* my_bst=bst_init(&my_value, sizeof(my_data));`
This variable will hold your root node. You must provide a non NULL value, and the size of that value. Then the bst will be initialized with that value as the root. The function tries to make its copy of the data. If there isn't enough memory avalible, it will fail.

#### Implementation

The function asserts that it hasn't recieved an empty value, then tries to allocate memory for the node and its copy of the data. It then initializes the roots values and returns the root.

### **Pushing Function**

`void bst_push(struct bst_node* root, void* value, size_t size, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*))`

#### Usage

This function is for pushing values to the bst. You must provide the root, the value you want to push along with its size, and functions for comparing and checking equality (0.3) . You cannot push to an uninitialized tree or try to push an empty value.

#### Implementation

After validating the input, the function searches for the place to insert the new node. If it finds an identical node, it returns, otherwise it creates a new node in the correct location. It uses the `pushed` flag to break out of the loop. 

### **Popping Function**

`void bst_pop(struct bst_node** root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*))`

#### Usage

The header is similar to the push function and the same conditions apply, except we must provide a pointer to the root. If the value is not found, the tree remains unchanged, otherwise it is removed.

#### Implementation
After validating the input we search for the target and it's paret. Since we need to search for both, we do not use a normal searech function. We first find the parent of the value, and then its child with the proper value.

The reason the parent is also needed is the need for updating its pointers.
If the target can't be found, the function returns. Otherwise there are 3 cases.
In the first 2, the root may change. Because of this, the value of the root pointer from the caller must also change. This is why the function needs a pointer to the root, since we need to modify the real pointer value, not out local copy of it.

In the first case, there are no children. Here the target is replaced with NULL and then freed. If the removed function is the root, the tree must be initialized again. The parents pointers are also updated. 

In the second case, there is only one child (there is one code block for the left child and one for the right child) Here the parent inherits that child and the target gets freed.

In the case with both children present, the function searches for the successor and switches its values with the target. Then it removes the successor in a similar way to the second case.

### **Printing Functions**
```c
void bst_preorder_print(struct bst_node* root, void (*print)(void*));
void bst_inorder_print(struct bst_node* root, void (*print)(void*));
void bst_postorder_print(struct bst_node* root, void (*print)(void*));
```
Pass the root and your print function. The values will be printed in the specified order. With inorder print, they should always be sorted.
The implementation is recursive, calling the print function in the specified order.

### **Utility Functions**
```c
int bst_size(struct bst_node* root); 
int bst_levels(struct bst_node* root); 
void* bst_min(struct bst_node* root); 
void* bst_max(struct bst_node* root);
```

These functions are not necessary, but usefull to have. They return information about the tree and only require the root.

### **Searching Functions**
`struct bst_node* bst_search_child_with_value(struct bst_node* root, void* value, bool (*check_equality)(void*, void*));`

This function takes as input a node and the equality function. It checks if the node has a child with a certain value, and then returns it. If it doesn't find such a child, it returns NULL.

`struct bst_node* bst_search_parent(struct bst_node* root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*));`

This function returns the parent of the node with a certain value. When there is a need for both the child and its parent, these two functions should be used together.

`struct bst_node* bst_search(struct bst_node* root, void* value, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*));
`
This function combines the two from the above in order to return a node with a certain value.
```c
struct bst_node* bst_successor_parent(struct bst_node* root);
struct bst_node* bst_predecessor_parent(struct bst_node* root);
struct bst_node* bst_successor(struct bst_node* root);
struct bst_node* bst_predecessor(struct bst_node* root);
```

Finds the successor or predecessor of a node. There are also functions for finding their parents.

### **Free Function**

`void bst_free(struct bst_node** root)`

Since the root will be freed as well, the function needs a pointer to it. After that the function recursevily frees all of the tree.

## **1.3.1 AVL Tree**

### Introduction
From the outside, the avl tree functions like a normal tree. However, the AVL structure ensures that the tree is balanced, making insertion/deletion/traversal faster. The way it achieves this is trough the use of a balance factor.

The avl related functions start with avl_ .

Most of the functions are similar to the bst ones, with the searching and utilities functions remaining unchanged. The major difference is in in the push/pop functions. The functions rebalance the tree after each change. Also, since the root may change due to a rotation, the push function also requires a pointer to root.

### Struct definition
```c
struct avl_node { 
        struct  avl_node *right;
        struct  avl_node *left;
        int balance_factor;
        void* value;
};
```

The node differs from bst by including the balance factor.

### Balance factor
`int avl_node_balance_factor(struct avl_node* root)`
This function is used for calculating the balance factor of a node. It is equal to the difference between the levels of the right and the left subtree.

### Rotations

```c
struct avl_node* avl_left_rotate(struct avl_node* root)
struct avl_node* avl_right_rotate(struct avl_node* root)
struct avl_node* avl_right_left_rotate(struct avl_node* root)
struct avl_node* avl_left_right_rotate(struct avl_node* root)
```

The rotations are used to rebalance the tree. The "rotation" is in reality just a swap. In the left rotation the right child is swaped with the root. After this the balance factor is updated. The left rotation is symetric.

Combined rotations are just a series of base rotations.

### Balancing

`struct avl_node* avl_balance(struct avl_node* root)`
 
The balance function work by treating all 4 rotation cases. The sign of the balance factor chooses between two groups of two cases. After that using some varibles we compare the factors of the grandchildren. Based on that one case is chosen from the remaining two.
