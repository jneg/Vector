#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector Vector;

// Allocates Vector |v| with bytes per element |bs|.
int VecNew(Vector **v, size_t bs);

// Adds element to end of Vector |v|.
int VecPush(Vector *v, void *data);

// Removes last element in Vector |v|.
int VecPop(Vector *v);

// Overwrites element at |index| with |data| in Vector |v|.
int VecReplace(Vector *v, size_t index, void *data);

// Shifts right elements then overwrites element at |index| with |data| in
// Vector |v|.
int VecInsert(Vector *v, size_t index, void *data);

// Removes element at |index| in Vector |v|.
int VecRemove(Vector *v, size_t index);

// Copies |get| into Vector |v| at |index|.
int VecGet(Vector *v, size_t index, void *get);

// Removes all elements in Vector |v|.
int VecClear(Vector *v);

// Clears and frees Vector |v|.
int VecDelete(Vector **v);

// Returns the number of elements of Vector |v|.
int VecSize(Vector *v);

// Returns the element size of Vector |v|.
int VecElemSize(Vector *v);

// Returns the memory capacity of Vector |v|.
int VecCapacity(Vector *v);

// Returns an iterator to the first element of Vector |v|.
void *VecBegin(Vector *v);

// Returns an iterator to the last element of Vector |v|.
void *VecEnd(Vector *v);

#endif
