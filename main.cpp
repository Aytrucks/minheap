#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "heap.h"
#include <iostream>


int main(int argc, char** argv) {
    FILE* fp;
    HEAP* Heap;
    ELEMENT* pELEMENT;
    double key, cap;
    int returnV, flag, calls, position;
    char Word[100];

    if (argc < 4) {
        fprintf(stderr, "Usage: %s <ifile> <ofile> flag\n", argv[0]);
        exit(0);
    }

    /*

    fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "Error: cannot open file %s\n", argv[1]);
        exit(0);
    }
    
    if (!Heap) {
        fprintf(stderr, "Error: calloc failed\n");
        exit(0);
    }
 */
    sscanf(argv[3], "%d", &flag);

    while (1) {
        returnV = nextInstruction(Word,&position, &key, &cap);

        if (returnV == 0) {
            fprintf(stderr, "Warning: Invalid instruction\n");
            continue;
        }


        if (strcmp(Word, "Stop") == 0) {
            return 0;
        }

        if (strcmp(Word, "Init") == 0) {
            
            Heap = (HEAP*)calloc(cap, sizeof(HEAP));

            Init(Heap, cap);
            
            continue;
        }

        if (strcmp(Word, "Print") == 0) {
            printf("%d\n", Heap->size);
            Print(Heap);
            
            continue;
        }

        if (strcmp(Word, "Write") == 0) {
            if (Heap != NULL) {
                fp = fopen(argv[2], "w");
                if (!fp) {
                    fprintf(stderr, "Error: cannot open file %s\n", argv[2]);
                    exit(0);
                }
                fprintf(fp, "%d\n", Heap->size);
                int n = 0;
                while (n < Heap->size) {
                    fprintf(fp, "%lf\n", Heap->H[n]->key);
                    n++;
                }
                fclose(fp);
            }
            else {
                fprintf(stderr, "Error: heap is NULL");
            }
            continue;
        }

        if (strcmp(Word, "Read") == 0) {
            
            fp = fopen(argv[1], "r");
            if (!fp) {
                fprintf(stderr, "Error: cannot open file %s\n", argv[1]);
                exit(0);
            }
            Heap->first = 0;
            Heap->size = 0;
            
            while ((returnV = fscanf(fp, "%lf", &key)) == 1) {
                pELEMENT = new ELEMENT;
                pELEMENT->key = key;
                Heap->H[Heap->size] = pELEMENT;

                if (Heap->first == 0 && key > Heap->capacity) {
                    fprintf(stderr, "Error: capacity too small\n");
                    //fclose(fp);
                    break;
                }

                if (Heap->first != 0) {
                    Heap->size++;
                }
                Heap->first++;
                
            }
            calls = buildHeap(Heap);
            if (flag == 1 && Heap->first != 0) {
                printf("Number of Heapify calls: %d\n",calls-1);
            }
            fclose(fp);
            continue;
            
        }

        if (strcmp(Word, "ExtractMin") == 0) {
            calls = ExtractMin(Heap);
            if (flag == 1) {
                printf("Number of Heapify calls: %d\n", calls);
            }
            continue;
        }

        if (strcmp(Word, "Insert") == 0) {
            heapInsert(Heap, key);
            continue;
        }


        if (strcmp(Word, "DecreaseKey") == 0) {
            heapDecreaseKey(Heap,position, key);
            continue;
        }
    }

    return 1;
}