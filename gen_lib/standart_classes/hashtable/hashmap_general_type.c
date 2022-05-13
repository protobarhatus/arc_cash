#include "hashmap_general_type.h"

unsigned int int_hash_functionHashMap(const unsigned int * el)
{
    //числа выбраны на рандоме
    return (59 * (*el) + 29) % 100003;
}

unsigned int callHashFunctionHashMap(const HashMap * table, const Type1 * el)
{
    if ((unsigned long long int) table->hash_function == 0x1)
        return int_hash_functionHashMap((const unsigned int *) el);
    return table->hash_function(el);
}


HashMap makeHashMap(int size, HashFunctionType1 hash_function)
{
    HashMap table;
    table.table = calloc(size, sizeof(HashMap));
    for (int i = 0; i < size; ++i)
        table.table[i] = defaultListPairType1Type2();
    table.table_size = size;
    table.hash_function = hash_function;
    table.amount_of_elements = 0;
    return table;

}

void destructHashMap(HashMap * table)
{
    if (table->table == NULL)
        return;
    for (int i = 0; i < table->table_size; ++i)
        destructListPairType1Type2(&table->table[i]);
    table->table_size = -1;
    free(table->table);
    table->table = 0;
    table->hash_function = NULL;
    table->amount_of_elements = -1;
}

HashMap copyHashMap(const HashMap * table)
{
    HashMap res = makeHashMap(table->table_size, table->hash_function);
    for (int i = 0; i < table->table_size; ++i)
        res.table[i] = copyListPairType1Type2(&table->table[i]);
    res.amount_of_elements = table->amount_of_elements;
    return res;
}

HashMap moveHashMap(HashMap * table)
{
    HashMap res;
    res.table_size = table->table_size;
    res.hash_function = table->hash_function;
    res.table = table->table;
    res.amount_of_elements = table->amount_of_elements;

    table->table = NULL;
    table->table_size = -1;
    table->amount_of_elements = -1;

    return res;
}

void addElementHashMap(HashMap * table, Type1_Ref key, const Type2 * element)
{
    unsigned int hash = callHashFunctionHashMap(table, &key) % table->table_size;
    pushBackToListPairType1Type2RV(&table->table[hash], defaultPairType1Type2(&key, element));
    table->amount_of_elements++;
}
void addElementHashMapRVLV(HashMap * table, Type1 key, const Type2 * element)
{
    unsigned int hash = callHashFunctionHashMap(table, &key) % table->table_size;
    pushBackToListPairType1Type2RV(&table->table[hash], defaultPairType1Type2RVLV(key, element));
    table->amount_of_elements++;
}
void addElementHashMapLVRV(HashMap * table, Type1_Ref key, Type2 element)
{
    unsigned int hash = callHashFunctionHashMap(table, &key) % table->table_size;
    pushBackToListPairType1Type2RV(&table->table[hash], defaultPairType1Type2LVRV(&key, element));
    table->amount_of_elements++;
}
void addElementHashMapRV(HashMap * table, Type1 key, Type2 element)
{
    unsigned int hash = callHashFunctionHashMap(table, &key) % table->table_size;
    pushBackToListPairType1Type2RV(&table->table[hash], defaultPairType1Type2RV(key, element));
    table->amount_of_elements++;
}


HashMapIterator atHashMap(HashMap * table, Type1_Ref key)
{
    int hash = callHashFunctionHashMap(table, &key) % table->table_size;
    for (ListPairType1Type2Iterator it = beginListPairType1Type2(&table->table[hash]);
         it != endListPairType1Type2(&table->table[hash]);
         it = iterateListPairType1Type2(it))
    {
        if (equalType1(&it->data->first, &key))
            return defaultPairIntListPairType1Type2IteratorRVLV(hash, &it);
    }
    return endHashMap(table);
}

HashMapIterator endHashMap(HashMap * table)
{
    return defaultPairIntListPairType1Type2IteratorRV(table->table_size, NULL);
}
bool isEndHashMap(const HashMap * table, HashMapIterator it)
{
    return it.first == table->table_size && it.second == NULL;
}
bool iscEndHashMap(const HashMap * table, HashMapConstIterator it)
{
    return it.first == table->table_size && it.second == NULL;
}

HashMapConstIterator catHashMap(const HashMap * table, Type1_Ref key)
{
    int hash = callHashFunctionHashMap(table, &key) % table->table_size;
    for (ListPairType1Type2ConstIterator it = cbeginListPairType1Type2(&table->table[hash]);
         it != cendListPairType1Type2(&table->table[hash]);
         it = citerateListPairType1Type2(it))
    {
        if (equalType1(&it->data->first, &key))
            return defaultPairIntListPairType1Type2ConstIteratorRVLV(hash, &it);
    }
    return cendHashMap(table);
}

HashMapConstIterator cendHashMap(const HashMap * table)
{
    return defaultPairIntListPairType1Type2ConstIteratorRV(table->table_size, NULL);
}

void eraseFromHashMap(HashMap * table, HashMapIterator it)
{
    assert(table->amount_of_elements > 0);
    table->amount_of_elements--;
    assert(&table->table[it.first] == it.second->list);
    eraseListPairType1Type2Node(it.second);
}