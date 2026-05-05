#include "mergesort.h"
using namespace std;

void MergeSort::mesclar(vector<int> &vetor, int inicio, int meio, int fim) {
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

void MergeSort::ordenar(vector<int> &vetor, int inicio, int fim) {
    if (inicio >= fim) return;

    int meio = inicio + (fim - inicio) / 2;

    ordenar(vetor, inicio, meio);
    ordenar(vetor, meio+1, fim);
    mesclar(vetor, inicio, meio, fim);
}