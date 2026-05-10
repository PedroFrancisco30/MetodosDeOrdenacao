import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import static java.lang.Math.pow;

public class mainMerge {
    public static void main(String[] args) throws IOException {

        List<Integer> listaNumeros, listaAux;
        long tempoTotal = 0;
        long memoriaTotal = 0;
        Runtime runtime = Runtime.getRuntime();
        MergeSort sorter = new MergeSort();

        System.out.println("Comparacoes de tempo e memoria:");

        // ========== RANDOM ==========
        listaNumeros = lerUltimaLinha.ler("Codigo Fonte/config/input/random.dat");
        System.out.println("\nMerge Sort - Random:");
        System.out.println("Tamanho\t\tTempo Medio (s)\t\tMemoria Media (KB)");

        for (int pot = 2; pot <= 6; pot++) {
            tempoTotal = 0;
            memoriaTotal = 0;

            for (int i = 0; i < 15; i++) {
                listaAux = new ArrayList<>(listaNumeros.subList(0, (int) pow(10, pot)));

                runtime.gc();
                long memAntes = runtime.totalMemory() - runtime.freeMemory();

                long inicio = System.nanoTime();
                sorter.mergeSort(listaAux, 0, listaAux.size() - 1);
                long fim = System.nanoTime();

                long memDepois = runtime.totalMemory() - runtime.freeMemory();

                tempoTotal   += (fim - inicio);
                memoriaTotal += Math.max(0, memDepois - memAntes);
            }

            double tempoMedio   = tempoTotal / 1_000_000_000.0 / 15;
            double memoriaMédia = memoriaTotal / 1024.0 / 15;
            System.out.printf("10^%d\t\t%.6fs\t\t%.2f KB%n", pot, tempoMedio, memoriaMédia);
        }

        // ========== CRESCENTE ==========
        listaNumeros = lerUltimaLinha.ler("Codigo Fonte/config/input/crescente.dat");
        System.out.println("\nMerge Sort - Crescente:");
        System.out.println("Tamanho\t\tTempo Medio (s)\t\tMemoria Media (KB)");

        for (int pot = 2; pot <= 6; pot++) {
            tempoTotal = 0;
            memoriaTotal = 0;

            for (int i = 0; i < 15; i++) {
                listaAux = new ArrayList<>(listaNumeros.subList(0, (int) pow(10, pot)));

                runtime.gc();
                long memAntes = runtime.totalMemory() - runtime.freeMemory();

                long inicio = System.nanoTime();
                sorter.mergeSort(listaAux, 0, listaAux.size() - 1);
                long fim = System.nanoTime();

                long memDepois = runtime.totalMemory() - runtime.freeMemory();

                tempoTotal   += (fim - inicio);
                memoriaTotal += Math.max(0, memDepois - memAntes);
            }

            double tempoMedio   = tempoTotal / 1_000_000_000.0 / 15;
            double memoriaMédia = memoriaTotal / 1024.0 / 15;
            System.out.printf("10^%d\t\t%.6fs\t\t%.2f KB%n", pot, tempoMedio, memoriaMédia);
        }

        // ========== DECRESCENTE ==========
        listaNumeros = lerUltimaLinha.ler("Codigo Fonte/config/input/decrescente.dat");
        System.out.println("\nMerge Sort - Decrescente:");
        System.out.println("Tamanho\t\tTempo Medio (s)\t\tMemoria Media (KB)");

        for (int pot = 2; pot <= 6; pot++) {
            tempoTotal = 0;
            memoriaTotal = 0;

            for (int i = 0; i < 15; i++) {
                listaAux = new ArrayList<>(listaNumeros.subList(0, (int) pow(10, pot)));

                runtime.gc();
                long memAntes = runtime.totalMemory() - runtime.freeMemory();

                long inicio = System.nanoTime();
                sorter.mergeSort(listaAux, 0, listaAux.size() - 1);
                long fim = System.nanoTime();

                long memDepois = runtime.totalMemory() - runtime.freeMemory();

                tempoTotal   += (fim - inicio);
                memoriaTotal += Math.max(0, memDepois - memAntes);
            }

            double tempoMedio   = tempoTotal / 1_000_000_000.0 / 15;
            double memoriaMédia = memoriaTotal / 1024.0 / 15;
            System.out.printf("10^%d\t\t%.6fs\t\t%.2f KB%n", pot, tempoMedio, memoriaMédia);
        }
    }
}