#include "arc_cash.h"




ArcCash defaultArcCash(int c, int hashmap_length) {

    ArcCash res;
    res.p = 0;
    res.c = c;
    res.cash_line = calloc(LINE_SIZE, sizeof(char));
    res.prepared_line = NULL;
    res.pages_map = makeHashMapIntDlit(hashmap_length, 0x1);
    res.untouched_space = 0;
    assert(res.cash_line != NULL);

    res.dlc_store = calloc(1, sizeof(ComArr));
    *res.dlc_store = initComArr(c);
    res.T1 = getT1(res.dlc_store);
    res.T2 = getT2(res.dlc_store);
    res.B1 = getB1(res.dlc_store);
    res.B2 = getB2(res.dlc_store);

    return res;
}
void destructArcCash(ArcCash * cash) {

    free(cash->cash_line);
    cash->cash_line = NULL;
    destructHashMapIntDlit(&cash->pages_map);
    cash->prepared_line = NULL;

    destrComArr(cash->dlc_store);
    free(cash->dlc_store);
}

static int min(int a, int b) {

    return a < b ? a : b;
}
static int max(int a, int b) {

    return a > b ? a : b;
}

typedef HashMapIntDlitIterator PageLoc;

static Dlit iterData(PageLoc iter)
{
    return iter.second->data->second;
}
//возвращает адрес освободившегося места в линии.
static int replacePages(ArcCash * cash, int page, PageLoc loc) {

    int freed_adres;
    if (sizeDirList(&cash->T1) >= 1 && ((isInDirList(iterData(loc), &cash->B2) && sizeDirList(&cash->T1) == cash->p)
            || (sizeDirList(&cash->T1) > cash->p))) {
        Dlit moved = lastDirList(&cash->T1);
        freed_adres = nodeData(cash->dlc_store, moved)->addres;
        moveNodeToBegin(&cash->B2, moved);

    }
    else {
        Dlit moved = lastDirList(&cash->T2);
        freed_adres = nodeData(cash->dlc_store, moved)->addres;
        moveNodeToBegin(&cash->B2, moved);
    }
    return freed_adres;
}

void addNewPageToT1(ArcCash * cash, PageId page)
{
    Dlit it = pushFront(&cash->T1, &page);
    addElementHashMapIntDlit(&cash->pages_map, page.page, &it);
}

bool checkOutIfArcAndDBLMiss(ArcCash * cash, int page, PageLoc iter) {

    int free_adr = -1;
    //case(i)
    if (sizeDirList(&cash->B1) + sizeDirList(&cash->T1) == cash->c) {

        if (sizeDirList(&cash->T1) < cash->c) {

            eraseNode(&cash->B1, lastDirList(&cash->B1));
            free_adr = replacePages(cash, page, iter);
        }
        else {

            Dlit to_erase = lastDirList(&cash->T1);
            free_adr = nodeData(cash->dlc_store, to_erase)->addres;
            eraseNode(&cash->T1, to_erase);
        }

    }
    //case(ii)
    if (sizeDirList(&cash->B1) + sizeDirList(&cash->T1) < cash->c &&
        sizeDirList(&cash->B1) + sizeDirList(&cash->B2) + sizeDirList(&cash->T1) + sizeDirList(&cash->T2) >= cash->c) {

        if (sizeDirList(&cash->B1) + sizeDirList(&cash->B2) + sizeDirList(&cash->T1) + sizeDirList(&cash->T2) == 2*cash->c) {

            eraseNode(&cash->B2, lastDirList(&cash->B2));
        }
        free_adr = replacePages(cash, page, iter);
    }

    PageId new_page;
    new_page.page = page;
    new_page.addres = (free_adr == -1 ? cash->untouched_space : free_adr);
    addNewPageToT1(cash, new_page);

    if (free_adr == -1) {

        cash->prepared_line = &cash->cash_line[cash->untouched_space * LINE_SIZE];
        ++cash->untouched_space;
    }
    else
        cash->prepared_line = &cash->cash_line[free_adr * LINE_SIZE];

    return false;

}

bool checkOutPageArcCash(ArcCash * cash, int page) {

    assert(cash->prepared_line == NULL);

    PageLoc iter = atHashMapIntDlit(&cash->pages_map, page);
    if (isEndHashMapIntDlit(&cash->pages_map, iter)) {

        //ARC miss and DBL(c) miss
        return checkOutIfArcAndDBLMiss(cash, page, iter);
    }
    else {

        Dlit loc = iterData(iter);
        if (isInDirList(loc, &cash->T1) || isInDirList(loc, &cash->T2)) {

            moveNodeToBegin(&cash->T2, loc);
            cash->prepared_line = &cash->cash_line[nodeData(cash->dlc_store, loc)->addres * LINE_SIZE];
            return true;
        }
        if (isInDirList(loc, &cash->B1)) {

            //ARC miss and DBL(c) hit
            cash->p = min(cash->c, cash->p + max(sizeDirList(&cash->B2) / sizeDirList(&cash->B1), 1));
            int free_adr = replacePages(cash, page, iter);
            moveNodeToBegin(&cash->T2, loc);
            cash->prepared_line = &cash->cash_line[free_adr * LINE_SIZE];
            nodeData(cash->dlc_store, loc)->addres = free_adr;
            return false;
        }
        if (isInDirList(loc, &cash->B2)) {

            //ARC miss and DBL(c) hit
            cash->p = max(0, cash->p - max(sizeDirList(&cash->B1) / sizeDirList(&cash->B2), 1));
            int free_adr = replacePages(cash, page, iter);
            moveNodeToBegin(&cash->T2, loc);
            cash->prepared_line = &cash->cash_line[free_adr * LINE_SIZE];
            nodeData(cash->dlc_store, loc)->addres = free_adr;
            return false;
        }
        //должны реализоваться верхние случаи
        assert(false);
    }
}

char * readPageArcCash(ArcCash * cash)
{
    assert(cash->prepared_line != NULL);
    char * ret = cash->prepared_line;
    cash->prepared_line = NULL;
    return ret;
}

void writePageArcCash(ArcCash * cash, char * page)
{
    assert(cash->prepared_line != NULL);
    assert(page != NULL);
    memcpy(cash->prepared_line, page, LINE_SIZE);
    cash->prepared_line = NULL;
}

void deactArcCash(ArcCash * cash)
{
    assert(cash->prepared_line != NULL);
    cash->prepared_line = NULL;
}

void printfCashState(const ArcCash * cash)
{
    printf("ARC:\n");
    printf("T1: ");
    for (Dlit it = firstDirList(&cash->T1); it != endDirList(); it = iterateDirList(cash->dlc_store, it))
        printf("%d ", nodeData(cash->dlc_store, it)->page);

    printf("\nT2: ");
    for (Dlit it = firstDirList(&cash->T2); it != endDirList(); it = iterateDirList(cash->dlc_store, it))
        printf("%d ", nodeData(cash->dlc_store, it)->page);
    printf("\n\nDLC:\n");
    printf("B1: ");
    for (Dlit it = firstDirList(&cash->B1); it != endDirList(); it = iterateDirList(cash->dlc_store, it))
        printf("%d ", nodeData(cash->dlc_store, it)->page);
    printf("\nB2: ");
    for (Dlit it = firstDirList(&cash->B2); it != endDirList(); it = iterateDirList(cash->dlc_store, it))
        printf("%d ", nodeData(cash->dlc_store, it)->page);
    printf("\n\n\n");

}