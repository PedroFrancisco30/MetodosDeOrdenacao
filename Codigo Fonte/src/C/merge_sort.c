#include <stdlib.h>

// Função Merge (Mescla)
void merge(int *array, int indxEsq, int meio, int indxDir) {
    int n1 = meio - indxEsq + 1;
    int n2 = indxDir - meio;

    // Alocação dinâmica equivalente a new ArrayList<>() / array_slice
    int *ladoEsq = (int *)malloc(n1 * sizeof(int));
    int *ladoDir = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        ladoEsq[i] = array[indxEsq + i];
       
    for (int i = 0; i < n2; i++)
        ladoDir[i] = array[meio + 1 + i];

    int auxEsq = 0, auxDir = 0, auxArray = indxEsq;

    // Enquanto os dois não chegarem ao limite
    while (auxEsq < n1 && auxDir < n2) {
        if (ladoEsq[auxEsq] <= ladoDir[auxDir]) {
            array[auxArray] = ladoEsq[auxEsq]; // Joga o elemento pro outro lado
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

    // Em C é obrigatório liberar a memória alocada para evitar vazamentos
    free(ladoEsq);
    free(ladoDir);
}

// Merge Sort Sequencial
void mergeSort(int *array, int indxEsq, int indxDir) {
    if (indxEsq < indxDir) {
        int meio = indxEsq + (indxDir - indxEsq) / 2; // Evita overflow em C

        mergeSort(array, indxEsq, meio); // Ordena o lado esquerdo
        mergeSort(array, meio + 1, indxDir); // Ordena o lado direito
        merge(array, indxEsq, meio, indxDir); // Mescla
    }
}
