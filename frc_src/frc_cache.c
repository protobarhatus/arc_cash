#include "frc_cache.h"

typedef HashMapIntDlitIterator PageLoc;

static int intMin(int a, int b);
static int intMax(int a, int b);
static Dlit iterData(PageLoc iter);
static bool isPagelocInDirList(FrcCache *cash, PageLoc x, const DirList *dir);
static void addNewPageToT1(FrcCache *cash, PageId page);
static void deletePageFromDBL(FrcCache *cash, DirList *list, Dlit page);
static int absL1(FrcCache *cash);
static int absL2(FrcCache *cash);

FrcCache defaultFrcCache(int c, int p, int hashmap_length) {
    FrcCache res;
    res.p = p;
    res.c = c;
    res.pages_map = makeHashMapIntDlit(hashmap_length, HM_INT_STANDART_CACHE);
    res.dbl_store = calloc(1, sizeof(ComArr));
    *res.dbl_store = initComArr(c);
    res.T1 = getT1(res.dbl_store);
    res.T2 = getT2(res.dbl_store);
    res.B1 = getB1(res.dbl_store);
    res.B2 = getB2(res.dbl_store);

    return res;
}

void destructFrcCache(FrcCache *cash) {
    destructHashMapIntDlit(&cash->pages_map);
    destrComArr(cash->dbl_store);
    free(cash->dbl_store);
}

static int intMin(int a, int b) {
    return a < b ? a : b;
}

static int intMax(int a, int b) {
    return a > b ? a : b;
}

static Dlit iterData(PageLoc iter) {
    return iter.second->data->second;
}

static bool isPagelocInDirList(FrcCache *cash, PageLoc x, const DirList *dir) {
    return !isEndHashMapIntDlit(&cash->pages_map, x) && isInDirList(iterData(x), dir);
}


static void addNewPageToT1(FrcCache *cash, PageId page) {
    Dlit it = pushFront(&cash->T1, &page);
    addElementHashMapIntDlit(&cash->pages_map, page.page, &it);
}

static void deletePageFromDBL(FrcCache *cash, DirList *list, Dlit page) {
    int page_num = nodeData(cash->dbl_store, page)->page;
    eraseFromHashMapIntDlit(&cash->pages_map, atHashMapIntDlit(&cash->pages_map, page_num));
    eraseNode(list, page);
}

static int absL1(FrcCache *cash) {
    return sizeDirList(&cash->T1) + sizeDirList(&cash->B1);
}

static int absL2(FrcCache *cash) {
    return sizeDirList(&cash->T2) + sizeDirList(&cash->B2);
}

// x должен пойти в T1
bool checkOutIfFrcAndDBLMiss(FrcCache *cash, int page, PageLoc iter) {
    //L1 заполненно. Соответственно T1 тоже заполненно
    if (absL1(cash) == cash->c) {
        deletePageFromDBL(cash, &cash->B1, lastDirList(&cash->B1));
        moveNodeToBegin(&cash->B1, lastDirList(&cash->T1));
        PageId p = {page, 0};
        addNewPageToT1(cash, p);
        return false;
    }

    //|L1| < c, но T1 заполненно
    if (sizeDirList(&cash->T1) == cash->p) {
        moveNodeToBegin(&cash->B1, lastDirList(&cash->T1));
    }

    //в T1 есть место
    PageId p = {page, 0};
    addNewPageToT1(cash, p);
    return false;
}

void validateLine(FrcCache *cache, DirList *T, DirList *B, int tmax, int c) {
    while (sizeDirList(T) > tmax) {
        moveNodeToBegin(B, lastDirList(T));
    }
    while (sizeDirList(T) + sizeDirList(B) > c) {
        deletePageFromDBL(cache, B, lastDirList(B));
    }
}

void validateDBL(FrcCache *cache) {
    validateLine(cache, &cache->T1, &cache->B1, cache->p, cache->c);
    validateLine(cache, &cache->T2, &cache->B2, cache->c - cache->p, cache->c);
}

bool checkOutPageFrcCache(FrcCache *cache, int page) {
    PageLoc iter = atHashMapIntDlit(&cache->pages_map, page);
    if (isEndHashMapIntDlit(&cache->pages_map, iter)) {     //FRC miss and DBL(c) miss
        return checkOutIfFrcAndDBLMiss(cache, page, iter);
    }
    Dlit x = iterData(iter);
    if (isInDirList(x, &cache->T1) || isInDirList(x, &cache->T2)) {
        moveNodeToBegin(&cache->T2, x);
        validateDBL(cache);
        return true;
    }

    // x в одном из списков {B1, B2}
    moveNodeToBegin(&cache->T2, x);
    validateDBL(cache);
    return false;
}

void printfFrcCacheState(const FrcCache *cash) {
    printf("ARC:\n");
    printf("T1: ");
    for (Dlit it = firstDirList(&cash->T1); it != endDirList(); it = iterateDirList(cash->dbl_store, it)) {
        printf("%d ", nodeData(cash->dbl_store, it)->page);
    }

    printf("\nT2: ");
    for (Dlit it = firstDirList(&cash->T2); it != endDirList(); it = iterateDirList(cash->dbl_store, it)) {
        printf("%d ", nodeData(cash->dbl_store, it)->page);
    }
    printf("\n\nDBL:\n");
    printf("B1: ");
    for (Dlit it = firstDirList(&cash->B1); it != endDirList(); it = iterateDirList(cash->dbl_store, it)) {
        printf("%d ", nodeData(cash->dbl_store, it)->page);
    }
    printf("\nB2: ");
    for (Dlit it = firstDirList(&cash->B2); it != endDirList(); it = iterateDirList(cash->dbl_store, it)) {
        printf("%d ", nodeData(cash->dbl_store, it)->page);
    }
    printf("\n\n\n");
}
