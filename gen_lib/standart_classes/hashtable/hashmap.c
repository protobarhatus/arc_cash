#include "hashmap.h"

HashMapIntInt defaultHashMapIntInt()
{
    return makeHashMapIntInt(100000, 0x1);
}