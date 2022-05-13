#include "string.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include "prefix_tree.h"

//+1 should always be for terminal sym
static inline int allocationSize(int len)
{
    //300 is random just not very big not very small. strings are not resized as often as vectors so double mem if len is like 10000
    //is excessive
    return (len > 300 ? len + 100 : 2*len + 1);
}
String defaultString(const char * string)
{
    String res = createString(strlen(string));

    for (int i = 0; i < res.length; ++i)
        res.string[i] = string[i];
    return res;
}

String createString(int length)
{
    assert(length >= 0);
    String res;
    res.length = length;
    res.allocated_space = allocationSize(res.length);
    res.string = calloc(res.allocated_space, 1);
    res.string[res.length] = '\0';
    return res;
}

String cleanString()
{
    return createString(0);
}

String copyString(const String * str)
{
    String res;
    res.length = str->length;
    res.allocated_space = str->allocated_space;
    res.string = calloc(res.allocated_space, 1);
    for (int i = 0; i <= str->length; ++i)
        res.string[i] = str->string[i];
    return res;
}

String moveString(String * str)
{
    String res = *str;
    str->string = NULL;
    str->length = -2;
    str->allocated_space = -2;
    return res;
}

void destructString(String * str)
{
    free(str->string);
    str->string = NULL;
    str->length = -2;
    str->allocated_space = -2;
}

StringRef wrapStandartString(const char * string)
{
    StringRef res;
    res.length = strlen(string);
    res.string = (char*)string;
    res.allocated_space = -2;
    return res;
}

StringRef wrapString(const String * str, int shift)
{
    assert(shift <= str->length);
    StringRef res;
    res.length = str->length - shift;
    res.allocated_space = -2;
    res.string = str->string + shift;
    return res;
}

void resizeString(String * str, int new_length)
{
    if (new_length > str->length)
        extendString(str, new_length);
    else
        shrinkString(str, new_length);
}
void shrinkString(String * str, int new_length)
{
    assert(new_length <= str->length);
    for (int i = str->length - 1; i >= new_length; --i)
        str->string[i] = '\0';
    str->length = new_length;
}
void extendString(String * str, int new_length)
{
    assert(new_length >= str->length);
    if (str->allocated_space > new_length)
    {
        for (int i = str->length + 1; i <= new_length; ++i)
            str->string[i] = '\0';
        str->length = new_length;
        return;
    }
    str->allocated_space = allocationSize(new_length);
    str->string = realloc(str->string, str->allocated_space);
    for (int i = str->length + 1; i <= new_length; ++i)
        str->string[i] = '\0';
    str->length = new_length;


}

void concatToString(String * str, const String * right)
{
    int old_length = str->length;
    extendString(str, str->length + right->length);
    for (int i = 0; i < right->length; ++i)
        str->string[old_length + i] = right->string[i];
}

String stringFromChar(char sym)
{
    String res = createString(1);
    res.string[0] = sym;
    return res;
}

String concatString(const String * a, const String * b)
{
    String res = createString(a->length + b->length);
    for (int i = 0; i < a->length; ++i)
        res.string[i] = a->string[i];
    for (int i = 0; i < b->length; ++i)
        res.string[i + a->length] = b->string[i];
    return res;
}

VectorInt makePiFunction(const String * str)
{
    VectorInt res = defaultVectorIntWithStrictSizeRV(str->length, 0);
    int i, k;
    *atVectorInt(&res, 0) = 0;

    for (i = 1; str->string[i] != '\0'; ++i)
    {
        k = *atVectorInt(&res, i - 1);

        while (k > 0 && str->string[i] != str->string[k])
        {
            k = *atVectorInt(&res, k - 1);
        }
        if (str->string[i] == str->string[k])
            ++k;
        *atVectorInt(&res, i) = k;
    }
    return res;
}

int findSubString(const String * str, const String * substr)
{
    int need_len = substr->length;
    int ind = 0, k = 0;
    VectorInt p_func = makePiFunction(substr);

    ind = 0;

    while (str->string[ind] != '\0')
    {
        while (k > 0 && str->string[ind] != substr->string[k])
        {
            k = *atVectorInt(&p_func, k - 1);
        }
        if (str->string[ind] == substr->string[k])
            k = k + 1;
        if (k == need_len)
        {
            destructVectorInt(&p_func);
            return ind - need_len + 1;
        }
        ++ind;
    }


    destructVectorInt(&p_func);
    return -1;
}

int lessStringByStreamAlphabet(const String * a, const String * b)
{
    for (int i = 0; i < a->length && i < b->length; ++i)
    {
        if (a->string[i] < b->string[i])
            return -1;
        if (a->string[i] > b->string[i])
            return 1;
    }
    if (a->length < b->length)
        return -1;
    if (a->length > b->length)
        return 1;
    return 0;
}
int lessStringByStreamAlphabetComparator(const void * a, const void * b)
{
    return lessStringByStreamAlphabet((const String*)a, (const String*)b);
}

