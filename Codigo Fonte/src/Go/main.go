package main

import (
	"bufio"
	"fmt"
	"os"
	"runtime"
	"strconv"
	"strings"
	"time"

	"MetodosDeOrdenacao/mergesort"
	"MetodosDeOrdenacao/parallelmergesort"
)

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
		campos := strings.Fields(linha)
		for _, campo := range campos {
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

	if err := scanner.Err(); err != nil {
		return nil, fmt.Errorf("erro ao ler arquivo: %w", err)
	}

	return numeros, nil
}

// medirMemoria retorna quantos KB foram alocados durante a execução da função f
func medirMemoria(f func()) uint64 {
	runtime.GC() // força GC antes para limpar lixo anterior
	var antes, depois runtime.MemStats
	runtime.ReadMemStats(&antes)

	f()

	runtime.ReadMemStats(&depois)
	alocado := depois.TotalAlloc - antes.TotalAlloc
	return alocado / 1024 // converte bytes → KB
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
			"Entradas (n)", "MergeSort", "Mem(KB)", "ParallelMergeSort", "Mem(KB)")
		fmt.Println("-------------------------------------------------------------------------------------------------------------")

		for _, limite := range limites {
			numeros, err := lerNumerosDoArquivo(arquivo.caminho, limite)
			if err != nil {
				fmt.Printf("Erro ao ler %d elementos: %v\n", limite, err)
				continue
			}

			copia1 := make([]int, len(numeros))
			copy(copia1, numeros)

			copia2 := make([]int, len(numeros))
			copy(copia2, numeros)

			var tempoMerge time.Duration
			var tempoParallel time.Duration

			memMerge := medirMemoria(func() {
				inicio := time.Now()
				mergesort.MergeSort(copia1)
				tempoMerge = time.Since(inicio)
			})

			memParallel := medirMemoria(func() {
				inicio := time.Now()
				parallelmergesort.ParallelMergeSort(copia2, 0)
				tempoParallel = time.Since(inicio)
			})

			exp := 0
			tmp := limite
			for tmp >= 10 {
				tmp /= 10
				exp++
			}

			fmt.Printf("%-18s  %-20s %-12d  %-20s %-12d\n",
				fmt.Sprintf("10^%d (%d)", exp, limite),
				tempoMerge,
				memMerge,
				tempoParallel,
				memParallel,
			)
		}

		fmt.Println("=============================================================================================================")
		fmt.Println()
	}
}
