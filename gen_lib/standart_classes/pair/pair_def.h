#ifndef PAIR_DEF_H
#define PAIR_DEF_H

#include "types_and_functions_declarations/general_type.h"
#include "vector/vector.h"
#include "pair_general_type.h"
#define MAKE_PAIR(UCN0, TYPE0, ARITHM_TYPE0, UCN1, TYPE1, ARITHM_TYPE1)\
                                                                                              \
                                                                                              \
                                                                                              \
                                                                                              \
struct Pair##UCN0##UCN1##_struct                                                              \
{                                                                                             \
    UCN0 first;                                                                               \
    UCN1 second;                                                                              \
};                                                                                            \
typedef struct Pair##UCN0##UCN1##_struct Pair##UCN0##UCN1;             \
typedef Pair##UCN0##UCN1 Pair##UCN0##UCN1##_Ref ;                                                                      \
                                                                                              \
static inline Pair##UCN0##UCN1 defaultPair##UCN0##UCN1(const UCN0 * t1, const UCN1 * t2);     \
static inline Pair##UCN0##UCN1 defaultPair##UCN0##UCN1##LVRV(const UCN0 * t1, UCN1 t2);       \
static inline Pair##UCN0##UCN1 defaultPair##UCN0##UCN1##RVLV(UCN0 t1, const UCN1 * t2);       \
static inline Pair##UCN0##UCN1 defaultPair##UCN0##UCN1##RV(UCN0 t1, UCN1 t2);                 \
                                                                                              \
static inline Pair##UCN0##UCN1 copyPair##UCN0##UCN1(const Pair##UCN0##UCN1 * p);              \
static inline void destructPair##UCN0##UCN1(Pair##UCN0##UCN1 * p);                            \
static inline Pair##UCN0##UCN1 movePair##UCN0##UCN1(Pair##UCN0##UCN1 * p);                    \
                                                                                              \
DECLARE_STRUCT_TYPE(Pair##UCN0##UCN1, Pair##UCN0##UCN1)                                       \
                                                                                              \
                                                                                              \
                                                                                              \
                                                                                              \
                                                                                              \
                                                                                             \
                                                                                             \
static inline Pair##UCN0##UCN1 defaultPair##UCN0##UCN1(const UCN0 * t1, const UCN1 * t2)     \
{                                                                                            \
    Pair##UCN0##UCN1 res;                                                                    \
    res.first = TYPE0##_TYPE_COPY(UCN0, t1);                                                 \
    res.second = TYPE1##_TYPE_COPY(UCN1, t2);                                                \
    return res;                                                                              \
}                                                                                            \
static inline Pair##UCN0##UCN1 defaultPair##UCN0##UCN1##LVRV(const UCN0 * t1, UCN1 t2)       \
{                                                                                            \
    Pair##UCN0##UCN1 res;                                                                    \
    res.first = TYPE0##_TYPE_COPY(UCN0, t1);                                                 \
    res.second = t2;                                                                         \
    return res;                                                                              \
}                                                                                            \
static inline Pair##UCN0##UCN1 defaultPair##UCN0##UCN1##RVLV(UCN0 t1, const UCN1 * t2)       \
{                                                                                            \
    Pair##UCN0##UCN1 res;                                                                    \
    res.first = t1;                                                                          \
    res.second = TYPE1##_TYPE_COPY(UCN1, t2);                                                \
    return res;                                                                              \
}                                                                                            \
static inline Pair##UCN0##UCN1 defaultPair##UCN0##UCN1##RV(UCN0 t1, UCN1 t2)                 \
{                                                                                            \
    Pair##UCN0##UCN1 res;                                                                    \
    res.first = t1;                                                                          \
    res.second = t2;                                                                         \
    return res;                                                                              \
}                                                                                            \
                                                                                             \
static inline Pair##UCN0##UCN1 copyPair##UCN0##UCN1(const Pair##UCN0##UCN1 * p)              \
{                                                                                            \
    Pair##UCN0##UCN1 res;                                                                    \
    res.first = TYPE0##_TYPE_COPY(UCN0, &p->first);                                          \
    res.second = TYPE1##_TYPE_COPY(UCN1, &p->second);                                        \
    return res;                                                                              \
                                                                                             \
}                                                                                            \
                                                                                             \
static inline void destructPair##UCN0##UCN1(Pair##UCN0##UCN1 * p)                            \
{                                                                                            \
    TYPE0##_TYPE_DESTRUCT(UCN0, &p->first);                                                  \
    TYPE1##_TYPE_DESTRUCT(UCN1, &p->second);                                                 \
                                                                                             \
}                                                                                            \
                                                                                             \
static inline Pair##UCN0##UCN1 movePair##UCN0##UCN1(Pair##UCN0##UCN1 * p)                    \
{                                                                                            \
    Pair##UCN0##UCN1 res;                                                                    \
    res.first = TYPE0##_TYPE_MOVE(UCN0, &p->first);                                          \
    res.second = TYPE1##_TYPE_MOVE(UCN1, &p->second);                                        \
    return res;                                                                              \
}                                                                                            \


#endif
