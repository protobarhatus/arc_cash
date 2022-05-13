#ifndef FIBONACHY_NIM_STRING_H
#define FIBONACHY_NIM_STRING_H

#include "types_and_functions_declarations/type_declaration.h"
#include "types_and_functions_declarations/functions_extensions.h"
#include "vector/vector.h"
#include "vector/vector_def.h"
#include "vector/algorithms.h"
#include "pair/pair.h"


struct String_struct
{
    char * string;
    int length;
    int allocated_space;
};
typedef struct String_struct String;
typedef String StringRef;


String defaultString(const char * string);
String createString(int length);
String cleanString();

String copyString(const String * str);
String moveString(String * str);
void destructString(String * str);

char * dissolveString(String * str);


StringRef wrapStandartString(const char * string);
StringRef wrapString(const String * str, int shift);

DECLARE_STRUCT_TYPE(String, String)

static inline char * atString(String * str, int i)
{
    assert(i >= 0 && i < str->length);
    return str->string + i;
}
static inline const char * catString(const String * str, int i)
{
    assert(i >= 0 && i < str->length);
    return str->string + i;
}

static inline int getLengthString(const String * str)
{
    return str->length;
}

String stringFromChar(char sym);

void resizeString(String * str, int new_length);
void shrinkString(String * str, int new_length);
void extendString(String * str, int new_length);

void concatToString(String * str, const String * right);
String concatString(const String * a, const String * b);
void addSymToString(String * str, char sym);


String terminateString();
//end is terminateString()
String stringConcatMany(String first, ...);



GENERATE_RIGHT_VALUE_BINARY_EXTENSIONS(String, String, concat, String)

GENERATE_RIGHT_VALUE_CUMULATIVE_UNARY_EXTENSIONS_SE_NAMING(String, String, concatTo)

VectorInt makePiFunction(const String * str);

int findSubString(const String * str, const String * substr);

GENERATE_RIGHT_VALUE_BINARY_EXTENSIONS(String, String, findSub, int);


MAKE_VECTOR(String, STRUCT, STRUCT)

int lessStringByStreamAlphabet(const String * a, const String * b);
int lessStringByStreamAlphabetComparator(const void * a, const void * b);

enum StringReadMode_enum
{
    SCAN_WORD,
    SCAN_LINE
};
typedef enum StringReadMode_enum StringReadMode;
String scanfString(StringReadMode mode, char * end_sym);
VectorString scanfVectorString(StringReadMode mode);

struct PrefixTree_struct;
VectorPairIntInt findPatternsByPrefixTree(const String * test, struct PrefixTree_struct * automat);

void reverseOnString(String * str);

bool equalString(const String * a, const String * b);


String reverseString(const String * str);

GENERATE_RIGHT_VALUE_UNARY_EXTENSIONS(String, String, reverse, String)
String intToString(int num);
String intToStringInBase(long long int num, int base);


MAKE_PAIR(Int, SIMPLE, SIMPLE, String, STRUCT, STRUCT)
MAKE_PAIR(String, STRUCT, STRUCT, Int, SIMPLE, SIMPLE)
MAKE_PAIR(String, STRUCT, STRUCT, String, STRUCT, STRUCT)

MAKE_VECTOR(PairIntString, STRUCT, STRUCT)
MAKE_VECTOR(PairStringInt, STRUCT, STRUCT)
MAKE_VECTOR(PairStringString, STRUCT, STRUCT)


String randString(int len, int alph);

#endif //FIBONACHY_NIM_STRING_H
