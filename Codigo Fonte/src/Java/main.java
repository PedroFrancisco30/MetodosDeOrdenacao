import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class main {
    public static void main(String[] args) {

        List<Integer> listaNumerosAux;
        List<List<Integer>> listaNumeros = new ArrayList<>(), listaTeste = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader("config/input/input.dat"));) {
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

        for (int j = 0; j < listaNumeros.size(); j++) {
            System.out.println("Tempo gasto para " + listaNumeros.get(j).size() + " elementos.");

            listaTeste.set(0, new ArrayList<>(listaNumeros.get(j)));
            listaTeste.set(1, new ArrayList<>(listaNumeros.get(j)));

            long inicio1 = System.currentTimeMillis();
            MergeSort.mergeSort(listaTeste.get(0), 0, listaTeste.get(0).size() - 1);
            long fim1 = System.currentTimeMillis();

            long inicio2 = System.currentTimeMillis();
            ParallelMergeSort.paralleMergeSort(listaTeste.get(1), 0, listaTeste.get(1).size() - 1, ParallelMergeSort.LIMITE_PARALELO);
            long fim2 = System.currentTimeMillis();

            System.out.println("MergeSort: " + (fim1 - inicio1) + "ms.\n" +
                    "Parallel MergeSort: " + (fim2 - inicio2) + "ms.");
            System.out.println("======================");
        }
    }
}
