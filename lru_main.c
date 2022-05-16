#include <stdio.h>
#include "lru_cache.h"

int main(int argc, char *argv[]) {
    FILE *output_file = NULL;
    int c = 0, nreqs = 0, hits = 0;
    LRUCache cache = {};

    if (argc < 2) {
        printf("\nno file name, abort\n\n");
        return 0;
    }

    scanf("%d%d", &c, &nreqs);
    cache = defaultLRUCache(c, 100000);
    for (int i = 0; i < nreqs; ++i) {
        int page_ident = 0;
        scanf("%d", &page_ident);
        if (checkOutPageLRUCache(&cache, page_ident,  NULL)) {
            hits += 1;
        } else {
            addPageLRUCache(&cache, defaultPage(page_ident, NULL));
        }
    }

    destructLRUCache(&cache);
    output_file = fopen(argv[1], "a");
    assert(output_file);
    fprintf(output_file, "%d\t%d\t%.2f", c, hits, 100 * ((float) hits) / ((float) nreqs));
    fclose(output_file);
    return 0;
}
