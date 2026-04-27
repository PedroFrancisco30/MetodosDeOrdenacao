import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class main {
    public static void main(String[] args) {

        List<Integer> listaNumerosAux;
        List<List<Integer>> listaNumeros = new ArrayList<>();

        try(BufferedReader br = new BufferedReader(new FileReader("config/input/input.dat"));){
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
        }catch (IOException e){
            e.printStackTrace();
        }

        System.out.println("Printando tamanhos das listas");

        for (int i = 0; i < listaNumeros.size(); i++) {
            System.out.println(listaNumeros.get(i).size());
        }

        MergeSort.mergeSort(listaNumeros.get(0), 0, listaNumeros.get(0).size()-1);

        System.out.println(listaNumeros.get(0).toString());
    }
}
