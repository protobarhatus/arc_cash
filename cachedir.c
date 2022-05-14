#include "cachedir.h"

#define DUMP_POSITION(comment_str)                                          \
    do {                                                                    \
        printf("\n%s: %s: %s", __FILE__, __PRETTY_FUNCTION__, __LINE__);    \
        printf(comment_str);                                                \
    } while (0);

static DirListIterator insertBeforeNS(DirList *list, DirListIterator idx, PageId *page);
static DirListIterator insertAfterNS(DirList *list, DirListIterator idx, PageId *page);
static void deleteNodeNS(DirList *list, DirListIterator idx);

ComArr initComArr(int c) {
    ComArr common_arr = {};
    common_arr.capacity = 2 * c + NLISTS;

#ifdef SAFEMODE
    if (c >= INT_MAX / 2 - NLISTS) {
        DUMP_POSITION("\nmemory error: cache capacity exceeds possible max value\n\n");
        destrComArr(common_arr);
        return common_arr;
    }
    if (c <= 0) {
        DUMP_POSITION("\nmemory error: invalid cache capacity value\n\n");
        destrComArr(common_arr);
        return common_arr;
    }
#endif

    common_arr.data = (Node *) malloc (sizeof(Node) * common_arr.capacity);
#ifdef SAFEMODE
    if (common_arr.data == NULL) {
        DUMP_POSITION("\nmemory error: failed to allocate memory for cache directory\n\n");
        destrComArr(common_arr);
        return common_arr;
    }
#endif

    common_arr.data[T1_FICT_IDX].next = common_arr.data[T1_FICT_IDX].prev = common_arr.data[T1_FICT_IDX].fict = T1_FICT_IDX;
    common_arr.data[T2_FICT_IDX].next = common_arr.data[T2_FICT_IDX].prev = common_arr.data[T2_FICT_IDX].fict = T2_FICT_IDX;
    common_arr.data[B1_FICT_IDX].next = common_arr.data[B1_FICT_IDX].prev = common_arr.data[B1_FICT_IDX].fict = B1_FICT_IDX;
    common_arr.data[B2_FICT_IDX].next = common_arr.data[B2_FICT_IDX].prev = common_arr.data[B2_FICT_IDX].fict = B2_FICT_IDX;

    common_arr.free_list_head = NLISTS;
    for (int i = NLISTS; i < common_arr.capacity; ++i) {
        common_arr.data[i].next = i + 1;
        common_arr.data[i].fict = FREE_NODE;
    }
    common_arr.data[common_arr.capacity - 1].next = FREE_END;

    return common_arr;
}

ComArr copyComArr(const ComArr *src) {
    assert(src);

    ComArr new_com_arr = {};
    new_com_arr.capacity = src->capacity;
    new_com_arr.free_list_head = src->free_list_head;

    new_com_arr.data = (Node *) malloc (sizeof(Node) * new_com_arr.capacity);
#ifdef SAFEMODE
    if (new_com_arr.data == NULL) {
        DUMP_POSITION("\nmemory error: failed to allocate memory for copied cache directory\n\n");
        destrComArr(new_com_arr);
        return new_com_arr;
    }
#endif
    memcpy(new_com_arr.data, src->data, new_com_arr.capacity * sizeof(Node));

    return new_com_arr;
}

void destrComArr(ComArr *common_arr) {
    assert(common_arr);
#ifdef SAFEMODE
    if (common_arr->capacity == DESTROYED_COM_ARR) {
        DUMP_POSITION("\nruntime error: common array redestruction requested\n\n");
        if (common_arr->data) {
            free(common_arr->data);
        }
        common_arr->data = NO_PERMISSION_ADDR;
        return;
    }
#endif
    common_arr->capacity = common_arr->free_list_head = DESTROYED_COM_ARR;
    if (common_arr->data) {
        free(common_arr->data);
    }
    common_arr->data = NO_PERMISSION_ADDR;
}

