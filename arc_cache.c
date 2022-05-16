#include "arc_cache.h"

static int min(int a, int b);
static int max(int a, int b);
static Dlit iterData(PageLoc iter);
static bool isPagelocInDirList(ArcCache *cache, PageLoc x, const DirList *dir);
static int replacePages(ArcCache *cache, int page, PageLoc loc);
static void addNewPageToT1(ArcCache *cache, PageId page);
static void deletePageFromDBL(ArcCache *cache, DirList *list, Dlit page);

typedef HashMapIntDlitIterator PageLoc;

ArcCache defaultArcCache(int c, int hashmap_length) {
    ArcCache res;
    res.p = 0;
    res.c = c;
    res.cache_line = calloc(LINE_SIZE, sizeof(char));
    res.prepared_line = NULL;
    res.pages_map = makeHashMapIntDlit(hashmap_length, HM_INT_STANDART_CACHE);
    res.untouched_space = 0;
    assert(res.cache_line != NULL);

    res.dbl_store = calloc(1, sizeof(ComArr));
    *res.dbl_store = initComArr(c);
    res.T1 = getT1(res.dbl_store);
    res.T2 = getT2(res.dbl_store);
    res.B1 = getB1(res.dbl_store);
    res.B2 = getB2(res.dbl_store);

    return res;
}

void destructArcCache(ArcCache *cache) {
    free(cache->cache_line);
    cache->cache_line = NULL;
    destructHashMapIntDlit(&cache->pages_map);
    cache->prepared_line = NULL;

    destrComArr(cache->dbl_store);
    free(cache->dbl_store);
}

static int min(int a, int b) {
    return a < b ? a : b;
}

static int max(int a, int b) {
    return a > b ? a : b;
}

static Dlit iterData(PageLoc iter) {
    return iter.second->data->second;
}

static bool isPagelocInDirList(ArcCache *cache, PageLoc x, const DirList *dir) {
    return !isEndHashMapIntDlit(&cache->pages_map, x) && isInDirList(iterData(x), dir);
}

// возвращает адрес освободившегося места в линии
static int replacePages(ArcCache *cache, int page, PageLoc loc) {
    int freed_address;
    if (sizeDirList(&cache->T1) >= 1 && ((isPagelocInDirList(cache, loc, &cache->B2) && sizeDirList(&cache->T1) == cache->p)
            || (sizeDirList(&cache->T1) > cache->p))) {
        Dlit moved = lastDirList(&cache->T1);
        freed_address = nodeData(cache->dbl_store, moved)->address;
        moveNodeToBegin(&cache->B1, moved);
    } else {
        Dlit moved = lastDirList(&cache->T2);
        freed_address = nodeData(cache->dbl_store, moved)->address;
        moveNodeToBegin(&cache->B2, moved);
    }
    return freed_address;
}

static void addNewPageToT1(ArcCache *cache, PageId page) {
    Dlit it = pushFront(&cache->T1, &page);
    addElementHashMapIntDlit(&cache->pages_map, page.page, &it);
}

static void deletePageFromDBL(ArcCache *cache, DirList *list, Dlit page) {
    int page_num = nodeData(cache->dbl_store, page)->page;
    eraseFromHashMapIntDlit(&cache->pages_map, atHashMapIntDlit(&cache->pages_map, page_num));
    eraseNode(list, page);
}

bool checkOutIfArcAndDBLMiss(ArcCache *cache, int page, PageLoc iter) {
    int free_adr = -1;

    //case(i)
    if (sizeDirList(&cache->B1) + sizeDirList(&cache->T1) == cache->c) {
        if (sizeDirList(&cache->T1) < cache->c) {
            deletePageFromDBL(cache, &cache->B1, lastDirList(&cache->B1));
            free_adr = replacePages(cache, page, iter);
        } else {
            Dlit to_erase = lastDirList(&cache->T1);
            free_adr = nodeData(cache->dbl_store, to_erase)->address;
            deletePageFromDBL(cache, &cache->T1, to_erase);
        }
    }

    //case(ii)
    else if (sizeDirList(&cache->B1) + sizeDirList(&cache->T1) < cache->c &&
        sizeDirList(&cache->B1) + sizeDirList(&cache->B2) + sizeDirList(&cache->T1) + sizeDirList(&cache->T2) >= cache->c) {
        if (sizeDirList(&cache->B1) + sizeDirList(&cache->B2) + sizeDirList(&cache->T1) + sizeDirList(&cache->T2) == 2*cache->c) {
            deletePageFromDBL(cache, &cache->B2, lastDirList(&cache->B2));
        }
        free_adr = replacePages(cache, page, iter);
    }

    PageId new_page;
    new_page.page = page;
    new_page.address = (free_adr == -1 ? cache->untouched_space : free_adr);
    addNewPageToT1(cache, new_page);

    if (free_adr == -1) {
        cache->prepared_line = &cache->cache_line[cache->untouched_space * LINE_SIZE];
        ++cache->untouched_space;
    } else {
        cache->prepared_line = &cache->cache_line[free_adr * LINE_SIZE];
    }

    return false;
}

