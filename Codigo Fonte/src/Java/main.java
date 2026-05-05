import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class main {
    public static void main(String[] args) {

        List<Integer> listaNumerosAux;
        List<Double> temposMediosMerge = new ArrayList<>(), temposMediosParallel = new ArrayList<>();
        List<List<Integer>> listaNumeros = new ArrayList<>(), listaTeste = new ArrayList<>();
        long tempoMergeAux, tempoMergeParallelAux, inicio1 = 0, inicio2 = 0, fim1 = 0, fim2 = 0;

        // Lendo input
        try (BufferedReader br = new BufferedReader(new FileReader("Codigo Fonte/config/input/input.dat"));) {
            String linha;
            while ((linha = br.readLine()) != null) {
                listaNumerosAux = new ArrayList<>(); // Nova lista para cada linha

                for (String num : linha.trim().split("\\s+")) { // Separa em array por espaco
                    if (!num.isEmpty()) {
                        listaNumerosAux.add(Integer.parseInt(num));
                    }
                }

                listaNumeros.add(listaNumerosAux);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        listaTeste.add(new ArrayList<>());
        listaTeste.add(new ArrayList<>());

        for (List<Integer> listaNumero : listaNumeros) {
            tempoMergeAux = 0;
            tempoMergeParallelAux = 0;
            for (int i = 0; i < 15; i++) {
                listaTeste.set(0, new ArrayList<>(listaNumero));

                inicio1 = System.nanoTime();
                MergeSort.mergeSort(listaTeste.getFirst(), 0, listaTeste.getFirst().size() - 1);
                fim1 = System.nanoTime();

                tempoMergeAux += (fim1 - inicio1);
            }

            for(int i = 0; i < 15; i++){
                listaTeste.set(1, new ArrayList<>(listaNumero));

                inicio2 = System.nanoTime();
                ParallelMergeSort.paralleMergeSort(listaTeste.get(1), 0, listaTeste.get(1).size() - 1, ParallelMergeSort.LIMITE_PARALELO);
                fim2 = System.nanoTime();

                tempoMergeParallelAux += (fim2 - inicio2);
            }

            temposMediosMerge.add((double)tempoMergeAux / 15 / 1_000_000_000);
            temposMediosParallel.add((double)tempoMergeParallelAux / 15 / 1_000_000_000);
        }

        System.out.println("Tempos medios apos 15 testes: ");
        System.out.println("Metodo - 10a2  /  10a3  /  10a4  /  10a5  /  10a6");
        System.out.printf("Merge    %f\t%f\t%f\t%f\t%f\n", temposMediosMerge.get(0), temposMediosMerge.get(1), temposMediosMerge.get(2), temposMediosMerge.get(3), temposMediosMerge.get(4));
        System.out.printf("Parallel %f\t%f\t%f\t%f\t%f\n", temposMediosParallel.get(0), temposMediosParallel.get(1), temposMediosParallel.get(2), temposMediosParallel.get(3), temposMediosParallel.get(4));
    }
}
