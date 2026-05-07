import time
import os
import tracemalloc
from merge_sort import merge_sort
from parallel_merge_sort import parallel_merge_sort, LIMITE_PARALELO
from multiprocessing import Process, Array, Value, Lock
import ctypes

_mem_lock = Lock() if __name__ == "__main__" else None

def worker(array_shared, indx_esq, indx_dir, profundidade, n):
    """Função executada em cada processo filho."""
    array = list(array_shared[:n])
    tracemalloc.start()
    parallel_merge_sort(array, indx_esq, indx_dir, profundidade)
    _, pico = tracemalloc.get_traced_memory()
    tracemalloc.stop()
    # Copia resultado de volta para memória compartilhada
    for i in range(n):
        array_shared[i] = array[i]


def medir_seq(lista):
    tracemalloc.start()
    inicio = time.time() * 1000
    merge_sort(lista, 0, len(lista) - 1)
    fim = time.time() * 1000
    _, pico = tracemalloc.get_traced_memory()
    tracemalloc.stop()
    return (fim - inicio), (pico / 1024)


def medir_parallel(lista):
    tracemalloc.start()
    inicio = time.time() * 1000
    parallel_merge_sort(lista, 0, len(lista) - 1, LIMITE_PARALELO)
    fim = time.time() * 1000
    _, pico = tracemalloc.get_traced_memory()
    tracemalloc.stop()
    return (fim - inicio), (pico / 1024)


def processar_arquivo(caminho_arquivo):
    lista_numeros = []

    try:
        with open(caminho_arquivo, 'r') as arquivo:
            for linha in arquivo:
                linha_numeros = [int(num) for num in linha.strip().split() if num]
                if linha_numeros:
                    lista_numeros.append(linha_numeros)
    except FileNotFoundError:
        print(f"Erro: Arquivo não encontrado em {caminho_arquivo}\n")
        return

    if not lista_numeros:
        print(f"Aviso: O arquivo está vazio ou com formato inválido.\n")
        return

    tempos_merge, tempos_parallel = [], []
    mems_merge, mems_parallel = [], []

    for lista_numero in lista_numeros:
        t_merge = t_parallel = m_merge = m_parallel = 0.0

        for _ in range(15):
            t, m = medir_seq(list(lista_numero))
            t_merge += t
            m_merge += m

            t, m = medir_parallel(list(lista_numero))
            t_parallel += t
            m_parallel += m

        tempos_merge.append(t_merge / 15)
        tempos_parallel.append(t_parallel / 15)
        mems_merge.append(m_merge / 15)
        mems_parallel.append(m_parallel / 15)

    print("Metodo - 10^2  /  10^3  /  10^4  /  10^5  /  10^6")
    print("--- Tempo médio (ms) ---")
    print(f"Merge  {' / '.join([f'{t:.4f}ms' for t in tempos_merge])}")
    print(f"Parall {' / '.join([f'{t:.4f}ms' for t in tempos_parallel])}")
    print("--- Memória pico média (KB) ---")
    print(f"Merge  {' / '.join([f'{m:.2f}KB' for m in mems_merge])}")
    print(f"Parall {' / '.join([f'{m:.2f}KB' for m in mems_parallel])}\n")


def main():
    base = os.path.dirname(os.path.abspath(__file__))

    arquivos_input = [
        os.path.join(base, "..", "..", "config", "input", "crescente.dat"),
        os.path.join(base, "..", "..", "config", "input", "decrescente.dat"),
        os.path.join(base, "..", "..", "config", "input", "random.dat"),
    ]

    for arquivo in arquivos_input:
        arquivo = os.path.normpath(arquivo)
        print(f"--- Processando: {arquivo} ---")
        try:
            processar_arquivo(arquivo)
        except Exception as e:
            print(f"Erro ao processar {arquivo}: {type(e).__name__}: {e}\n")


if __name__ == "__main__":
    main()