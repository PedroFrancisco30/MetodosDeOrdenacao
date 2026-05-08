import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import static java.lang.Math.pow;

public class mainParallel {
    static void main() throws IOException {
        List<Integer> listaNumerosRandom, listaNumerosCres, listaNumerosDec, listaAux;
        String ultima = "";
        long tempoTotal = 0;

        listaNumerosRandom = lerUltimaLinha.ler("Codigo Fonte/config/input/random.dat");

        //System.out.println(listaNumerosRandom.size());
        //System.out.println(listaNumerosCres.size());
        //System.out.println(listaNumerosDec.size());

        System.out.println("Comparacoes de tempo:");

/*
        System.out.println("Merge Sorte Random:");
        for(int pot = 2; pot <= 6; pot++) {
            tempoTotal = 0;
            for (int i = 0; i < 15; i++) {
                listaAux = new ArrayList<>(listaNumerosRandom.subList(0, (int) pow(10, pot))); // cópia!

                long inicio = System.nanoTime();
                ParallelMergeSort.paralleMergeSort(listaAux, 0, listaAux.size()-1, ParallelMergeSort.LIMITE_PARALELO);
                long fim = System.nanoTime();

                tempoTotal += (fim - inicio);
            }
            double tempoMedio = tempoTotal / 1_000_000_000.0 / 15;
            System.out.printf("%.6f\t", tempoMedio);
        }



        listaNumerosCres   = lerUltimaLinha.ler("Codigo Fonte/config/input/crescente.dat");
        System.out.println("\nMerge Sorte Ordenado Crescente:");
        for(int pot = 2; pot <= 6; pot++) {
            tempoTotal = 0;
            for (int i = 0; i < 15; i++) {
                listaAux = new ArrayList<>(listaNumerosCres.subList(0, (int) pow(10, pot))); // cópia!

                long inicio = System.nanoTime();
                ParallelMergeSort.paralleMergeSort(listaAux, 0, listaAux.size()-1, ParallelMergeSort.LIMITE_PARALELO);
                long fim = System.nanoTime();

                tempoTotal += (fim - inicio);
            }
            double tempoMedio = tempoTotal / 1_000_000_000.0 / 15;
            System.out.printf("%.6f\t", tempoMedio);
        }


*/
        listaNumerosDec    = lerUltimaLinha.ler("Codigo Fonte/config/input/decrescente.dat");
        System.out.println("\nMerge Sorte Ordenado Decrescente:");
        for(int pot = 2; pot <= 6; pot++) {
            tempoTotal = 0;
            for (int i = 0; i < 15; i++) {
                listaAux = new ArrayList<>(listaNumerosDec.subList(0, (int) pow(10, pot))); // cópia!

                long inicio = System.nanoTime();
                ParallelMergeSort.paralleMergeSort(listaAux, 0, listaAux.size()-1, ParallelMergeSort.LIMITE_PARALELO);
                long fim = System.nanoTime();

                tempoTotal += (fim - inicio);
            }
            double tempoMedio = tempoTotal / 1_000_000_000.0 / 15;
            System.out.printf("%.6f\t", tempoMedio);
        }


    }
}
