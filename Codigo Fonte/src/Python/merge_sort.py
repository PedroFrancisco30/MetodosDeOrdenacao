def merge(array, indx_esq, meio, indx_dir, mem):
    lado_esq = array[indx_esq : meio + 1]
    lado_dir = array[meio + 1 : indx_dir + 1]

    # Conta os bytes alocados pelos dois slices temporários (8 bytes por ponteiro em CPython 64-bit)
    mem[0] += (indx_dir - indx_esq + 1) * 8

    aux_esq   = 0
    aux_dir   = 0
    aux_array = indx_esq

    while aux_esq < len(lado_esq) and aux_dir < len(lado_dir):
        if lado_esq[aux_esq] <= lado_dir[aux_dir]:
            array[aux_array] = lado_esq[aux_esq]
            aux_esq += 1
        else:
            array[aux_array] = lado_dir[aux_dir]
            aux_dir += 1
        aux_array += 1

    while aux_esq < len(lado_esq):
        array[aux_array] = lado_esq[aux_esq]
        aux_esq += 1
        aux_array += 1

    while aux_dir < len(lado_dir):
        array[aux_array] = lado_dir[aux_dir]
        aux_dir += 1
        aux_array += 1


def merge_sort(array, indx_esq, indx_dir, mem):
    if indx_esq < indx_dir:
        meio = (indx_esq + indx_dir) // 2
        merge_sort(array, indx_esq, meio, mem)
        merge_sort(array, meio + 1, indx_dir, mem)
        merge(array, indx_esq, meio, indx_dir, mem)