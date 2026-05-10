package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
	"sync/atomic"
	"time"

	"MetodosDeOrdenacao/mergesort"
	"MetodosDeOrdenacao/parallelmergesort"
)

const RUNS = 15

func lerNumerosDoArquivo(caminho string, limite int) ([]int, error) {
	arquivo, err := os.Open(caminho)
	if err != nil {
		return nil, fmt.Errorf("erro ao abrir arquivo: %w", err)
	}
	defer arquivo.Close()

	numeros := make([]int, 0, limite)
	scanner := bufio.NewScanner(arquivo)
	scanner.Buffer(make([]byte, 10*1024*1024), 10*1024*1024)

	for scanner.Scan() && len(numeros) < limite {
		linha := scanner.Text()
		for _, campo := range strings.Fields(linha) {
			if len(numeros) >= limite {
				break
			}
			n, err := strconv.Atoi(campo)
			if err != nil {
				continue
			}
			numeros = append(numeros, n)
		}
	}

	return numeros, scanner.Err()
}

func main() {
	arquivos := []struct {
		nome    string
		caminho string
	}{
		{"random.dat", "../../config/input/random.dat"},
		{"crescente.dat", "../../config/input/crescente.dat"},
		{"decrescente.dat", "../../config/input/decrescente.dat"},
	}

	limites := []int{100, 1_000, 10_000, 100_000, 1_000_000}

	for _, arquivo := range arquivos {
		fmt.Println("=============================================================================================================")
		fmt.Printf("   Arquivo: %s\n", arquivo.nome)
		fmt.Println("=============================================================================================================")
		fmt.Printf("%-18s  %-20s %-12s  %-20s %-12s\n",
			"Entradas (n)", "MergeSort (s)", "Mem(KB)", "ParallelMergeSort (s)", "Mem(KB)")
		fmt.Println("-------------------------------------------------------------------------------------------------------------")

		for _, limite := range limites {
			numeros, err := lerNumerosDoArquivo(arquivo.caminho, limite)
			if err != nil {
				fmt.Printf("Erro ao ler %d elementos: %v\n", limite, err)
				continue
			}

			// --- 15 runs para tempo ---
			var somaTempoMerge, somaTempoParallel time.Duration
			for i := 0; i < RUNS; i++ {
				var memDescartada int64

				copia1 := make([]int, len(numeros))
				copy(copia1, numeros)
				t1 := time.Now()
				mergesort.MergeSort(copia1, &memDescartada)
				somaTempoMerge += time.Since(t1)

				atomic.StoreInt64(&memDescartada, 0)
				copia2 := make([]int, len(numeros))
				copy(copia2, numeros)
				t2 := time.Now()
				parallelmergesort.ParallelMergeSort(copia2, 0, &memDescartada)
				somaTempoParallel += time.Since(t2)
			}
			tempoMerge    := somaTempoMerge    / RUNS
			tempoParallel := somaTempoParallel / RUNS

			// --- 1 run separado para memória ---
			var memMerge, memParallel int64

			copia1 := make([]int, len(numeros))
			copy(copia1, numeros)
			mergesort.MergeSort(copia1, &memMerge)

			copia2 := make([]int, len(numeros))
			copy(copia2, numeros)
			parallelmergesort.ParallelMergeSort(copia2, 0, &memParallel)

			exp := 0
			for tmp := limite; tmp >= 10; tmp /= 10 {
				exp++
			}

			fmt.Printf("%-18s  %-20s %-12d  %-20s %-12d\n",
				fmt.Sprintf("10^%d (%d)", exp, limite),
				fmt.Sprintf("%.6fs", tempoMerge.Seconds()),
				memMerge/1024,
				fmt.Sprintf("%.6fs", tempoParallel.Seconds()),
				memParallel/1024,
			)
		}

		fmt.Println("=============================================================================================================")
		fmt.Println()
	}
}