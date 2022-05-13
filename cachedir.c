#include "cachedir.h"

#define DUMP_POSITION()                                                     \
    do {                                                                    \
        printf("\n%s: %s: %s", __FILE__, __PRETTY_FUNCTION__, __LINE__);    \
    } while (0);

ComArr initComArr(int c) {
    ComArr common_arr = {};
    common_arr.capacity = 2 * c + NLISTS;

#ifdef SAFEMODE
    if (c > INT_MAX / 2 - NLISTS) {
        DUMP_POSITION();
        printf("\nmemory error: cache capacity exceeds possible max value\n\n");
        return NULL;
    }
    if (c <= 0) {
        DUMP_POSITION();
        printf("\nmemory error: invalid cache capacity value\n\n");
        return NULL;
    }
#endif

    common_arr.data = (Node *) malloc (sizeof (Node) * common_arr.capacity);
#ifdef SAFEMODE
    if (common_arr.data == NULL) {
        DUMP_POSITION();
        printf("\nmemory error: failed to allocate memory for cache directory\n\n");
        return NULL;
    }
#endif

    common_arr.data[T1_FICT_IDX].next = common_arr.data[T1_FICT_IDX].prev = T1_FICT_IDX;
    common_arr.data[T2_FICT_IDX].next = common_arr.data[T2_FICT_IDX].prev = T2_FICT_IDX;
    common_arr.data[B1_FICT_IDX].next = common_arr.data[B1_FICT_IDX].prev = B1_FICT_IDX;
    common_arr.data[B2_FICT_IDX].next = common_arr.data[B2_FICT_IDX].prev = B2_FICT_IDX;

    common_arr.free_list_head = NLISTS;
    for (int i = NLISTS; i < common_arr.capacity; ++i) {
        common_arr.data[i].next = i + 1;
    }
    common_arr.data[common_arr.capacity - 1].next = FREE_END;

    return common_arr;
}

ComArr copyComArr(const ComArr *src) {
    ComArr new_com_arr = {};
    new_com_arr.capacity = src->capacity;
    new_com_arr.free_list_head = src->free_list_head;

    new_com_arr.data = (Node *) malloc (sizeof (Node) * new_com_arr.capacity);
#ifdef SAFEMODE
    if (new_com_arr.data == NULL) {
        DUMP_POSITION();
        printf("\nmemory error: failed to allocate memory for copied cache directory\n\n");
        return NULL;
    }
#endif
    memcpy(new_com_arr.data, src->data, new_com_arr.capacity);

    return new_com_arr;
}

void destrComArr(ComArr *common_arr) {
    common_arr->capacity = common_arr->free_list_head = DESTROYED_COM_ARR;
    free(common_arr->data);
    common_arr->data = NO_PERMISSION_ADDR;
}

DirList getT1(ComArr *common_arr) {
    DirList list = {};
    list.common_arr = common_arr;
    list.fict = T1_FICT_IDX;
    list.size = 0;
    return list;
}

DirList getB1(ComArr *common_arr) {
    DirList list = {};
    list.common_arr = common_arr;
    list.fict = B1_FICT_IDX;
    list.size = 0;
    return list;
}

DirList getT2(ComArr *common_arr) {
    DirList list = {};
    list.common_arr = common_arr;
    list.fict = T2_FICT_IDX;
    list.size = 0;
    return list;
}

DirList getB2(ComArr *common_arr) {
    DirList list = {};
    list.common_arr = common_arr;
    list.fict = B2_FICT_IDX;
    list.size = 0;
    return list;
}

DirList copyDirList(const DirList *src) {
    DirList new_dir_list = *src;
    return new_dir_list;
}

int sizeDirList(const DirList *list) {
    return list->size;
}
