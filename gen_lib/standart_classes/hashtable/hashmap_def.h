#ifndef HASHMAP_DEF_H
#define HASHMAP_DEF_H

#include "list/list.h"
#include "hashmap_general_type.h"
#define PREPARE_HASHMAP(UCN0, TYPE0, ARITHM_TYPE0, UCN1, TYPE1, ARITHM_TYPE1)\
                                                                                                                                \
                                                                                                                                \
                                                                                                                                \
typedef unsigned int (*HashFunction##UCN0)(const UCN0 * arg);                                                                   \
                                                                                                                                \
struct HashMap##UCN0##UCN1##_struct                                                                                             \
{                                                                                                                               \
    ListPair##UCN0##UCN1 * table;                                                                                               \
    int table_size;                                                                                                             \
    int amount_of_elements;                                                                                                     \
    HashFunction##UCN0 hash_function;                                                                                           \
};                                                                                                                              \
                                                                                                                                \
typedef struct HashMap##UCN0##UCN1##_struct HashMap##UCN0##UCN1;                                                                \
typedef HashMap##UCN0##UCN1 HashMapRef##UCN0##UCN1;                                                                             \
                                                                                                                                \
                                                                                                                                \
MAKE_PAIR(Int, SIMPLE, SIMPLE, ListPair##UCN0##UCN1##Iterator, SIMPLE, STRUCT)                                                  \
MAKE_PAIR(Int, SIMPLE, SIMPLE, ListPair##UCN0##UCN1##ConstIterator, SIMPLE, STRUCT)                                             \
                                                                                                                                \
typedef PairIntListPair##UCN0##UCN1##Iterator HashMap##UCN0##UCN1##Iterator;                                                    \
typedef PairIntListPair##UCN0##UCN1##ConstIterator HashMap##UCN0##UCN1##ConstIterator;                                          \
                                                                                                                                \
static inline HashMap##UCN0##UCN1 makeHashMap##UCN0##UCN1(int size, HashFunction##UCN0 hash_f);                                 \
                                                                                                                                \
static inline void destructHashMap##UCN0##UCN1(HashMap##UCN0##UCN1 * map);                                                      \
                                                                                                                                \
static inline HashMap##UCN0##UCN1 copyHashMap##UCN0##UCN1(const HashMap##UCN0##UCN1 * Map);                                     \
                                                                                                                                \
static inline HashMap##UCN0##UCN1 moveHashMap##UCN0##UCN1(HashMap##UCN0##UCN1 * Map);                                           \
                                                                                                                                \
static inline void addElementHashMap##UCN0##UCN1(HashMap##UCN0##UCN1 * Map, UCN0##_Ref key, const UCN1 * element);              \
static inline void addElementHashMap##UCN0##UCN1##RVLV(HashMap##UCN0##UCN1 * Map, UCN0 key, const UCN1 * element);              \
static inline void addElementHashMap##UCN0##UCN1##LVRV(HashMap##UCN0##UCN1 * Map, UCN0##_Ref key, UCN1 element);                \
static inline void addElementHashMap##UCN0##UCN1##RV(HashMap##UCN0##UCN1 * Map, UCN0 key, UCN1 element);                        \
                                                                                                                                \
                                                                                                                                \
static inline HashMap##UCN0##UCN1##Iterator atHashMap##UCN0##UCN1(HashMap##UCN0##UCN1 * table, UCN0##_Ref key);                 \
                                                                                                                                \
static inline HashMap##UCN0##UCN1##Iterator endHashMap##UCN0##UCN1(HashMap##UCN0##UCN1 * table);                                \
                                                                                                                                \
static inline HashMap##UCN0##UCN1##ConstIterator catHashMap##UCN0##UCN1(const HashMap##UCN0##UCN1 * table, UCN0##_Ref key);     \
                                                                                                                                \
static inline HashMap##UCN0##UCN1##ConstIterator cendHashMap##UCN0##UCN1(const HashMap##UCN0##UCN1 * table);                    \
                                                                                                                                \
static inline void eraseFromHashMap##UCN0##UCN1(HashMap##UCN0##UCN1 * table, HashMap##UCN0##UCN1##Iterator it);                 \
                                                                                                                                \
static inline bool isEndHashMap##UCN0##UCN1(const HashMap##UCN0##UCN1 * table, HashMap##UCN0##UCN1##Iterator it);               \
                                                                                                                                \
static inline bool iscEndHashMap##UCN0##UCN1(const HashMap##UCN0##UCN1 * table, HashMap##UCN0##UCN1##ConstIterator it);         \
                                                                                                                                \
                                                                                                                                \
                                                                                                                               \
                                                                                                                               \
static inline unsigned int int_hash_functionHashMap##UCN0##UCN1(const unsigned int * el)                                       \
{                                                                                                                              \
    /*числа выбраны на рандоме*/                                                                          \
    return (59 * (*el) + 29) % 100003;                                                                                         \
}                                                                                                                              \
                                                                                                                               \
static inline unsigned int callHashFunctionHashMap##UCN0##UCN1(const HashMap##UCN0##UCN1 * table, const UCN0 * el)             \
{                                                                                                                              \
    if ((unsigned long long int) table->hash_function == 0x1)                                                                  \
        return int_hash_functionHashMap##UCN0##UCN1((const unsigned int *) el);                                                \
    return table->hash_function(el);                                                                                           \
}                                                                                                                              \
                                                                                                                               \
                                                                                                                               \
static inline HashMap##UCN0##UCN1 makeHashMap##UCN0##UCN1(int size, HashFunction##UCN0 hash_function)                          \
{                                                                                                                              \
    HashMap##UCN0##UCN1 table;                                                                                                 \
    table.table = calloc(size, sizeof(HashMap##UCN0##UCN1));                                                                   \
    for (int i = 0; i < size; ++i)                                                                                             \
        table.table[i] = defaultListPair##UCN0##UCN1();                                                                        \
    table.table_size = size;                                                                                                   \
    table.hash_function = hash_function;                                                                                       \
    table.amount_of_elements = 0;                                                                                              \
    return table;                                                                                                              \
                                                                                                                               \
}                                                                                                                              \
                                                                                                                               \
static inline void destructHashMap##UCN0##UCN1(HashMap##UCN0##UCN1 * table)                                                    \
{                                                                                                                              \
    if (table->table == NULL)                                                                                                  \
        return;                                                                                                                \
    for (int i = 0; i < table->table_size; ++i)                                                                                \
        destructListPair##UCN0##UCN1(&table->table[i]);                                                                        \
    table->table_size = -1;                                                                                                    \
    free(table->table);                                                                                                        \
    table->table = 0;                                                                                                          \
    table->hash_function = NULL;                                                                                               \
    table->amount_of_elements = -1;                                                                                            \
}                                                                                                                              \
                                                                                                                               \
static inline HashMap##UCN0##UCN1 copyHashMap##UCN0##UCN1(const HashMap##UCN0##UCN1 * table)                                   \
{                                                                                                                              \
    HashMap##UCN0##UCN1 res = makeHashMap##UCN0##UCN1(table->table_size, table->hash_function);                                \
    for (int i = 0; i < table->table_size; ++i)                                                                                \
        res.table[i] = copyListPair##UCN0##UCN1(&table->table[i]);                                                             \
    res.amount_of_elements = table->amount_of_elements;                                                                        \
    return res;                                                                                                                \
}                                                                                                                              \
                                                                                                                               \
static inline HashMap##UCN0##UCN1 moveHashMap##UCN0##UCN1(HashMap##UCN0##UCN1 * table)                                         \
{                                                                                                                              \
    HashMap##UCN0##UCN1 res;                                                                                                   \
    res.table_size = table->table_size;                                                                                        \
    res.hash_function = table->hash_function;                                                                                  \
    res.table = table->table;                                                                                                  \
    res.amount_of_elements = table->amount_of_elements;                                                                        \
                                                                                                                               \
    table->table = NULL;                                                                                                       \
    table->table_size = -1;                                                                                                    \
    table->amount_of_elements = -1;                                                                                            \
                                                                                                                               \
    return res;                                                                                                                \
}                                                                                                                              \
                                                                                                                               \
static inline void addElementHashMap##UCN0##UCN1(HashMap##UCN0##UCN1 * table, UCN0##_Ref key, const UCN1 * element)            \
{                                                                                                                              \
    unsigned int hash = callHashFunctionHashMap##UCN0##UCN1(table, &key) % table->table_size;                                  \
    pushBackToListPair##UCN0##UCN1##RV(&table->table[hash], defaultPair##UCN0##UCN1(&key, element));                           \
    table->amount_of_elements++;                                                                                               \
}                                                                                                                              \
static inline void addElementHashMap##UCN0##UCN1##RVLV(HashMap##UCN0##UCN1 * table, UCN0 key, const UCN1 * element)            \
{                                                                                                                              \
    unsigned int hash = callHashFunctionHashMap##UCN0##UCN1(table, &key) % table->table_size;                                  \
    pushBackToListPair##UCN0##UCN1##RV(&table->table[hash], defaultPair##UCN0##UCN1##RVLV(key, element));                      \
    table->amount_of_elements++;                                                                                               \
}                                                                                                                              \
static inline void addElementHashMap##UCN0##UCN1##LVRV(HashMap##UCN0##UCN1 * table, UCN0##_Ref key, UCN1 element)              \
{                                                                                                                              \
    unsigned int hash = callHashFunctionHashMap##UCN0##UCN1(table, &key) % table->table_size;                                  \
    pushBackToListPair##UCN0##UCN1##RV(&table->table[hash], defaultPair##UCN0##UCN1##LVRV(&key, element));                     \
    table->amount_of_elements++;                                                                                               \
}                                                                                                                              \
static inline void addElementHashMap##UCN0##UCN1##RV(HashMap##UCN0##UCN1 * table, UCN0 key, UCN1 element)                      \
{                                                                                                                              \
    unsigned int hash = callHashFunctionHashMap##UCN0##UCN1(table, &key) % table->table_size;                                  \
    pushBackToListPair##UCN0##UCN1##RV(&table->table[hash], defaultPair##UCN0##UCN1##RV(key, element));                        \
    table->amount_of_elements++;                                                                                               \
}                                                                                                                              \
                                                                                                                               \
                                                                                                                               \
static inline HashMap##UCN0##UCN1##Iterator atHashMap##UCN0##UCN1(HashMap##UCN0##UCN1 * table, UCN0##_Ref key)                 \
{                                                                                                                              \
    int hash = callHashFunctionHashMap##UCN0##UCN1(table, &key) % table->table_size;                                           \
    for (ListPair##UCN0##UCN1##Iterator it = beginListPair##UCN0##UCN1(&table->table[hash]);                                   \
         it != endListPair##UCN0##UCN1(&table->table[hash]);                                                                   \
         it = iterateListPair##UCN0##UCN1(it))                                                                                 \
    {                                                                                                                          \
        if (equal##UCN0(&it->data->first, &key))                                                                               \
            return defaultPairIntListPair##UCN0##UCN1##IteratorRVLV(hash, &it);                                                \
    }                                                                                                                          \
    return endHashMap##UCN0##UCN1(table);                                                                                      \
}                                                                                                                              \
                                                                                                                               \
static inline HashMap##UCN0##UCN1##Iterator endHashMap##UCN0##UCN1(HashMap##UCN0##UCN1 * table)                                \
{                                                                                                                              \
    return defaultPairIntListPair##UCN0##UCN1##IteratorRV(table->table_size, NULL);                                            \
}                                                                                                                              \
static inline bool isEndHashMap##UCN0##UCN1(const HashMap##UCN0##UCN1 * table, HashMap##UCN0##UCN1##Iterator it)               \
{                                                                                                                              \
    return it.first == table->table_size && it.second == NULL;                                                                 \
}                                                                                                                              \
static inline bool iscEndHashMap##UCN0##UCN1(const HashMap##UCN0##UCN1 * table, HashMap##UCN0##UCN1##ConstIterator it)         \
{                                                                                                                              \
    return it.first == table->table_size && it.second == NULL;                                                                 \
}                                                                                                                              \
                                                                                                                               \
static inline HashMap##UCN0##UCN1##ConstIterator catHashMap##UCN0##UCN1(const HashMap##UCN0##UCN1 * table, UCN0##_Ref key)     \
{                                                                                                                              \
    int hash = callHashFunctionHashMap##UCN0##UCN1(table, &key) % table->table_size;                                           \
    for (ListPair##UCN0##UCN1##ConstIterator it = cbeginListPair##UCN0##UCN1(&table->table[hash]);                             \
         it != cendListPair##UCN0##UCN1(&table->table[hash]);                                                                  \
         it = citerateListPair##UCN0##UCN1(it))                                                                                \
    {                                                                                                                          \
        if (equal##UCN0(&it->data->first, &key))                                                                               \
            return defaultPairIntListPair##UCN0##UCN1##ConstIteratorRVLV(hash, &it);                                           \
    }                                                                                                                          \
    return cendHashMap##UCN0##UCN1(table);                                                                                     \
}                                                                                                                              \
                                                                                                                               \
static inline HashMap##UCN0##UCN1##ConstIterator cendHashMap##UCN0##UCN1(const HashMap##UCN0##UCN1 * table)                    \
{                                                                                                                              \
    return defaultPairIntListPair##UCN0##UCN1##ConstIteratorRV(table->table_size, NULL);                                       \
}                                                                                                                              \
                                                                                                                               \
static inline void eraseFromHashMap##UCN0##UCN1(HashMap##UCN0##UCN1 * table, HashMap##UCN0##UCN1##Iterator it)                 \
{                                                                                                                              \
    assert(table->amount_of_elements > 0);                                                                                     \
    table->amount_of_elements--;                                                                                               \
    assert(&table->table[it.first] == it.second->list);                                                                        \
    eraseListPair##UCN0##UCN1##Node(it.second);                                                                                \
}                                                                                                                              \


#define MAKE_HASHMAP(UCN0, TYPE0, ARITHM_TYPE0, UCN1, TYPE1, ARITHM_TYPE1) PREPARE_HASHMAP(UCN0, TYPE0, ARITHM_TYPE0, UCN1, TYPE1, ARITHM_TYPE1)


#endif
