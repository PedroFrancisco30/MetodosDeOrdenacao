package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
	"time"
)

// mergeSort ordena recursivamente um slice de inteiros
func mergeSort(arr []int) []int {
	if len(arr) <= 1 {
		return arr
	}

	meio := len(arr) / 2
	esquerda := mergeSort(arr[:meio])
	direita := mergeSort(arr[meio:])

	return merge(esquerda, direita)
}

// merge combina dois slices já ordenados em um único slice ordenado
func merge(esquerda, direita []int) []int {
	resultado := make([]int, 0, len(esquerda)+len(direita))
	i, j := 0, 0

	for i < len(esquerda) && j < len(direita) {
		if esquerda[i] <= direita[j] {
			resultado = append(resultado, esquerda[i])
			i++
		} else {
			resultado = append(resultado, direita[j])
			j++
		}
	}

	resultado = append(resultado, esquerda[i:]...)
	resultado = append(resultado, direita[j:]...)

	return resultado
}

// lerNumerosDoArquivo lê até 'limite' números do arquivo
func lerNumerosDoArquivo(caminho string, limite int) ([]int, error) {

	arquivo, err := os.Open(caminho)//abrindo o arquivo 
	if err != nil {
		return nil, fmt.Errorf("erro ao abrir arquivo: %w", err)
	}
	defer arquivo.Close()//garantindo que o arquivo que vai ser fechado quando a funcao terminar

	numeros := make([]int, 0, limite)
	scanner := bufio.NewScanner(arquivo)
	scanner.Buffer(make([]byte, 10*1024*1024), 10*1024*1024) // buffer grande para linhas longas

	for scanner.Scan() && len(numeros) < limite {//agrupando os inteiros do arquivo que foram separados por espaço

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
		fmt.Printf("   Benchmark Merge Sort - %s\n", arquivo.nome)
		fmt.Println("=================================================")
		fmt.Printf("%-15s  %-20s  %-10s\n", "Entradas (n)", "Tempo", "Elementos lidos")
		fmt.Println("-------------------------------------------------")

		for _, limite := range limites {
			numeros, err := lerNumerosDoArquivo(arquivo.caminho, limite)
			if err != nil {
				fmt.Printf("Erro ao ler %d elementos: %v\n", limite, err)
				continue
			}

			lidos := len(numeros)
			copia := make([]int, lidos)
			copy(copia, numeros)//criando uma copia para nao ordenar o que ja tinha sido ordenado 

			inicio := time.Now()
			mergeSort(copia)
			duracao := time.Since(inicio)//calculando o tempo inicial e quanto tempo levou

			exp := 0
			tmp := limite
			for tmp >= 10 {
				tmp /= 10
				exp++
			}

			fmt.Printf("%-15s  %-20s  %-10d\n",
				fmt.Sprintf("10^%d (%d)", exp, limite),
				duracao,
				lidos,
			)
		}

		fmt.Println("=================================================")
		fmt.Println()
	}
}