DirList getT1(const ComArr *common_arr) {
    assert(common_arr);
    DirList list = {};
    list.common_arr = common_arr;
    list.fict = T1_FICT_IDX;
    list.size = 0;
    return list;
}

DirList getB1(const ComArr *common_arr) {
    assert(common_arr);
    DirList list = {};
    list.common_arr = common_arr;
    list.fict = B1_FICT_IDX;
    list.size = 0;
    return list;
}

DirList getT2(const ComArr *common_arr) {
    assert(common_arr);
    DirList list = {};
    list.common_arr = common_arr;
    list.fict = T2_FICT_IDX;
    list.size = 0;
    return list;
}

DirList getB2(const ComArr *common_arr) {
    assert(common_arr);
    DirList list = {};
    list.common_arr = common_arr;
    list.fict = B2_FICT_IDX;
    list.size = 0;
    return list;
}

DirList copyDirList(const DirList *src) {
    assert(src);
    DirList new_dir_list = *src;
    return new_dir_list;
}

int sizeDirList(const DirList *list) {
    assert(list);
    return list->size;
}

DirListIterator pushBack(DirList *list, const PageId *page) {
    assert(list);
    assert(page);
#ifdef SAFEMODE
    if (list->common_arr->free_list_head == FREE_END) {
        DUMP_POSITION("\nruntime error: free node over capacity limit requested\n\n");
        return endDirList();
    }
#endif
    return insertBeforeNS(list, list->fict, page);
}

DirListIterator pushFront(DirList *list, const PageId *page) {
    assert(list);
    assert(page);
#ifdef SAFEMODE
    if (list->common_arr->free_list_head == FREE_END) {
        DUMP_POSITION("\nruntime error: free node over capacity limit requested\n\n");
        return endDirList();
    }
#endif
    return insertAfterNS(list, list->fict, page);
}

DirListIterator endDirList() {
    return END_OF_DIR_LIST;
}

DirListIterator firstDirList(const DirList *list) {
    assert(list);
    return (list->size > 0) ? list->common_arr->data[list->fict].next : endDirList();
}

DirListIterator lastDirList(const DirList *list) {
    assert(list);
    return (list->size > 0) ? list->common_arr->data[list->fict].prev : endDirList();
}

DirListIterator iterateDirList(const ComArr *common_arr, DirListIterator idx) {
    assert(common_arr);

    DirListIterator next = -1;
#ifdef SAFEMODE
    if (idx < NLISTS || idx >= common_arr->capacity) {
        DUMP_POSITION("\nruntime error: invalid idx to iterate\n\n");
        return endDirList();
    }
    if (common_arr->data[idx].fict == FREE_NODE) {
        DUMP_POSITION("\nruntime error: free node iteration requested\n\n");
        return endDirList();
    }
#endif
    next = common_arr->data[idx].next;
    return (next < NLISTS) ? endDirList() : next;
}

void eraseNode(DirList *list, DirListIterator idx) {            // should be checked carefully
    assert(list);

#ifdef SAFEMODE
    if (idx < NLISTS || idx >= list->common_arr->capacity) {
        DUMP_POSITION("\nruntime error: invalid idx to erase\n\n");
        return;
    }
    if (list->common_arr->data[idx].fict == FREE_NODE) {
        DUMP_POSITION("\nruntime error: free node deletion requested\n\n");
        return;
    }
#endif
    deleteNodeNS(list, idx);
}

PageId *nodeData(const ComArr *common_arr, DirListIterator idx) {
    assert(common_arr);

#ifdef SAFEMODE
    if (idx < NLISTS || idx >= common_arr->capacity) {
        DUMP_POSITION("\nruntime error: invalid idx to get data\n\n");
        return NULL;
    }
    if (common_arr->data[idx].fict == FREE_NODE) {
        DUMP_POSITION("\nruntime error: free node data requested\n\n");
        return NULL;
    }
#endif
    return common_arr->data[idx].page;
}

