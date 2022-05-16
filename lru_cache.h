#ifndef FIBONACHY_NIM_LRU_CACHE_H
#define FIBONACHY_NIM_LRU_CACHE_H

#include <assert.h>
#include "Page.h"
#include "hashtable/hashmap.h"
#include "list/list.h"

typedef Page Page_Ref;
typedef Page PageRef;
MAKE_LIST(Page, STRUCT, STRUCT)
MAKE_PAIR(Int, SIMPLE, SIMPLE, ListPageIterator, SIMPLE, STRUCT)
MAKE_LIST(PairIntListPageIterator, SIMPLE, STRUCT)
MAKE_HASHMAP(Int, SIMPLE, SIMPLE, ListPageIterator, SIMPLE, STRUCT)

typedef struct {
    ListPage page_list;
    HashMapIntListPageIterator page_to_vec_index;
    int size;
} LRUCache;

void addPageLRUCache(LRUCache *cache, PageRef page);
bool checkOutPageLRUCache(LRUCache *cache, int page, char **page_data);
LRUCache defaultLRUCache(int cache_size, int hash_awaylable_amount);
void destructLRUCache(LRUCache *cache);

#endif // FIBONACHY_NIM_LRU_CACHE_H
