#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

vector *vec_new(size_t bs)
{
    if(bs < 0 || bs > 8) {
        perror("New: Invalid byte length");
        exit(EXIT_FAILURE);
    }

    vector *v = malloc(sizeof *v);
    if(!v) {
        perror("Failed to allocate initial vector");
        exit(EXIT_FAILURE);
    }

    v->cap = 0;
    v->len = 0;
    v->bs = bs;

    return v;
}

void vec_push(vector *v, void *data)
{
    if(!v) {
        perror("Push: null vector");
        return;
    }
    
    if(!data) {
        perror("Push: null data");
        return;
    }

    if(v->cap == 0 || v->cap%8 != 0 || v->cap == v->len) {
        if(v->cap == 0 || v->cap%8 != 0) {
            v->cap += (8-v->cap%8);
        } else {
            v->cap *= 2;
        }

        v = realloc(v, sizeof *v + v->cap*v->bs);
        if(!v) {
            perror("Push: realloc failed");
            return;
        }

        memset(v->data + v->len*v->bs, 0, (v->cap-v->len)*v->bs);
    }

    memcpy(v->data + v->len++ * v->bs, data, v->bs);
}

void vec_pop(vector *v)
{
    if(!v) {
        perror("Pop: null vector");
        return;
    }

    if(v->len == 0) {
        perror("Pop: length already zero")
        return;
    }

    memset(v->data + --v->len * v->bs, 0, v->bs);
}

void vec_insert(vector *v, size_t index, void *data)
{ 
    if(!v) {
        perror("Insert: null vector");
        return;
    }

    if(!data) {
        perror("Insert: null data");
        return;
    }

    if(index < 0 || index >= v->len) {
        perror("Insert: index invalid");
        return;
    }

    memcpy(v->data + index*v->bs, data, v->bs);
}

void vec_erase(vector *v, size_t index)
{
    if(!v) {
        perror("Erase: null vector");
        return;
    }

    if(index < 0 || index >= v->len) {
        perror("Erase: index invalid")
        return;
    }

    memset(v->data + index*v->bs, 0, v->bs);
}

void vec_shrink(vector *v, size_t newlen)
{
    if(!v) {
        perror("Shrink: null vector");
        return;
    }

    if(newlen < 0 || newlen >=v->len) {
        perror("Shrink: new length invalid");
        return;
    }

    memset(v->data + newlen*v->bs, 0, (v->len-newlen)*v->bs);

    v->cap = v->len = newlen;
    v = realloc(v, sizeof *v + v->cap*v->bs);
    if(!v) {
        perror("Shrink: realloc failed");
        return;
    }
}

char vec_char(vector *v, size_t index)
{
    if(!v) {
        perror("Char: null vector");
        return '?';
    }

    if(index < 0 || index >= v->len) {
        perror("Char: index invalid")
        return '?';
    }

    return *(v->data + index*v->bs);
}

short vec_short(vector *v, size_t index)
{
    if(!v) {
        perror("Short: null vector");
        return -1;
    }

    if(index < 0 || index >= v->len) {
        perror("Short: index invalid")
        return -1;
    }

    return *(short*)(v->data + index*v->bs);
}

int vec_int(vector *v, size_t index)
{
    if(!v) {
        perror("Int: null vector");
        return -1;
    }

    if(index < 0 || index >= v->len) {
        perror("Int: index invalid")
        return -1;
    }

    return *(int*)(v->data + index*v->bs);
}

long vec_long(vector *v, size_t index)
{
    if(!v) {
        perror("Long: null vector");
        return -1;
    }

    if(index < 0 || index >= v->len) {
        perror("Long: index invalid")
        return -1;
    }

    return *(long*)(v->data + index*v->bs);
}

double vec_double(vector *v, size_t index)
{
    if(!v) {
        perror("Double: null vector");
        return -1.0;
    }

    if(index < 0 || index >= v->len) {
        perror("Double: index invalid")
        return -1.0;
    }

    return *(double*)(v->data + index*v->bs);
}

void vec_del(vector **v)
{
    if(!v || !*v) {
        perror("Delete: null vector");
        return;
    }

    free(*v);
    *v = NULL;
}
