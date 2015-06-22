#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

#define CAP_MIN 8

typedef struct Vector
{
    size_t cap, len, bs;
    char *data;
} Vector;

// Mallocs a Vector |v| and sets default values
int VecNew(Vector **v, size_t bs);

// Adds element to end of |v| and allocates memory if necessary
int VecPush(Vector *v, void *data);

// Removes last element
int VecPop(Vector *v);

// Overwrites element at index with data
int VecReplace(Vector *v, size_t index, void *data);

// Shifts right elements and overwrites element at index
int VecInsert(Vector *v, size_t index, void *data);

// Removes element by shifting right elements on top of it
int VecRemove(Vector *v, size_t index);

// Reallocates memory to new length
int VecShrink(Vector *v, size_t newlen);

// Copies element at index into get
int VecGet(Vector *v, size_t index, void *get);

// Returns iterator to the first element
void *VecBegin(Vector *v);

// Returns iterator to the last element
void *VecEnd(Vector *v);

// Frees struct vector
int VecDelete(Vector *v);

#endif
