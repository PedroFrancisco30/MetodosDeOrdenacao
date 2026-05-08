#include "mergesort.h"
using namespace std;

void MergeSort::mesclar(vector<int>& vetor, int inicio, int meio, int fim, long& mem_bytes) {
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

void MergeSort::ordenar(vector<int>& vetor, int inicio, int fim, long& mem_bytes) {
    if (inicio >= fim) return;
    int meio = inicio + (fim - inicio) / 2;
    ordenar(vetor, inicio, meio, mem_bytes);
    ordenar(vetor, meio + 1, fim, mem_bytes);
    mesclar(vetor, inicio, meio, fim, mem_bytes);
}