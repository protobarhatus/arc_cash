#include <stdio.h>
#include "lru_cache.h"

// #define DEMONSTRATION_MODE

int main(int argc, char *argv[]) {
#ifdef DEMONSTRATION_MODE
    FILE *output_file = NULL;
#endif
    int c = 0, nreqs = 0, hits = 0;
    LRUCache cache = {};

#ifdef DEMONSTRATION_MODE
    if (argc < 2) {
        printf("\nno file name, abort\n\n");
        return 0;
    }
#endif

    scanf("%d%d", &c, &nreqs);
    cache = defaultLRUCache(c, 100000);
    for (int i = 0; i < nreqs; ++i) {
        int page_ident = 0;
        scanf("%d", &page_ident);
        if (checkOutPageLRUCache(&cache, page_ident, NULL)) {
            hits += 1;
        } else {
            addPageLRUCache(&cache, defaultPage(page_ident, NULL));
        }
    }

    destructLRUCache(&cache);
#ifdef DEMONSTRATION_MODE
    output_file = fopen(argv[1], "a");
    assert(output_file);
    fprintf(output_file, "%9.d\t\t\t%.6d\t\t\t%.2f", c, hits, 100 * ((float) hits) / ((float) nreqs));
    fclose(output_file);
#else
    printf("%d", hits);
#endif
    return 0;
}
