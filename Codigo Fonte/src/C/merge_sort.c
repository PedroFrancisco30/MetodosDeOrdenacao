#include <stdlib.h>
#include <stdatomic.h>
#include "merge_sort.h"

// Intercala dois segmentos já ordenados do array.
// Exposta no header para o paralelo poder chamar após o join das threads.
void mergeIntercalar(int *array, int indxEsq, int meio, int indxDir, atomic_llong *mem) {
    int n = indxDir - indxEsq + 1;

    // Conta os bytes do buffer temporário alocado nesta intercalação
    atomic_fetch_add(mem, (long long)n * sizeof(int));

    int *temp = (int *)malloc(n * sizeof(int));
    if (!temp) return;

    int n1 = meio - indxEsq + 1;

    for (int i = 0; i < n; i++)
        temp[i] = array[indxEsq + i];

    int auxEsq   = 0;
    int auxDir   = n1;
    int auxArray = indxEsq;

    while (auxEsq < n1 && auxDir < n) {
        if (temp[auxEsq] <= temp[auxDir])
            array[auxArray++] = temp[auxEsq++];
        else
            array[auxArray++] = temp[auxDir++];
    }

    while (auxEsq < n1)
        array[auxArray++] = temp[auxEsq++];

    while (auxDir < n)
        array[auxArray++] = temp[auxDir++];

    free(temp);
}

static void mergeSortRec(int *array, int indxEsq, int indxDir, atomic_llong *mem) {
    if (indxEsq < indxDir) {
        int meio = indxEsq + (indxDir - indxEsq) / 2;
        mergeSortRec(array, indxEsq, meio, mem);
        mergeSortRec(array, meio + 1, indxDir, mem);
        mergeIntercalar(array, indxEsq, meio, indxDir, mem);
    }
}

void mergeSort(int *array, int indxEsq, int indxDir, atomic_llong *mem) {
    if (indxEsq >= indxDir) return;
    mergeSortRec(array, indxEsq, indxDir, mem);
}