#ifndef FIBONACHY_NIM_FUNCTIONS_EXTENSIONS_H
#define FIBONACHY_NIM_FUNCTIONS_EXTENSIONS_H

//useful extensions for standart functions like RETV funcUCN(const TN * a, const TN * b)
//its veery inconvenient to do arithmetic without this overloads because have to make buffers for all subcomputatons
//to avoid memory leaks
//ones below are deprecated

#define GENERATE_RIGHT_VALUE_UNARY_EXTENSIONS_TO_VOID_FUNC(TN, UCN, FUNC) \
static inline void FUNC##UCN##RV(TN a)                                    \
{\
    FUNC##UCN(&a);                                                        \
    destruct##UCN(&a);\
}


#define GENERATE_RIGHT_VALUE_UNARY_EXTENSIONS(TN, UCN, FUNC, RETV) \
static inline RETV FUNC##UCN##RV(TN a)                         \
{                                                            \
    RETV res = FUNC##UCN(&a);                                  \
    destruct##UCN(&a);                                       \
    return res;                                              \
}

#define GENERATE_RIGHT_VALUE_BINARY_EXTENSIONS(TN, UCN, FUNC, RETV) \
static inline RETV FUNC##UCN##LVRV(const TN * a, TN b)                 \
{                                                      \
    RETV res = FUNC##UCN(a, &b);                         \
    destruct##UCN(&b);                                 \
    return res;                                        \
}                                                      \
static inline RETV FUNC##UCN##RVLV(TN a, const TN * b)                 \
{                                                      \
    RETV res = FUNC##UCN(&a, b);                         \
    destruct##UCN(&a);                                 \
    return res;                                        \
}                                                      \
static inline RETV FUNC##UCN##RV(TN a, TN b)                           \
{                                                      \
    RETV res = FUNC##UCN(&a, &b);                        \
    destruct##UCN(&a);                                 \
    destruct##UCN(&b);                                 \
    return res;                                        \
}                                                      \




#define GENERATE_RIGHT_VALUE_CUMULATIVE_UNARY_EXTENSIONS_SE_NAMING(TN, UCN, FUNC) \
static inline void FUNC##UCN##RV(TN * a, TN b)                                \
{\
    FUNC##UCN(a, &b);                                                   \
    destruct##UCN(&b);\
}

#define GENERATE_RIGHT_VALUE_CUMULATIVE_UNARY_EXTENSION(TN, UCN, FUNC) \
static inline void FUNC##RV(TN * a, UCN b)                              \
{\
    FUNC(a, &b);                                                                        \
    destruct##UCN(&b);                                                                    \
}

//these are not deprecated
#define GENERATE_RV_EXTENSIONS_TO_UNARY_FUNC(RETV, FUNC, ARG) \
static inline RETV FUNC##RV(ARG arg)                              \
{                                                             \
    RETV res = FUNC(&arg)  ;                                  \
    destruct##ARG(&arg);                                      \
    return res;\
}

#define GENERATE_RV_EXTENSIONS_TO_UNARY_VOID_FUNC(FUNC, ARG) \
static inline void FUNC##RV(ARG arg) {                       \
    FUNC(&arg);                                              \
    destruct##ARG(&arg);\
}                                                             \


#define GENERATE_RV_EXTENSIONS_TO_BINARY_FUNC(RETV, FUNC, Type1, Type2) \
static inline RETV FUNC##LVRV(const Type1 * a, Type2 b)                 \
{                                                                       \
    RETV res = FUNC(a, &b);                                             \
    destruct##Type2(&b);                                                \
    return res;\
}                                                                       \
static inline RETV FUNC##RVLV(Type1 a, const Type2 * b)                 \
{                                                                       \
    RETV res = FUNC(&a, b);                                             \
    destruct##Type1(&a);                                                \
    return res;\
                                                                        \
}                                                                       \
static inline RETV FUNC##RV(Type1 * a, Type2 * b) {                    \
    RETV res = FUNC(&a, &b);                                            \
    destruct##Type1(&a);                                                \
    destruct##Type2(&b);                                                \
    return res;\
}

#define GENERATE_RV_EXTENSIONS_TO_BINARY_VOID_FUNC(FUNC, Type1, Type2) \
static inline void FUNC##LVRV(const Type1 * a, Type2 b)                 \
{                                                                       \
    FUNC(a, &b);                                             \
    destruct##Type2(&b);                                                \
}                                                                       \
static inline void FUNC##RVLV(Type1 a, const Type2 * b)                 \
{                                                                       \
    FUNC(&a, b);                                             \
    destruct##Type1(&a);                                                \
                                                                        \
}                                                                       \
static inline void FUNC##RV(Type1 * a, Type2 * b) {                    \
    FUNC(&a, &b);                                            \
    destruct##Type1(&a);                                                \
    destruct##Type2(&b);                                                \
}

#define GENERATE_RV_EXTENSIONS_TO_CUMULATIVE_UNARY_FUNC(RETV, FUNC, TN, UCN) \
static inline RETV FUNC##RV(TN * a, UCN b)                                       \
{\
    RETV res = FUNC(a, &b);                                                      \
    destruct##UCN(&b);                                                           \
    return res;\
}
#define GENERATE_RV_EXTENSIONS_TO_CUMULATIVE_UNARY_VOID_FUNC(FUNC, TN, UCN) \
static inline void FUNC##RV(TN * a, UCN b)\
{\
    FUNC(a, &b);                                                            \
    destruct##UCN(&b);                                                      \
}




#endif //FIBONACHY_NIM_FUNCTIONS_EXTENSIONS_H
