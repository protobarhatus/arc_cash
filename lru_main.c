#include "lru_cache.h"

int main()
{
    int m, n;
    scanf("%d%d", &m, &n);
    LRUCache cache = defaultLRUCache(m, 1000);
    int succ = 0;
    for (int i = 0; i < n; ++i)
    {
        int page;
        scanf("%d", &page);
        //у него формат именно такой, менять тут нельзя
        if (checkOutPageLRUCache(&cache, page,  NULL))
            ++succ;
        else
            addPageLRUCache(&cache, defaultPage(page, NULL));
    }
    printf("%d", succ);
    destructLRUCache(&cache);
}

