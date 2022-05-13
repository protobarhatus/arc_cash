#ifndef FIBONACHY_NIM_HASH_TABLE_H
#define FIBONACHY_NIM_HASH_TABLE_H

#include "hash_table_def.h"
#include "pair/pair.h"
#include "list/list.h"
MAKE_PAIR(Int, SIMPLE, SIMPLE, ListIntIterator, SIMPLE, STRUCT)
MAKE_PAIR(Int, SIMPLE, SIMPLE, ListIntConstIterator, SIMPLE, STRUCT)
MAKE_PAIR(Int, SIMPLE, SIMPLE, ListDoubleIterator, SIMPLE, STRUCT)
MAKE_PAIR(Int, SIMPLE, SIMPLE, ListDoubleConstIterator, SIMPLE, STRUCT)

MAKE_HASHTABLE(Int, SIMPLE, SIMPLE)

MAKE_HASHTABLE(Double, SIMPLE, SIMPLE)


HashTableInt defaultHashTableInt();
#endif