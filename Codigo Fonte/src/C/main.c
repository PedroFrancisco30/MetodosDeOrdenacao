#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdatomic.h>
#include "merge_sort.h"

#define LIMITE_PARALELO 1
#define RUNS 15

void paralleMergeSort(int *array, int indxEsq, int indxDir, int profundidade, atomic_llong *mem);

// Tempo em segundos com precisão de microssegundos
double currentTimeSec() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec + t.tv_usec / 1e6;
}

typedef struct {
    int   *dados;
    size_t tamanho;
} ArrayDinamico;

void processarArquivo(const char *caminho) {
    ArrayDinamico listaNumeros[100];
    int qtdLinhas = 0;

    FILE *arquivo = fopen(caminho, "r");
    if (!arquivo) {
        printf("Erro: Nao foi possivel abrir o arquivo %s\n\n", caminho);
        return;
    }

    char  *linha        = NULL;
    size_t tamanhoBuffer = 0;

    while (getline(&linha, &tamanhoBuffer, arquivo) != -1) {
        int  capacidade = 1000;
        int *listaAux   = (int *)malloc(capacidade * sizeof(int));
        int  cont       = 0;
        char *ptr = linha, *fimPtr;

        while (*ptr != '\0') {
            long num = strtol(ptr, &fimPtr, 10);
            if (ptr == fimPtr) { ptr++; continue; }
            if (cont >= capacidade) {
                capacidade *= 2;
                listaAux = (int *)realloc(listaAux, capacidade * sizeof(int));
            }
            listaAux[cont++] = (int)num;
            ptr = fimPtr;
        }

        if (cont > 0) {
            listaNumeros[qtdLinhas].dados   = listaAux;
            listaNumeros[qtdLinhas].tamanho = cont;
            qtdLinhas++;
        } else {
            free(listaAux);
        }
    }
    free(linha);
    fclose(arquivo);

    if (qtdLinhas == 0) {
        printf("Aviso: arquivo vazio ou formato invalido.\n\n");
        return;
    }

    double temposMediosMerge[100]    = {0};
    double temposMediosParallel[100] = {0};
    double memMerge[100]             = {0};
    double memParallel[100]          = {0};

    for (int i = 0; i < qtdLinhas; i++) {
        size_t tam   = listaNumeros[i].tamanho;
        size_t bytes = tam * sizeof(int);

        int *buf1 = (int *)malloc(bytes);
        int *buf2 = (int *)malloc(bytes);

        // --- 15 runs de tempo (memória descartada) ---
        double somaTempoMerge = 0, somaTempoParallel = 0;
        for (int j = 0; j < RUNS; j++) {
            atomic_llong descartada = 0;

            memcpy(buf1, listaNumeros[i].dados, bytes);
            double t1 = currentTimeSec();
            mergeSort(buf1, 0, tam - 1, &descartada);
            somaTempoMerge += currentTimeSec() - t1;

            atomic_store(&descartada, 0);
            memcpy(buf2, listaNumeros[i].dados, bytes);
            double t2 = currentTimeSec();
            paralleMergeSort(buf2, 0, tam - 1, LIMITE_PARALELO, &descartada);
            somaTempoParallel += currentTimeSec() - t2;
        }
        temposMediosMerge[i]    = somaTempoMerge    / RUNS;
        temposMediosParallel[i] = somaTempoParallel / RUNS;

        // --- 1 run separado para memória ---
        atomic_llong memM = 0, memP = 0;

        memcpy(buf1, listaNumeros[i].dados, bytes);
        mergeSort(buf1, 0, tam - 1, &memM);

        memcpy(buf2, listaNumeros[i].dados, bytes);
        paralleMergeSort(buf2, 0, tam - 1, LIMITE_PARALELO, &memP);

        memMerge[i]    = (double)atomic_load(&memM) / 1024.0;
        memParallel[i] = (double)atomic_load(&memP) / 1024.0;

        free(buf1);
        free(buf2);
    }

    printf("Metodo     - 10^2  /  10^3  /  10^4  /  10^5  /  10^6\n");

    printf("Merge  (s)   ");
    for (int i = 0; i < qtdLinhas; i++)
        printf("%.6f%s", temposMediosMerge[i], i < qtdLinhas - 1 ? " / " : "");

    printf("\nMerge  (KB)  ");
    for (int i = 0; i < qtdLinhas; i++)
        printf("%.2f%s", memMerge[i], i < qtdLinhas - 1 ? " / " : "");

    printf("\nParall (s)   ");
    for (int i = 0; i < qtdLinhas; i++)
        printf("%.6f%s", temposMediosParallel[i], i < qtdLinhas - 1 ? " / " : "");

    printf("\nParall (KB)  ");
    for (int i = 0; i < qtdLinhas; i++)
        printf("%.2f%s", memParallel[i], i < qtdLinhas - 1 ? " / " : "");

    printf("\n\n");

    for (int i = 0; i < qtdLinhas; i++)
        free(listaNumeros[i].dados);
}

int main() {
    const char *arquivos[3] = {
        "../../config/input/crescente.dat",
        "../../config/input/decrescente.dat",
        "../../config/input/random.dat"
    };

    for (int f = 0; f < 3; f++) {
        printf("--- Processando: %s ---\n", arquivos[f]);
        processarArquivo(arquivos[f]);
    }

    return 0;
}