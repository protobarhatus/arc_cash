#include "hash_table_general_type.h"


int int_hash_functionHashTable(const unsigned int * el)
{
    //числа выбраны на рандоме
    return (59 * (*el) + 29) % 100003;
}

int callHashFunctionHashTable(const HashTable * table, const GeneralType * el)
{
    if ((unsigned long long int) table->hash_function == 0x1)
        return int_hash_functionHashTable((const unsigned int *) el);
    return table->hash_function(el);
}


HashTable makeHashTable(int size, HashFunctionGeneralType hash_function)
{
    HashTable table;
    table.table = calloc(size, sizeof(HashTable));
    for (int i = 0; i < size; ++i)
        table.table[i] = defaultListGeneralType();
    table.table_size = size;
    table.hash_function = hash_function;
    table.amount_of_elements = 0;
    return table;

}
void destructHashTable(HashTable * table)
{

    if (table->table == NULL)
        return;
    for (int i = 0; i < table->table_size; ++i)
        destructListGeneralType(&table->table[i]);
    table->table_size = -1;
    free(table->table);
    table->table = 0;
    table->hash_function = NULL;
    table->amount_of_elements = -1;

}

HashTable copyHashTable(const HashTable * table)
{
    HashTable res = makeHashTable(table->table_size, table->hash_function);
    for (int i = 0; i < table->table_size; ++i)
        res.table[i] = copyListGeneralType(&table->table[i]);
    res.amount_of_elements = table->amount_of_elements;
    return res;
}

HashTable moveHashTable(HashTable * table)
{
    HashTable res;
    res.table_size = table->table_size;
    res.hash_function = table->hash_function;
    res.table = table->table;
    res.amount_of_elements = table->amount_of_elements;

    table->table = NULL;
    table->table_size = -1;
    table->amount_of_elements = -1;

    return res;
}

void addElementHashTable(HashTable * table, GeneralType_Ref element)
{
    int hash = callHashFunctionHashTable(table, &element) % table->table_size;
    pushBackToListGeneralTypeRV(&table->table[hash], copyGeneralType(&element));
    table->amount_of_elements++;

}
void addElementHashTableRV(HashTable * table, GeneralType element)
{
    int hash = callHashFunctionHashTable(table, &element) % table->table_size;
    pushBackToListGeneralTypeRV(&table->table[hash], element);
    table->amount_of_elements++;
}

HashTableIterator atHashTable(HashTable * table, GeneralType_Ref key)
{
    int hash = callHashFunctionHashTable(table, &key) % table->table_size;
    for (ListGeneralTypeIterator it = beginListGeneralType(&table->table[hash]);
            it != endListGeneralType(&table->table[hash]);
                it = iterateListGeneralType(it))
    {
        if (equalGeneralType(it->data, &key))
            return defaultPairIntListGeneralTypeIteratorRVLV(hash, &it);
    }
    return endHashTable(table);
}
HashTableIterator endHashTable(HashTable * table)
{
    return defaultPairIntListGeneralTypeIteratorRVLV(table->table_size, NULL);
}

HashTableConstIterator catHashTable(const HashTable * table, GeneralType_Ref key)
{
    int hash = callHashFunctionHashTable(table, &key) % table->table_size;
    for (ListGeneralTypeConstIterator it = cbeginListGeneralType(&table->table[hash]);
         it != cendListGeneralType(&table->table[hash]);
         it = citerateListGeneralType(it))
    {
        if (equalGeneralType(it->data, &key))
            return defaultPairIntListGeneralTypeConstIteratorRVLV(hash, &it);
    }
    return cendHashTable(table);
}

HashTableConstIterator cendHashTable(const HashTable * table)
{
    return defaultPairIntListGeneralTypeConstIteratorRV(table->table_size, NULL);
}

void eraseFromHashTable(HashTable * table, HashTableIterator it)
{
    assert(table->amount_of_elements > 0);
    table->amount_of_elements--;
    assert(&table->table[it.first] == it.second->list);
    eraseListGeneralTypeNode(it.second);
}