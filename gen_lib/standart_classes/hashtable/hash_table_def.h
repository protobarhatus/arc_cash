#ifndef HASHTABLE_DEF_H
#define HASHTABLE_DEF_H

#include "types_and_functions_declarations/general_type.h"
#include "list/list.h"
#include "hash_table_general_type.h"
#define PREPARE_HASHTABLE(UCN0, TYPE0, ARITHM_TYPE0)\
                                                                                                                    \
                                                                                                                    \
                                                                                                                    \
                                                                                                                    \
                                                                                                                    \
                                                                                                                    \
typedef unsigned int (*HashFunction##UCN0)(const UCN0 * arg);                                                       \
                                                                                                                    \
                                                                                                                    \
struct HashTable##UCN0##_struct {                                                                                   \
    List##UCN0 * table;                                                                                             \
    int table_size;                                                                                                 \
    int amount_of_elements;                                                                                         \
    HashFunction##UCN0 hash_function;                                                                               \
};                                                                                                                  \
typedef struct HashTable##UCN0##_struct HashTable##UCN0;                                                            \
typedef HashTable##UCN0 HashTableRef##UCN0;                                                                         \
                                                                                                                    \
                                                                                                                    \
                                                                                                                    \
typedef PairIntList##UCN0##Iterator HashTable##UCN0##Iterator;                                                      \
typedef PairIntList##UCN0##ConstIterator HashTable##UCN0##ConstIterator;                                            \
                                                                                                                    \
static inline HashTable##UCN0 makeHashTable##UCN0(int size, HashFunction##UCN0 hash_function);                      \
                                                                                                                    \
static inline void destructHashTable##UCN0(HashTable##UCN0 * table);                                                \
                                                                                                                    \
static inline HashTable##UCN0 copyHashTable##UCN0(const HashTable##UCN0 * table);                                   \
                                                                                                                    \
static inline HashTable##UCN0 moveHashTable##UCN0(HashTable##UCN0 * table);                                         \
                                                                                                                    \
static inline void addElementHashTable##UCN0(HashTable##UCN0 * table, UCN0##_Ref element);                          \
static inline void addElementHashTable##UCN0##RV(HashTable##UCN0 * table, UCN0 element);                            \
                                                                                                                    \
static inline HashTable##UCN0##Iterator atHashTable##UCN0(HashTable##UCN0 * table, UCN0##_Ref key);                 \
                                                                                                                    \
static inline HashTable##UCN0##Iterator endHashTable##UCN0(HashTable##UCN0 * table);                                \
                                                                                                                    \
static inline bool isEndHashTable##UCN0(HashTable##UCN0 * table, HashTable##UCN0##Iterator it);                     \
                                                                                                                    \
static inline HashTable##UCN0##ConstIterator catHashTable##UCN0(const HashTable##UCN0 * table, UCN0##_Ref key);     \
                                                                                                                    \
static inline HashTable##UCN0##ConstIterator cendHashTable##UCN0(const HashTable##UCN0 * table);                    \
                                                                                                                    \
static inline void eraseFromHashTable##UCN0(HashTable##UCN0 * table, HashTable##UCN0##Iterator it);                 \
                                                                                                                    \
                                                                                                                    \
                                                                                                                    \
                                                                                                                    \
                                                                                                                   \
                                                                                                                   \
                                                                                                                   \
static inline int int_hash_functionHashTable##UCN0(const unsigned int * el)                                        \
{                                                                                                                  \
    /*числа выбраны на рандоме*/                                                              \
    return (59 * (*el) + 29) % 100003;                                                                             \
}                                                                                                                  \
                                                                                                                   \
static inline int callHashFunctionHashTable##UCN0(const HashTable##UCN0 * table, const UCN0 * el)                  \
{                                                                                                                  \
    if ((unsigned long long int) table->hash_function == 0x1)                                                      \
        return int_hash_functionHashTable##UCN0((const unsigned int *) el);                                        \
    return table->hash_function(el);                                                                               \
}                                                                                                                  \
                                                                                                                   \
                                                                                                                   \
