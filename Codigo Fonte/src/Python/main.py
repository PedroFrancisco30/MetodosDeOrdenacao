import time
import os
from merge_sort import merge_sort
from parallel_merge_sort import parallel_merge_sort, LIMITE_PARALELO

def processar_arquivo(caminho_arquivo):
    lista_numeros = []
    tempos_medios_merge = []
    tempos_medios_parallel = []

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
        print(f"Aviso: O arquivo {caminho_arquivo} está vazio ou com formato inválido.\n")
        return

    for lista_numero in lista_numeros:
        tempo_merge_aux = 0.0
        tempo_merge_parallel_aux = 0.0

        for _ in range(15):
            lista_teste_seq = list(lista_numero)
            lista_teste_paral = list(lista_numero)

            inicio1 = time.time() * 1000
            merge_sort(lista_teste_seq, 0, len(lista_teste_seq) - 1)
            fim1 = time.time() * 1000

            inicio2 = time.time() * 1000
            parallel_merge_sort(lista_teste_paral, 0, len(lista_teste_paral) - 1, LIMITE_PARALELO)
            fim2 = time.time() * 1000

            tempo_merge_aux += (fim1 - inicio1)
            tempo_merge_parallel_aux += (fim2 - inicio2)

        tempos_medios_merge.append(tempo_merge_aux / 15.0)
        tempos_medios_parallel.append(tempo_merge_parallel_aux / 15.0)

    print("Metodo - 10^2  /  10^3  /  10^4  /  10^5  /  10^6")
    
    str_merge = " / ".join([f"{tempo:.2f}" for tempo in tempos_medios_merge])
    str_parallel = " / ".join([f"{tempo:.2f}" for tempo in tempos_medios_parallel])
    
    print(f"Merge  {str_merge}")
    print(f"Parall {str_parallel}\n")

def main():
    # Array contendo os caminhos para os 3 arquivos
    arquivos_input = [
        "crescente.dat",
        "decrescente.dat",
        "random.dat"
    ]

    for arquivo in arquivos_input:
        print(f"--- Processando resultados para: {arquivo} ---")
        processar_arquivo(arquivo)

if __name__ == "__main__":
    main()
