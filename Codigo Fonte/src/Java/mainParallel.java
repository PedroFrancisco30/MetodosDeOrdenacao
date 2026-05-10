import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicLong;
import static java.lang.Math.pow;

public class mainParallel {
    public static void main(String[] args) throws IOException {
        List<Integer> listaNumeros, listaAux;
        ParallelMergeSort sorter = new ParallelMergeSort();

        System.out.println("Comparacoes de tempo e memoria:");

        String[] nomes    = { "Random", "Crescente", "Decrescente" };
        String[] arquivos = {
                "Codigo Fonte/config/input/random.dat",
                "Codigo Fonte/config/input/crescente.dat",
                "Codigo Fonte/config/input/decrescente.dat"
        };

        for (int f = 0; f < arquivos.length; f++) {
            listaNumeros = lerUltimaLinha.ler(arquivos[f]);
            System.out.println("\nParallel Merge Sort - " + nomes[f] + ":");
            System.out.println("Tamanho\t\tTempo Medio (s)\t\tMemoria (KB)");

            for (int pot = 2; pot <= 6; pot++) {
                int tamanho = (int) pow(10, pot);

                // --- 15 runs só para tempo ---
                long tempoTotal = 0;
                for (int i = 0; i < 15; i++) {
                    listaAux = new ArrayList<>(listaNumeros.subList(0, tamanho));
                    AtomicLong memDescartada = new AtomicLong(0);

                    long inicio = System.nanoTime();
                    sorter.paralleMergeSort(listaAux, 0, listaAux.size() - 1,
                            sorter.LIMITE_PARALELO, memDescartada);
                    long fim = System.nanoTime();
                    tempoTotal += (fim - inicio);
                }
                double tempoMedio = tempoTotal / 1_000_000_000.0 / 15;

                // --- 1 run separado só para memória ---
                listaAux = new ArrayList<>(listaNumeros.subList(0, tamanho));
                AtomicLong mem = new AtomicLong(0);
                sorter.paralleMergeSort(listaAux, 0, listaAux.size() - 1,
                        sorter.LIMITE_PARALELO, mem);
                double memoriaKb = mem.get() / 1024.0;

                System.out.printf("10^%d\t\t%.6fs\t\t%.2f KB%n", pot, tempoMedio, memoriaKb);
            }
        }
    }
}