#include "../test_idents.h"
#include "cachetest.h"

void run_test(TEST_IDENT ident, FILE **res_file) {
    char com_line[128] = "";

    fprintf(*res_file, "\n\nLRU performance (1000000 requests):\n\nCache capacity           Hits          Hit ratio (%%)");
    for (int i = 0; i < 13; ++i) {
        fprintf(*res_file, "\n");
        sprintf(com_line, "./lru testres.log < testpool/%d-%d.tst", ident, i);
        fclose(*res_file);
        system(com_line);
        *res_file = fopen("testres.log", "a");
    }

    fprintf(*res_file, "\n\n\nFRC performance (1000000 requests):\n\nCache capacity           Hits          Hit ratio (%%)");
    for (int i = 0; i < 13; ++i) {
        fprintf(*res_file, "\n");
        sprintf(com_line, "./frc testres.log < testpool/%d-%d.tst", ident, i);
        fclose(*res_file);
        system(com_line);
        *res_file = fopen("testres.log", "a");
    }

    fprintf(*res_file, "\n\n\nARC performance (1000000 requests):\n\nCache capacity           Hits          Hit ratio (%%)");
    for (int i = 0; i < 13; ++i) {
        fprintf(*res_file, "\n");
        sprintf(com_line, "./arc testres.log < testpool/%d-%d.tst", ident, i);
        fclose(*res_file);
        system(com_line);
        *res_file = fopen("testres.log", "a");
    }
    fputs("\n\n--------------------------------------------------------\n\n\n", *res_file);
}
