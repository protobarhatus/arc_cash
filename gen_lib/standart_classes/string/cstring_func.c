#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "cstring_func.h"
#include <ctype.h>
#include <stdio.h>

bool ciEqualChar(char a, char b)
{
    return toupper(a) == toupper(b);
}

void patpreproc(char const * needle, int * needle_lps)
{
    int i, k;
    needle_lps[0] = 0;

    for (i = 1; needle[i] != '\0'; ++i)
    {
        k = needle_lps[i - 1];

        while (k > 0 && !ciEqualChar(needle[i] , needle[k]))
        {
            k = needle_lps[k - 1];
        }
        if (ciEqualChar(needle[i] , needle[k]))
            ++k;
        needle_lps[i] = k;
    }
}
//don't trust st but contest requires it
char *strstrci(char const *needle, int const *st, char const *haystack)
{
    int need_len = strlen(needle);
    int ind = 0, k = 0;
    int * p_func = calloc(need_len, sizeof(int));
    patpreproc(needle, p_func);

    ind = 0;

    while (haystack[ind] != '\0')
    {
        while (k > 0 && !ciEqualChar(haystack[ind] , needle[k]))
        {
            assert(k < need_len);
            k = p_func[k - 1];
        }
        if (ciEqualChar(haystack[ind], needle[k]))
            k = k + 1;
        if (k == need_len)
        {
            free(p_func);
            return (char*)(haystack + (ind - need_len + 1));
        }
        ++ind;
    }


    free(p_func);
    return NULL;
}
char * scanfCString()
{
    char * str = calloc(1, 1);
    int alloced_len = 1;
    int len = 0;
    char sym;
    while (isprint(sym = getchar()))
    {
        if (len == alloced_len - 1)
        {
            alloced_len = alloced_len * 2 + 1;
            str = realloc(str, alloced_len);
        }
        str[len] = sym;
        ++len;
    }
    str[len] = '\0';
    return str;
}