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

## **0.1 The `void* ` data type**

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
## **1.1 Binary Search Trees**

### **Introduction**
The binary tree is one of the most known tree data structures, where each node has at most two children.
The binary search trees adds one more rule: all of the right subtree values must be higher than the root, and the left smaller.  This means that the tree can't store duplicate values.

All of the binary search tree related functions start with bst_
### **Struct Definition**

```c
struct bst_node { 
        struct  bst_node* right;
        struct  bst_node* left;
        void* value;
};
```

The node stores pointers to its childrem and its generic value;

### **Initialization Function**

`struct bst_node* bst_init(void* value, size_t size)`

#### Usage
When declaring a new binary tree, you should type something like `struct bst_node* my_bst=bst_init(&my_value, sizeof(my_data));`
This variable will hold your root node. You must provide a non NULL value, and the size of that value. Then the bst will be initialized with that value as the root. The function tries to make its copy of the data. If there isn't enough memory avalible, it will fail.

#### Implementation

The function asserts that it hasn't recieved an empty value, then tries to allocate memory for the node and its copy of the data. It then initializes the roots values and returns the root.
...

### **Pushing Function**

`void bst_push(struct bst_node* root, void* value, size_t size, bool (*check_equality)(void*, void*), void* (*compare)(void*, void*))`

#### Usage
This function is for pushing values to the bst. You must provide the root, the value you want to push along with its size, and functions for comparing and checking equality (0.3) . You cannot push to an uninitialized tree or try to push an empty value.

#### Implementation

After validating the input, the function searches for the place to insert the new node. If it finds an identical node, it returns, oherwise it creates a new node in the correct location. It uses the `pushed` flag to break out of the loop. 

### **Popping Function**
...

### **Printing Functions**
...

### **Utility Functions**
...

### **Searching Functions**
...

### **Free Functions**
...

