#include <stdlib.h>
#include <pthread.h>

#define LIMITE_PARALELO 3

void paralleMergeSort(int *array, int indxEsq, int indxDir, int profundidade);
void merge(int *array, int indxEsq, int meio, int indxDir);

// Estrutura auxiliar para passar argumentos para a Thread em C
typedef struct {
    int *array;
    int indxEsq;
    int indxDir;
    int profundidade;
} ThreadArgs;

// Função wrapper exigida pela pthread_create
void* threadFunc(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    paralleMergeSort(args->array, args->indxEsq, args->indxDir, args->profundidade);
    free(args); // Libera o struct de argumentos
    return NULL;
}

// Merge Sort Paralelo
void paralleMergeSort(int *array, int indxEsq, int indxDir, int profundidade) {
    if (indxEsq < indxDir) {
        int meio = indxEsq + (indxDir - indxEsq) / 2;

        if (profundidade > 0) {
            pthread_t thread1, thread2;

            // Prepara os argumentos
            ThreadArgs *args1 = (ThreadArgs *)malloc(sizeof(ThreadArgs));
            args1->array = array; args1->indxEsq = indxEsq; args1->indxDir = meio; args1->profundidade = profundidade - 1;

            ThreadArgs *args2 = (ThreadArgs *)malloc(sizeof(ThreadArgs));
            args2->array = array; args2->indxEsq = meio + 1; args2->indxDir = indxDir; args2->profundidade = profundidade - 1;

        
            pthread_create(&thread1, NULL, threadFunc, args1);
            pthread_create(&thread2, NULL, threadFunc, args2);

            pthread_join(thread1, NULL);
            pthread_join(thread2, NULL);
        } else {
            // Para de criar Threads infinitas
            paralleMergeSort(array, indxEsq, meio, 0);
            paralleMergeSort(array, meio + 1, indxDir, 0);
        }


        merge(array, indxEsq, meio, indxDir);
    }
}
