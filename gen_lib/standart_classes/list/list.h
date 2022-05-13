#ifndef FIBONACHY_NIM_LIST_H
#define FIBONACHY_NIM_LIST_H

#include <types_and_functions_declarations/type_declaration.h>
#include "list_def.h"
#include "pair/pair.h"

MAKE_LIST(Int, SIMPLE, SIMPLE)

MAKE_LIST(GeneralType, STRUCT, STRUCT)

MAKE_LIST(Type1, STRUCT, STRUCT)

MAKE_LIST(Type2, STRUCT, STRUCT)

MAKE_LIST(PairType1Type2, STRUCT, STRUCT)

MAKE_PAIR(Int, SIMPLE, SIMPLE, ListGeneralTypeIterator , SIMPLE, STRUCT)
MAKE_PAIR(Int, SIMPLE, SIMPLE, ListGeneralTypeConstIterator, SIMPLE, STRUCT)

MAKE_LIST(Double, SIMPLE, SIMPLE)



MAKE_LIST(PairIntInt, SIMPLE, STRUCT)

#endif //FIBONACHY_NIM_LIST_H
