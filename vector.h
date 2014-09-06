#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector vector;

enum Vector_errors
{
    VEC_SUCCESS,
    VEC_MALLOC,
    VEC_REALLOC,
    VEC_INDEX
};

struct Vector
{
    size_t cap, len, bs;
    char data[];
};

int vec_new(vector **v, size_t bs);
int vec_push(vector **v, void *data);
int vec_pop(vector **v);
int vec_replace(vector **v, size_t index, void *data);
int vec_insert(vector **v, size_t index, void *data);
int vec_remove(vector **v, size_t index);
int vec_shrink(vector **v, size_t newlen);
int vec_get(vector **v, size_t index, void *get);
void *vec_begin(vector *v);
void *vec_end(vector *v);
int vec_delete(vector **v);
const char *vec_error(int error);

#endif
