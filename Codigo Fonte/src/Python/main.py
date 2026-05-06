import time
import os
from merge_sort import merge_sort
from parallel_merge_sort import parallel_merge_sort, LIMITE_PARALELO

def main():
    lista_numeros = []
    tempos_medios_merge = []
    tempos_medios_parallel = []

    caminho_arquivo = "input.dat"

    # Lendo input
    try:
        with open(caminho_arquivo, 'r') as arquivo:
            for linha in arquivo:
                linha_numeros = [int(num) for num in linha.strip().split() if num]
                if linha_numeros:
                    lista_numeros.append(linha_numeros)
    except FileNotFoundError:
        print(f"Erro: Arquivo não encontrado em {caminho_arquivo}")
        return

    for lista_numero in lista_numeros:
        tempo_merge_aux = 0.0
        tempo_merge_parallel_aux = 0.0

        for _ in range(15):
            lista_teste_seq = list(lista_numero)
            lista_teste_paral = list(lista_numero)

            # --- Teste Sequencial ---
            inicio1 = time.time() * 1000
            merge_sort(lista_teste_seq, 0, len(lista_teste_seq) - 1)
            fim1 = time.time() * 1000

            # --- Teste Paralelo ---
            inicio2 = time.time() * 1000
            parallel_merge_sort(lista_teste_paral, 0, len(lista_teste_paral) - 1, LIMITE_PARALELO)
            fim2 = time.time() * 1000

            tempo_merge_aux += (fim1 - inicio1)
            tempo_merge_parallel_aux += (fim2 - inicio2)

        tempos_medios_merge.append(tempo_merge_aux / 15.0)
        tempos_medios_parallel.append(tempo_merge_parallel_aux / 15.0)

    print("Tempos medios apos 15 testes: ")
    print("Metodo - 10^2  /  10^3  /  10^4  /  10^5  /  10^6")
   
    str_merge = " / ".join([f"{tempo:.2f}" for tempo in tempos_medios_merge])
    str_parallel = " / ".join([f"{tempo:.2f}" for tempo in tempos_medios_parallel])
   
    print(f"Merge  {str_merge}")
    print(f"Parall {str_parallel}")

if __name__ == "__main__":
    main()
