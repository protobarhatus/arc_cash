#ifndef VECTOR_DEF_H
#define VECTOR_DEF_H

#include "stdlib.h"
#include "string.h"
#include "../types_and_functions_declarations/general_type.h"
#include "vector_general_type.h"
#define MAKE_VECTOR(UCN0, TYPE0, ARITHM_TYPE0)\
                                                                                                             \
                                                                                                             \
                                                                                                             \
                                                                                                             \
                                                                                                             \
                                                                                                             \
                                                                                                             \
struct Vector##UCN0##_struct                                                                                 \
{                                                                                                            \
    UCN0 * vec;                                                                                              \
    int size;                                                                                                \
    int allocated_size;                                                                                      \
                                                                                                             \
                                                                                                             \
    UCN0 * (*at)(struct Vector##UCN0##_struct * obj, int i);                                                 \
    const UCN0 * (*cat)(const struct Vector##UCN0##_struct * obj, int i);                                    \
    int (*getSize)(const struct Vector##UCN0##_struct * obj);                                                \
    void (*pushBack)(struct Vector##UCN0##_struct * obj, const UCN0* el);                                    \
    void (*pushBackRV)(struct Vector##UCN0##_struct * obj, UCN0 el);                                         \
    UCN0 * (*back)(struct Vector##UCN0##_struct * obj);                                                      \
    void (*pushBackCalloced)(struct Vector##UCN0##_struct * obj, UCN0 * el);                                 \
    void (*popBack)(struct Vector##UCN0##_struct * obj);                                                     \
    void (*resize)(struct Vector##UCN0##_struct * obj, int new_size);                                        \
};                                                                                                           \
                                                                                                             \
typedef struct Vector##UCN0##_struct Vector##UCN0;                                                           \
typedef Vector##UCN0 VectorRef##UCN0;                                                                        \
                                                                                                             \
static inline Vector##UCN0 defaultVector##UCN0(int size, const UCN0 * def_value);                            \
static inline Vector##UCN0 defaultVector##UCN0##RV(int size, UCN0 def_value);                                \
                                                                                                             \
static inline Vector##UCN0 defaultVector##UCN0##WithStrictSize(int size, const UCN0 * def_value);            \
static inline Vector##UCN0 defaultVector##UCN0##WithStrictSizeRV(int size, UCN0 def_value);                  \
                                                                                                             \
static inline VectorRef##UCN0 wrapVector##UCN0(const UCN0 * vec, int size);                                  \
                                                                                                             \
static inline Vector##UCN0 emptyVector##UCN0();                                                              \
                                                                                                             \
static inline Vector##UCN0 copyVector##UCN0(const Vector##UCN0 * cop);                                       \
static inline Vector##UCN0 moveVector##UCN0(Vector##UCN0 * cop);                                             \
static inline void destructVector##UCN0(Vector##UCN0 * vec);                                                 \
                                                                                                             \
static inline UCN0 * atVector##UCN0(Vector##UCN0 * v, int i);                                                \
static inline const UCN0 * catVector##UCN0(const Vector##UCN0 * v, int i);                                   \
                                                                                                             \
static inline bool equalVector##UCN0(const Vector##UCN0 * a, const Vector##UCN0 * b);                        \
                                                                                                             \
static inline void popBackVector##UCN0(Vector##UCN0 * a);                                                    \
                                                                                                             \
static inline void pushBackVector##UCN0(Vector##UCN0 * a, const UCN0 * val);                                 \
static inline void pushBackVector##UCN0##RV(Vector##UCN0 * a, UCN0 val);                                     \
                                                                                                             \
static inline int getSizeVector##UCN0(const Vector##UCN0 * a);                                               \
                                                                                                             \
static inline void resizeVector##UCN0(Vector##UCN0 * vec, int new_size);                                     \
                                                                                                             \
static inline void pushBackCallocedVector##UCN0(Vector##UCN0 * vec, UCN0 * obj);                             \
                                                                                                             \
static inline UCN0 * Vector##UCN0##DissolveIntoPointer(VectorRef##UCN0 * vec);                               \
                                                                                                             \
static inline UCN0 * Vector##UCN0##Back(Vector##UCN0 * vec);                                                 \
                                                                                                             \
static inline void sortVector##UCN0(Vector##UCN0 * vec, int (*comparator)(const void *, const void *) );     \
                                                                                                             \
DECLARE_STRUCT_TYPE(Vector##UCN0, Vector##UCN0)                                                              \
                                                                                                             \
                                                                                                             \
                                                                                                           \
                                                                                                           \
static inline void assignFunctionsVector##UCN0(Vector##UCN0 * vec)                                         \
{                                                                                                          \
    vec->at = &atVector##UCN0;                                                                             \
    vec->cat = &catVector##UCN0;                                                                           \
    vec->resize = &resizeVector##UCN0;                                                                     \
    vec->getSize = &getSizeVector##UCN0;                                                                   \
    vec->pushBack = &pushBackVector##UCN0;                                                                 \
    vec->pushBackRV = &pushBackVector##UCN0##RV;                                                           \
    vec->popBack = &popBackVector##UCN0;                                                                   \
    vec->back = &Vector##UCN0##Back;                                                                       \
    vec->pushBackCalloced = &pushBackCallocedVector##UCN0;                                                 \
                                                                                                           \
}                                                                                                          \
                                                                                                           \
static inline Vector##UCN0 defaultVector##UCN0(int size, const UCN0 * def_value)                           \
{                                                                                                          \
    Vector##UCN0 res;                                                                                      \
    res.size = size;                                                                                       \
    res.allocated_size = size * 2 + 1;                                                                     \
    res.vec = calloc(res.allocated_size, sizeof(UCN0));                                                    \
    assignFunctionsVector##UCN0(&res);                                                                     \
    if (def_value == NULL)                                                                                 \
        return res;                                                                                        \
    for (int i = 0; i < size; ++i)                                                                         \
        res.vec[i] = TYPE0##_TYPE_COPY(UCN0, def_value);                                                   \
                                                                                                           \
                                                                                                           \
                                                                                                           \
    return res;                                                                                            \
}                                                                                                          \
static inline Vector##UCN0 defaultVector##UCN0##RV(int size, UCN0 def_value)                               \
{                                                                                                          \
    Vector##UCN0 res;                                                                                      \
    res.size = size;                                                                                       \
    res.allocated_size = size * 2 + 1;                                                                     \
    res.vec = calloc(res.allocated_size, sizeof(UCN0));                                                    \
    if (size > 0)                                                                                          \
    {                                                                                                      \
        for (int i = 1; i < size; ++i)                                                                     \
            res.vec[i] = TYPE0##_TYPE_COPY(UCN0, &def_value);                                              \
        res.vec[0] = TYPE0##_TYPE_MOVE(UCN0, &def_value);                                                  \
    }                                                                                                      \
    else                                                                                                   \
        TYPE0##_TYPE_DESTRUCT(UCN0, &def_value);                                                           \
                                                                                                           \
    assignFunctionsVector##UCN0(&res);                                                                     \
    return res;                                                                                            \
}                                                                                                          \
                                                                                                           \
static inline Vector##UCN0 defaultVector##UCN0##WithStrictSize(int size, const UCN0 * def_value)           \
{                                                                                                          \
    Vector##UCN0 res;                                                                                      \
    res.size = size;                                                                                       \
    res.allocated_size = size;                                                                             \
    res.vec = calloc(res.allocated_size, sizeof(UCN0));                                                    \
    assignFunctionsVector##UCN0(&res);                                                                     \
    if (def_value == NULL)                                                                                 \
        return res;                                                                                        \
    for (int i = 0; i < size; ++i)                                                                         \
        res.vec[i] = TYPE0##_TYPE_COPY(UCN0, def_value);                                                   \
                                                                                                           \
                                                                                                           \
                                                                                                           \
    return res;                                                                                            \
}                                                                                                          \
static inline Vector##UCN0 defaultVector##UCN0##WithStrictSizeRV(int size, UCN0 def_value)                 \
{                                                                                                          \
    Vector##UCN0 res;                                                                                      \
    res.size = size;                                                                                       \
    res.allocated_size = size;                                                                             \
    res.vec = calloc(res.allocated_size, sizeof(UCN0));                                                    \
    if (size > 0)                                                                                          \
    {                                                                                                      \
        for (int i = 1; i < size; ++i)                                                                     \
            res.vec[i] = TYPE0##_TYPE_COPY(UCN0, &def_value);                                              \
        res.vec[0] = TYPE0##_TYPE_MOVE(UCN0, &def_value);                                                  \
    }                                                                                                      \
    else                                                                                                   \
        TYPE0##_TYPE_DESTRUCT(UCN0, &def_value);                                                           \
                                                                                                           \
    assignFunctionsVector##UCN0(&res);                                                                     \
    return res;                                                                                            \
}                                                                                                          \
                                                                                                           \
static inline VectorRef##UCN0 wrapVector##UCN0(const UCN0 * vec, int size)                                 \
{                                                                                                          \
    VectorRef##UCN0 res;                                                                                   \
    res.size = size;                                                                                       \
    res.allocated_size = -2;                                                                               \
    res.vec = (UCN0 *)vec;                                                                                 \
                                                                                                           \
    assignFunctionsVector##UCN0(&res);                                                                     \
    return res;                                                                                            \
}                                                                                                          \
                                                                                                           \
static inline Vector##UCN0 emptyVector##UCN0()                                                             \
{                                                                                                          \
    Vector##UCN0 res;                                                                                      \
    res.size = 0;                                                                                          \
    res.allocated_size = 0;                                                                                \
    res.vec = NULL;                                                                                        \
                                                                                                           \
    assignFunctionsVector##UCN0(&res);                                                                     \
                                                                                                           \
    return res;                                                                                            \
}                                                                                                          \
                                                                                                           \
static inline Vector##UCN0 copyVector##UCN0(const Vector##UCN0 * cop)                                      \
{                                                                                                          \
    Vector##UCN0 res;                                                                                      \
    res.size = cop->size;                                                                                  \
    res.allocated_size = cop->allocated_size;                                                              \
    res.vec = calloc(res.allocated_size, sizeof(UCN0));                                                    \
    for (int i = 0; i < cop->size; ++i)                                                                    \
        res.vec[i] = TYPE0##_TYPE_COPY(UCN0, cop->vec + i);                                                \
                                                                                                           \
    assignFunctionsVector##UCN0(&res);                                                                     \
    return res;                                                                                            \
}                                                                                                          \
static inline Vector##UCN0 moveVector##UCN0(Vector##UCN0 * cop)                                            \
{                                                                                                          \
    Vector##UCN0 res;                                                                                      \
    res.size = cop->size;                                                                                  \
    res.allocated_size = cop->allocated_size;                                                              \
    res.vec = cop->vec;                                                                                    \
    cop->size = 0;                                                                                         \
    cop->allocated_size = -2;                                                                              \
    cop->vec = NULL;                                                                                       \
    assignFunctionsVector##UCN0(&res);                                                                     \
    return res;                                                                                            \
}                                                                                                          \
                                                                                                           \
static inline UCN0 * atVector##UCN0(Vector##UCN0 * v, int i)                                               \
{                                                                                                          \
    return v->vec + i;                                                                                     \
}                                                                                                          \
static inline const UCN0 * catVector##UCN0(const Vector##UCN0 * v, int i)                                  \
{                                                                                                          \
    return v->vec + i;                                                                                     \
}                                                                                                          \
                                                                                                           \
static inline bool equalVector##UCN0(const Vector##UCN0 * a, const Vector##UCN0 * b)                       \
{                                                                                                          \
    if (a->size != b->size)                                                                                \
        return false;                                                                                      \
    for (int i = 0; i < a->size;++i)                                                                       \
    {                                                                                                      \
        if (!equal##UCN0(catVector##UCN0(a, i), catVector##UCN0(b, i)))                                    \
            return false;                                                                                  \
    }                                                                                                      \
    return true;                                                                                           \
}                                                                                                          \
                                                                                                           \
static inline void popBackVector##UCN0(Vector##UCN0 * a)                                                   \
{                                                                                                          \
    if (a->size == 0)                                                                                      \
        return;                                                                                            \
    a->size--;                                                                                             \
    TYPE0##_TYPE_DESTRUCT(UCN0, atVector##UCN0(a, a->size));                                               \
}                                                                                                          \
                                                                                                           \
static inline void pushBackVector##UCN0(Vector##UCN0 * a, const UCN0 * val)                                \
{                                                                                                          \
    if (a->allocated_size > a->size)                                                                       \
    {                                                                                                      \
        a->vec[a->size] = TYPE0##_TYPE_COPY(UCN0, val);                                                    \
        a->size++;                                                                                         \
        return;                                                                                            \
    }                                                                                                      \
    a->allocated_size = a->allocated_size * 2 + 1;                                                         \
    a->vec = realloc(a->vec, a->allocated_size * sizeof(UCN0));                                            \
    assert(a->vec != NULL);                                                                                \
                                                                                                           \
    a->vec[a->size] = TYPE0##_TYPE_COPY(UCN0, val);                                                        \
    a->size++;                                                                                             \
                                                                                                           \
}                                                                                                          \
                                                                                                           \
static inline void pushBackVector##UCN0##RV(Vector##UCN0 * a, UCN0 val)                                    \
{                                                                                                          \
    if (a->allocated_size > a->size)                                                                       \
    {                                                                                                      \
        a->vec[a->size] = TYPE0##_TYPE_MOVE(UCN0, &val);                                                   \
        a->size++;                                                                                         \
        return;                                                                                            \
    }                                                                                                      \
    a->allocated_size = a->allocated_size * 2 + 1;                                                         \
    a->vec = realloc(a->vec, a->allocated_size * sizeof(UCN0));                                            \
    assert(a->vec != NULL);                                                                                \
                                                                                                           \
    a->vec[a->size] = TYPE0##_TYPE_MOVE(UCN0, &val);                                                       \
    a->size++;                                                                                             \
}                                                                                                          \
static inline void destructVector##UCN0(Vector##UCN0 * vec)                                                \
{                                                                                                          \
    for (int i = 0; i < vec->size; ++i)                                                                    \
    {                                                                                                      \
        TYPE0##_TYPE_DESTRUCT(UCN0, vec->vec + i);                                                         \
    }                                                                                                      \
    free(vec->vec);                                                                                        \
    vec->vec = NULL;                                                                                       \
    vec->size = 0;                                                                                         \
    vec->allocated_size = -2;                                                                              \
}                                                                                                          \
                                                                                                           \
static inline int getSizeVector##UCN0(const Vector##UCN0 * a)                                              \
{                                                                                                          \
    return a->size;                                                                                        \
}                                                                                                          \
                                                                                                           \
static inline void resizeVector##UCN0(Vector##UCN0 * vec, int new_size)                                    \
{                                                                                                          \
    /*assert(new_size < vec->size);*/                                                                      \
    if (new_size >= vec->size)                                                                             \
    {                                                                                                      \
        if (new_size > vec->allocated_size)                                                                \
        {                                                                                                  \
            while (new_size >= vec->allocated_size)                                                        \
                vec->allocated_size = vec->allocated_size * 2 + 1;                                         \
            vec->vec = realloc(vec->vec, vec->allocated_size * sizeof(UCN0));                              \
        }                                                                                                  \
        memset(atVector##UCN0(vec, vec->size), 0, (new_size - vec->size) * sizeof (UCN0));                 \
        vec->size = new_size;                                                                              \
        return;                                                                                            \
    }                                                                                                      \
    for (int i = vec->size - 1; i >= new_size; --i)                                                        \
        TYPE0##_TYPE_DESTRUCT(UCN0, vec->vec + i);                                                         \
    vec->size = new_size;                                                                                  \
                                                                                                           \
}                                                                                                          \
                                                                                                           \
static inline void pushBackCallocedVector##UCN0(Vector##UCN0 * vec, UCN0 * obj)                            \
{                                                                                                          \
    pushBackVector##UCN0##RV(vec, *obj);                                                                   \
    free(obj);                                                                                             \
}                                                                                                          \
                                                                                                           \
static inline UCN0 * Vector##UCN0##DissolveIntoPointer(VectorRef##UCN0 * vec)                              \
{                                                                                                          \
    vec->size = -1;                                                                                        \
    vec->allocated_size = -1;                                                                              \
    return vec->vec;                                                                                       \
}                                                                                                          \
                                                                                                           \
static inline UCN0 * Vector##UCN0##Back(Vector##UCN0 * vec)                                                \
{                                                                                                          \
    if (vec->size == 0)                                                                                    \
        return NULL;                                                                                       \
    return vec->vec + vec->size - 1;                                                                       \
}                                                                                                          \
                                                                                                           \
static inline void sortVector##UCN0(Vector##UCN0 * vec, int (*comparator)(const void *, const void *))     \
{                                                                                                          \
    qsort(vec->vec, vec->size, sizeof(UCN0), comparator);                                                  \
}                                                                                                          \


#endif
