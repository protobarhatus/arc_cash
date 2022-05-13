#ifndef FIBONACHY_NIM_HASHMAP_GENERAL_TYPE_H
#define FIBONACHY_NIM_HASHMAP_GENERAL_TYPE_H
#include "list/list.h"
typedef unsigned int (*HashFunctionType1)(const Type1 * arg);

struct HashMap_struct
{
    ListPairType1Type2 * table;
    int table_size;
    int amount_of_elements;
    HashFunctionType1 hash_function;
};

typedef struct HashMap_struct HashMap;
typedef HashMap HashMapRef;


MAKE_PAIR(Int, SIMPLE, SIMPLE, ListPairType1Type2Iterator, SIMPLE, STRUCT)
MAKE_PAIR(Int, SIMPLE, SIMPLE, ListPairType1Type2ConstIterator, SIMPLE, STRUCT)

typedef PairIntListPairType1Type2Iterator HashMapIterator;
typedef PairIntListPairType1Type2ConstIterator HashMapConstIterator;

HashMap makeHashMap(int size, HashFunctionType1 hash_f);

void destructHashMap(HashMap * map);

HashMap copyHashMap(const HashMap * Map);

HashMap moveHashMap(HashMap * Map);

void addElementHashMap(HashMap * Map, Type1_Ref key, const Type2 * element);
void addElementHashMapRVLV(HashMap * Map, Type1 key, const Type2 * element);
void addElementHashMapLVRV(HashMap * Map, Type1_Ref key, Type2 element);
void addElementHashMapRV(HashMap * Map, Type1 key, Type2 element);


HashMapIterator atHashMap(HashMap * table, Type1_Ref key);

HashMapIterator endHashMap(HashMap * table);

HashMapConstIterator catHashMap(const HashMap * table, Type1_Ref key);

HashMapConstIterator cendHashMap(const HashMap * table);

void eraseFromHashMap(HashMap * table, HashMapIterator it);

bool isEndHashMap(const HashMap * table, HashMapIterator it);

bool iscEndHashMap(const HashMap * table, HashMapConstIterator it);

#endif //FIBONACHY_NIM_HASHMAP_GENERAL_TYPE_H
