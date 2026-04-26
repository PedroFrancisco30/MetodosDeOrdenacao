import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

import static java.lang.Math.pow;

public class writeInput {
    public static void main(String[] args) {
        int limite;

        File file = new File("config/input/input.dat");

        Random random = new Random(42);

        try(FileWriter fw = new FileWriter(file, false)) {

            for(int pot = 2; pot <= 6; pot++) {
                limite = (int) Math.pow(10, pot);
                for (int i = 0; i < limite; i++) {
                    fw.write(random.nextInt(limite) + " ");
                }
                fw.write("\n");
            }

            fw.flush(); // Evitar erros ao compilar do buffer

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
