#include <stdio.h>
#include "frc_cache.h"
#include "user_interacts/user_interactions.h"
#include "../shared/AutoChecker/AutoChecker.h"

int main(int argc, char *argv[]) {
    setbuf(stdout, 0);
#ifdef DEMONSTRATION_MODE
    FILE *output_file = NULL;
#endif
    int c = 0, nreqs = 0, hits = 0;
    FrcCache cache = {};

#ifdef DEMONSTRATION_MODE
    if (argc < 2) {
        printf("\nno file name, abort\n\n");
        return 0;
    }
#endif

    c = scanfInt(); nreqs = scanfInt();
    cache = defaultFrcCache(c, c / FRC_CP_RATIO, 100000);
#ifdef FLAW_CONTROL
    for (int i = 0; i < nreqs; ++i) {
        int x = scanfInt();
        if (checkInputFrc(&cache, x, false) != RES_OK) {
            printf("\n\n\nFRC: ERROR OCCURED: caching process interrupted\n\n\n");
            return 0;
        }
    }
#else
    for (int i = 0; i < nreqs; ++i) {
        int x = scanfInt();
        Page p = defaultPage(x, NULL);
        if (checkOutPageFrcCache(&cache, x)) {
            hits += 1;
        }
    }
#endif

    destructFrcCache(&cache);
#ifdef DEMONSTRATION_MODE
    output_file = fopen(argv[1], "a");
    assert(output_file);
    fprintf(output_file, "%9.d               %.6d             %.2f", c, hits, 100 * ((float) hits) / ((float) nreqs));
    fclose(output_file);
#else
    printf("%d", hits);
#endif
    return 0;
}
