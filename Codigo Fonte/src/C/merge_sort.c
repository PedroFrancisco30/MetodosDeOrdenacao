#include <stdlib.h>
#include "merge_sort.h" 

extern long long memoria_alocada_bytes;

void merge(int *array, int indxEsq, int meio, int indxDir) {
    int n1 = meio - indxEsq + 1;
    int n2 = indxDir - meio;

    memoria_alocada_bytes += (n1 + n2) * sizeof(int);

    int *ladoEsq = (int *)malloc(n1 * sizeof(int));
    int *ladoDir = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        ladoEsq[i] = array[indxEsq + i];
       
    for (int i = 0; i < n2; i++)
        ladoDir[i] = array[meio + 1 + i];

    int auxEsq = 0, auxDir = 0, auxArray = indxEsq;

    while (auxEsq < n1 && auxDir < n2) {
        if (ladoEsq[auxEsq] <= ladoDir[auxDir]) {
            array[auxArray] = ladoEsq[auxEsq]; 
            auxEsq++;
        } else {
            array[auxArray] = ladoDir[auxDir];
            auxDir++;
        }
        auxArray++;
    }

    while (auxEsq < n1) {
        array[auxArray] = ladoEsq[auxEsq];
        auxEsq++;
        auxArray++;
    }

    while (auxDir < n2) {
        array[auxArray] = ladoDir[auxDir];
        auxDir++;
        auxArray++;
    }

    free(ladoEsq);
    free(ladoDir);
}

void mergeSort(int *array, int indxEsq, int indxDir) {
    if (indxEsq < indxDir) {
        int meio = indxEsq + (indxDir - indxEsq) / 2; 

        mergeSort(array, indxEsq, meio); 
        mergeSort(array, meio + 1, indxDir); 
        merge(array, indxEsq, meio, indxDir); 
    }
}
