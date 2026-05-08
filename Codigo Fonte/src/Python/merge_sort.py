def merge(array, indx_esq, meio, indx_dir):
    lado_esq = array[indx_esq : meio + 1]
    lado_dir = array[meio + 1 : indx_dir + 1]

    aux_esq = 0
    aux_dir = 0
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


def merge_sort(array, indx_esq, indx_dir):
    if indx_esq < indx_dir:
        meio = (indx_esq + indx_dir) // 2
        merge_sort(array, indx_esq, meio)
        merge_sort(array, meio + 1, indx_dir)
        merge(array, indx_esq, meio, indx_dir)