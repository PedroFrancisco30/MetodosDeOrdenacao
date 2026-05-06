#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

void mergeSort(int *array, int indxEsq, int indxDir);
void paralleMergeSort(int *array, int indxEsq, int indxDir, int profundidade);

#define LIMITE_PARALELO 3

// Função auxiliar para capturar tempo em milissegundos
long long currentTimeMillis() {
    struct timeval tempo;
    gettimeofday(&tempo, NULL);
    return (tempo.tv_sec * 1000) + (tempo.tv_usec / 1000);
}

// Estrutura dinâmica para guardar os arrays 
typedef struct {
    int *dados;
    size_t tamanho;
} ArrayDinamico;

int main() {
    ArrayDinamico listaNumeros[10]; // Suporta até 10 linhas do input.dat (pode aumentar)
    int qtdLinhas = 0;
   
    double temposMediosMerge[10] = {0};
    double temposMediosParallel[10] = {0};

    const char *caminho = "input.dat";
    FILE *arquivo = fopen(caminho, "r");

    if (!arquivo) {
        printf("Erro: Não foi possível abrir o arquivo %s\n", caminho);
        return 1;
    }

    char *linha = NULL;
    size_t tamanhoBuffer = 0;
    ssize_t lido;

    while ((lido = getline(&linha, &tamanhoBuffer, arquivo)) != -1) {
        int capacidade = 1000;
        int *listaAux = (int *)malloc(capacidade * sizeof(int));
        int cont = 0;

        char *ptr = linha;
        char *fimPtr;
       
        while (*ptr != '\0') {
            long num = strtol(ptr, &fimPtr, 10);
            if (ptr == fimPtr) {
                ptr++; 
            } else {
                if (cont >= capacidade) {
                    capacidade *= 2;
                    listaAux = (int *)realloc(listaAux, capacidade * sizeof(int));
                }
                listaAux[cont++] = (int)num;
                ptr = fimPtr;
            }
        }

        if (cont > 0) {
            listaNumeros[qtdLinhas].dados = listaAux;
            listaNumeros[qtdLinhas].tamanho = cont;
            qtdLinhas++;
        } else {
            free(listaAux);
        }
    }
    free(linha);
    fclose(arquivo);

    for (int i = 0; i < qtdLinhas; i++) {
        long long tempoMergeAux = 0;
        long long tempoMergeParallelAux = 0;
        size_t tamArray = listaNumeros[i].tamanho;
        size_t bytesArray = tamArray * sizeof(int);

        int *listaTeste1 = (int *)malloc(bytesArray);
        int *listaTeste2 = (int *)malloc(bytesArray);

        for (int j = 0; j < 15; j++) {
            memcpy(listaTeste1, listaNumeros[i].dados, bytesArray);
            memcpy(listaTeste2, listaNumeros[i].dados, bytesArray);

            // Teste Sequencial
            long long inicio1 = currentTimeMillis();
            mergeSort(listaTeste1, 0, tamArray - 1);
            long long fim1 = currentTimeMillis();

            // Teste Paralelo
            long long inicio2 = currentTimeMillis();
            paralleMergeSort(listaTeste2, 0, tamArray - 1, LIMITE_PARALELO);
            long long fim2 = currentTimeMillis();

            tempoMergeAux += (fim1 - inicio1);
            tempoMergeParallelAux += (fim2 - inicio2);
        }

        temposMediosMerge[i] = (double)tempoMergeAux / 15.0;
        temposMediosParallel[i] = (double)tempoMergeParallelAux / 15.0;

        free(listaTeste1);
        free(listaTeste2);
    }

    printf("Tempos medios apos 15 testes: \n");
    printf("Metodo - 10^2  /  10^3  /  10^4  /  10^5  /  10^6\n");
   
    printf("Merge  ");
    for (int i = 0; i < qtdLinhas; i++) {
        printf("%.2f%s", temposMediosMerge[i], (i == qtdLinhas - 1) ? "" : " / ");
    }
    printf("\nParall ");
    for (int i = 0; i < qtdLinhas; i++) {
        printf("%.2f%s", temposMediosParallel[i], (i == qtdLinhas - 1) ? "" : " / ");
    }
    printf("\n");

    for (int i = 0; i < qtdLinhas; i++) {
        free(listaNumeros[i].dados);
    }

    return 0;
}
