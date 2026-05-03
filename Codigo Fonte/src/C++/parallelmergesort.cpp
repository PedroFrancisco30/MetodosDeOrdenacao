#include <vector>
#include <thread>

using namespace std;

void unir(vector<int> &vetor, int inicio, int meio, int fim) {
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

void parallelmergesort(vector<int> &vetor, int inicio, int fim, int profundidade) {
    if (inicio >= fim) return;

    int meio = inicio + (fim - inicio) / 2;

    if (profundidade < 3) {
        thread t1(parallelmergesort, std::ref(vetor), inicio, meio, profundidade + 1);
        thread t2(parallelmergesort, std::ref(vetor), meio + 1, fim, profundidade + 1);

        t1.join();
        t2.join();
    } else {
        parallelmergesort(vetor, inicio, meio, profundidade + 1);
        parallelmergesort(vetor, meio+1, fim, profundidade + 1);
    }

    unir(vetor, inicio, meio, fim);
}