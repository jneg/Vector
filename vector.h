#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

enum Vector_errors
{
    VEC_SUCCESS,
    VEC_MALLOC,
    VEC_REALLOC,
    VEC_INDEX
};

struct vector
{
    size_t cap, len, bs;
    char data[];
};

// mallocs struct vector and sets default values
int vec_new(struct vector **const v, size_t size, size_t bs);

// adds element to end and allocates memory if necessary
int vec_push(struct vector **const v, void *data);

// removes last element
int vec_pop(struct vector **const v);

// overwrites element at index with data
int vec_replace(struct vector **const v, size_t index, void *data);

// shifts right elements and overwrites element at index
int vec_insert(struct vector **const v, size_t index, void *data);

// removes element by shifting right elements on top of it
int vec_remove(struct vector **const v, size_t index);

// reallocates memory to new length
int vec_shrink(struct vector **const v, size_t newlen);

// copies element at index into get
int vec_get(struct vector **const v, size_t index, void *get);

// returns iterator to the first element
inline void *vec_begin(struct vector *const v);

// returns iterator to the last element
inline void *vec_end(struct vector *const v);

// frees struct vector
int vec_delete(struct vector **const v);

// returns a string of the error code
const char *vec_error(int error);

#endif
