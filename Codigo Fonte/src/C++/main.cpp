#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <cmath>
#include "mergesort.h"
#include "parallelmergesort.h"

using namespace std;

int main() {

    const int execucoes = 15;

    int linha_atual = 0;

    string linha;

    ifstream arquivo;

    arquivo.open("../../config/input/input.dat");

    if (!arquivo.is_open()) {
        cout << "Erro ao ler o arquivo" << endl;
        return 1;
    }

    while (getline(arquivo, linha)) {
        vector<int> vetor_base;

        stringstream ss(linha);

        int numero;
        while (ss >> numero) {
            vetor_base.push_back(numero);
        }

        double media1 = 0;
        double media2 = 0;

        for(int i = 0; i < execucoes; i++){
            vector<int> vetor1 = vetor_base;
            vector<int> vetor2 = vetor_base;

            auto inicio1 = chrono::high_resolution_clock::now();
            mergesort(vetor1, 0, vetor1.size() - 1);
            auto fim1 = chrono::high_resolution_clock::now();

            auto inicio2 = chrono::high_resolution_clock::now();
            parallelmergesort(vetor2, 0, vetor2.size() - 1, 0);
            auto fim2 = chrono::high_resolution_clock::now();

            chrono::duration<double> tempo1 = fim1 - inicio1;
            chrono::duration<double> tempo2 = fim2 - inicio2;

            media1 += tempo1.count();
            media2 += tempo2.count();
        }

        media1 /= execucoes;
        media2 /= execucoes;

        cout << (int)pow(10, linha_atual + 2) << " entradas:" << endl;
        cout << fixed << setprecision(6);
        cout << "Média mergesort: " << media1 << "s" << endl;
        cout << "Média parallel mergesort: " << media2 << "s" << endl;
        cout << "--------------------------------------" << endl;

        
        linha_atual++;
    }
    arquivo.close();
    return 0;
}