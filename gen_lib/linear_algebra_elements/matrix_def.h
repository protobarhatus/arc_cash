#ifndef MATRIX_DEF_H
#define MATRIX_DEF_H

#include "../vector/vector.h"
#include "../types_and_functions_declarations/general_type.h"
#include <stdio.h>
#include <stdarg.h>
#include "standart_classes/pair/pair.h"
#include "matrix_general_type.h"
#include "../vector/algorithms.h"
#include "vector_algebraic_addendum.h"
#define MAKE_MATRIX(UCN0, TYPE0, ARITHM_TYPE0)\
                                                                                                                                                     \
                                                                                                                                                     \
                                                                                                                                                     \
                                                                                                                                                     \
struct Matrix##UCN0##_struct {                                                                                                                       \
                                                                                                                                                     \
    VectorVector##UCN0 matrix;                                                                                                                       \
    int lines, columns;                                                                                                                              \
    Vector##UCN0 * (*at)(struct Matrix##UCN0##_struct * a, int i);                                                                                   \
                                                                                                                                                     \
    bool is_on_buffer;                                                                                                                               \
    /*its for matrix that is build on buffer. allocked_* means from its current start till end without considering allocked space behind*/           \
    int start_line, start_column, allocked_lines, allocked_columns;                                                                                  \
    /*thats made only in non buffered matrix*/                                                                                                       \
    UCN0 value_beyond_allocked_space;                                                                                                                \
    /*thats for buffered matrix. reason is that for buffered matrixes it is preferable to be Ref, but Ref*/                                          \
    /*dont require destructor*/                                                                                                                      \
    const UCN0 * value_beyond_allocked_space_ptr;                                                                                                    \
                                                                                                                                                     \
};                                                                                                                                                   \
                                                                                                                                                     \
                                                                                                                                                     \
                                                                                                                                                     \
typedef struct Matrix##UCN0##_struct Matrix##UCN0;                                                                                                   \
typedef Matrix##UCN0 MatrixRef##UCN0;                                                                                                                \
                                                                                                                                                     \
static inline Matrix##UCN0 defaultMatrix##UCN0(int lines, int columns, UCN0 def_value);                                                              \
static inline Matrix##UCN0 makeUnitMatrix##UCN0(int n);                                                                                              \
                                                                                                                                                     \
static inline Matrix##UCN0 copyMatrix##UCN0(const Matrix##UCN0 * mat);                                                                               \
static inline Matrix##UCN0 moveMatrix##UCN0(Matrix##UCN0 * mat);                                                                                     \
static inline void destructMatrix##UCN0(Matrix##UCN0 * mat);                                                                                         \
static inline bool equalMatrix##UCN0(const Matrix##UCN0 * a, const Matrix##UCN0 * b);                                                                \
                                                                                                                                                     \
