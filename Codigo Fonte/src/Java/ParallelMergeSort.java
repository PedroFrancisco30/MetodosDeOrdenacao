import java.util.ArrayList;
import java.util.List;

public class ParallelMergeSort {

    final int LIMITE_PARALELO = 1;

    void paralleMergeSort(List<Integer> array, int indxEsq, int indxDir, int profundidade) {
        if (indxEsq < indxDir) {
            int meio = (indxEsq + indxDir) / 2;

            if (profundidade > 0) {
                Thread thread1 = new Thread(() -> paralleMergeSort(array, indxEsq, meio, profundidade - 1));
                Thread thread2 = new Thread(() -> paralleMergeSort(array, meio + 1, indxDir, profundidade - 1));

                thread1.start();
                thread2.start();

                try {
                    thread1.join();
                    thread2.join();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            } else {
                paralleMergeSort(array, indxEsq, meio, 0);
                paralleMergeSort(array, meio + 1, indxDir, 0);
            }

            merge(array, indxEsq, meio, indxDir);
        }
    }

    void merge(List<Integer> array, int indxEsq, int meio, int indxDir) {
        List<Integer> ladoEsq = new ArrayList<>(), ladoDir = new ArrayList<>();

        for (int i = indxEsq; i <= meio; i++)
            ladoEsq.add(array.get(i));

        for (int i = meio + 1; i <= indxDir; i++)
            ladoDir.add(array.get(i));

        int auxEsq = 0, auxDir = 0, auxArray = indxEsq;

        while (auxEsq < ladoEsq.size() && auxDir < ladoDir.size()) {
            if (ladoEsq.get(auxEsq) <= ladoDir.get(auxDir)) {
                array.set(auxArray, ladoEsq.get(auxEsq));
                auxEsq++;
            } else {
                array.set(auxArray, ladoDir.get(auxDir));
                auxDir++;
            }
            auxArray++;
        }

        while (auxEsq < ladoEsq.size()) {
            array.set(auxArray, ladoEsq.get(auxEsq));
            auxEsq++;
            auxArray++;
        }

        while (auxDir < ladoDir.size()) {
            array.set(auxArray, ladoDir.get(auxDir));
            auxDir++;
            auxArray++;
        }
    }
}