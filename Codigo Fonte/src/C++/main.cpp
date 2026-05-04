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

int main() {

    ifstream arquivo("../../config/input/input.dat");

    if (!arquivo.is_open()) {
        cout << "Erro ao ler o arquivo" << endl;
        return 1;
    }

    MergeSort ms;
    ParallelMergeSort pms(3);
    Benchmark bench(15);

    string linha;
    int linha_atual = 0;

    while (getline(arquivo, linha)) {
        vector<int> vetor_base;
        stringstream ss(linha);
        int numero;
        while (ss >> numero) {
            vetor_base.push_back(numero);
        }

        int entradas = (int)pow(10, linha_atual + 2);

        auto r1 = bench.executar(ms,  vetor_base, "mergesort",          entradas);
        auto r2 = bench.executar(pms, vetor_base, "parallel mergesort", entradas);

        cout << (int)pow(10, linha_atual + 2) << " entradas:" << endl;
        cout << fixed << setprecision(6);
        cout << "Média mergesort:          " << r1.media << "s" << endl;
        cout << "Média parallel mergesort: " << r2.media << "s" << endl;
        cout << "--------------------------------------" << endl;

        linha_atual++;
    }

    return 0;
}
