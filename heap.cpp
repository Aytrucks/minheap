#include "heap.h"
#include <iostream>
#include <stdio.h>

int parent(int x) {
	return (x - 1) / 2;
}
int left(int x) {
	return (2 * x + 1);
}
int right(int x) {
	return (2 * x + 2);
}
int hcalls = -1;

void exchange(double *a, double *b) {
	double temp = *a;
	*a = *b;
	*b = temp;
}

int buildHeap(HEAP* heap) {
	hcalls = 0;
	int hsize = heap->size;
	for (int i = hsize / 2 ; i >= 0; i--) {	
		hcalls++;
		Heapify(heap, i);
	}
	return hcalls;
}

void Heapify(HEAP* heap, int x) {
	int l = left(x);
	int r = right(x);
	int smal = x;
	if (l < heap->size && heap->H[l]->key < heap->H[x]->key) {
		smal = l;
	}
	if (r < heap->size && heap->H[r]->key < heap->H[smal]->key) {
		smal = r;
	}
	if (smal != x) {
		exchange(&heap->H[x]->key, &heap->H[smal]->key);
		hcalls++;
		Heapify(heap, smal);
	}
}

void heapDecreaseKey(HEAP* heap, int position, double NewKey) {
	int pos = position - 1;
	heap->H[pos]->key = NewKey;
	while (pos != 0 && heap->H[parent(pos)]->key > heap->H[pos]->key) {
		exchange(&heap->H[pos]->key, &heap->H[parent(pos)]->key);
		pos = parent(pos);
	}
};

int ExtractMin(HEAP* heap){
	if (heap == NULL) {
		std::cerr << "Error: heap is NULL" << std::endl;
		return 1;
	}

	if (heap->size == 0) {
		std::cerr << "Error: heap is empty";
		return 1;
	}
	double key = heap->H[0]->key;

	hcalls = 1;

	if (heap->size == 1) {
		heap->size--;
		fprintf(stdout, "ExtractMin: %lf\n", key);
		return 1;
	}
	
	heap->H[0]->key = heap->H[heap->size - 1]->key;
	heap->size--;
	Heapify(heap,0);

	fprintf(stdout, "ExtractMin: %lf\n", key);
	return hcalls;
}

void Init(HEAP* heap, double cap) {
	heap->size= 0;
	heap->capacity = cap;
	heap->H = (ELEMENT**)calloc(cap, sizeof(ELEMENT*));
}

void Print(HEAP* heap) {
	
	//printf("%d", heap->size);
	if (heap == NULL) {
		std::cout<<"Error: heap is NULL"<<std::endl;
		return;
	}

	for (int i = 0; i < heap->size; i++) {
		printf("%lf\n", heap->H[i]->key);
	}
}

void heapInsert(HEAP* heap, double key) {
	if (heap == NULL) {
		std::cout<<"Error: heap is NULL"<<std::endl;
		return;
	}
	if (heap->size == heap->capacity) {
		//printf("Error: heap is full");
		return;
	}
	ELEMENT* element = (ELEMENT*)calloc(1, sizeof(ELEMENT));
	element->key = key;

	heap->size++;
	int i = heap->size - 1;
	heap->H[i] = element;

	while (i != 0 && heap->H[parent(i)]->key > heap->H[i]->key)
	{
		exchange(&heap->H[i]->key, &heap->H[parent(i)]->key);
		i = parent(i);

	}
}



