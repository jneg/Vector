#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector vector;
typedef enum Vector_errors VEC_ERR;

enum Vector_errors
{
    VEC_SUCCESS,
    VEC_MALLOC,
    VEC_REALLOC,
    VEC_NULL,
    VEC_DATA,
    VEC_INDEX
};

struct Vector
{
    size_t cap, len, bs;
    char data[];
};

extern VEC_ERR vec_new(vector **v, size_t bs);
extern VEC_ERR vec_push(vector *v, void *data);
extern VEC_ERR vec_pop(vector *v);
extern VEC_ERR vec_insert(vector *v, size_t index, void *data);
extern VEC_ERR vec_erase(vector *v, size_t index);
extern VEC_ERR vec_shrink(vector *v, size_t newlen);
extern VEC_ERR vec_get(vector *v, size_t index, void *get);
extern VEC_ERR vec_delete(vector **v);
extern void vec_error(VEC_ERR error);

#endif
