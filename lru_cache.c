#include "lru_cache.h"
#include "assert.h"

LRUCache defaultLRUCache(int cache_size, int hash_awaylable_amount)
{
    LRUCache res;
    res.page_list = defaultListPage();

    res.page_to_vec_index = makeHashMapIntListPageIterator(hash_awaylable_amount, 0x1);
    res.size = cache_size;
    return res;
}

bool checkOutPageLRUCache(LRUCache * cache, int page, char ** page_data)
{

    assert(cache->page_list.last_element == NULL || cache->page_list.last_element->next == NULL);

    HashMapIntListPageIteratorIterator it = atHashMapIntListPageIterator(&cache->page_to_vec_index, page);

    if (isEndHashMapIntListPageIterator(&cache->page_to_vec_index, it))
    {
        //cachee miss
        return false;
    }
    //page fount
    if (page_data != NULL)
    {
        assert(*page_data == NULL);
        *page_data = it.second->data->second->data->data;
    }
    moveNodeToEndListPage(&cache->page_list, it.second->data->second);
    return true;
}
void addPageLRUCache(LRUCache * cache, PageRef page)
{
    assert(cache->page_list.last_element == NULL || cache->page_list.last_element->next == NULL);

    pushBackToListPageRV(&cache->page_list, copyPage(&page));
    HashMapIntListPageIteratorIterator it = atHashMapIntListPageIterator(&cache->page_to_vec_index, page.number);
    if (isEndHashMapIntListPageIterator(&cache->page_to_vec_index, it))
    {
        addElementHashMapIntListPageIteratorLVRV(&cache->page_to_vec_index, page.number, rbeginListPage(&cache->page_list));
    }
    else
        assert(false);

    if (cache->page_list.size > cache->size)
    {
        int end_page = beginListPage(&cache->page_list)->data->number;
        eraseFromHashMapIntListPageIterator(&cache->page_to_vec_index, atHashMapIntListPageIterator(&cache->page_to_vec_index, end_page));
        eraseListPageNode(beginListPage(&cache->page_list));
    }
}


void destructLRUCache(LRUCache * cache)
{
    destructListPage(&cache->page_list);
    destructHashMapIntListPageIterator(&cache->page_to_vec_index);
}