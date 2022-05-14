#ifndef FIBONACHY_NIM_HASHMAP_H
#define FIBONACHY_NIM_HASHMAP_H

#include "hashmap_def.h"
#include "list/list.h"

MAKE_HASHMAP(Int, SIMPLE, SIMPLE, Int, SIMPLE, SIMPLE)
#define HM_INT_STANDART_CACHE 0x1

HashMapIntInt defaultHashMapIntInt();

#endif //FIBONACHY_NIM_HASHMAP_H
