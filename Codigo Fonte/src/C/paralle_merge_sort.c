#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include "merge_sort.h"

void paralleMergeSort(int *array, int indxEsq, int indxDir, int profundidade, atomic_llong *mem);

typedef struct {
    int           *array;
    int            indxEsq;
    int            indxDir;
    int            profundidade;
    atomic_llong  *mem;
} ThreadArgs;

static void *threadFunc(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    paralleMergeSort(args->array, args->indxEsq, args->indxDir, args->profundidade, args->mem);
    free(args);
    return NULL;
}

void paralleMergeSort(int *array, int indxEsq, int indxDir, int profundidade, atomic_llong *mem) {
    if (indxEsq >= indxDir) return;

    // Sem mais profundidade: usa mergesort sequencial
    if (profundidade <= 0) {
        mergeSort(array, indxEsq, indxDir, mem);
        return;
    }

    int meio = indxEsq + (indxDir - indxEsq) / 2;

    // Cria uma thread para a metade esquerda
    pthread_t thread1;
    ThreadArgs *args1 = (ThreadArgs *)malloc(sizeof(ThreadArgs));
    args1->array       = array;
    args1->indxEsq     = indxEsq;
    args1->indxDir     = meio;
    args1->profundidade = profundidade - 1;
    args1->mem         = mem;
    pthread_create(&thread1, NULL, threadFunc, args1);

    // Processa a metade direita na thread atual
    paralleMergeSort(array, meio + 1, indxDir, profundidade - 1, mem);

    // Aguarda a thread esquerda terminar
    pthread_join(thread1, NULL);

    // CORREÇÃO DO BUG: intercala as duas metades após o join
    // Antes este merge estava faltando — o array ficava semi-ordenado
    mergeIntercalar(array, indxEsq, meio, indxDir, mem);
}