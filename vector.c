#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

// Note: I do not check for null pointers,
// check for them yourself

// Note: iterate through the whole struct vector using
// for(it = vec_begin(v); it != vec_end(v); ++it)
// where "it" is a pointer to the correct type

// allocates more memory if necessary
static int vec_alloc(struct vector **v)
{
    if((*v)->cap < 16 || (*v)->cap == (*v)->len) {
        if((*v)->cap < 16)
            (*v)->cap = 16;
        else
            (*v)->cap *= 2;

        *v = realloc(*v, sizeof **v + (*v)->cap * (*v)->bs);
        if(!*v)
            return VEC_REALLOC;
    }

    return VEC_SUCCESS;
}

// mallocs struct vector and sets default values
int vec_new(struct vector **v, size_t bs)
{
    *v = malloc(sizeof **v);
    if(!*v)
        return VEC_MALLOC;

    (*v)->len = (*v)->cap = 0;
    (*v)->bs = bs;

    return VEC_SUCCESS;
}

// adds element to end and allocates memory if necessary
int vec_push(struct vector **v, void *data)
{
    if(vec_alloc(v) == VEC_REALLOC)
        return VEC_REALLOC;

    memcpy((*v)->data + (*v)->len++ * (*v)->bs, data, (*v)->bs);

    return VEC_SUCCESS;
}

// removes last element
int vec_pop(struct vector **v)
{
    if((*v)->len == 0)
        return VEC_INDEX;

    --(*v)->len;

    return VEC_SUCCESS;
}

// overwrites element at index with data
int vec_replace(struct vector **v, size_t index, void *data)
{ 
    if(index >= (*v)->len)
        return VEC_INDEX;

    memcpy((*v)->data + index * (*v)->bs, data, (*v)->bs);
    
    return VEC_SUCCESS;
}

// shifts right elements and overwrites element at index
int vec_insert(struct vector **v, size_t index, void *data)
{
    if(index >= (*v)->len)
        return VEC_INDEX;

    if(vec_alloc(v) == VEC_REALLOC)
        return VEC_REALLOC;

    memcpy((*v)->data + (index + 1) * (*v)->bs, (*v)->data + index * (*v)->bs, ((*v)->len++ - index) * (*v)->bs);
    memcpy((*v)->data + index * (*v)->bs, data, (*v)->bs);

    return VEC_SUCCESS;
}

// removes element by shifting right elements on top of it
int vec_remove(struct vector **v, size_t index)
{
    if(index >= (*v)->len)
        return VEC_INDEX;

    memcpy((*v)->data + index * (*v)->bs, (*v)->data + (index + 1) * (*v)->bs, (--(*v)->len - index) * (*v)->bs);
    
    return VEC_SUCCESS;
}

// deallocates memory until new length
int vec_shrink(struct vector **v, size_t newlen)
{
    if(newlen >= (*v)->len)
        return VEC_INDEX;

    (*v)->cap = (*v)->len = newlen;
    *v = realloc(*v, sizeof **v + (*v)->cap * (*v)->bs);
    if(!*v)
        return VEC_REALLOC;
    
    return VEC_SUCCESS;
}

// copies element at index into get
int vec_get(struct vector **v, size_t index, void *get)
{
    if(index >= (*v)->len)
        return VEC_INDEX;

    memcpy(get, (*v)->data + index * (*v)->bs, (*v)->bs);
    
    return VEC_SUCCESS;
}

// returns iterator to the first element
void *vec_begin(struct vector *v)
{
    return v->data;
}

// returns iterator to the end of last element
void *vec_end(struct vector *v)
{
    return v->data + v->len * v->bs;
}

// frees struct vector
int vec_delete(struct vector **v)
{
    free(*v);
    *v = NULL;
    
    return VEC_SUCCESS;
}

// returns a string of the error code
// enjoy your memory leaks
const char *vec_error(int state)
{
    if(state == VEC_SUCCESS) {
        return strdup("Success");
    } else if(state == VEC_MALLOC) {
        return strdup("Failed to malloc struct vector!");
    } else if(state == VEC_REALLOC) {
        return strdup("Failed to realloc struct vector!");
    } else if(state == VEC_INDEX) {
        return strdup("Index out of bounds!");
    } else {
        return strdup("Invalid state");
    }
}
