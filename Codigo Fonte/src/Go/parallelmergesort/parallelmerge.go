package parallelmergesort

import (
	"sync"
	"sync/atomic"
)

const LIMITE_GOROUTINES = 1

// ParallelMergeSort ordena com goroutines até o limite de profundidade.
// mem acumula o total de bytes alocados nos slices temporários de merge.
func ParallelMergeSort(arr []int, profundidade int, mem *int64) []int {
	if len(arr) <= 1 {
		return arr
	}

	// Quando atingir o limite, usa mergesort sequencial
	if profundidade >= LIMITE_GOROUTINES {
		return mergeSort(arr, mem)
	}

	meio := len(arr) / 2

	var esquerda, direita []int
	var wg sync.WaitGroup
	wg.Add(2)

	go func() {
		defer wg.Done()
		esquerda = ParallelMergeSort(arr[:meio], profundidade+1, mem)
	}()

	go func() {
		defer wg.Done()
		direita = ParallelMergeSort(arr[meio:], profundidade+1, mem)
	}()

	wg.Wait()

	return merge(esquerda, direita, mem)
}

func mergeSort(arr []int, mem *int64) []int {
	if len(arr) <= 1 {
		return arr
	}
	meio := len(arr) / 2
	esquerda := mergeSort(arr[:meio], mem)
	direita := mergeSort(arr[meio:], mem)
	return merge(esquerda, direita, mem)
}

func merge(esquerda, direita []int, mem *int64) []int {
	n := len(esquerda) + len(direita)

	// Conta os bytes do slice resultado alocado nesta intercalação (8 bytes por int em Go 64-bit)
	atomic.AddInt64(mem, int64(n)*8)

	resultado := make([]int, 0, n)
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