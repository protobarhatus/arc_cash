#ifndef FIBONACHY_NIM_PAIR_GENERAL_TYPE_H
#define FIBONACHY_NIM_PAIR_GENERAL_TYPE_H
#include "types_and_functions_declarations/general_type.h"
#include "vector/vector.h"
struct Pair_struct
{
    Type1 first;
    Type2 second;
};
typedef struct Pair_struct Pair;
typedef Pair PairRef;
typedef Pair Pair_Ref;

Pair defaultPair(const Type1 * t1, const Type2 * t2);
Pair defaultPairLVRV(const Type1 * t1, Type2 t2);
Pair defaultPairRVLV(Type1 t1, const Type2 * t2);
Pair defaultPairRV(Type1 t1, Type2 t2);

Pair copyPair(const Pair * p);
void destructPair(Pair * p);
Pair movePair(Pair * p);

DECLARE_STRUCT_TYPE(Pair, Pair)




#endif //FIBONACHY_NIM_PAIR_GENERAL_TYPE_H
