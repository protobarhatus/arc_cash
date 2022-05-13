#include "arc_cash.h"
int sizeListOpt(const ListOpt *);
ListOpt defaultListOpt();
ListOpt copyListOpt(const ListOpt *);
void destructListOpt(ListOpt *);

void pushBack(ListOpt *, const PageId *);
void pushFront(ListOpt *, const PageId *);

bool isIn(ListOptIterator, const ListOpt * );


void eraseNode(ListOpt *, ListOptIterator );


PageId* nodeData(ListOptIterator);
void moveNodeToBegin(ListOptIterator what, ListOpt * where);
void moveNodeToEnd(ListOptIterator what, ListOpt * where);

LOit lastListOpt(ListOpt *);


ListOptIterator beginListOpt(ListOpt *);
ListOptIterator endListOpt(ListOpt *);

ListOptIterator iterateListOpt(ListOptIterator) ;

///-----------------------------------------------------------------



ArcCash defaultArcCash(int c, int hashmap_length) {

    ArcCash res;
    res.p = 0;
    res.c = c;
    res.cash_line = calloc(LINE_SIZE, sizeof(char));
    res.prepared_line = NULL;
    res.pages_map = makeHashMapIntLOit(hashmap_length, 0x1);
    res.untouched_space = 0;
    assert(res.cash_line != NULL);

    INITIALIZE_T_B

    return res;
}
void destructArcCash(ArcCash * cash) {

    free(cash->cash_line);
    cash->cash_line = NULL;
    destructHashMapIntLOit(&cash->pages_map);
    cash->prepared_line = NULL;

    DESTRUCT_T_B
}

static int min(int a, int b) {

    return a < b ? a : b;
}
static int max(int a, int b) {

    return a > b ? a : b;
}

typedef HashMapIntLOitIterator PageLoc;

static LOit iterData(PageLoc iter)
{
    return iter.second->data->second;
}
//возвращает адрес освободившегося места в линии.
static int replacePages(ArcCash * cash, int page, PageLoc loc) {

    int freed_adres;
    if (sizeListOpt(&cash->T1) >= 1 && ((isIn(iterData(loc), &cash->B2) && sizeListOpt(&cash->T1) == cash->p)
            || (sizeListOpt(&cash->T1) > cash->p))) {
        LOit moved = lastListOpt(&cash->T1);
        freed_adres = nodeData(moved)->addres;
        moveNodeToBegin(moved, &cash->B2);

    }
    else {
        LOit moved = lastListOpt(&cash->T2);
        freed_adres = nodeData(moved)->addres;
        moveNodeToBegin(moved, &cash->B2);
    }
    return freed_adres;
}

bool checkOutIfArcAndDBLMiss(ArcCash * cash, int page, PageLoc iter) {

    int free_adr = -1;
    //case(i)
    if (sizeListOpt(&cash->B1) + sizeListOpt(&cash->T1) == cash->c) {

        if (sizeListOpt(&cash->T1) < cash->c) {

            eraseNode(&cash->B1, lastListOpt(&cash->B1));
            free_adr = replacePages(cash, page, iter);
        }
        else {

            LOit to_erase = lastListOpt(&cash->T1);
            free_adr = nodeData(to_erase)->addres;
            eraseNode(&cash->T1, to_erase);
        }

    }
    //case(ii)
    if (sizeListOpt(&cash->B1) + sizeListOpt(&cash->T1) < cash->c &&
        sizeListOpt(&cash->B1) + sizeListOpt(&cash->B2) + sizeListOpt(&cash->T1) + sizeListOpt(&cash->T2) >= cash->c) {

        if (sizeListOpt(&cash->B1) + sizeListOpt(&cash->B2) + sizeListOpt(&cash->T1) + sizeListOpt(&cash->T2) == 2*cash->c) {

            eraseNode(&cash->B2, lastListOpt(&cash->B2));
        }
        free_adr = replacePages(cash, page, iter);
    }

    PageId new_page;
    new_page.page = page;
    new_page.addres = (free_adr == -1 ? cash->untouched_space : free_adr);
    pushFront(&cash->T1, &new_page);

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

    PageLoc iter = atHashMapIntLOit(&cash->pages_map, page);
    if (isEndHashMapIntLOit(&cash->pages_map, iter)) {

        //ARC miss and DBL(c) miss
        return checkOutIfArcAndDBLMiss(cash, page, iter);
    }
    else {

        LOit loc = iterData(iter);
        if (isIn(loc, &cash->T1) || isIn(loc, &cash->T2)) {

            moveNodeToBegin(loc, &cash->T2);
            cash->prepared_line = &cash->cash_line[nodeData(loc)->addres * LINE_SIZE];
            return true;
        }
        if (isIn(loc, &cash->B1)) {

            //ARC miss and DBL(c) hit
            cash->p = min(cash->c, cash->p + max(sizeListOpt(&cash->B2) / sizeListOpt(&cash->B1), 1));
            int free_adr = replacePages(cash, page, iter);
            moveNodeToBegin(loc, &cash->T2);
            cash->prepared_line = &cash->cash_line[free_adr * LINE_SIZE];
            nodeData(loc)->addres = free_adr;
            return false;
        }
        if (isIn(loc, &cash->B2)) {

            //ARC miss and DBL(c) hit
            cash->p = max(0, cash->p - max(sizeListOpt(&cash->B1) / sizeListOpt(&cash->B2), 1));
            int free_adr = replacePages(cash, page, iter);
            moveNodeToBegin(loc, &cash->T2);
            cash->prepared_line = &cash->cash_line[free_adr * LINE_SIZE];
            nodeData(loc)->addres = free_adr;
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
    memcpy(cash->prepared_line, page, LINE_SIZE);
    cash->prepared_line = NULL;
}