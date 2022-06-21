#ifndef FIBONACHY_NIM_ARC_cache_H
#define FIBONACHY_NIM_ARC_cache_H

#include "hashtable/hashmap.h"
#include  "../shared/modes.h"
#include "../shared/Page/Page.h"
#include "../shared/cachedir/cachedir.h"

/*ArcCache emulates working of cache with adaptive replacement policy
 * detailed description of algorithm is available here http://theory.stanford.edu/~megiddo/pdf/IEEE_COMPUTER_0404.pdf
 * to initialize cache, call either defaultArcCache
 *
 * to use, call checkOutPageArcCache to check if page x is placed in cache and also save it in cache memory
 * and do all necessary work by algorithm
 * then, if return value is true call readPageArcCache to get access to data in this page
 * otherwise, call writePageArcCache to save page's data to the cache
 *
 * if there is no actual data to save in cache and you use it only to count cache hits then
 * use deactArcCache function after any result of checkOutPageArcCache
 *
 * Calling one of three of these functions after checkOutPageArcCache is obligatory and otherwise
 * it will not work properly
 *
 * dont forget to call destructArcCache when everything is done
 * */

typedef DirListIterator Dlit;

MAKE_PAIR(Int, SIMPLE, SIMPLE, Dlit, SIMPLE, STRUCT)
MAKE_LIST(PairIntDlit, SIMPLE, STRUCT)

MAKE_HASHMAP(Int, SIMPLE, SIMPLE, Dlit, SIMPLE, STRUCT)

#define LINE_SIZE 60

struct ArcCache_struct {
    HashMapIntDlit pages_map;
    DirList B1, B2, T1, T2;
    char * cache_line;
    int p;
    int c;

    char * prepared_line;

    // структура данных где хранятся данные для DBL(2). Работа при этом идет с B1, B2, T1, T2 - интерфейсами ComArr
    ComArr * dbl_store;
    int untouched_space;
};
typedef struct ArcCache_struct ArcCache;

// hashmap_length is how much buckets are allowed in hashmap inside cache. the bigger value the better
// the perfomance (if page's numbers can be bigger then hashmap_length), but muuuch more memory it takes
ArcCache defaultArcCache(int c, int hashmap_length);
void destructArcCache(ArcCache * cache);

bool checkOutPageArcCache(ArcCache * cache, int page);

char * readPageArcCache(ArcCache * cache);
void writePageArcCache(ArcCache * cache, char * page);

//вызывается после checkOut, если кэш работает в холостую, т е нет реальных данных для записи/чтения
void deactArcCache(ArcCache * cache);

void printfCacheState(const ArcCache * cache);

#endif // FIBONACHY_NIM_ARC_cache_H
