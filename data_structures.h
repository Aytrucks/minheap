#ifndef _data_structures_h
#define _data_structures_h 1

typedef struct TAG_ELEMENT {
    double key;
}ELEMENT;

typedef struct TAG_HEAP {
    int capacity; //max size of heap
    int size; //how many elements are in heap
    ELEMENT** H;
    int first = 0;

}HEAP;

#endif