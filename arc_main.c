#include <stdio.h>
#include "arc_cache.h"
#include "user_interacts/user_interactions.h"
#include "AutoChecker.h"

// #define FLAW_CONTROL

int main(int argc, char *argv[]) {
    setbuf(stdout, 0);
    FILE *output_file = NULL;
    int c = 0, nreqs = 0, hits = 0;
    ArcCache cache = {};
    
    if (argc < 2) {
        printf("\nno file name, abort\n\n");
        return 0;
    }

    c = scanfInt(); nreqs = scanfInt();
    cache = defaultArcCache(c, 100000);
#ifdef FLAW_CONTROL
    for (int i = 0; i < nreqs; ++i) {
        int x = scanfInt();
        if (checkInput(&cache, x, false) != RES_OK) {
            printf("\n\n\nARC: ERROR OCCURED: caching process interrupted\n\n\n");
            return 0;
        }
    }
#else
    for (int i = 0; i < nreqs; ++i) {
        int x = scanfInt();
        Page p = defaultPage(x, NULL);
        if (checkOutPageArcCache(&cache, x)) {
            hits += 1;
        }
        deactArcCache(&cache);
    }
#endif

    destructArcCache(&cache);
    output_file = fopen(argv[1], "a");
    assert(output_file);
    fprintf(output_file, "%d\t%d\t%.2f", c, hits, 100 * ((float) hits) / ((float) nreqs));
    fclose(output_file);
    return 0;
}
