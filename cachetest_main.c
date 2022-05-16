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
            fprintf(res_file, "[[[%s]]]:", test_names[i]);
            run_test(i, &res_file);
        }

        fclose(res_file);
        return 0;
    }
    for (int i = 1; i < argc; ++i) {
        bool found = false;
        for (int j = 0; j < NTESTS; ++j) {
            if (strcmp(test_names[j], argv[i]) == 0) {
                fprintf(res_file, "[[[%s]]]:", test_names[j]);
                run_test(j, &res_file);
                found = true;
                break;
            }
        }
        if (!found) {
            char com_line[48] = {}, path[128] = {};
            FILE *user_file = NULL;
            sprintf(path, "tests/%s", argv[i]);
            user_file = fopen(path, "r");
            if (user_file == NULL) {
                fprintf(res_file, "\n\n%s: no such data file in the <tests> directory\n\n", argv[i]);
                continue;
            }

            fprintf(res_file, "<<<%s>>>:", argv[i]);
            fprintf(res_file, "\n\nLRU performance:\n\nCache capacity           Hits          Hit ratio (%%)\n");
            sprintf(com_line, "./LRU test_results.txt < tests/%s", argv[i]);
            fclose(res_file);
            system(com_line);
            res_file = fopen("test_results.txt", "a");
            fprintf(res_file, "\n\n\nFRC performance:\n\nCache capacity           Hits          Hit ratio (%%)\n");
            sprintf(com_line, "./FRC test_results.txt < tests/%s", argv[i]);
            fclose(res_file);
            system(com_line);
            res_file = fopen("test_results.txt", "a");
            fprintf(res_file, "\n\n\nARC performance:\n\nCache capacity           Hits          Hit ratio (%%)\n");
            sprintf(com_line, "./ARC test_results.txt < tests/%s", argv[i]);
            fclose(res_file);
            system(com_line);
            res_file = fopen("test_results.txt", "a");
            fputs("\n\n--------------------------------------------------------\n\n\n", res_file);

            fclose(user_file);
        }
    }

    fclose(res_file);
    return 0;
}
