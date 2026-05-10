import threading
from merge_sort import merge

LIMITE_PARALELO = 1

def parallel_merge_sort(array, indx_esq, indx_dir, profundidade, mem):
    if indx_esq < indx_dir:
        meio = (indx_esq + indx_dir) // 2

        if profundidade > 0:
            thread1 = threading.Thread(
                target=parallel_merge_sort,
                args=(array, indx_esq, meio, profundidade - 1, mem)
            )
            thread2 = threading.Thread(
                target=parallel_merge_sort,
                args=(array, meio + 1, indx_dir, profundidade - 1, mem)
            )
            thread1.start()
            thread2.start()
            thread1.join()
            thread2.join()
        else:
            parallel_merge_sort(array, indx_esq, meio, 0, mem)
            parallel_merge_sort(array, meio + 1, indx_dir, 0, mem)

        merge(array, indx_esq, meio, indx_dir, mem)