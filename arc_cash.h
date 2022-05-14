#ifndef FIBONACHY_NIM_ARC_CASH_H
#define FIBONACHY_NIM_ARC_CASH_H

#include "hashtable/hashmap.h"
#include "Page.h"
#include "cachedir.h"

typedef DirListIterator Dlit;



///----------------------------------


MAKE_PAIR(Int, SIMPLE, SIMPLE, Dlit, SIMPLE, STRUCT)
MAKE_LIST(PairIntDlit, SIMPLE, STRUCT)

MAKE_HASHMAP(Int, SIMPLE, SIMPLE, Dlit, SIMPLE, STRUCT)

#define LINE_SIZE 60

struct ArcCash_struct {

    HashMapIntDlit pages_map;
    DirList B1, B2, T1, T2;
    char * cash_line;
    int p;
    int c;

    char * prepared_line;
    //структура данных где хранятся данные для DLC(2). Работа при этом идет с B1, B2, T1, T2 - интерфейсами ComArr
    ComArr * dlc_store;
    int untouched_space;
};
typedef struct ArcCash_struct ArcCash;

ArcCash defaultArcCash(int c, int hashmap_length);
void destructArcCash(ArcCash * cash);


bool checkOutPageArcCash(ArcCash * cash, int page);

char * readPageArcCash(ArcCash * cash);
void writePageArcCash(ArcCash * cash, char * page);
//вызывается после checkOut, если кэш работает в холостую, т е нет реальных данных для записи/чтения
void deactArcCash(ArcCash * cash);

void printfCashState(const ArcCash * cash);

#endif //FIBONACHY_NIM_ARC_CASH_H
