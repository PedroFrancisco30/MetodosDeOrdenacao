import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class writeInput {
    public static void main(String[] args) {
        int limite;

        File file = new File("Codigo Fonte/config/input/random.dat");

        Random random = new Random(42);

        try(FileWriter fw = new FileWriter(file, false)) {

            // Criando aleatorio
            for(int pot = 2; pot <= 6; pot++) {
                limite = (int) Math.pow(10, pot);
                for (int i = 0; i < limite; i++) {
                    fw.write(random.nextInt(limite) + " ");
                }
                fw.write("\n");
            }

            /*
            // Criando crescente
            for(int pot = 2; pot <= 6; pot++) {
                limite = (int) Math.pow(10, pot);
                for (int i = 0; i < limite; i++) {
                    fw.write(i + " ");
                }
                fw.write("\n");
            }
             */

            /*
            //Criando decrescente
            for(int pot = 2; pot <= 6; pot++) {
                limite = (int) Math.pow(10, pot);
                for (int i = 0; i < limite; i++) {
                    fw.write(limite-i + " ");
                }
                fw.write("\n");
            }
             */

            fw.flush(); // Evitar erros ao compilar do buffer



        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
