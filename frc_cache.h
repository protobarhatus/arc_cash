#ifndef FIBONACHY_NIM_FCR_CACHE_H
#define FIBONACHY_NIM_FCR_CACHE_H

#include "hashtable/hashmap.h"
#include "Page.h"
#include "cachedir.h"
#include "arc_cache.h"    // для обьявления типа хеш таблицы и т п

/* FcrCache is similar to ArcCache, but it has a bit less adaptive policy
 * So the internal parametr p should be given from outside
 * Also this class is for only counting of cache hits so dont need to call anything after checkOutPage
 * */

struct FcrCache_struct {
    HashMapIntDlit pages_map;
    DirList B1, B2, T1, T2;
    int p;
    int c;
    ComArr * dbl_store;
};
typedef struct FcrCache_struct FcrCache;

// hashmap_length is how much buckets are allowed in hashmap inside cache. the bigger value the better
// the perfomance (if page's numbers can be bigger then hashmap_length), but muuuch more memory it takes
FcrCache defaultFcrCache(int c, int p, int hashmap_length);
void destructFcrCache(FcrCache * cash);

bool checkOutPageFcrCache(FcrCache * cache, int page);
void printfFcrCacheState(const FcrCache * cash);

#endif //FIBONACHY_NIM_FCR_CACHE_H