DECLARE_STRUCT_TYPE(Matrix##UCN0, Matrix##UCN0);                                                                                                     \
                                                                                                                                                     \
static inline MatrixRef##UCN0 getMatrix##UCN0##OnBuffer(const Matrix##UCN0 * origin, int lines_start, int lines_finish, int lines, int columns);     \
                                                                                                                                                     \
static inline void addToMatrix##UCN0(Matrix##UCN0 * a, const Matrix##UCN0 * b);                                                                      \
static inline void subToMatrix##UCN0(Matrix##UCN0 * a, const Matrix##UCN0 * b);                                                                      \
                                                                                                                                                     \
                                                                                                                                                     \
                                                                                                                                                     \
static inline Matrix##UCN0 addMatrix##UCN0(const Matrix##UCN0 * a, const Matrix##UCN0 * b);                                                          \
static inline Matrix##UCN0 subMatrix##UCN0(const Matrix##UCN0 * a, const Matrix##UCN0 * b);                                                          \
                                                                                                                                                     \
static inline Matrix##UCN0 multMatrix##UCN0(const Matrix##UCN0 * a, const Matrix##UCN0 * b);                                                         \
static inline Matrix##UCN0 divMatrix##UCN0(const Matrix##UCN0 * a, const Matrix##UCN0 * b);                                                          \
static inline void multToMatrix##UCN0(Matrix##UCN0 * a, const Matrix##UCN0 * b);                                                                     \
static inline void divToMatrix##UCN0(Matrix##UCN0 * a, const Matrix##UCN0 * b);                                                                      \
                                                                                                                                                     \
static inline Matrix##UCN0 unitMatrix##UCN0();                                                                                                       \
static inline Matrix##UCN0 nullMatrix##UCN0();                                                                                                       \
                                                                                                                                                     \
static inline Matrix##UCN0 minusMatrix##UCN0(const Matrix##UCN0 * a);                                                                                \
static inline Matrix##UCN0 sqrtMatrix##UCN0(const Matrix##UCN0 * a);                                                                                 \
                                                                                                                                                     \
DECLARE_TYPE_AS_ARITHMETIC(Matrix##UCN0, Matrix##UCN0);                                                                                              \
                                                                                                                                                     \
                                                                                                                                                     \
                                                                                                                                                     \
static inline Vector##UCN0 * atMatrix##UCN0(Matrix##UCN0 * mat, int i)                                                                               \
{                                                                                                                                                    \
    assert(!mat->is_on_buffer);                                                                                                                      \
    return atVectorVector##UCN0(&mat->matrix, i);                                                                                                    \
}                                                                                                                                                    \
static inline const Vector##UCN0 * catMatrix##UCN0(const Matrix##UCN0 * mat, int i)                                                                  \
{                                                                                                                                                    \
    assert(!mat->is_on_buffer);                                                                                                                      \
    return catVectorVector##UCN0(&mat->matrix, i);                                                                                                   \
}                                                                                                                                                    \
                                                                                                                                                     \
                                                                                                                                                     \
static inline UCN0 * atMatrix##UCN0##El(Matrix##UCN0 * mat, int i, int j)                                                                            \
{                                                                                                                                                    \
    if (mat->is_on_buffer)                                                                                                                           \
    {                                                                                                                                                \
        assert (i < mat->allocked_lines && j < mat->allocked_columns);                                                                               \
        return  atVector##UCN0(atVectorVector##UCN0(&mat->matrix, i + mat->start_line), j + mat->start_column);                                      \
    }                                                                                                                                                \
    assert(i < mat->lines && j < mat->columns);                                                                                                      \
    return &mat->matrix.vec[i].vec[j];                                                                                                               \
    return atVector##UCN0(atVectorVector##UCN0(&mat->matrix, i), j);                                                                                 \
}                                                                                                                                                    \
static inline const UCN0 * catMatrix##UCN0##El(const Matrix##UCN0 * mat, int i, int j)                                                               \
{                                                                                                                                                    \
    if (mat->is_on_buffer)                                                                                                                           \
    {                                                                                                                                                \
        if (i >= mat->allocked_lines || j >= mat->allocked_columns)                                                                                  \
            return mat->value_beyond_allocked_space_ptr;                                                                                             \
        return  catVector##UCN0(catVectorVector##UCN0(&mat->matrix, i + mat->start_line), j + mat->start_column);                                    \
    }                                                                                                                                                \
    assert(i < mat->lines && j < mat->columns);                                                                                                      \
    return &mat->matrix.vec[i].vec[j];                                                                                                               \
    return catVector##UCN0(catVectorVector##UCN0(&mat->matrix, i), j);                                                                               \
}                                                                                                                                                    \
static inline void setValueToMatrix##UCN0(Matrix##UCN0 * mat, int i, int j, UCN0 value)                                                              \
{                                                                                                                                                    \
    if (mat->is_on_buffer)                                                                                                                           \
    {                                                                                                                                                \
        if (i >= mat->allocked_lines || j >= mat->allocked_columns)                                                                                  \
            return;                                                                                                                                  \
    }                                                                                                                                                \
    TYPE0##_TYPE_REPLACE(UCN0, atMatrix##UCN0##El(mat, i, j) , TYPE0##_TYPE_MOVE(UCN0, &value));                                                     \
}                                                                                                                                                    \
                                                                                                                                                     \
static inline Matrix##UCN0 scanfMatrix##UCN0();                                                                                                      \
                                                                                                                                                     \
static inline Matrix##UCN0 inverseMatrix##UCN0(Matrix##UCN0 * matrix);                                                                               \
                                                                                                                                                     \
GENERATE_RIGHT_VALUE_UNARY_EXTENSIONS(Matrix##UCN0, Matrix##UCN0, inverse, Matrix##UCN0);                                                            \
static inline void printfMatrix##UCN0(const Matrix##UCN0 * mat);                                                                                     \
                                                                                                                                                     \
GENERATE_RIGHT_VALUE_UNARY_EXTENSIONS_TO_VOID_FUNC(Matrix##UCN0, Matrix##UCN0, printf)                                                               \
                                                                                                                                                     \
                                                                                                                                                     \
static inline Matrix##UCN0 naiveMultMatrix##UCN0(const Matrix##UCN0 * a, const Matrix##UCN0 * b);                                                    \
                                                                                                                                                     \
                                                                                                                                                     \
                                                                                                                                                     \
                                                                                                                                                     \
                                                                                                                                                     \
                                                                                                                                                                       \
                                                                                                                                                                       \
                                                                                                                                                                       \
                                                                                                                                                                       \
                                                                                                                                                                       \
                                                                                                                                                                       \
                                                                                                                                                                       \
static inline void assignFunctionsMatrix##UCN0(Matrix##UCN0 * mat)                                                                                                     \
{                                                                                                                                                                      \
    mat->at = &atMatrix##UCN0;                                                                                                                                         \
}                                                                                                                                                                      \
                                                                                                                                                                       \
static inline Matrix##UCN0 defaultMatrix##UCN0(int lines, int columns, UCN0 def_value)                                                                                 \
{                                                                                                                                                                      \
    Matrix##UCN0 result;                                                                                                                                               \
    result.lines = lines;                                                                                                                                              \
    result.columns = columns;                                                                                                                                          \
    /*here def_value is destroyed so dont have to call destructor*/                                                                                                    \
    result.matrix = defaultVectorVector##UCN0##RV(lines, defaultVector##UCN0##RV(columns, def_value));                                                                 \
    assignFunctionsMatrix##UCN0(&result);                                                                                                                              \
                                                                                                                                                                       \
    result.start_line = 0;                                                                                                                                             \
    result.start_column = 0;                                                                                                                                           \
    result.allocked_lines = result.lines;                                                                                                                              \
    result.allocked_columns = result.columns;                                                                                                                          \
    result.is_on_buffer = false;                                                                                                                                       \
    result.value_beyond_allocked_space = null##UCN0();                                                                                                                 \
    result.value_beyond_allocked_space_ptr = NULL;                                                                                                                     \
    return result;                                                                                                                                                     \
}                                                                                                                                                                      \
                                                                                                                                                                       \
static inline Matrix##UCN0 makeUnitMatrix##UCN0(int n)                                                                                                                 \
{                                                                                                                                                                      \
    Matrix##UCN0 res;                                                                                                                                                  \
    res.lines = n;                                                                                                                                                     \
    res.columns = n;                                                                                                                                                   \
    res.matrix = defaultVectorVector##UCN0##RV(n, defaultVector##UCN0##RV(n, null##UCN0()));                                                                           \
    for (int i = 0; i < n; ++i)                                                                                                                                        \
        *atMatrix##UCN0##El(&res, i, i) = unit##UCN0();                                                                                                                \
                                                                                                                                                                       \
    res.start_line = 0;                                                                                                                                                \
    res.start_column = 0;                                                                                                                                              \
    res.allocked_lines = res.lines;                                                                                                                                    \
    res.allocked_columns = res.columns;                                                                                                                                \
    res.is_on_buffer = false;                                                                                                                                          \
    assignFunctionsMatrix##UCN0(&res);                                                                                                                                 \
    return res;                                                                                                                                                        \
}                                                                                                                                                                      \
static inline Matrix##UCN0 copyMatrix##UCN0(const Matrix##UCN0 * mat)                                                                                                  \
{                                                                                                                                                                      \
    assert(!mat->is_on_buffer);                                                                                                                                        \
    Matrix##UCN0 res;                                                                                                                                                  \
                                                                                                                                                                       \
    res.lines = mat->lines;                                                                                                                                            \
    res.columns = mat->columns;                                                                                                                                        \
    res.matrix = copyVectorVector##UCN0(&mat->matrix);                                                                                                                 \
    res.is_on_buffer = false;                                                                                                                                          \
    res.allocked_lines = mat->allocked_lines;                                                                                                                          \
    res.start_column = mat->start_column;                                                                                                                              \
    res.start_line = mat->start_line;                                                                                                                                  \
    res.allocked_columns = mat->allocked_columns;                                                                                                                      \
    res.value_beyond_allocked_space = TYPE0##_TYPE_COPY(UCN0, &mat->value_beyond_allocked_space);                                                                      \
    res.value_beyond_allocked_space_ptr = mat->value_beyond_allocked_space_ptr;                                                                                        \
                                                                                                                                                                       \
    assignFunctionsMatrix##UCN0(&res);                                                                                                                                 \
    return res;                                                                                                                                                        \
}                                                                                                                                                                      \
static inline Matrix##UCN0 moveMatrix##UCN0(Matrix##UCN0 * mat)                                                                                                        \
{                                                                                                                                                                      \
    Matrix##UCN0 res;                                                                                                                                                  \
                                                                                                                                                                       \
    res.lines = mat->lines;                                                                                                                                            \
    res.columns = mat->columns;                                                                                                                                        \
    res.matrix = moveVectorVector##UCN0(&mat->matrix);                                                                                                                 \
    res.is_on_buffer = mat->is_on_buffer;                                                                                                                              \
    res.allocked_lines = mat->allocked_lines;                                                                                                                          \
    res.start_column = mat->start_column;                                                                                                                              \
    res.start_line = mat->start_line;                                                                                                                                  \
    res.allocked_columns = mat->allocked_columns;                                                                                                                      \
    res.value_beyond_allocked_space = TYPE0##_TYPE_MOVE(UCN0, &mat->value_beyond_allocked_space);                                                                      \
    res.value_beyond_allocked_space_ptr = mat->value_beyond_allocked_space_ptr;                                                                                        \
                                                                                                                                                                       \
    mat->lines = -1;                                                                                                                                                   \
    mat->columns = -1;                                                                                                                                                 \
    assignFunctionsMatrix##UCN0(&res);                                                                                                                                 \
    return res;                                                                                                                                                        \
}                                                                                                                                                                      \
                                                                                                                                                                       \
static inline bool equalMatrix##UCN0(const Matrix##UCN0 * a, const Matrix##UCN0 * b)                                                                                   \
{                                                                                                                                                                      \
    if (a->lines != b->lines || a->columns != b->columns)                                                                                                              \
        return false;                                                                                                                                                  \
    for (int i = 0; i < a->lines; ++i)                                                                                                                                 \
    {                                                                                                                                                                  \
        for (int j = 0; j < a->columns; ++j)                                                                                                                           \
        {                                                                                                                                                              \
            if (!equal##UCN0(catMatrix##UCN0##El(a, i, j), catMatrix##UCN0##El(b, i, j)))                                                                              \
                return false;                                                                                                                                          \
        }                                                                                                                                                              \
    }                                                                                                                                                                  \
    return true;                                                                                                                                                       \
}                                                                                                                                                                      \
static inline void destructMatrix##UCN0(Matrix##UCN0 * mat)                                                                                                            \
{                                                                                                                                                                      \
    if (mat->is_on_buffer)                                                                                                                                             \
    {                                                                                                                                                                  \
        return;                                                                                                                                                        \
    }                                                                                                                                                                  \
    destructVectorVector##UCN0(&mat->matrix);                                                                                                                          \
    TYPE0##_TYPE_DESTRUCT(UCN0, &mat->value_beyond_allocked_space);                                                                                                    \
}                                                                                                                                                                      \
                                                                                                                                                                       \
static inline MatrixRef##UCN0 getMatrix##UCN0##OnBuffer(const Matrix##UCN0 * origin, int lines_start, int columns_start, int lines, int columns)                       \
{                                                                                                                                                                      \
    MatrixRef##UCN0 res;                                                                                                                                               \
                                                                                                                                                                       \
    res.matrix = origin->matrix;                                                                                                                                       \
    res.lines = lines;                                                                                                                                                 \
    res.columns = columns;                                                                                                                                             \
    res.is_on_buffer = true;                                                                                                                                           \
    res.start_line = origin->start_line + lines_start;                                                                                                                 \
    res.start_column = origin->start_column + columns_start;                                                                                                           \
    res.allocked_lines = origin->allocked_lines - lines_start;                                                                                                         \
    res.allocked_columns = origin->allocked_columns - columns_start;                                                                                                   \
    if (origin->is_on_buffer)                                                                                                                                          \
        res.value_beyond_allocked_space_ptr = origin->value_beyond_allocked_space_ptr;                                                                                 \
    else                                                                                                                                                               \
        res.value_beyond_allocked_space_ptr = &origin->value_beyond_allocked_space;                                                                                    \
                                                                                                                                                                       \
    assignFunctionsMatrix##UCN0(&res);                                                                                                                                 \
    return res;                                                                                                                                                        \
}                                                                                                                                                                      \
                                                                                                                                                                       \
static inline void addToMatrix##UCN0(Matrix##UCN0 * a, const Matrix##UCN0 * b)                                                                                         \
{                                                                                                                                                                      \
                                                                                                                                                                       \
    assert(a->lines <= b->lines && a->columns <= b->columns);                                                                                                          \
    for (int i = 0; i < a->lines; ++i)                                                                                                                                 \
    {                                                                                                                                                                  \
        for (int j = 0; j < a->columns; ++j)                                                                                                                           \
            if (!a->is_on_buffer || (i < a->allocked_lines && j < a->allocked_columns))                                                                                \
                ARITHM_TYPE0##_TYPE_ADD_TO(UCN0, atMatrix##UCN0##El(a, i, j), catMatrix##UCN0##El(b, i, j));                                                           \
    }                                                                                                                                                                  \
                                                                                                                                                                       \
}                                                                                                                                                                      \
static inline Matrix##UCN0 addMatrix##UCN0(const Matrix##UCN0 * a, const Matrix##UCN0 * b)                                                                             \
{                                                                                                                                                                      \
                                                                                                                                                                       \
    assert(a->lines == b->lines && a->columns == b->columns);                                                                                                          \
    Matrix##UCN0 res = defaultMatrix##UCN0(a->lines, a->columns, null##UCN0());                                                                                        \
    addToMatrix##UCN0(&res, a);                                                                                                                                        \
    addToMatrix##UCN0(&res, b);                                                                                                                                        \
    return res;                                                                                                                                                        \
}                                                                                                                                                                      \
static inline void subToMatrix##UCN0(Matrix##UCN0 * a, const Matrix##UCN0 * b)                                                                                         \
{                                                                                                                                                                      \
                                                                                                                                                                       \
    assert(a->lines <= b->lines && a->columns <= b->columns);                                                                                                          \
    for (int i = 0; i < a->lines; ++i)                                                                                                                                 \
    {                                                                                                                                                                  \
        for (int j = 0; j < a->columns; ++j)                                                                                                                           \
        {                                                                                                                                                              \
            if (!a->is_on_buffer || (i < a->allocked_lines && j < a->allocked_columns))                                                                                \
                ARITHM_TYPE0##_TYPE_SUB_TO(UCN0, atMatrix##UCN0##El(a, i, j), catMatrix##UCN0##El(b, i, j));                                                           \
        }                                                                                                                                                              \
    }                                                                                                                                                                  \
}                                                                                                                                                                      \
static inline Matrix##UCN0 subMatrix##UCN0(const Matrix##UCN0 * a, const Matrix##UCN0 * b)                                                                             \
{                                                                                                                                                                      \
                                                                                                                                                                       \
    assert(a->lines == b->lines && a->columns == b->columns);                                                                                                          \
    Matrix##UCN0 res = defaultMatrix##UCN0(a->lines, a->columns, null##UCN0());                                                                                        \
    /*cannot just make copy because matrixes may be on buffer and now thats assert*/                                                                                   \
    addToMatrix##UCN0(&res, a);                                                                                                                                        \
    subToMatrix##UCN0(&res, b);                                                                                                                                        \
    return res;                                                                                                                                                        \
}                                                                                                                                                                      \
/*unsafe if call explicitly from outside*/                                                                                                                             \
static inline Matrix##UCN0 naiveMultMatrix##UCN0(const Matrix##UCN0 * a, const Matrix##UCN0 * b)                                                                       \
{                                                                                                                                                                      \
    Matrix##UCN0 res = defaultMatrix##UCN0(a->lines, b->columns, null##UCN0());                                                                                        \
    int a_lines = min(a->lines, a->allocked_lines);                                                                                                                    \
    int b_columns = min(b->columns, b->allocked_columns);                                                                                                              \
    int m_columns = min(min(a->columns, a->allocked_columns), min(b->lines, b->allocked_lines));                                                                       \
    for (int i = 0; i < a_lines; ++i)                                                                                                                                  \
    {                                                                                                                                                                  \
        for (int j = 0; j < b_columns; ++j)                                                                                                                            \
        {                                                                                                                                                              \
            for (int k = 0; k < m_columns; ++k)                                                                                                                        \
                /*ARITHM_TYPE0##_TYPE_ADD_TO_RV(UCN0, atMatrix##UCN0##El(&res, i, j),*/                                                                                \
                  /*                 ARITHM_TYPE0##_TYPE_MULT(UCN0, catMatrix##UCN0##El(a, i, k), catMatrix##UCN0##El(b, k, j)));*/                                    \
                ARITHM_TYPE0##_TYPE_ADD_TO_RV(UCN0, &res.matrix.vec[i].vec[j],                                                                                         \
                                   ARITHM_TYPE0##_TYPE_MULT(UCN0, &a->matrix.vec[i + a->start_line].vec[k + a->start_column],                                          \
                                                   &b->matrix.vec[k + b->start_line].vec[j + b->start_column]));                                                       \
        }                                                                                                                                                              \
    }                                                                                                                                                                  \
    return res;                                                                                                                                                        \
}                                                                                                                                                                      \
static inline Matrix##UCN0 multMatrix##UCN0##RV(Matrix##UCN0 a, Matrix##UCN0 b);                                                                                       \
                                                                                                                                                                       \
static inline Matrix##UCN0* addMatrix##UCN0##OnBuff(Matrix##UCN0* buff, const Matrix##UCN0 * a, const Matrix##UCN0 * b)                                                \
{                                                                                                                                                                      \
    for (int i = 0; i < buff->lines; ++i)                                                                                                                              \
    {                                                                                                                                                                  \
        for (int j = 0; j < buff->columns; ++j)                                                                                                                        \
            TYPE0##_TYPE_REPLACE(UCN0, atMatrix##UCN0##El(buff, i, j), ARITHM_TYPE0##_TYPE_ADD(UCN0, catMatrix##UCN0##El(a, i, j), catMatrix##UCN0##El(b, i, j)));     \
    }                                                                                                                                                                  \
    return buff;                                                                                                                                                       \
}                                                                                                                                                                      \
static inline Matrix##UCN0* subMatrix##UCN0##OnBuff(Matrix##UCN0* buff, const Matrix##UCN0 * a, const Matrix##UCN0 * b)                                                \
{                                                                                                                                                                      \
    for (int i = 0; i < buff->lines; ++i)                                                                                                                              \
    {                                                                                                                                                                  \
        for (int j = 0; j < buff->columns; ++j)                                                                                                                        \
        {                                                                                                                                                              \
            TYPE0##_TYPE_REPLACE(UCN0, atMatrix##UCN0##El(buff, i, j), ARITHM_TYPE0##_TYPE_SUB(UCN0, catMatrix##UCN0##El(a, i, j), catMatrix##UCN0##El(b, i, j)));     \
        }                                                                                                                                                              \
    }                                                                                                                                                                  \
    return buff;                                                                                                                                                       \
}                                                                                                                                                                      \
                                                                                                                                                                       \
static inline void chainAddingOrSubtractionToMatrix##UCN0(Matrix##UCN0 * mat, ...)                                                                                     \
{                                                                                                                                                                      \
    va_list arg;                                                                                                                                                       \
    va_start(arg, mat);                                                                                                                                                \
    Sign next_sign;                                                                                                                                                    \
    while ((next_sign = va_arg(arg, Sign)) != STOP)                                                                                                                    \
    {                                                                                                                                                                  \
        if (next_sign == PLUS)                                                                                                                                         \
            addToMatrix##UCN0(mat, va_arg(arg, const Matrix##UCN0 *));                                                                                                 \
        else                                                                                                                                                           \
            subToMatrix##UCN0(mat, va_arg(arg, const Matrix##UCN0 *));                                                                                                 \
    }                                                                                                                                                                  \
    va_end(arg);                                                                                                                                                       \
}                                                                                                                                                                      \
                                                                                                                                                                       \
static inline Matrix##UCN0 scanfMatrix##UCN0()                                                                                                                         \
{                                                                                                                                                                      \
    int len = scanfInt(), col = scanfInt();                                                                                                                            \
    Matrix##UCN0 res = defaultMatrix##UCN0(len, col, null##UCN0());                                                                                                    \
    for (int i = 0; i < len; ++i)                                                                                                                                      \
    {                                                                                                                                                                  \
        for (int j = 0; j < col; ++j)                                                                                                                                  \
        {                                                                                                                                                              \
            TYPE0##_TYPE_REPLACE(UCN0, atMatrix##UCN0##El(&res, i, j), scanf##UCN0());                                                                                 \
        }                                                                                                                                                              \
    }                                                                                                                                                                  \
    return res;                                                                                                                                                        \
}                                                                                                                                                                      \
                                                                                                                                                                       \
/*unsafe if call explicitly from outside*/                                                                                                                             \
static inline Matrix##UCN0 strassenAlgorithmForMatrix##UCN0(const Matrix##UCN0 * a, const Matrix##UCN0 * b)                                                            \
{                                                                                                                                                                      \
    int size_in_mult;                                                                                                                                                  \
    MatrixRef##UCN0 A, B;                                                                                                                                              \
                                                                                                                                                                       \
    size_in_mult = max(max(findNextPower(a->lines), findNextPower(a->columns)),                                                                                        \
                    max(findNextPower(b->lines), findNextPower(b->columns)));                                                                                          \
    A = getMatrix##UCN0##OnBuffer(a, 0, 0, size_in_mult, size_in_mult);                                                                                                \
    B = getMatrix##UCN0##OnBuffer(b, 0, 0, size_in_mult, size_in_mult);                                                                                                \
                                                                                                                                                                       \
    int half_size_in_mult = size_in_mult / 2;                                                                                                                          \
    /*all names are matching ones in wiki*/                                                                                                                            \
    MatrixRef##UCN0 A11 = getMatrix##UCN0##OnBuffer(&A, 0, 0, half_size_in_mult, half_size_in_mult);                                                                   \
    MatrixRef##UCN0 A12 = getMatrix##UCN0##OnBuffer(&A, 0, half_size_in_mult, half_size_in_mult, half_size_in_mult);                                                   \
    MatrixRef##UCN0 A21 = getMatrix##UCN0##OnBuffer(&A, half_size_in_mult, 0, half_size_in_mult, half_size_in_mult);                                                   \
    MatrixRef##UCN0 A22 = getMatrix##UCN0##OnBuffer(&A, half_size_in_mult, half_size_in_mult, half_size_in_mult, half_size_in_mult);                                   \
                                                                                                                                                                       \
    MatrixRef##UCN0 B11 = getMatrix##UCN0##OnBuffer(&B, 0, 0, half_size_in_mult, half_size_in_mult);                                                                   \
    MatrixRef##UCN0 B12 = getMatrix##UCN0##OnBuffer(&B, 0, half_size_in_mult, half_size_in_mult, half_size_in_mult);                                                   \
    MatrixRef##UCN0 B21 = getMatrix##UCN0##OnBuffer(&B, half_size_in_mult, 0, half_size_in_mult, half_size_in_mult);                                                   \
    MatrixRef##UCN0 B22 = getMatrix##UCN0##OnBuffer(&B, half_size_in_mult, half_size_in_mult, half_size_in_mult, half_size_in_mult);                                   \
                                                                                                                                                                       \
                                                                                                                                                                       \
    Matrix##UCN0 M1 = multMatrix##UCN0##RV(addMatrix##UCN0(&A11, &A22), addMatrix##UCN0(&B11, &B22));                                                                  \
    Matrix##UCN0 M2 = multMatrix##UCN0##RVLV(addMatrix##UCN0(&A21, &A22), &B11);                                                                                       \
    Matrix##UCN0 M3 = multMatrix##UCN0##LVRV(&A11, subMatrix##UCN0(&B12, &B22));                                                                                       \
    Matrix##UCN0 M4 = multMatrix##UCN0##LVRV(&A22, subMatrix##UCN0(&B21, &B11));                                                                                       \
    Matrix##UCN0 M5 = multMatrix##UCN0##RVLV(addMatrix##UCN0(&A11, &A12), &B22);                                                                                       \
    Matrix##UCN0 M6 = multMatrix##UCN0##RV(subMatrix##UCN0(&A21, &A11), addMatrix##UCN0(&B11, &B12));                                                                  \
    Matrix##UCN0 M7 = multMatrix##UCN0##RV(subMatrix##UCN0(&A12, &A22), addMatrix##UCN0(&B21, &B22));                                                                  \
                                                                                                                                                                       \
                                                                                                                                                                       \
    Matrix##UCN0 res = defaultMatrix##UCN0(a->lines, b->columns, null##UCN0());                                                                                        \
    MatrixRef##UCN0 C11 = getMatrix##UCN0##OnBuffer(&res, 0, 0, half_size_in_mult, half_size_in_mult);                                                                 \
    MatrixRef##UCN0 C12 = getMatrix##UCN0##OnBuffer(&res, 0, half_size_in_mult, half_size_in_mult, b->columns - half_size_in_mult);                                    \
    MatrixRef##UCN0 C21 = getMatrix##UCN0##OnBuffer(&res, half_size_in_mult, 0, a->lines - half_size_in_mult, half_size_in_mult);                                      \
    MatrixRef##UCN0 C22 = getMatrix##UCN0##OnBuffer(&res, half_size_in_mult, half_size_in_mult, a->lines - half_size_in_mult, b->columns - half_size_in_mult);         \
                                                                                                                                                                       \
                                                                                                                                                                       \
    /*Matrix##UCN0 C11 = addMatrix##UCN0##RV(addMatrix##UCN0(&M1, &M4), subMatrix##UCN0(&M7, &M5));*/                                                                  \
    /*Matrix##UCN0 C12 = addMatrix##UCN0(&M3, &M5);*/                                                                                                                  \
    /*Matrix##UCN0 C21 = addMatrix##UCN0(&M2, &M4);*/                                                                                                                  \
    /*Matrix##UCN0 C22 = addMatrix##UCN0##RV(subMatrix##UCN0(&M1, &M2), addMatrix##UCN0(&M3, &M6));*/                                                                  \
                                                                                                                                                                       \
    chainAddingOrSubtractionToMatrix##UCN0(&C11, PLUS, &M1, PLUS, &M4, MINUS, &M5, PLUS, &M7, STOP);                                                                   \
    chainAddingOrSubtractionToMatrix##UCN0(&C12, PLUS, &M3, PLUS, &M5, STOP);                                                                                          \
    chainAddingOrSubtractionToMatrix##UCN0(&C21, PLUS, &M2, PLUS, &M4, STOP);                                                                                          \
    chainAddingOrSubtractionToMatrix##UCN0(&C22, PLUS, &M1, MINUS, &M2, PLUS, &M3, PLUS, &M6, STOP);                                                                   \
                                                                                                                                                                       \
                                                                                                                                                                       \
                                                                                                                                                                       \
    destructMatrix##UCN0(&M1);                                                                                                                                         \
    destructMatrix##UCN0(&M2);                                                                                                                                         \
    destructMatrix##UCN0(&M3);                                                                                                                                         \
    destructMatrix##UCN0(&M4);                                                                                                                                         \
    destructMatrix##UCN0(&M5);                                                                                                                                         \
    destructMatrix##UCN0(&M6);                                                                                                                                         \
    destructMatrix##UCN0(&M7);                                                                                                                                         \
                                                                                                                                                                       \
    return res;                                                                                                                                                        \
}                                                                                                                                                                      \
                                                                                                                                                                       \
                                                                                                                                                                       \
static inline Matrix##UCN0 multMatrix##UCN0(const Matrix##UCN0 * a, const Matrix##UCN0 * b)                                                                            \
{                                                                                                                                                                      \
                                                                                                                                                                       \
    assert(a->columns == b->lines);                                                                                                                                    \
                                                                                                                                                                       \
    /*very rough estimate but seems to work*/                                                                                                                          \
    if (a->lines + a->columns + b->columns <= 1000)                                                                                                                    \
        return naiveMultMatrix##UCN0(a, b);                                                                                                                            \
    return strassenAlgorithmForMatrix##UCN0(a, b);                                                                                                                     \
}                                                                                                                                                                      \
static inline Matrix##UCN0 divMatrix##UCN0(const Matrix##UCN0 * a, const Matrix##UCN0 * b)                                                                             \
{                                                                                                                                                                      \
    assert(false);                                                                                                                                                     \
}                                                                                                                                                                      \
static inline void multToMatrix##UCN0(Matrix##UCN0 * a, const Matrix##UCN0 * b)                                                                                        \
{                                                                                                                                                                      \
    replaceMatrix##UCN0(a, multMatrix##UCN0(a, b));                                                                                                                    \
}                                                                                                                                                                      \
static inline void divToMatrix##UCN0(Matrix##UCN0 * a, const Matrix##UCN0 * b)                                                                                         \
{                                                                                                                                                                      \
    assert(false);                                                                                                                                                     \
}                                                                                                                                                                      \
static inline Matrix##UCN0 unitMatrix##UCN0()                                                                                                                          \
{                                                                                                                                                                      \
    /*it could work without type passed but without size its meaningless (tho it can be done if make states like in general types*/                                    \
    /*and somewhere it even could be useful buuut too specific*/                                                                                                       \
    assert(false);                                                                                                                                                     \
}                                                                                                                                                                      \
static inline Matrix##UCN0 nullMatrix##UCN0()                                                                                                                          \
{                                                                                                                                                                      \
    /*same as unitMatrix##UCN0()*/                                                                                                                                     \
    assert(false);                                                                                                                                                     \
}                                                                                                                                                                      \
static inline Matrix##UCN0 minusMatrix##UCN0(const Matrix##UCN0 * a)                                                                                                   \
{                                                                                                                                                                      \
    Matrix##UCN0 res = defaultMatrix##UCN0(a->lines, a->columns, null##UCN0());                                                                                        \
    for (int i = 0; i < a->lines; ++i)                                                                                                                                 \
    {                                                                                                                                                                  \
        for (int j = 0; j < a->columns; ++j)                                                                                                                           \
            *atMatrix##UCN0##El(&res, i, j) = minus##UCN0(catMatrix##UCN0##El(a, i, j));                                                                               \
    }                                                                                                                                                                  \
    return res;                                                                                                                                                        \
}                                                                                                                                                                      \
static inline Matrix##UCN0 sqrtMatrix##UCN0(const Matrix##UCN0 * a)                                                                                                    \
{                                                                                                                                                                      \
    assert(false);                                                                                                                                                     \
}                                                                                                                                                                      \
                                                                                                                                                                       \
                                                                                                                                                                       \
                                                                                                                                                                       \
                                                                                                                                                                       \
                                                                                                                                                                       \
                                                                                                                                                                       \
                                                                                                                                                                       \
                                                                                                                                                                       \
                                                                                                                                                                       \
                                                                                                                                                                       \
                                                                                                                                                                       \
/*------- for inverse*/                                                                                                                                                \
static inline int getIndexOfFirstNonZero##UCN0(Vector##UCN0 * vec)                                                                                                     \
{                                                                                                                                                                      \
    for (int i = 0; i < vec->getSize(vec); ++i)                                                                                                                        \
        if (!isNull##UCN0(vec->at(vec, i)) )                                                                                                                           \
            return i;                                                                                                                                                  \
    return vec->getSize(vec);                                                                                                                                          \
}                                                                                                                                                                      \
                                                                                                                                                                       \
static inline int pairSecComparator##UCN0(const void * ap, const void * bp)                                                                                            \
{                                                                                                                                                                      \
    PairIntInt * a = (PairIntInt*)ap;                                                                                                                                  \
    PairIntInt * b = (PairIntInt*)bp;                                                                                                                                  \
    if (a->second < b->second)                                                                                                                                         \
        return -1;                                                                                                                                                     \
    if (a->second > b->second)                                                                                                                                         \
        return 1;                                                                                                                                                      \
    /*first does not matter*/                                                                                                                                          \
    return 0;                                                                                                                                                          \
}                                                                                                                                                                      \
                                                                                                                                                                       \
static inline void swapVectorsRat##UCN0(Vector##UCN0 * a, Vector##UCN0 * b)                                                                                            \
{                                                                                                                                                                      \
    Vector##UCN0 t;                                                                                                                                                    \
    memcpy(&t, a, sizeof(Vector##UCN0));                                                                                                                               \
    memcpy(a, b, sizeof(Vector##UCN0));                                                                                                                                \
    memcpy(b, &t, sizeof(Vector##UCN0));                                                                                                                               \
}                                                                                                                                                                      \
                                                                                                                                                                       \
static inline void sortRows##UCN0(int height, Matrix##UCN0 * matrix, VectorPairIntInt * indexes_of_first_non_zero, Matrix##UCN0 * result)                              \
{                                                                                                                                                                      \
    for (int i = 0; i < height; ++i)                                                                                                                                   \
    {                                                                                                                                                                  \
        *indexes_of_first_non_zero->at(indexes_of_first_non_zero, i) =                                                                                                 \
                defaultPairIntIntRV( i, getIndexOfFirstNonZero##UCN0(matrix->matrix.at(&matrix->matrix, i)) );                                                         \
    }                                                                                                                                                                  \
    sortVectorPairIntInt(indexes_of_first_non_zero, &pairSecComparator##UCN0);                                                                                         \
    for (int i = 0; i < height; ++i)                                                                                                                                   \
    {                                                                                                                                                                  \
        if (i < atVectorPairIntInt(indexes_of_first_non_zero, i)->first)                                                                                               \
        {                                                                                                                                                              \
            swapVectorsRat##UCN0(atMatrix##UCN0(matrix, i), atMatrix##UCN0(matrix, atVectorPairIntInt(indexes_of_first_non_zero, i)->first));                          \
            swapVectorsRat##UCN0(atMatrix##UCN0(result, i), atMatrix##UCN0(result, atVectorPairIntInt(indexes_of_first_non_zero, i)->first));                          \
        }                                                                                                                                                              \
    }                                                                                                                                                                  \
}                                                                                                                                                                      \
                                                                                                                                                                       \
static inline void divideOnLeadElement##UCN0(Matrix##UCN0 * matrix, Matrix##UCN0 * result, int x)                                                                      \
{                                                                                                                                                                      \
    UCN0 lead_el = *atMatrix##UCN0##El(matrix, x, x);                                                                                                                  \
    for (int i = x; i < matrix->lines; ++i)                                                                                                                            \
    {                                                                                                                                                                  \
        ARITHM_TYPE0##_TYPE_DIV_TO(UCN0, atMatrix##UCN0##El(matrix, x, i), &lead_el);                                                                                  \
    }                                                                                                                                                                  \
    for (int i = 0; i < matrix->lines; ++i)                                                                                                                            \
    {                                                                                                                                                                  \
        ARITHM_TYPE0##_TYPE_DIV_TO(UCN0, atMatrix##UCN0##El(result, x, i), &lead_el);                                                                                  \
    }                                                                                                                                                                  \
}                                                                                                                                                                      \
                                                                                                                                                                       \
/*by gauss algorithm.*/                                                                                                                                                \
/*algorithm will give divide by zero error somewhere (in divideByLeadElement) if determinant is null*/                                                                 \
static inline Matrix##UCN0 inverseMatrix##UCN0(Matrix##UCN0 * matrix)                                                                                                  \
{                                                                                                                                                                      \
/*only squares matrix are inverted*/                                                                                                                                   \
assert(matrix->lines == matrix->columns);                                                                                                                              \
    Matrix##UCN0 result = makeUnitMatrix##UCN0(matrix->lines);                                                                                                         \
    int height = matrix->lines;                                                                                                                                        \
    int width = matrix->columns;                                                                                                                                       \
                                                                                                                                                                       \
    VectorPairIntInt indexes_of_first_non_zero = defaultVectorPairIntIntRV(height, defaultPairIntIntRV(0,0));                                                          \
                                                                                                                                                                       \
                                                                                                                                                                       \
    sortRows##UCN0(height, matrix, &indexes_of_first_non_zero, &result);                                                                                               \
/*to triangular form*/                                                                                                                                                 \
    for (int n = 0; n < height; ++n) {                                                                                                                                 \
        divideOnLeadElement##UCN0(matrix, &result, n);                                                                                                                 \
        for (int i = n + 1; i < height; ++i)                                                                                                                           \
        {                                                                                                                                                              \
            UCN0 multiplier = minus##UCN0##RV(ARITHM_TYPE0##_TYPE_DIV(UCN0, atMatrix##UCN0##El(matrix, i, n), atMatrix##UCN0##El(matrix, n, n)));                      \
            /*HOW ITS UGLY IN C*/                                                                                                                                      \
            replaceVector##UCN0(atMatrix##UCN0(matrix, i) , addVector##UCN0##LVRV(matrix->at(matrix, i),                                                               \
                                                         Vector##UCN0##MultedOnNum(atMatrix##UCN0(matrix, n), &multiplier)));                                          \
            replaceVector##UCN0(atMatrix##UCN0(&result, i) , addVector##UCN0##LVRV(atMatrix##UCN0(&result, i),                                                         \
                                                          Vector##UCN0##MultedOnNum(atMatrix##UCN0(&result, n) , &multiplier)));                                       \
                                                                                                                                                                       \
                                                                                                                                                                       \
        }                                                                                                                                                              \
                                                                                                                                                                       \
    }                                                                                                                                                                  \
                                                                                                                                                                       \
/*back to normal*/                                                                                                                                                     \
    for (int n = height - 1; n >= 0; --n)                                                                                                                              \
    {                                                                                                                                                                  \
        for (int i = n - 1; i >= 0; --i)                                                                                                                               \
        {                                                                                                                                                              \
            UCN0 multiplier = minus##UCN0##RV(ARITHM_TYPE0##_TYPE_DIV(UCN0, atMatrix##UCN0##El(matrix, i, n), atMatrix##UCN0##El(matrix, n, n)));                      \
            replaceVector##UCN0(atMatrix##UCN0(matrix, i) , addVector##UCN0##LVRV(matrix->at(matrix, i),                                                               \
                                                         Vector##UCN0##MultedOnNum(matrix->at(matrix, n), &multiplier)));                                              \
            replaceVector##UCN0(atMatrix##UCN0(&result, i) , addVector##UCN0##LVRV(atMatrix##UCN0(&result, i),                                                         \
                                                          Vector##UCN0##MultedOnNum(atMatrix##UCN0(&result, n) , &multiplier)));                                       \
        }                                                                                                                                                              \
    }                                                                                                                                                                  \
    destructVectorPairIntInt(&indexes_of_first_non_zero);                                                                                                              \
    return result;                                                                                                                                                     \
}                                                                                                                                                                      \
                                                                                                                                                                       \
static inline void printfMatrix##UCN0(const Matrix##UCN0 * mat)                                                                                                        \
{                                                                                                                                                                      \
    for (int i = 0; i < mat->lines; ++i)                                                                                                                               \
    {                                                                                                                                                                  \
        for (int j = 0; j < mat->columns; ++j)                                                                                                                         \
        {                                                                                                                                                              \
            printf##UCN0(catMatrix##UCN0##El(mat, i, j));                                                                                                              \
        }                                                                                                                                                              \
        printf("\n");                                                                                                                                                  \
    }                                                                                                                                                                  \
    printf("\n");                                                                                                                                                      \
}                                                                                                                                                                      \


#endif
