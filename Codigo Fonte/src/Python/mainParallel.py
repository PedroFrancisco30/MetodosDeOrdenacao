import time
import os
from parallel_merge_sort import parallel_merge_sort, LIMITE_PARALELO

RUNS = 15

# ==================== MEDICAO ====================

def medir_tempo(func, lista, profundidade):
    mem_descartada = [0]
    inicio = time.time()
    func(lista, 0, len(lista) - 1, profundidade, mem_descartada)
    return time.time() - inicio


def medir_memoria(func, lista, profundidade):
    mem = [0]
    func(lista, 0, len(lista) - 1, profundidade, mem)
    return mem[0] / 1024


# ==================== PROCESSAMENTO ====================

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

    tempos_parallel = []
    mems_parallel   = []

    for lista_numero in lista_numeros:
        # --- 15 runs para tempo ---
        t_parallel = 0.0
        for _ in range(RUNS):
            t_parallel += medir_tempo(parallel_merge_sort, list(lista_numero), LIMITE_PARALELO)
        tempos_parallel.append(t_parallel / RUNS)

        # --- 1 run separado para memória ---
        mems_parallel.append(medir_memoria(parallel_merge_sort, list(lista_numero), LIMITE_PARALELO))

    tamanhos = [f"10^{p}" for p in range(2, 2 + len(lista_numeros))]

    print(f"{'Tamanho':<10} {'Tempo Medio (s)':<22} {'Memoria (KB)'}")
    print("-" * 55)
    for i, tam in enumerate(tamanhos):
        print(f"{tam:<10} {tempos_parallel[i]:<22.6f} {mems_parallel[i]:.2f}")
    print()


# ==================== MAIN ====================

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