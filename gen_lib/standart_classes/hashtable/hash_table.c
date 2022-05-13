#include "hash_table.h"



HashTableInt defaultHashTableInt()
{
    return makeHashTableInt(100000, 0x1);
}