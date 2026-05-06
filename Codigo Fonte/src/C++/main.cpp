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

    // Criação do vetor random

    ifstream arquivo1("../../config/input/random.dat");

    if (!arquivo1.is_open()) {
        cout << "Erro ao ler o arquivo" << endl;
        return 1;
    }

    MergeSort ms;
    ParallelMergeSort pms(3);
    Benchmark bench(15);

    string linha;
    int linha_atual = 0;

    cout << "Randomico:" << endl;
    cout << "--------------------------------------" << endl;

    while (getline(arquivo1, linha)) {
        vector<int> vetor_base;
        stringstream ss(linha);
        int numero;
        while (ss >> numero) {
            vetor_base.push_back(numero);
        }

        int entradas = (int)pow(10, linha_atual + 2);

        // Teste entradas random
        auto r1 = bench.executar(ms,  vetor_base, "mergesort",          entradas);
        auto r2 = bench.executar(pms, vetor_base, "parallel mergesort", entradas);

        cout << (int)pow(10, linha_atual + 2) << " entradas:" << endl;
        cout << fixed << setprecision(6);
        cout << "Média mergesort:          " << r1.media << "s" << endl;
        cout << "Média parallel mergesort: " << r2.media << "s" << endl;
        cout << "--------------------------------------" << endl;
        

        linha_atual++;
    }

    arquivo1.close();

    cout << "\n";


    // Criação do Vetor Crescente

    ifstream arquivo2("../../config/input/crescente.dat");

    if (!arquivo2.is_open()) {
        cout << "Erro ao ler o arquivo" << endl;
        return 1;
    }

    linha_atual = 0;

    cout << "Crescente:" << endl;
    cout << "--------------------------------------" << endl;

    while (getline(arquivo2, linha)) {
        vector<int> vetor_base;
        stringstream ss(linha);
        int numero;
        while (ss >> numero) {
            vetor_base.push_back(numero);
        }

        int entradas = (int)pow(10, linha_atual + 2);

        // Teste entradas random
        auto r1 = bench.executar(ms,  vetor_base, "mergesort",          entradas);
        auto r2 = bench.executar(pms, vetor_base, "parallel mergesort", entradas);

        cout << (int)pow(10, linha_atual + 2) << " entradas:" << endl;
        cout << fixed << setprecision(6);
        cout << "Média mergesort:          " << r1.media << "s" << endl;
        cout << "Média parallel mergesort: " << r2.media << "s" << endl;
        cout << "--------------------------------------" << endl;

        linha_atual++;
    }

    arquivo2.close();

    cout << "\n";


    // Criação do Vetor decrescente

    ifstream arquivo3("../../config/input/decrescente.dat");

    if (!arquivo3.is_open()) {
        cout << "Erro ao ler o arquivo" << endl;
        return 1;
    }

    linha_atual = 0;

    cout << "Descrescente:" << endl;
    cout << "--------------------------------------" << endl;

    while (getline(arquivo3, linha)) {
        vector<int> vetor_base;
        stringstream ss(linha);
        int numero;
        while (ss >> numero) {
            vetor_base.push_back(numero);
        }

        int entradas = (int)pow(10, linha_atual + 2);

        // Teste entradas random
        auto r1 = bench.executar(ms,  vetor_base, "mergesort",          entradas);
        auto r2 = bench.executar(pms, vetor_base, "parallel mergesort", entradas);

        cout << (int)pow(10, linha_atual + 2) << " entradas:" << endl;
        cout << fixed << setprecision(6);
        cout << "Média mergesort:          " << r1.media << "s" << endl;
        cout << "Média parallel mergesort: " << r2.media << "s" << endl;
        cout << "--------------------------------------" << endl;

        linha_atual++;
    }

    arquivo3.close();

    cout << "\n";

    return 0;
}
