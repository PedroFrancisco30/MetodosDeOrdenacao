package mergesort

// MergeSort ordena recursivamente um slice de inteiros
func MergeSort(arr []int) []int {
	if len(arr) <= 1 {
		return arr
	}

	meio := len(arr) / 2
	esquerda := MergeSort(arr[:meio])
	direita := MergeSort(arr[meio:])

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