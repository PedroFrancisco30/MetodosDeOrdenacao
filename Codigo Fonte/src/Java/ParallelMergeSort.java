import java.util.ArrayList;
import java.util.List;

public class ParallelMergeSort {

    static final int LIMITE_PARALELO = 3; // Evita explodir threads

    static void paralleMergeSort(List<Integer> array, int indxEsq, int indxDir, int profundidade){
        if(indxEsq < indxDir){
            int meio = (indxEsq + indxDir) / 2;

            if(profundidade > 0) {
                Thread thread1 = new Thread(() -> paralleMergeSort(array, indxEsq, meio, profundidade - 1)); // Ordena o lado esquerda da metade
                Thread thread2 = new Thread(() -> paralleMergeSort(array, meio + 1, indxDir, profundidade - 1)); // Ordena o lado direita a partir da metade

                // Essas lambdas estao abreviando a criacao de um Runnable e metodo run

                thread1.start(); // Iniciou em paralelo
                thread2.start();

                try {
                    thread1.join();
                    thread2.join();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }else{ // Para de criar Threads infinitas
                paralleMergeSort(array, indxEsq, meio, 0);
                paralleMergeSort(array, meio+1, indxDir, 0);
            }


            // Espera as duas acabar para que ai faca o merge
            merge(array, indxEsq, meio, indxDir); // Mescla os dois index os ordenando,
        }
    }

    static void merge(List<Integer> array, int indxEsq, int meio,int indxDir){
        List<Integer> ladoEsq = new ArrayList<>(), ladoDir = new ArrayList<>();

        for (int i = indxEsq; i <= meio; i++)
            ladoEsq.add(array.get(i));

        for (int i = meio + 1; i <= indxDir; i++)
            ladoDir.add(array.get(i));

        int auxEsq = 0, auxDir = 0, auxArray = indxEsq;

        while (auxEsq < ladoEsq.size() && auxDir < ladoDir.size()){ // Enquanto os dois nao chegarem ao limite
            if(ladoEsq.get(auxEsq) <= ladoDir.get(auxDir)){
                array.set(auxArray, ladoEsq.get(auxEsq)); // Joga o elemento pro outro lado do array, ordenando em ele
                auxEsq++;
            }else{
                array.set(auxArray, ladoDir.get(auxDir));
                auxDir++;
            }
            auxArray++;
        }

        while (auxEsq < ladoEsq.size()){
            array.set(auxArray, ladoEsq.get(auxEsq));
            auxEsq++;
            auxArray++;
        }

        while (auxDir < ladoDir.size()){
            array.set(auxArray, ladoDir.get(auxDir));
            auxDir++;
            auxArray++;
        }
    }
}
