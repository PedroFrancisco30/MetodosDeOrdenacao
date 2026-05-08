#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <string>
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

    int n = (int)medias1.size();

    vector<int> col_w(n);
    for (int i = 0; i < n; i++) {
        string header = "10^" + to_string(i + 2);

        ostringstream t1, t2, m1, m2;
        t1 << fixed << setprecision(6) << medias1[i] << "s";
        t2 << fixed << setprecision(6) << medias2[i] << "s";
        m1 << mems1[i] << " KB";
        m2 << mems2[i] << " KB";

        col_w[i] = max((int)header.size(),
                   max((int)t1.str().size(),
                   max((int)t2.str().size(),
                   max((int)m1.str().size(),
                       (int)m2.str().size()))));
    }

    const int LABEL_W = 24;
    const string SEP = " | ";

    int total_w = LABEL_W;
    for (int i = 0; i < n; i++)
        total_w += (int)SEP.size() + col_w[i];

    auto print_row = [&](const string& label, const vector<string>& vals) {
        cout << left << setw(LABEL_W) << label;
        for (int i = 0; i < n; i++)
            cout << SEP << right << setw(col_w[i]) << vals[i];
        cout << "\n";
    };

    cout << "\n" << titulo << ":\n";
    cout << string(total_w, '-') << "\n";

    vector<string> headers(n);
    for (int i = 0; i < n; i++)
        headers[i] = "10^" + to_string(i + 2);
    print_row("Entradas", headers);

    cout << string(total_w, '-') << "\n";

    vector<string> v1(n), v2(n);
    for (int i = 0; i < n; i++) {
        ostringstream s; s << fixed << setprecision(6) << medias1[i] << "s";
        v1[i] = s.str();
    }
    for (int i = 0; i < n; i++) {
        ostringstream s; s << fixed << setprecision(6) << medias2[i] << "s";
        v2[i] = s.str();
    }
    print_row("mergesort (tempo)", v1);
    print_row("parallel ms (tempo)", v2);

    cout << string(total_w, '-') << "\n";

    vector<string> m1v(n), m2v(n);
    for (int i = 0; i < n; i++) {
        ostringstream s; s << mems1[i] << " KB"; m1v[i] = s.str();
    }
    for (int i = 0; i < n; i++) {
        ostringstream s; s << mems2[i] << " KB"; m2v[i] = s.str();
    }
    print_row("mergesort (mem)", m1v);
    print_row("parallel ms (mem)", m2v);

    cout << string(total_w, '-') << "\n";
}

int main() {
    MergeSort ms;
    ParallelMergeSort pms(2);
    Benchmark bench(15);

    executar_benchmark("../../config/input/random.dat",      "Randomico",   bench, ms, pms);
    executar_benchmark("../../config/input/crescente.dat",   "Crescente",   bench, ms, pms);
    executar_benchmark("../../config/input/decrescente.dat", "Decrescente", bench, ms, pms);

    return 0;
}