static inline HashTable##UCN0 makeHashTable##UCN0(int size, HashFunction##UCN0 hash_function)                      \
{                                                                                                                  \
    HashTable##UCN0 table;                                                                                         \
    table.table = calloc(size, sizeof(HashTable##UCN0));                                                           \
    for (int i = 0; i < size; ++i)                                                                                 \
        table.table[i] = defaultList##UCN0();                                                                      \
    table.table_size = size;                                                                                       \
    table.hash_function = hash_function;                                                                           \
    table.amount_of_elements = 0;                                                                                  \
    return table;                                                                                                  \
                                                                                                                   \
}                                                                                                                  \
static inline void destructHashTable##UCN0(HashTable##UCN0 * table)                                                \
{                                                                                                                  \
                                                                                                                   \
    if (table->table == NULL)                                                                                      \
        return;                                                                                                    \
    for (int i = 0; i < table->table_size; ++i)                                                                    \
        destructList##UCN0(&table->table[i]);                                                                      \
    table->table_size = -1;                                                                                        \
    free(table->table);                                                                                            \
    table->table = 0;                                                                                              \
    table->hash_function = NULL;                                                                                   \
    table->amount_of_elements = -1;                                                                                \
                                                                                                                   \
}                                                                                                                  \
                                                                                                                   \
static inline HashTable##UCN0 copyHashTable##UCN0(const HashTable##UCN0 * table)                                   \
{                                                                                                                  \
    HashTable##UCN0 res = makeHashTable##UCN0(table->table_size, table->hash_function);                            \
    for (int i = 0; i < table->table_size; ++i)                                                                    \
        res.table[i] = copyList##UCN0(&table->table[i]);                                                           \
    res.amount_of_elements = table->amount_of_elements;                                                            \
    return res;                                                                                                    \
}                                                                                                                  \
                                                                                                                   \
static inline HashTable##UCN0 moveHashTable##UCN0(HashTable##UCN0 * table)                                         \
{                                                                                                                  \
    HashTable##UCN0 res;                                                                                           \
    res.table_size = table->table_size;                                                                            \
    res.hash_function = table->hash_function;                                                                      \
    res.table = table->table;                                                                                      \
    res.amount_of_elements = table->amount_of_elements;                                                            \
                                                                                                                   \
    table->table = NULL;                                                                                           \
    table->table_size = -1;                                                                                        \
    table->amount_of_elements = -1;                                                                                \
                                                                                                                   \
    return res;                                                                                                    \
}                                                                                                                  \
                                                                                                                   \
static inline void addElementHashTable##UCN0(HashTable##UCN0 * table, UCN0##_Ref element)                          \
{                                                                                                                  \
    int hash = callHashFunctionHashTable##UCN0(table, &element) % table->table_size;                               \
    pushBackToList##UCN0##RV(&table->table[hash], TYPE0##_TYPE_COPY(UCN0, &element));                              \
    table->amount_of_elements++;                                                                                   \
                                                                                                                   \
}                                                                                                                  \
static inline void addElementHashTable##UCN0##RV(HashTable##UCN0 * table, UCN0 element)                            \
{                                                                                                                  \
    int hash = callHashFunctionHashTable##UCN0(table, &element) % table->table_size;                               \
    pushBackToList##UCN0##RV(&table->table[hash], element);                                                        \
    table->amount_of_elements++;                                                                                   \
}                                                                                                                  \
                                                                                                                   \
static inline HashTable##UCN0##Iterator atHashTable##UCN0(HashTable##UCN0 * table, UCN0##_Ref key)                 \
{                                                                                                                  \
    int hash = callHashFunctionHashTable##UCN0(table, &key) % table->table_size;                                   \
    for (List##UCN0##Iterator it = beginList##UCN0(&table->table[hash]);                                           \
            it != endList##UCN0(&table->table[hash]);                                                              \
                it = iterateList##UCN0(it))                                                                        \
    {                                                                                                              \
        if (equal##UCN0(it->data, &key))                                                                           \
            return defaultPairIntList##UCN0##IteratorRVLV(hash, &it);                                              \
    }                                                                                                              \
    return endHashTable##UCN0(table);                                                                              \
}                                                                                                                  \
static inline HashTable##UCN0##Iterator endHashTable##UCN0(HashTable##UCN0 * table)                                \
{                                                                                                                  \
    return defaultPairIntList##UCN0##IteratorRV(table->table_size, NULL);                                          \
}                                                                                                                  \
static inline bool isEndHashTable##UCN0(HashTable##UCN0 * table, HashTable##UCN0##Iterator it)                     \
{                                                                                                                  \
    return it.first == table->table_size && it.second == NULL;                                                     \
}                                                                                                                  \
                                                                                                                   \
static inline HashTable##UCN0##ConstIterator catHashTable##UCN0(const HashTable##UCN0 * table, UCN0##_Ref key)     \
{                                                                                                                  \
    int hash = callHashFunctionHashTable##UCN0(table, &key) % table->table_size;                                   \
    for (List##UCN0##ConstIterator it = cbeginList##UCN0(&table->table[hash]);                                     \
         it != cendList##UCN0(&table->table[hash]);                                                                \
         it = citerateList##UCN0(it))                                                                              \
    {                                                                                                              \
        if (equal##UCN0(it->data, &key))                                                                           \
            return defaultPairIntList##UCN0##ConstIteratorRVLV(hash, &it);                                         \
    }                                                                                                              \
    return cendHashTable##UCN0(table);                                                                             \
}                                                                                                                  \
                                                                                                                   \
static inline HashTable##UCN0##ConstIterator cendHashTable##UCN0(const HashTable##UCN0 * table)                    \
{                                                                                                                  \
    return defaultPairIntList##UCN0##ConstIteratorRV(table->table_size, NULL);                                     \
}                                                                                                                  \
                                                                                                                   \
static inline void eraseFromHashTable##UCN0(HashTable##UCN0 * table, HashTable##UCN0##Iterator it)                 \
{                                                                                                                  \
    assert(table->amount_of_elements > 0);                                                                         \
    table->amount_of_elements--;                                                                                   \
    assert(&table->table[it.first] == it.second->list);                                                            \
    eraseList##UCN0##Node(it.second);                                                                              \
}                                                                                                                  \


#define MAKE_HASHTABLE(UCN0, TYPE0, ARITHM_TYPE0) PREPARE_HASHTABLE(UCN0, TYPE0, ARITHM_TYPE0)


#endif
