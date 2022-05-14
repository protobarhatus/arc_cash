#include "hashmap.h"

HashMapIntInt defaultHashMapIntInt()
{
    return makeHashMapIntInt(100000, HM_INT_STANDART_CACHE);
}