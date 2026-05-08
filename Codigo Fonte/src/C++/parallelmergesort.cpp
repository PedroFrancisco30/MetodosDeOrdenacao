#include "parallelmergesort.h"
#include <thread>
using namespace std;

ParallelMergeSort::ParallelMergeSort(int profundidade_max)
    : profundidade_max_(profundidade_max) {}

void ParallelMergeSort::unir(vector<int>& vetor, int inicio, int meio, int fim, long& mem_bytes) {
    vector<int> temp;
    int i = inicio, j = meio + 1;
    while (i <= meio && j <= fim)
        temp.push_back(vetor[i] <= vetor[j] ? vetor[i++] : vetor[j++]);
    while (i <= meio) temp.push_back(vetor[i++]);
    while (j <= fim)  temp.push_back(vetor[j++]);
    for (size_t k = 0; k < temp.size(); k++)
        vetor[inicio + k] = temp[k];
    mem_bytes += (long)(fim - inicio + 1) * sizeof(int);
}

void ParallelMergeSort::executar(vector<int>& vetor, int inicio, int fim, int profundidade, long& mem_bytes) {
    if (inicio >= fim) return;
    int meio = inicio + (fim - inicio) / 2;
    if (profundidade < profundidade_max_) {
        long mb1 = 0, mb2 = 0;
        thread t1([&]() { executar(vetor, inicio, meio, profundidade + 1, mb1); });
        thread t2([&]() { executar(vetor, meio + 1, fim, profundidade + 1, mb2); });
        t1.join();
        t2.join();
        mem_bytes += mb1 + mb2;
    } else {
        executar(vetor, inicio, meio, profundidade + 1, mem_bytes);
        executar(vetor, meio + 1, fim, profundidade + 1, mem_bytes);
    }
    unir(vetor, inicio, meio, fim, mem_bytes);
}

void ParallelMergeSort::ordenar(vector<int>& vetor, int inicio, int fim, long& mem_bytes) {
    executar(vetor, inicio, fim, 0, mem_bytes);
}