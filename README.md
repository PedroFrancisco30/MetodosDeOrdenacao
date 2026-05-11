# Merge Sort & Parallel Merge Sort — Análise Comparativa de Desempenho

> Trabalho prático da disciplina de **Algoritmos e Estruturas de Dados**  
> CEFET-MG Campus V — Divinópolis, MG

---

## Autores

| Nome | E-mail |
|---|---|
| Felipe Silva | felipe.silva.03@aluno.cefetmg.br |
| Pedro Francisco Sousa Silva | pedro.silva.30@aluno.cefetmg.br |
| Pedro Henrique Silva Costa | pedro.28@aluno.cefetmg.br |
| Paulo Henrique Hemetrio | hemetrio@aluno.cefetmg.br |

---

## Sobre o Projeto

Este repositório contém as implementações e os dados experimentais utilizados no artigo *"Análise Comparativa de Desempenho entre os Algoritmos Merge Sort e Parallel Merge Sort em Ambientes Multicore"*.

O estudo compara o **Merge Sort sequencial** com o **Parallel Merge Sort por invocação de threads** em cinco linguagens de programação, avaliando tempo de execução, consumo de memória e escalabilidade em entradas de até 10⁶ elementos.

---

## Linguagens Implementadas

| Linguagem | Mecanismo de concorrência | Estrutura de dados |
|---|---|---|
| C | `pthreads` (POSIX Threads) | `int*` (array nativo) |
| C++ | `std::thread` + `join()` | `std::vector<int>` |
| Java | `Thread` nativa da JVM + `join()` | `List<Integer>` (ArrayList) |
| Go | goroutines + `sync.WaitGroup` | `[]int` (slice) |
| Python | `threading` (limitado pelo GIL) | `list` |

---

## Ambiente de Execução

- **SO:** Linux
- **Processador:** 12th Gen Intel Core i5-1235U (10 núcleos / 12 threads)
- **Memória RAM:** 16 GB DDR4 3200 MT/s
- **Compiladores / Interpretadores:**
  - GCC v13.3.0
  - G++ v13.3.0
  - Java JDK 24.0.2
  - Go 1.22.3
  - Python 3.12.3

---

## Metodologia

### Tamanhos de entrada
`10²`, `10³`, `10⁴`, `10⁵` e `10⁶` elementos.

### Configurações de ordenação prévia
- **Aleatória** — caso médio, mais representativo de uso real
- **Crescente** — melhor caso prático para cache e branch predictor
- **Decrescente** — padrão de comparações regular e previsível

### Coleta
Cada configuração foi executada **15 vezes**; o valor reportado é a **média aritmética**.

### Métricas
- Tempo de execução (*wall-clock time*), em milissegundos / segundos
- Consumo de memória (RSS — *Resident Set Size*), em kilobytes

---

## Principais Resultados

### Speedup do Parallel Merge Sort vs. Sequencial (n = 10⁶, linguagem C)

| Entrada | Merge Sort (ms) | Parallel (ms) | Speedup |
|---|---|---|---|
| Aleatória | 296,13 | 99,33 | **2,98×** |
| Crescente | 130,60 | 76,27 | 1,71× |
| Decrescente | 126,20 | 73,33 | 1,72× |

### Ranking de desempenho — n = 10⁶, entrada aleatória

| Pos. | Sequencial | Tempo (s) | Paralelo 4t | Tempo (s) |
|---|---|---|---|---|
| 1º | C | 0,1533 | Go | 0,1433 |
| 2º | C++ | 0,3385 | C++ | 0,1657 |
| 3º | Go | 0,3407 | C | 0,2071 |
| 4º | Java | 0,4095 | Java | 0,2417 |
| 5º | Python | 6,0465 | Python | 4,9733 |

### Consumo de memória — Merge Sort Sequencial (KB)

| Linguagem | 10² | 10³ | 10⁴ | 10⁵ | 10⁶ |
|---|---|---|---|---|---|
| C / C++ / Java | 2,63 | 38,97 | 521,94 | 6.519,25 | 77.935,25 |
| Go / Python | 5,25 | 77,94 | 1.043,88 | 13.038,50 | 155.870,50 |

> Go e Python consomem o dobro de C/C++/Java porque usam 8 bytes por elemento (int64 e ponteiro PyObject, respectivamente), enquanto C, C++ e Java usam inteiros de 4 bytes.

---

## Conclusões

- O **ponto de equilíbrio** entre sequencial e paralelo está em torno de **10⁴ elementos**: abaixo disso, o overhead de criação e sincronização de threads supera o ganho.
- **Go** foi a linguagem com maior speedup no paralelo (2,38× no cenário aleatório), superando C++ graças ao menor overhead de troca de contexto das goroutines.
- **C** venceu no sequencial em todos os cenários, mas apresentou speedup negativo no paralelo com entradas estruturadas (crescente/decrescente) devido a contenção de cache entre núcleos.
- **Python** não consegue paralelizar efetivamente em tarefas CPU-bound por causa do GIL (Global Interpreter Lock); em alguns cenários, a versão paralela foi mais lenta que a sequencial.
- O consumo de memória é **determinístico e independente da distribuição dos dados** — cresce como Θ(n) para o RSS e é idêntico para os três tipos de entrada em um mesmo n.

---

## Referências

- D. E. Knuth, *The Art of Computer Programming, Vol. 3: Sorting and Searching*, 2nd ed., Addison-Wesley, 1998.
- T. H. Cormen et al., *Introduction to Algorithms*, 4th ed., MIT Press, 2022.
- A. Maus, "A faster, all parallel merge sort algorithm for multicore processors," NIK-2018.
- J. E. Solsona and S. Nesmachnow, "Empirical evaluation of parallel implementations of MergeSort," *ACI*, vol. 17, no. 1, 2025. DOI: [10.18272/aci.v17i1.3701](https://doi.org/10.18272/aci.v17i1.3701)
- G. M. Amdahl, "Validity of the single processor approach to achieving large scale computing capabilities," AFIPS, 1967.
