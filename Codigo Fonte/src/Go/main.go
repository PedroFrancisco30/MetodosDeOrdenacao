package main

import (
	"bufio"
	"fmt"
	"os"
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
	defer arquivo.Close()// Garante que o arquivo será fechado quando a função terminar,

	numeros := make([]int, 0, limite)
	scanner := bufio.NewScanner(arquivo)	// bufio.Scanner lê o arquivo linha por linha sem carregar tudo na memória
	scanner.Buffer(make([]byte, 10*1024*1024), 10*1024*1024)

	// Lê linha por linha enquanto não atingir o limite de números
	for scanner.Scan() && len(numeros) < limite {
		linha := scanner.Text()
		campos := strings.Fields(linha)		// strings.Fields separa a linha pelos espaços
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

func main() {
	arquivos := []struct {
		nome    string
		caminho string
	}{
		{"random.dat", "/home/chicao/MetodosDeOrdenacao/Codigo Fonte/config/input/random.dat"},
		{"crescente.dat", "/home/chicao/MetodosDeOrdenacao/Codigo Fonte/config/input/crescente.dat"},
		{"decrescente.dat", "/home/chicao/MetodosDeOrdenacao/Codigo Fonte/config/input/decrescente.dat"},
	}

	limites := []int{100, 1_000, 10_000, 100_000, 1_000_000}

	for _, arquivo := range arquivos {
		fmt.Println("=================================================")
		fmt.Printf("   Arquivo: %s\n", arquivo.nome)
		fmt.Println("=================================================")
		fmt.Printf("%-15s  %-20s  %-20s\n", "Entradas (n)", "MergeSort", "ParallelMergeSort")
		fmt.Println("-------------------------------------------------")

		for _, limite := range limites {
			numeros, err := lerNumerosDoArquivo(arquivo.caminho, limite)
			if err != nil {
				fmt.Printf("Erro ao ler %d elementos: %v\n", limite, err)
				continue
			}

			// Cria uma cópia dos dados para o MergeSort.
			copia1 := make([]int, len(numeros))
			copy(copia1, numeros)

			// Cria uma segunda cópia para o ParallelMergeSort
			copia2 := make([]int, len(numeros))
			copy(copia2, numeros)

			inicio := time.Now()
			mergesort.MergeSort(copia1)
			tempoMerge := time.Since(inicio)

			inicio = time.Now()
			parallelmergesort.ParallelMergeSort(copia2, 0)
			tempoParallel := time.Since(inicio)

			exp := 0
			tmp := limite
			for tmp >= 10 {
				tmp /= 10
				exp++
			}

			fmt.Printf("%-15s  %-20s  %-20s\n",
				fmt.Sprintf("10^%d (%d)", exp, limite),
				tempoMerge,
				tempoParallel,
			)
		}

		fmt.Println("=================================================")
		fmt.Println()
	}
}