import threading

LIMITE_PARALELO = 1 # Evita explodir threads

from merge_sort import merge

def parallel_merge_sort(array, indx_esq, indx_dir, profundidade):
    if indx_esq < indx_dir:
        meio = (indx_esq + indx_dir) // 2

        if profundidade > 0:
            thread1 = threading.Thread(target=parallel_merge_sort, args=(array, indx_esq, meio, profundidade - 1))
            thread2 = threading.Thread(target=parallel_merge_sort, args=(array, meio + 1, indx_dir, profundidade - 1))

            thread1.start() # Iniciou em paralelo
            thread2.start()

            thread1.join() # Espera as threads terminarem
            thread2.join()
        else: 
            parallel_merge_sort(array, indx_esq, meio, 0)
            parallel_merge_sort(array, meio + 1, indx_dir, 0)

        # Espera as duas acabar para que ai faca o merge
        merge(array, indx_esq, meio, indx_dir)
