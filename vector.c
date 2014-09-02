#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

vector *vec_init(size_t bs)
{
   vector *v = malloc(sizeof(*v));
   if(!v)
   {
      perror("Failed to allocate initial vector");
      exit(1);
   }

   v->cap = 0;
   v->len = 0;
   v->bs = bs;
   return v;
}

void vec_push(vector *v, void *data)
{
   if(v->cap == 0 || v->cap%8 != 0 || v->cap == v->len)
   {
      if(v->cap == 0 || v->cap%8 != 0) v->cap += (8-v->cap%8);
      else v->cap *= 2;

      v = realloc(v, sizeof(*v) + v->cap*v->bs);
      if(!v)
      {
         perror("Failed to expand vector memory");
         exit(1);
      }
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

void vec_shrink(vector *v, size_t newlen)
{
   if(newlen >= v->len)
   {
      perror("New length to shrink to was not less than vector's length");
      exit(1);
   }
   memset(&v->data[newlen*v->bs], 0, (v->len-newlen)*v->bs);

   v->cap = v->len = newlen;
   v = realloc(v, sizeof(*v) + v->cap*v->bs);
   if(!v)
   {
      perror("Failed to shrink vector memory");
      exit(1);
   }
}

size_t vec_get(vector *v, size_t index)
{
   size_t ret;
   memcpy(&ret, &v->data[index*v->bs], v->bs);
   return ret;
}

void vec_free(vector **v)
{
   free(*v);
   *v = NULL;
   if(*v)
   {
      perror("Failed to free vector");
      exit(1);
   }
}
