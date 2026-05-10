#include <stdlib.h>
#include "merge_sort.h"

extern long long memoria_alocada_bytes;

static void merge(int *array, int *temp, int indxEsq, int meio, int indxDir) {
    int n1 = meio - indxEsq + 1;
    int n2 = indxDir - meio;
    int n  = n1 + n2;

    for (int i = 0; i < n; i++)
        temp[i] = array[indxEsq + i];

    int auxEsq   = 0;
    int auxDir   = n1;
    int auxArray = indxEsq;

    while (auxEsq < n1 && auxDir < n1 + n2) {
        if (temp[auxEsq] <= temp[auxDir])
            array[auxArray++] = temp[auxEsq++];
        else
            array[auxArray++] = temp[auxDir++];
    }

    while (auxEsq < n1)
        array[auxArray++] = temp[auxEsq++];

    while (auxDir < n1 + n2)
        array[auxArray++] = temp[auxDir++];
}

static void mergeSortRec(int *array, int *temp, int indxEsq, int indxDir) {
    if (indxEsq < indxDir) {
        int meio = indxEsq + (indxDir - indxEsq) / 2;
        mergeSortRec(array, temp, indxEsq, meio);
        mergeSortRec(array, temp, meio + 1, indxDir);
        merge(array, temp, indxEsq, meio, indxDir);
    }
}

void mergeSort(int *array, int indxEsq, int indxDir) {
    if (indxEsq >= indxDir) return;

    int n = indxDir - indxEsq + 1;
    memoria_alocada_bytes += n * sizeof(int);

    int *temp = (int *)malloc(n * sizeof(int));
    if (!temp) return;

    mergeSortRec(array, temp, indxEsq, indxDir);
    free(temp);
}