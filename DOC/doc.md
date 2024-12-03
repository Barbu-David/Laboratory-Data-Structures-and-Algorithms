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

The best way to program generics in C is probably the `void*`. It is a pointer that doesn't know what data it is pointing to. Unlike normal pointers, `void*` can not be derefferenced directly. Instead, it must be cast to another pointer type first.
 Since `void*` doesn't know the type of data it is pointing to, for most functions to be useful, the size of the data block must be provided. One example of` void*` being used in a such a manner is the `qsort()` function from stdlib. This data type is also used for most of the implementations here, except special cases like the trie tree.

## **0.2 Memory management**

This library aims to not interfeer with your memory management. Even tough you need to provide pointers to the data you want to manage, you don't need to preserve that data in any way after providing it. The data structures store their own copy of the data, and do not affect yours. Each data structure must be initialized before use, and freed after use, using their own init and free functions. However, in some special cases, like extracting from a binary heap, the data structure will provide you with a pointer that you have to manage, since the local copy has been handed over to you.

## **0.3 Generic functions**

For managing your generic data, you will be asked to provide generic functions comparing, printing, and checkinging equality.
The comparison funtion works in a non standard way. Instead of returning an integer like standard c comparison functions, it should return the pointer to the value considered larger or equal. This function doesn't check strict equality, that job goes to another function. 
This approach deviates from the norm of returning 1, 0 or -1. The reason for this change is the existance of data types where two instances with the same value may be considered distinct from each other. (For example you use a persons age for comparison, but if they have the same age, that doesn't mean they are the same person).

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

### **Struct Definition**



### **Initialization Function**
...

### **Pushing Function**
...

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

