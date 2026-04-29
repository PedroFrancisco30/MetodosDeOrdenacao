#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;

void mesclar(vector<int> &vetor, int inicio, int meio, int fim) {
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

void mergesort(vector<int> &vetor, int inicio, int fim) {
    if (inicio >= fim) return;

    int meio = inicio + (fim - inicio) / 2;

    mergesort(vetor, inicio, meio);
    mergesort(vetor, meio+1, fim);
    mesclar(vetor, inicio, meio, fim);
}

int main() {

    int linha_teste = 0;
    int linha_atual = 0;

    string linha;

    ifstream arquivo;

    arquivo.open("../../../config/input/input2.dat");

    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {

            if (linha_atual == linha_teste) {
                vector<int> lista_numeros;
                stringstream ss(linha);
                int numero;

                while (ss >> numero) {
                    lista_numeros.push_back(numero);
                }

                //Contagem do tempo
                auto inicio = chrono::high_resolution_clock::now();
                mergesort(lista_numeros, 0, lista_numeros.size() - 1);
                auto fim = chrono::high_resolution_clock::now();

                for(int i = 0; i <= lista_numeros.size()-1; i++) {
                    cout << lista_numeros[i] << ", ";
                }

                chrono::duration<double> tempo = fim - inicio;
                cout << "Tempo: " << tempo.count() << "s" << endl;

                break;
            }

            linha_atual++;
        }

        arquivo.close();
    }else{
        cout << "Erro ao ler o arquivo";
    }
    return 0;
}