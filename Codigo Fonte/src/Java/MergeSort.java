import java.util.ArrayList;
import java.util.List;

public class MergeSort {

    void mergeSort(List<Integer> array, int indxEsq, int indxDir, long[] mem) {
        if (indxEsq < indxDir) {
            int meio = (indxEsq + indxDir) / 2;

            mergeSort(array, indxEsq, meio, mem);
            mergeSort(array, meio + 1, indxDir, mem);
            merge(array, indxEsq, meio, indxDir, mem);
        }
    }

    void merge(List<Integer> array, int indxEsq, int meio, int indxDir, long[] mem) {
        int tamanho = indxDir - indxEsq + 1;

        // Conta os bytes alocados pelos dois buffers temporários (4 bytes por int)
        mem[0] += (long) tamanho * 4;

        List<Integer> ladoEsq = new ArrayList<>();
        List<Integer> ladoDir = new ArrayList<>();

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