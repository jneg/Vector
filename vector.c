#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

vector *vec_init(size_t bs)
{
   vector *v = malloc(sizeof(*v) + 8*bs);
   if(!v) exit(1);

   v->cap = 8;
   v->len = 0;
   v->bs = bs;
   return v;
}

void vec_push(vector *v, void *data)
{
   if(v->cap == v->len)
   {
      v->cap *= 2;

      v = realloc(v, sizeof(*v) + v->cap*v->bs);
      if(!v) exit(1);
      memset(&v->data[v->len*v->bs], 0, (v->cap-v->len)*v->bs);
   }

   memcpy(&v->data[(v->len++)*v->bs], data, v->bs);
}

void vec_pop(vector *v)
{
   memset(&v->data[(--v->len)*v->bs], 0, v->bs);
}

void vec_ins(vector *v, size_t index, void *data)
{
   memcpy(&v->data[index*v->bs], data, v->bs);
}

void vec_del(vector *v, size_t index)
{
   memset(&v->data[index*v->bs], 0, v->bs);
}

size_t vec_get(vector *v, size_t index)
{
   size_t ret;
   memcpy(&ret, &v->data[index*v->bs], v->bs);
   return ret;
}

void vec_empty(vector *v)
{
   memset(&v->data, 0, v->cap*v->bs);
}

void vec_free(vector *v)
{
   free(v);
   if(!v) exit(1);
}
