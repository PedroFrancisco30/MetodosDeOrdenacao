#ifndef MERGE_SORT_H
#define MERGE_SORT_H
 
#include <stdatomic.h>
 
void mergeSort(int *array, int indxEsq, int indxDir, atomic_llong *mem);
void mergeIntercalar(int *array, int indxEsq, int meio, int indxDir, atomic_llong *mem);
 
#endif
 