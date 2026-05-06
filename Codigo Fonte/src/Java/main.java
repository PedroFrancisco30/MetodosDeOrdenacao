import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class main {
    public static void main(String[] args) {

        List<Integer> listaNumerosRandom = new ArrayList<>(), listaNumerosCres = new ArrayList<>(), listaNumerosDec = new ArrayList<>();
        String ultima = "";

        // Lendo input
        try (BufferedReader br = new BufferedReader(new FileReader("Codigo Fonte/config/input/random.dat"))) {
            String linha;
            while ((linha = br.readLine()) != null) {
                ultima = linha; // Sempre sobrescreve, fica com a última
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // "ultima" agora contém a última linha do arquivo
        if (ultima != null) {
            listaNumerosRandom = new ArrayList<>();
            for (String num : ultima.trim().split("\\s+")) {
                if (!num.isEmpty()) {
                    listaNumerosRandom.add(Integer.parseInt(num));
                }
            }
        }

        try (BufferedReader br = new BufferedReader(new FileReader("Codigo Fonte/config/input/crescente.dat"))) {
            String linha;
            while ((linha = br.readLine()) != null) {
                ultima = linha; // Sempre sobrescreve, fica com a última
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // "ultima" agora contém a última linha do arquivo
        if (ultima != null) {
            listaNumerosCres = new ArrayList<>();
            for (String num : ultima.trim().split("\\s+")) {
                if (!num.isEmpty()) {
                    listaNumerosCres.add(Integer.parseInt(num));
                }
            }
        }

        try (BufferedReader br = new BufferedReader(new FileReader("Codigo Fonte/config/input/crescente.dat"))) {
            String linha;
            while ((linha = br.readLine()) != null) {
                ultima = linha; // Sempre sobrescreve, fica com a última
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // "ultima" agora contém a última linha do arquivo
        if (ultima != null) {
            listaNumerosCres = new ArrayList<>();
            for (String num : ultima.trim().split("\\s+")) {
                if (!num.isEmpty()) {
                    listaNumerosCres.add(Integer.parseInt(num));
                }
            }
        }

        System.out.println(listaNumerosRandom.size());


    }
}