String scanfString(StringReadMode mode, char * end_sym)
{
    char s = getc(stdin);
    while (isblank(s) || s == '\n')
        s = getc(stdin);
    String res = createString(0);
    switch (mode)
    {
        case SCAN_WORD:
            while (isgraph(s))
            {
                replaceString(&res , concatStringLVRV(&res, stringFromChar(s)));
                s = getc(stdin);
            }
            if (end_sym != NULL)
                *end_sym = s;
            break;
        case SCAN_LINE:
            while (isprint(s))
            {
                replaceString(&res , concatStringLVRV(&res, stringFromChar(s)));
                s = getc(stdin);
            }
            if (end_sym != NULL)
                *end_sym = s;
            break;
        default:
            assert(false);
    }
    return res;
}

VectorString scanfVectorString(StringReadMode mode)
{
    VectorString res = defaultVectorString(0, NULL);
    char end_sym;
    switch (mode)
    {
        case SCAN_WORD:
            do
            {
                pushBackVectorStringRV(&res, scanfString(SCAN_WORD, &end_sym));
            }while (isprint(end_sym));
            break;
        case SCAN_LINE:
            do
            {
                pushBackVectorStringRV(&res, scanfString(SCAN_WORD, &end_sym));
            }while (end_sym != EOF);
            break;
        default:
            assert(false);
    }
    return res;
}

static void swapChars(char * a, char * b)
{
    char t = *a;
    *a = *b;
    *b = t;
}

void reverseOnString(String * str)
{
    for (int i = 0; i < str->length / 2; ++i)
    {
        swapChars(atString(str, i), atString(str, str->length - 1 - i));
    }
}


VectorPairIntInt findPatternsByPrefixTree(const String * test, PrefixTree * automat)
{
    int size = test->length;

    VectorPairIntInt res = defaultVectorPairIntIntRV(0, defaultPairIntIntRV(0,0));
    for (int i = 0; i < size; ++i)
    {
        if (processSymbolByPrefixTree(automat, *catString(test, i)))
        {

            PrefixTreeNode * cur = automat->current;
            while (cur->previous != NULL && cur->is_end)
            {
                String fount_pattern = restoreStringToNode(cur);
                int fount_len = fount_pattern.length;
                pushBackVectorPairIntIntRV(&res, defaultPairIntIntRV(i - fount_len + 1, cur->pattern_number));
                destructString(&fount_pattern);
                cur = cur->suffix_ref;
            }

        }
    }


    return res;
}

bool equalString(const String * a, const String * b)
{
    if (a->length != b->length)
        return false;
    for (int i = 0; i < a->length; ++i)
    {
        if (a->string[i] != b->string[i])
            return false;
    }
    return true;
}

void addSymToString(String * str, char sym)
{
    concatToStringRV(str, stringFromChar(sym));
}

String reverseString(const String * str)
{
    String res = createString(str->length);
    for (int i = 0; i <= res.length - 1; ++i)
    {
        *atString(&res, i) = *catString(str, res.length - i - 1);
    }
    return res;
}

String intToString(int num)
{
    return intToStringInBase(num, 10);
}

char digFromNum(int num)
{
    if (num < 10)
        return '0' + num;
    return 'A' + num - 10;
}

String intToStringInBase(long long int num, int base)
{
    if (num == 0)
        return defaultString("0");
    String res = defaultString("");
    bool negative = num < 0;
    if (negative)
        num = -num;

    while (num > 0)
    {
        concatToStringRV(&res, stringFromChar(digFromNum(num % base)));
        num /= base;
    }

    if (negative)
        return concatStringRV(stringFromChar('-'), reverseStringRV(moveString(&res)));
    return reverseStringRV(moveString(&res));
}

char * dissolveString(String * str)
{
    char * ret = str->string;
    str->string = NULL;
    return ret;
}


String randString(int len, int alph)
{
    String res = createString(len);
    for (int i = 0; i < len; ++i)
        *atString(&res, i) = rand() % alph + 'a';
    return res;
}

String terminateString()
{
    String res;
    res.string = NULL;
    res.length = -1;
    res.allocated_space = -1;
    return res;
}
//end is terminateString()
String stringConcatMany(String first, ...)
{
    va_list arg;
    va_start(arg, first);
    String res = moveString(&first);
    while (true)
    {
        String str = va_arg(arg, String);
        if (str.string == NULL)
            break;
        concatToStringRV(&res, moveString(&str));
    }
    va_end(arg);
    return res;
}