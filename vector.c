#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

vector *vec_new(size_t bs)
{
   vector *v = malloc(sizeof(*v));
   if(!v) perror("Failed to allocate initial vector");

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
      if(!v) perror("Failed to expand vector memory");
      memset(v->data + v->len*v->bs, 0, (v->cap-v->len)*v->bs);
   }

   memcpy(v->data + v->len++ * v->bs, data, v->bs);
}

void vec_pop(vector *v)
{
   memset(v->data + --v->len * v->bs, 0, v->bs);
}

void vec_ins(vector *v, size_t index, void *data)
{ 
   memcpy(v->data + index*v->bs, data, v->bs);
}

void vec_erase(vector *v, size_t index)
{
   memset(v->data + index*v->bs, 0, v->bs);
}

void vec_shrink(vector *v, size_t newlen)
{
   if(newlen >= v->len)
   {
      perror("Can't shrink when the new length is larger than than vector's length");
      return;
   }

   memset(v->data + newlen*v->bs, 0, (v->len-newlen)*v->bs);

   v->cap = v->len = newlen;
   v = realloc(v, sizeof(*v) + v->cap*v->bs);
   if(!v) perror("Failed to shrink vector");
}

char vec_char(vector *v, size_t index)
{
   return *(v->data + index*v->bs);
}

short vec_short(vector *v, size_t index)
{
   return *(short*)(v->data + index*v->bs);
}

int vec_int(vector *v, size_t index)
{
   return *(int*)(v->data + index*v->bs);
}

long vec_long(vector *v, size_t index)
{
   return *(long*)(v->data + index*v->bs);
}

double vec_double(vector *v, size_t index)
{
   return *(double*)(v->data + index*v->bs);
}

void vec_del(vector **v)
{
   if(!*v)
   {
      perror("Failed to delete nulled vector");
      return;
   }

   free(*v);
   *v = NULL;
   if(*v) perror("Failed to null vector");
}
