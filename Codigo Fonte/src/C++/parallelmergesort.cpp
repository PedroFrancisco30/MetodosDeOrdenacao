#include "parallelmergesort.h"
#include <thread>

using namespace std;

ParallelMergeSort::ParallelMergeSort(int profundidade_max)
    : profundidade_max_(profundidade_max) {}

void ParallelMergeSort::unir(vector<int> &vetor, int inicio, int meio, int fim){
    vector<int> temp;
    int i = inicio;
    int j = meio + 1;

    while (i <= meio && j <= fim) {
        if (vetor[i] <= vetor[j]) {
            temp.push_back(vetor[i++]);
        } else {
            temp.push_back(vetor[j++]);
        }
    }

    while (i <= meio) temp.push_back(vetor[i++]);
    while (j <= fim) temp.push_back(vetor[j++]);

    for (size_t k = 0; k < temp.size(); k++)
        vetor[inicio + k] = temp[k];
}

void ParallelMergeSort::executar(vector<int> &vetor, int inicio, int fim, int profundidade) {
    if (inicio >= fim) return;

    int meio = inicio + (fim - inicio) / 2;

    if (profundidade < profundidade_max_) {
        thread t1(&ParallelMergeSort::executar, this, ref(vetor), inicio, meio, profundidade + 1);
        thread t2(&ParallelMergeSort::executar, this, ref(vetor), meio + 1, fim, profundidade + 1);

        t1.join();
        t2.join();
    } else {
        executar(vetor, inicio, meio, profundidade + 1);
        executar(vetor, meio+1, fim, profundidade + 1);
    }

    unir(vetor, inicio, meio, fim);
}

void ParallelMergeSort::ordenar(vector<int>& vetor, int inicio, int fim) {
    executar(vetor, inicio, fim, 0);
}