bool isInDirList(const DirList *list, DirListIterator idx) {
    assert(list);

#ifdef SAFEMODE
    if (idx < 0 || idx >= list->common_arr->capacity) {
        DUMP_POSITION("\nruntime error: invalid idx checked for being in a list\n\n");
        return NULL;
    }
#endif
    return (list->common_arr->data[idx].fict == list->fict) ? true : false;
}

void moveNodeToBegin(DirList *dest_list, DirListIterator src_idx) {
    assert(dest_list);

    Node *data = dest_list->common_arr->data;
#ifdef SAFEMODE
    if (src_idx < NLISTS || src_idx >= dest_list->common_arr->capacity) {
        DUMP_POSITION("\nruntime error: invalid idx to move to another list\n\n");
        return;
    }
    if (data[src_idx].fict == FREE_NODE) {
        DUMP_POSITION("\nruntime error: free node displacement requested\n\n");
        return;
    }
#endif

    data[data[src_idx].next].prev = data[src_idx].prev;
    data[data[src_idx].prev].next = data[src_idx].next;
    data[src_idx].next = data[dest_list->fict].next;
    data[src_idx].prev = dest_list->fict;
    data[data[dest_list->fict].next].prev = src_idx;
    data[dest_list->fict].next = src_idx;
}

void moveNodeToEnd(DirList *dest_list, DirListIterator src_idx) {
    assert(dest_list);

    Node *data = dest_list->common_arr->data;
#ifdef SAFEMODE
    if (src_idx < NLISTS || src_idx >= dest_list->common_arr->capacity) {
        DUMP_POSITION("\nruntime error: invalid idx to move to another list\n\n");
        return;
    }
    if (data[src_idx].fict == FREE_NODE) {
        DUMP_POSITION("\nruntime error: free node displacement requested\n\n");
        return;
    }
#endif

    data[data[src_idx].next].prev = data[src_idx].prev;
    data[data[src_idx].prev].next = data[src_idx].next;
    data[src_idx].prev = data[dest_list->fict].prev;
    data[src_idx].next = dest_list->fict;
    data[data[dest_list->fict].prev].next = src_idx;
    data[dest_list->fict].prev = src_idx;
}

static DirListIterator insertBeforeNS(DirList *list, DirListIterator idx, PageId *page) {
    Node *data = list->common_arr->data;
    ComArr *common_arr = list->common_arr;
    DirListIterator new_idx = -1;

    data[data[idx].prev].next = new_idx = common_arr->free_list_head;
    common_arr->free_list_head = data[common_arr->free_list_head].next;
    data[new_idx].prev = data[idx].prev;
    data[new_idx].next = idx;
    data[new_idx].page = page;
    data[new_idx].fict = data[idx].fict;
    data[idx].prev = new_idx;

    list->size += 1;
    return new_idx;
}

static DirListIterator insertAfterNS(DirList *list, DirListIterator idx, PageId *page) {
    Node *data = list->common_arr->data;
    ComArr *common_arr = list->common_arr;
    DirListIterator new_idx = -1;

    data[data[idx].next].prev = new_idx = common_arr->free_list_head;
    common_arr->free_list_head = data[common_arr->free_list_head].next;
    data[new_idx].next = data[idx].next;
    data[new_idx].prev = idx;
    data[new_idx].page = page;
    data[new_idx].fict = data[idx].fict;
    data[idx].next = new_idx;

    list->size += 1;
    return new_idx;
}

static void deleteNodeNS(DirList *list, DirListIterator idx) {
    Node *data = list->common_arr->data;
    ComArr *common_arr = list->common_arr;

    data[data[idx].next].prev = data[idx].prev;
    data[data[idx].prev].next = data[idx].next;
    data[idx].next = common_arr->free_list_head;
    common_arr->free_list_head = idx;
    data[idx].fict = FREE_NODE;

    list->size -= 1;
}

#undef DUMP_POSITION
