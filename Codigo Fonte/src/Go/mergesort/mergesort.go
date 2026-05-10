package mergesort

import "sync/atomic"

// MergeSort ordena recursivamente um slice de inteiros.
// mem acumula o total de bytes alocados nos slices temporários de merge.
func MergeSort(arr []int, mem *int64) []int {
	if len(arr) <= 1 {
		return arr
	}

	meio := len(arr) / 2
	esquerda := MergeSort(arr[:meio], mem)
	direita := MergeSort(arr[meio:], mem)

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