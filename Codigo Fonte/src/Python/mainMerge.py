import time
import os
from merge_sort import merge_sort

RUNS = 15

# ==================== MEDICAO ====================

def medir_tempo(func, lista, *args):
    inicio = time.time()
    mem_descartada = [0]
    func(lista, 0, len(lista) - 1, mem_descartada, *args)
    return time.time() - inicio


def medir_memoria(func, lista, *args):
    mem = [0]
    func(lista, 0, len(lista) - 1, mem, *args)
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

    tempos_merge = []
    mems_merge   = []

    for lista_numero in lista_numeros:
        # --- 15 runs para tempo ---
        t_merge = 0.0
        for _ in range(RUNS):
            t_merge += medir_tempo(merge_sort, list(lista_numero))
        tempos_merge.append(t_merge / RUNS)

        # --- 1 run separado para memória ---
        mems_merge.append(medir_memoria(merge_sort, list(lista_numero)))

    tamanhos = [f"10^{p}" for p in range(2, 2 + len(lista_numeros))]

    print(f"{'Tamanho':<10} {'Tempo Medio (s)':<22} {'Memoria (KB)'}")
    print("-" * 55)
    for i, tam in enumerate(tamanhos):
        print(f"{tam:<10} {tempos_merge[i]:<22.6f} {mems_merge[i]:.2f}")
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