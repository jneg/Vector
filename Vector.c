#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Vector.h"

/*
 * I do not check for pointer validity.

 * Iterate through the whole struct vector using
 * for (itr = vec_begin(v); itr != vec_end(v); ++itr)
 * where "itr" is a pointer to the correct type.
*/

// Sets the capacity of Vector |v| to the minimum capacity if it is 
// lower than the minimum capacity. Otherwise, doubles the capacity of Vector
// |v| if the capacity is equal to the length. Then reallocates the data
// with this new capacity.
static int VecResize(Vector *v) {
   if (v->cap < CAP_MIN) {
      v->cap = CAP_MIN;
   }
   else if (v->cap == v->len) {
      v->cap *= 2;
   }
   else {
      return EXIT_SUCCESS;
   }

   v->data = realloc(v->data, v->cap * v->bs);
   if(!v->data) {
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}

// Allocates Vector |v| with bytes per element |bs|.
int VecNew(Vector **v, size_t bs) {
   *v = calloc(1, sizeof(Vector));
   if (!*v) {
      return EXIT_FAILURE;
   }

   (*v)->bs = bs;

   return EXIT_SUCCESS;
}

// Adds |data| to the end of |v|.
int VecPush(Vector *v, void *data) {
   if (VecResize(v)) {
      return EXIT_FAILURE;
   }

   memcpy(v->data + v->len++ * v->bs, data, v->bs);

   return EXIT_SUCCESS;
}

// Removes the last element from |v|.
int VecPop(Vector *v) {
   if (v->len == 0) {
      return EXIT_FAILURE;
   }

   --v->len;

   return EXIT_SUCCESS;
}

// Overwrites element at |index| in Vector |v| with |data|.
int VecReplace(Vector *v, size_t index, void *data) { 
   if (v->len <= index) {
      return EXIT_FAILURE;
   }

   memcpy(v->data + index * v->bs, data, v->bs);
    
   return EXIT_SUCCESS;
}

// Shifts right elements and overwrites element at |index| in Vector |v| with
// |data|.
int VecInsert(Vector *v, size_t index, void *data) {
   if (v->len <= index || VecResize(v)) {
      return EXIT_FAILURE;
   }

   memcpy(v->data + (index + 1) * v->bs, v->data + index * v->bs,
    (v->len++ - index) * v->bs);
   memcpy(v->data + index * v->bs, data, v->bs);

   return EXIT_SUCCESS;
}

// Removes element at |index| in Vector |v| by shifting right elements on top of it.
int VecRemove(Vector *v, size_t index) {
   if (v->len <= index) {
      return EXIT_FAILURE;
   }

   memcpy(v->data + index * v->bs, v->data + (index + 1) * v->bs,
    (--v->len - index) * v->bs);
    
   return EXIT_SUCCESS;
}

// Copies element at |index| in Vector |v| into |get|.
int VecGet(Vector *v, size_t index, void *get) {
   if (v->len <= index) {
      return EXIT_FAILURE;
   }

   memcpy(get, v->data + index * v->bs, v->bs);
    
   return EXIT_SUCCESS;
}

// Returns an iterator to the first element in Vector |v|.
void *VecBegin(Vector *v)
{
   return v->data;
}

// Returns an iterator to the end of last element in Vector |v|.
void *VecEnd(Vector *v)
{
   return v->data + v->len * v->bs;
}

// Frees Vector |v|.
int VecDelete(Vector *v)
{
   free(v->data);
   free(v);
    
   return EXIT_SUCCESS;
}
