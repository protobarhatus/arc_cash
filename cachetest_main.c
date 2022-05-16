#include <stdio.h>
#include "test_idents.h"
#include "cachetest.h"

int main(int argc, char *argv[]) {
    char test_names [10][24] = {"dead", "noise", "whisper", "sets-far",
    "sets-close", "outburst-close", "outburst-far", "sets-outbursts",
    "base-pulse", "diap-pulse"};
    FILE *res_file = NULL;

    if (argc < 2) {
        printf ("\nno test name, abort\n\n");
        return 0;
    }
    if (strcmp(argv[1], "list") == 0) {
        printf("\nThe list of tests provided:\n\n");
        for (int i = 0; i < NTESTS; ++i) {
            printf("- ");
            puts(test_names[i]);
        }
        putchar('\n');
        return 0;
    }

    res_file = fopen("test_results.txt", "a");
    if (strcmp(argv[1], "all") == 0) {
        for (int i = 0; i < NTESTS; ++i) {
            fprintf(res_file, "\n\n\n%s:", test_names[i]);
            run_test(i, &res_file);
        }

        fclose(res_file);
        return 0;
    }
    for (int i = 1; i < argc; ++i) {
        bool found = false;
        for (int j = 0; j < NTESTS; ++j) {
            if (strcmp(test_names[j], argv[i]) == 0) {
                fprintf(res_file, "\n\n\n%s:", test_names[j]);
                run_test(j, &res_file);
                found = true;
                break;
            }
        }
        if (!found) {
            fprintf(res_file, "\n\n\n%s: no test with such name provided\n\n\n", argv[i]);
        }
    }

    fclose(res_file);
    return 0;
}
