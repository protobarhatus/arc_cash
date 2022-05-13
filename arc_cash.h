#ifndef FIBONACHY_NIM_ARC_CASH_H
#define FIBONACHY_NIM_ARC_CASH_H

#include "hashtable/hashmap.h"
#include "Page.h"

struct ListOpt_struct {};
typedef struct ListOpt_struct ListOpt;

struct ListOptIterator_struct {};
typedef struct ListOptIterator_struct ListOptIterator;

struct PageId_struct { int page,  addres;};
typedef struct PageId_struct PageId;

typedef ListOptIterator LOit;



///----------------------------------


MAKE_PAIR(Int, SIMPLE, SIMPLE, LOit, SIMPLE, STRUCT)
MAKE_LIST(PairIntLOit, SIMPLE, STRUCT)

MAKE_HASHMAP(Int, SIMPLE, SIMPLE, LOit, SIMPLE, STRUCT)

#define LINE_SIZE 60

struct ArcCash_struct {

    HashMapIntLOit pages_map;
    ListOpt B1, B2, T1, T2;
    char * cash_line;
    int p;
    int c;

    char * prepared_line;

    int untouched_space;
};
typedef struct ArcCash_struct ArcCash;

ArcCash defaultArcCash(int c, int hashmap_length);
void destructArcCash(ArcCash * cash);


bool checkOutPageArcCash(ArcCash * cash, int page);

char * readPageArcCash(ArcCash * cash);
void writePageArcCash(ArcCash * cash, char * page);

#endif //FIBONACHY_NIM_ARC_CASH_H
