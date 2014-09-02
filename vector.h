struct Vector
{
   size_t cap, len, bs;
   char data[];
};

typedef struct Vector vector;

extern vector *vec_init(size_t bs);
extern void vec_push(vector *v, void *data);
extern void vec_pop(vector *v);
extern void vec_ins(vector *v, size_t index, void *data);
extern void vec_del(vector *v, size_t index);
extern size_t vec_get(vector *v, size_t index);
extern void vec_empty(vector *v);
extern void vec_free(vector *v);
