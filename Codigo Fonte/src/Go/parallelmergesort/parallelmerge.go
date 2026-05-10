package parallelmergesort

import "sync"

const LIMITE_GOROUTINES = 2

func ParallelMergeSort(arr []int, profundidade int) []int {
    if len(arr) <= 1 {
        return arr
    }

    // Quando atingir o limite, vira mergesort normal sem criar mais goroutines
    if profundidade >= LIMITE_GOROUTINES {
        return mergeSort(arr)
    }

    meio := len(arr) / 2

    var esquerda, direita []int//tem que declarar essas variaveis de fora
    var wg sync.WaitGroup//espera as go routines acabarem antes de fazer o merge
    wg.Add(2)

    // Goroutine para o lado esquerdo
    go func() {
        defer wg.Done()
        esquerda = ParallelMergeSort(arr[:meio], profundidade+1)
    }()

    // Goroutine para o lado direito
    go func() {
        defer wg.Done()
        direita = ParallelMergeSort(arr[meio:], profundidade+1)
    }()

    wg.Wait() // espera as duas goroutines terminarem

    return merge(esquerda, direita)
}

// mergeSort normal usado quando atinge o limite de goroutines
func mergeSort(arr []int) []int {
    if len(arr) <= 1 {
        return arr
    }
    meio := len(arr) / 2
    esquerda := mergeSort(arr[:meio])
    direita := mergeSort(arr[meio:])
    return merge(esquerda, direita)
}

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