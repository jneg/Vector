typedef struct Vector vector;

struct Vector
{
   size_t cap, len, bs;
   char data[];
};

extern vector *vec_new(size_t bs);
extern void vec_push(vector *v, void *data);
extern void vec_pop(vector *v);
extern void vec_ins(vector *v, size_t index, void *data);
extern void vec_erase(vector *v, size_t index);
extern void vec_shrink(vector *v, size_t newlen);
extern char vec_char(vector *v, size_t index);
extern short vec_short(vector *v, size_t index);
extern int vec_int(vector *v, size_t index);
extern long vec_long(vector *v, size_t index);
extern double vec_double(vector *v, size_t index);
extern void vec_del(vector **v);
