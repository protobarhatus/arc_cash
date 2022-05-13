#ifndef FIBONACHY_NIM_HASH_TABLE_GENERAL_TYPE_H
#define FIBONACHY_NIM_HASH_TABLE_GENERAL_TYPE_H

#include "types_and_functions_declarations/general_type.h"
#include "list/list.h"

typedef unsigned int (*HashFunctionGeneralType)(const GeneralType * arg);


struct HashTable_struct {
    ListGeneralType * table;
    int table_size;
    int amount_of_elements;
    HashFunctionGeneralType hash_function;
};
typedef struct HashTable_struct HashTable;
typedef HashTable HashTableRef;



typedef PairIntListGeneralTypeIterator HashTableIterator;
typedef PairIntListGeneralTypeConstIterator HashTableConstIterator;

HashTable makeHashTable(int size, HashFunctionGeneralType hash_function);

void destructHashTable(HashTable * table);

HashTable copyHashTable(const HashTable * table);

HashTable moveHashTable(HashTable * table);

void addElementHashTable(HashTable * table, GeneralType_Ref element);
void addElementHashTableRV(HashTable * table, GeneralType element);

HashTableIterator atHashTable(HashTable * table, GeneralType_Ref key);

HashTableIterator endHashTable(HashTable * table);

HashTableConstIterator catHashTable(const HashTable * table, GeneralType_Ref key);

HashTableConstIterator cendHashTable(const HashTable * table);

void eraseFromHashTable(HashTable * table, HashTableIterator it);



#endif //FIBONACHY_NIM_HASH_TABLE_GENERAL_TYPE_H
