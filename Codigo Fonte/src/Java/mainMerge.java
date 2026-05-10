import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import static java.lang.Math.pow;

public class mainMerge {
    public static void main(String[] args) throws IOException {

        List<Integer> listaNumeros, listaAux;
        MergeSort sorter = new MergeSort();

        System.out.println("Comparacoes de tempo e memoria:");

        String[] nomes    = { "Random", "Crescente", "Decrescente" };
        String[] arquivos = {
                "Codigo Fonte/config/input/random.dat",
                "Codigo Fonte/config/input/crescente.dat",
                "Codigo Fonte/config/input/decrescente.dat"
        };

        for (int f = 0; f < arquivos.length; f++) {
            listaNumeros = lerUltimaLinha.ler(arquivos[f]);
            System.out.println("\nMerge Sort - " + nomes[f] + ":");
            System.out.println("Tamanho\t\tTempo Medio (s)\t\tMemoria (KB)");

            for (int pot = 2; pot <= 6; pot++) {
                int tamanho = (int) pow(10, pot);

                // --- 15 runs só para tempo ---
                long tempoTotal = 0;
                for (int i = 0; i < 15; i++) {
                    listaAux = new ArrayList<>(listaNumeros.subList(0, tamanho));
                    long[] memDescartada = { 0 };

                    long inicio = System.nanoTime();
                    sorter.mergeSort(listaAux, 0, listaAux.size() - 1, memDescartada);
                    long fim = System.nanoTime();
                    tempoTotal += (fim - inicio);
                }
                double tempoMedio = tempoTotal / 1_000_000_000.0 / 15;

                // --- 1 run separado só para memória ---
                listaAux = new ArrayList<>(listaNumeros.subList(0, tamanho));
                long[] mem = { 0 };
                sorter.mergeSort(listaAux, 0, listaAux.size() - 1, mem);
                double memoriaKb = mem[0] / 1024.0;

                System.out.printf("10^%d\t\t%.6fs\t\t%.2f KB%n", pot, tempoMedio, memoriaKb);
            }
        }
    }
}