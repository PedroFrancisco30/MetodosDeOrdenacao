import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class lerUltimaLinha {

    public static List<Integer> ler(String caminho) throws IOException {
        String ultima = "";
        try (BufferedReader br = new BufferedReader(new FileReader(caminho))) {
            String linha;
            while ((linha = br.readLine()) != null) {
                ultima = linha;
            }
        }
        List<Integer> lista = new ArrayList<>();
        for (String num : ultima.trim().split("\\s+")) {
            if (!num.isEmpty()) {
                lista.add(Integer.parseInt(num));
            }
        }
        return lista;
    }
}
