#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Vector.h"

#define CAP_MIN 8

struct Vector {
   size_t cap, len, bs;
   char *data;
};

// Iterate through the whole struct vector using
// for (itr = VecBegin(v); itr != VecEnd(v); ++itr)
// where "itr" is a pointer to the correct type.


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
   else if (v->cap > CAP_MIN && v->cap / v->len >= 4) {
      v->cap /= 2;
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
   if (!v) {
      return EXIT_FAILURE;
   }

   *v = calloc(1, sizeof(Vector));
   if (!*v) {
      return EXIT_FAILURE;
   }

   (*v)->bs = bs;
   (*v)->data = NULL;

   return EXIT_SUCCESS;
}

// Adds |data| to the end of |v|.
int VecPush(Vector *v, void *data) {
   if (!v || !data || VecResize(v)) {
      return EXIT_FAILURE;
   }

   memmove(v->data + v->len++ * v->bs, data, v->bs);

   return EXIT_SUCCESS;
}

// Removes the last element from |v|.
int VecPop(Vector *v) {
   if (!v || v->len == 0) {
      return EXIT_FAILURE;
   }

   --v->len;

   return VecResize(v);
}

// Overwrites element at |index| in Vector |v| with |data|.
int VecReplace(Vector *v, size_t index, void *data) { 
   if (!v || !data || index >= v->len || index < 0) {
      return EXIT_FAILURE;
   }

   memmove(v->data + index * v->bs, data, v->bs);
    
   return EXIT_SUCCESS;
}

// Shifts right elements and overwrites element at |index| in Vector |v| with
// |data|.
int VecInsert(Vector *v, size_t index, void *data) {
   if (!v || !data || index > v->len || index < 0 || VecResize(v)) {
      return EXIT_FAILURE;
   }

   memmove(v->data + (index + 1) * v->bs, v->data + index * v->bs,
    (v->len++ - index) * v->bs);
   memmove(v->data + index * v->bs, data, v->bs);

   return EXIT_SUCCESS;
}

// Removes element at |index| in Vector |v| by shifting right elements on top
// of it.
int VecRemove(Vector *v, size_t index) {
   if (!v || index >= v->len || index < 0) {
      return EXIT_FAILURE;
   }

   memmove(v->data + index * v->bs, v->data + (index + 1) * v->bs,
    (--v->len - index) * v->bs);
    
   return VecResize(v);
}

// Copies element at |index| in Vector |v| into |get|.
int VecGet(Vector *v, size_t index, void *get) {
   if (!v || !get || index >= v->len || index < 0) {
      return EXIT_FAILURE;
   }

   memmove(get, v->data + index * v->bs, v->bs);
    
   return EXIT_SUCCESS;
}

// Sets the capacity and length of Vector |v| to 0 and frees the data.
int VecClear(Vector *v) {
   if (!v) {
      return EXIT_FAILURE;
   }

   v->cap = v->len = 0;
   free(v->data);
   v->data = NULL;

   return EXIT_SUCCESS;
}

// Frees Vector |v|.
int VecDelete(Vector **v)
{
   if (!v || VecClear(*v)) {
      return EXIT_FAILURE;
   }

   free(*v);
   *v = NULL;
    
   return EXIT_SUCCESS;
}

// Returns the number of elements of Vector |v|.
int VecSize(Vector *v) {
   return v->len;
}

// Returns the element size of Vector |v|.
int VecElemSize(Vector *v) {
   return v->bs;
}

// Returns the memory capacity of Vector |v|.
int VecCapacity(Vector *v) {
   return v->cap;
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
