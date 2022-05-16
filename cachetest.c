#include "test_idents.h"
#include "cachetest.h"

void run_test(TEST_IDENT ident, FILE **res_file) {
    char com_line[36] = {};

    fprintf(*res_file, "\n\nLRU performance (1000000 requests):\n\nCache capacity\t\t Hits\t\tHit ratio (%%)");
    for (int i = 0; i < 13; ++i) {
        fprintf(*res_file, "\n");
        sprintf(com_line, "./LRU test_results.txt < tests/%d-%d.tst", ident, i);
        fclose(*res_file);
        system(com_line);
        *res_file = fopen("test_results.txt", "a");
    }

    fprintf(*res_file, "\n\n\nFRC performance (1000000 requests):\n\nCache capacity\t\t Hits\t\tHit ratio (%%)");
    for (int i = 0; i < 13; ++i) {
        fprintf(*res_file, "\n");
        sprintf(com_line, "./FRC test_results.txt < tests/%d-%d.tst", ident, i);
        fclose(*res_file);
        system(com_line);
        *res_file = fopen("test_results.txt", "a");
    }

    fprintf(*res_file, "\n\n\nARC performance (1000000 requests):\n\nCache capacity\t\t Hits\t\tHit ratio (%%)");
    for (int i = 0; i < 13; ++i) {
        fprintf(*res_file, "\n");
        sprintf(com_line, "./ARC test_results.txt < tests/%d-%d.tst", ident, i);
        fclose(*res_file);
        system(com_line);
        *res_file = fopen("test_results.txt", "a");
    }
    fputs("\n\n\n\n", *res_file);
}
