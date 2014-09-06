#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

VEC_ERR vec_new(vector **v, size_t bs)
{
    *v = malloc(sizeof **v);
    if(!*v)
        return VEC_NULL;

    (*v)->len = (*v)->cap = 0;
    (*v)->bs = bs;

    return VEC_SUCCESS;
}

VEC_ERR vec_push(vector *v, void *data)
{
    if(!v)
        return VEC_NULL;
    
    if(!data)
        return VEC_DATA;

    if(v->cap == 0 || v->cap%8 != 0 || v->cap == v->len) {
        if(v->cap == 0 || v->cap%8 != 0)
            v->cap += (8-v->cap%8);
        else
            v->cap *= 2;

        v = realloc(v, sizeof *v + v->cap*v->bs);
        if(!v)
            return VEC_REALLOC;

        memset(v->data + v->len*v->bs, 0, (v->cap-v->len)*v->bs);
    }

    memcpy(v->data + v->len++ * v->bs, data, v->bs);

    return VEC_SUCCESS;
}

VEC_ERR vec_pop(vector *v)
{
    if(!v)
        return VEC_NULL;

    if(v->len == 0)
        return VEC_INDEX;

    memset(v->data + --v->len*v->bs, 0, v->bs);

    return VEC_SUCCESS;
}

VEC_ERR vec_insert(vector *v, size_t index, void *data)
{ 
    if(!v)
        return VEC_NULL;

    if(!data)
        return VEC_DATA;

    if(index >= v->len)
        return VEC_INDEX;

    memcpy(v->data + index*v->bs, data, v->bs);
    
    return VEC_SUCCESS;
}

VEC_ERR vec_erase(vector *v, size_t index)
{
    if(!v)
        return VEC_NULL;

    if(index >= v->len)
        return VEC_INDEX;

    memset(v->data + index*v->bs, 0, v->bs);
    
    return VEC_SUCCESS;
}

VEC_ERR vec_shrink(vector *v, size_t newlen)
{
    if(!v)
        return VEC_NULL;

    if(newlen >= v->len)
        return VEC_INDEX;

    memset(v->data + newlen*v->bs, 0, (v->len-newlen)*v->bs);

    v->cap = v->len = newlen;
    v = realloc(v, sizeof *v + v->cap*v->bs);
    if(!v)
        return VEC_REALLOC;
    
    return VEC_SUCCESS;
}

VEC_ERR vec_get(vector *v, size_t index, void *get)
{
    if(!v)
        return VEC_NULL;

    if(index >= v->len)
        return VEC_INDEX;

    memcpy(get, v->data + index*v->bs, v->bs);
    
    return VEC_SUCCESS;
}

VEC_ERR vec_del(vector **v)
{
    if(!*v)
        return VEC_NULL;

    free(*v);
    *v = NULL;
    
    return VEC_SUCCESS;
}

void vec_error(VEC_ERR state)
{
    if(state == VEC_SUCCESS) {
        puts("Success");
    } else if(state == VEC_MALLOC) {
        puts("Vector Error: malloc unsuccessful");
    } else if(state == VEC_REALLOC) {
        puts("Vector Error: realloc unsuccessful");
    } else if(state == VEC_NULL) {
        puts("Vector Error: vector passed in was null");
    } else if(state == VEC_DATA) {
        puts("Vector Error: data passed in was null");
    } else if(state == VEC_INDEX) {
        puts("Vector Error: index out of bounds");
    } else {
        puts("State invalid");
    }
}
