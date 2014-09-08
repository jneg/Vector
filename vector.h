#ifndef VECTOR_H
#define VECTOR_H

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

int vec_new(struct vector **const v, size_t bs);
int vec_push(struct vector **const v, void *data);
int vec_pop(struct vector **const v);
int vec_replace(struct vector **const v, size_t index, void *data);
int vec_insert(struct vector **const v, size_t index, void *data);
int vec_remove(struct vector **const v, size_t index);
int vec_shrink(struct vector **const v, size_t newlen);
int vec_get(struct vector **const v, size_t index, void *get);
void *vec_begin(struct vector *const v);
void *vec_end(struct vector *const v);
int vec_delete(struct vector **const v);
const char *vec_error(int error);

#endif
