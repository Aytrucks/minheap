#ifndef _heap_h
#define _heap_h 1
#include "data_structures.h"

int parent(int x);
int left(int x);
int right(int x);

void Heapify(HEAP* heap, int x);
void exchange(double* a, double* b);

void Print(HEAP *);
void Init(HEAP *, double cap);
void heapInsert(HEAP *, double key);
int ExtractMin(HEAP *);
void heapDecreaseKey(HEAP *, int position, double NewKey);
int buildHeap(HEAP* heap);


#endif