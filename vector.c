#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

// mallocs vector and sets default values
int vec_new(vector **v, size_t bs)
{
    *v = malloc(sizeof **v);
    if(!*v)
        return VEC_MALLOC;

    (*v)->len = (*v)->cap = 0;
    (*v)->bs = bs;

    return VEC_SUCCESS;
}

// adds element to end and allocates memory if necessary
int vec_push(vector *v, void *data)
{
    if(v->cap == 0 || v->cap%8 != 0 || v->cap == v->len) {
        if(v->cap == 0 || v->cap%8 != 0)
            v->cap += (8-v->cap%8);
        else
            v->cap *= 2;

        v = realloc(v, sizeof *v + v->cap*v->bs);
        if(!v)
            return VEC_REALLOC;
    }

    memcpy(v->data + v->len++*v->bs, data, v->bs);

    return VEC_SUCCESS;
}

// removes end element
int vec_pop(vector *v)
{
    if(v->len == 0)
        return VEC_INDEX;

    --v->len;

    return VEC_SUCCESS;
}

// overwrites element at index with data
int vec_insert(vector *v, size_t index, void *data)
{ 
    if(index >= v->len)
        return VEC_INDEX;

    memcpy(v->data + index*v->bs, data, v->bs);
    
    return VEC_SUCCESS;
}

// removes element by shifting right elements on top of it
int vec_erase(vector *v, size_t index)
{
    if(index >= v->len)
        return VEC_INDEX;

    memcpy(v->data + index*v->bs, v->data + (index + 1)*v->bs, (--v->len - index)*v->bs);
    
    return VEC_SUCCESS;
}

// deallocates memory until new length
int vec_shrink(vector *v, size_t newlen)
{
    if(newlen >= v->len)
        return VEC_INDEX;

    v->cap = v->len = newlen;
    v = realloc(v, sizeof *v + v->cap*v->bs);
    if(!v)
        return VEC_REALLOC;
    
    return VEC_SUCCESS;
}

// copies element at index into get
int vec_get(vector *v, size_t index, void *get)
{
    if(index >= v->len)
        return VEC_INDEX;

    memcpy(get, v->data + index*v->bs, v->bs);
    
    return VEC_SUCCESS;
}

// returns iterator to the first element
void *vec_begin(vector *v)
{
    return v->data;
}

// returns iterator to the end of last element
void *vec_end(vector *v)
{
    return v->data + v->len*v->bs;
}

// frees vector
int vec_delete(vector **v)
{
    free(*v);
    *v = NULL;
    
    return VEC_SUCCESS;
}

// returns a string of the error code
const char *vec_error(int state)
{
    if(state == VEC_SUCCESS)
        return "Success";
    else if(state == VEC_MALLOC)
        return "Vector Error: malloc unsuccessful";
    else if(state == VEC_REALLOC)
        return "Vector Error: realloc unsuccessful";
    else if(state == VEC_INDEX)
        return "Vector Error: index out of bounds";
    else
        return "State invalid";
}
