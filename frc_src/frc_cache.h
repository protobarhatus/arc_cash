#ifndef FIBONACHY_NIM_FRC_CACHE_H
#define FIBONACHY_NIM_FRC_CACHE_H

#include  "../shared/modes.h"
#include "hashtable/hashmap.h"
#include "../shared/Page/Page.h"
#include "../shared/cachedir/cachedir.h"
#include "../arc_src/arc_cache.h"    // для обьявления типа хэш-таблицы и т.п.

/* FrcCache is similar to ArcCache, but it has a bit less adaptive policy
 * So the internal parametr p should be given from outside
 * Also this class is for only counting of cache hits so dont need to call anything after checkOutPage
 * */

struct FrcCache_struct {
    HashMapIntDlit pages_map;
    DirList B1, B2, T1, T2;
    int p;
    int c;
    ComArr * dbl_store;
};
typedef struct FrcCache_struct FrcCache;

// hashmap_length is how much buckets are allowed in hashmap inside cache. the bigger value the better
// the perfomance (if page's numbers can be bigger then hashmap_length), but muuuch more memory it takes
FrcCache defaultFrcCache(int c, int p, int hashmap_length);
void destructFrcCache(FrcCache * cash);

bool checkOutPageFrcCache(FrcCache * cache, int page);
void printfFrcCacheState(const FrcCache * cash);

#endif //FIBONACHY_NIM_FRC_CACHE_H