bool checkOutPageArcCache(ArcCache *cache, int page) {
    assert(cache->prepared_line == NULL);

    PageLoc iter = atHashMapIntDlit(&cache->pages_map, page);
    if (isEndHashMapIntDlit(&cache->pages_map, iter)) {           // ARC miss and DBL(2c) miss
        return checkOutIfArcAndDBLMiss(cache, page, iter);
    } else {
        Dlit loc = iterData(iter);
        
        if (isInDirList(loc, &cache->T1) || isInDirList(loc, &cache->T2)) {
            moveNodeToBegin(&cache->T2, loc);
            cache->prepared_line = &cache->cache_line[nodeData(cache->dbl_store, loc)->address * LINE_SIZE];
            return true;
        }
        if (isInDirList(loc, &cache->B1)) {     // ARC miss and DBL(2c) hit
            cache->p = min(cache->c, cache->p + max(sizeDirList(&cache->B2) / sizeDirList(&cache->B1), 1));
            int free_adr = replacePages(cache, page, iter);
            moveNodeToBegin(&cache->T2, loc);
            cache->prepared_line = &cache->cache_line[free_adr * LINE_SIZE];
            nodeData(cache->dbl_store, loc)->address = free_adr;
            return false;
        }
        if (isInDirList(loc, &cache->B2)) {     // ARC miss and DBL(2c) hit
            cache->p = max(0, cache->p - max(sizeDirList(&cache->B1) / sizeDirList(&cache->B2), 1));
            int free_adr = replacePages(cache, page, iter);
            moveNodeToBegin(&cache->T2, loc);
            cache->prepared_line = &cache->cache_line[free_adr * LINE_SIZE];
            nodeData(cache->dbl_store, loc)->address = free_adr;
            return false;
        }

        assert(false);    // должны реализоваться верхние случаи
    }
}

char *readPageArcCache(ArcCache *cache) {
    assert(cache->prepared_line != NULL);
    char *ret = cache->prepared_line;
    cache->prepared_line = NULL;
    return ret;
}

void writePageArcCache(ArcCache *cache, char *page) {
    assert(cache->prepared_line != NULL);
    assert(page != NULL);
    memcpy(cache->prepared_line, page, LINE_SIZE);
    cache->prepared_line = NULL;
}

void deactArcCache(ArcCache *cache) {
    assert(cache->prepared_line != NULL);
    cache->prepared_line = NULL;
}

void printfCacheState(const ArcCache *cache) {
    printf("ARC:\n");
    printf("T1: ");
    for (Dlit it = firstDirList(&cache->T1); it != endDirList(); it = iterateDirList(cache->dbl_store, it))
        printf("%d ", nodeData(cache->dbl_store, it)->page);

    printf("\nT2: ");
    for (Dlit it = firstDirList(&cache->T2); it != endDirList(); it = iterateDirList(cache->dbl_store, it))
        printf("%d ", nodeData(cache->dbl_store, it)->page);
    printf("\n\nDBL:\n");
    printf("B1: ");
    for (Dlit it = firstDirList(&cache->B1); it != endDirList(); it = iterateDirList(cache->dbl_store, it))
        printf("%d ", nodeData(cache->dbl_store, it)->page);
    printf("\nB2: ");
    for (Dlit it = firstDirList(&cache->B2); it != endDirList(); it = iterateDirList(cache->dbl_store, it))
        printf("%d ", nodeData(cache->dbl_store, it)->page);
    printf("\n\n\n");
}
