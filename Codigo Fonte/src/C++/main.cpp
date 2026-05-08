#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include "benchmark.h"
#include "mergesort.h"
#include "parallelmergesort.h"
using namespace std;

void executar_benchmark(const string& caminho, const string& titulo,
                        Benchmark& bench, MergeSort& ms, ParallelMergeSort& pms) {
    ifstream arquivo(caminho);
    if (!arquivo.is_open()) {
        cout << "Erro ao ler o arquivo: " << caminho << endl;
        return;
    }

    cout << titulo << ":\n";
    cout << "--------------------------------------\n";

    string linha;
    int linha_atual = 0;
    vector<double> medias1, medias2;
    vector<long>   mems1,   mems2;

    while (getline(arquivo, linha)) {
        vector<int> vetor_base;
        stringstream ss(linha);
        int numero;
        while (ss >> numero)
            vetor_base.push_back(numero);

        int entradas = (int)vetor_base.size();
        auto r1 = bench.executar(ms,  vetor_base, "mergesort",          entradas);
        auto r2 = bench.executar(pms, vetor_base, "parallel mergesort", entradas);

        medias1.push_back(r1.media);
        medias2.push_back(r2.media);
        mems1.push_back(r1.memoria_pico_kb);
        mems2.push_back(r2.memoria_pico_kb);

        linha_atual++;
    }


    cout << "Entradas:               ";
    for (int i = 0; i < (int)medias1.size(); i++)
        cout << "10^" << (i + 2) << (i + 1 < (int)medias1.size() ? " / " : "\n");

    cout << fixed << setprecision(6);
    cout << "mergesort (tempo):      ";
    for (int i = 0; i < (int)medias1.size(); i++)
        cout << medias1[i] << "s" << (i + 1 < (int)medias1.size() ? " / " : "\n");

    cout << "parallel ms (tempo):    ";
    for (int i = 0; i < (int)medias2.size(); i++)
        cout << medias2[i] << "s" << (i + 1 < (int)medias2.size() ? " / " : "\n");

    cout << "mergesort (mem KB):     ";
    for (int i = 0; i < (int)mems1.size(); i++)
        cout << mems1[i] << (i + 1 < (int)mems1.size() ? " / " : "\n");

    cout << "parallel ms (mem KB):   ";
    for (int i = 0; i < (int)mems2.size(); i++)
        cout << mems2[i] << (i + 1 < (int)mems2.size() ? " / " : "\n");

    cout << "--------------------------------------\n\n";
}

int main() {
    MergeSort ms;
    ParallelMergeSort pms(3);
    Benchmark bench(15);

    executar_benchmark("../../config/input/random.dat",      "Randomico",   bench, ms, pms);
    executar_benchmark("../../config/input/crescente.dat",   "Crescente",   bench, ms, pms);
    executar_benchmark("../../config/input/decrescente.dat", "Decrescente", bench, ms, pms);

    return 0;
}