#include <stdlib.h>
#include <pthread.h>
#include "merge_sort.h"

/* Protótipo antecipado para o threadFunc poder chamar */
void paralleMergeSort(int *array, int indxEsq, int indxDir, int profundidade);

typedef struct {
    int *array;
    int indxEsq;
    int indxDir;
    int profundidade;
} ThreadArgs;

static void *threadFunc(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    paralleMergeSort(args->array, args->indxEsq, args->indxDir, args->profundidade);
    free(args);
    return NULL;
}

void paralleMergeSort(int *array, int indxEsq, int indxDir, int profundidade) {
    if (indxEsq >= indxDir) return;

    // Se não há mais profundidade para paralelismo, usa o sequencial e PARA por aqui
    if (profundidade <= 0) {
        mergeSort(array, indxEsq, indxDir);
        return; 
    }

    int meio = indxEsq + (indxDir - indxEsq) / 2;
    pthread_t thread1;
    ThreadArgs *args1 = (ThreadArgs *)malloc(sizeof(ThreadArgs));
    args1->array = array; args1->indxEsq = indxEsq;
    args1->indxDir = meio; args1->profundidade = profundidade - 1;

    // Cria apenas uma thread para a esquerda e processa a direita na thread atual
    // Isso economiza o overhead de criar uma segunda thread desnecessariamente
    pthread_create(&thread1, NULL, threadFunc, args1);
    
    paralleMergeSort(array, meio + 1, indxDir, profundidade - 1);

    pthread_join(thread1, NULL);

    // Agora faz o merge (você precisará de uma função merge que não seja o mergeSort completo)
    // O ideal aqui é chamar apenas a função de intercalação, não o sort inteiro.
}