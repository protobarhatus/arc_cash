#ifndef FIBONACHY_NIM_TYPE_DECLARATION_H
#define FIBONACHY_NIM_TYPE_DECLARATION_H
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <complex.h>
#include <memory.h>
#include "string.h"
#include "functions_extensions.h"

/*to be used in generalized structures, type must be declared
 * declaration is creating a function named TYPE_<TypeNameInUpperCamelCase> that returns pointer to container variable
 * pointers to basic functions and element size
 * Note that since function is static inline, for every instance of it in different .c files, container
 * variable is different (if compiler will not optimize it) and thus cannot be changed at all
 * thats needed because structures that work with generalized type need implementations of all this functions
 * SIMPLE_TYPE means that it has no internal logic while copying and no work while destruction (may be internal type, or struct)
 * POINTER_TYPE is special declaration that serves for generalized structures. It must be pointer. Structures, made on that type, will
 * behave like structures on std::unique_ptr. Copy function of this type will have assert(false);
 * Structures on that type cannot be created on size > 1, and cannot be copied. (As i cannot mark it =delete in C, they will just
 * call assert(false) somewhere). In destructor, they will destruct object behind that pointer and free the pointer;
 * I need to create it and not use just unique_ptr, because in C to get data behind it i will need to call extra function and
 * this is just inconvenient and ugly
 * STRUCT_TYPE is any structure with complex behaviour
 *
 * while creating structure, user is obligated to call DECLARE_TYPE_<type_class>(<type>, <typename>) with appropriate type class (simple, or struct)
 * only after it he will be able to create vectors and other structures on this class
 * is it is STRUCT_TYPE, user also obligated to define TN copy##UCN(const TN * );
 * void destruct##UCN(TN * ); TN move##UCN(TN * ) funcs
 * TN is type and UCN is type name is UpperCamelCase
 * when declaring vectors or other generalized class, it will declare itself as a struct type automatically
 *
 * Also, for different purposes there may be different classes of types. This is main one, but
 * also there can be arithmetic containers and etc. All of them must be declared separatly if needed
 *
 *
 * Types may get Ref analogs. These are like links, they are build on existing data and doesn't own anything in them.
 * So, user must make sure he doesn't mess up with data that contains in them by pointers. (Its all user's responsibility) Tho its not forbidden
 * to change fields of ref object, but it's better for them to be constants at all. Also, their destruction is unneded
 * Aside from Ref, exists _Ref naming. Difference is: in structure VectorStruct, VectorStructRef is
 * a vector of StructRef. However, VectorRefStruct and VectorStruct_Ref are refs of Vector (these two
 * are the same). In generalized classes, need to write refs as GeneralType_Ref, because
 * they will be translated into UCN##_Ref. Thus, if template argument is container, it will be treated correctly*/


//!эту хрень я уже не использую по большей части. Она полезна только если захотеть писать под GeneralType,
//!но такие классы лишь скелет для кодогенерации, а использовать их вообще не надо, так что все бред
//!кроме Ref-ов, они актуальны
//!однако DECLARE_STRUCT или DECLARE_TYPE все еще обладают парой полезных эффектов, но юзать их необязательно



typedef void * (*CopyFunction)(void * dest, const void * src, size_t n);
typedef void * (*MoveFunction)(void * dest, void * src, size_t n);
typedef void (*DestructFunction)(void * el);
typedef bool (*ComparisonFunction)(const void * a, const void * b, int num);

//is created as global variable on every type in its macro def
struct TypePresenterContainer_struct
{
    CopyFunction cpy_func;
    DestructFunction destruct_function;
    MoveFunction move_function;
    ComparisonFunction equal_function;
    int element_size;
    const char * type_name;
};

typedef struct TypePresenterContainer_struct TypePresenterContainer;

static inline void dummyDestructor(void * p) {}
void* nonConstMemcpyDecl(void * dest, void * src, size_t n);

bool standartMemcmpWrapping(const void * a, const void * b, int num);

//If type TN is SIMPLE then it means that copy is completed by memcpy and destruction is unneded cause it don't need
//to free some data inside
//but functions copy##UCN and destruct##UCN still have to exist
//otherwise,
//User must provide functions copy##UCN and destruct##UCN except if TN is Vector itself
//then if initialized in right order, that functions will be auto generated
//if its pointer on simple type then destroying is just calling free().
//pointers on non simple types must provide appropriate cpyFunc and destrFunc
//cpyFunc means FULL copy, (with copy of data behind inside pointers)
#define SIMPLE_TYPE &memcpy, &dummyDestructor, &nonConstMemcpyDecl, &standartMemcmpWrapping
#define STRUCT_TYPE(UCN) &cpyFunc##UCN, &destrFunc##UCN, &moveFunc##UCN, &equalFunc##UCN


#define DECLARE_TYPE(TN, UCN, FUNCS) \
    static inline const TypePresenterContainer * TYPE_##UCN() { \
        static const TypePresenterContainer type  = {FUNCS, sizeof(TN), #UCN};                                     \
        return &type;}

//call every time with DECLARE_TYPE on SIMPLE_TYPE
#define GEN_DUMMY_FUNCS_FOR_SIMPLE_TYPE(TN, UCN) \
static inline TN copy##UCN(TN const * b) {return *b;} \
static inline void destruct##UCN(TN * a) {} \
static inline TN move##UCN(TN * b) {return *b;}  \


//not for all simple types its correct
#define GEN_SIMPLE_EQUAL_FUNCTION(TN, UCN) \
static inline bool equal##UCN(TN const * a, TN const * b) {return memcmp(a, b, sizeof(TN)) == 0;}

//call every time with DECLARE_TYPE on POINTER_TYPE, but since behaviour of POINTER type is more
//like struct type (i.e. complex copy and destruct logic), after it have to call GEN_DUMMY_FUNCS_FOR_STRUCT_TYPE
#define GEN_DUMMY_FUNCS_FOR_POINTER_TYPE(TN, UCN, STRUCT_BEHIND_PTR) \
    static inline TN copy##UCN(TN const  * src) {assert(false); return *src;};\
    static inline TN move##UCN(TN * src) { TN buff = *src; *src = NULL; return buff;}      \
    static inline void destruct##UCN(TN * obj) {  destruct##STRUCT_BEHIND_PTR(*obj); free(*obj); *obj = NULL; } \
    /*since point of unique ptr is there is no pointers with same value, natural comparison is by value*/                                                                 \
    static inline bool equal##UCN(TN const * a, TN const * b) { return equal##STRUCT_BEHIND_PTR(*a, *b);}\
//call every time with DECLARE_TYPE on STRUCT_TYPE (here they are not actually dummy but naming should be consistent
//the purpose of previous to is to have functions like copy##UCN for types that dont need it but
//they are have to be declared and thus defined
//but this is creation of wrapping functions that get generalized arguments but work according to type
//and copy##UCN, destruct##UCN, move##UCN MUST be defined from outside
#define GEN_DUMMY_FUNCS_FOR_STRUCT_TYPE(TN, UCN) \
   TN copy##UCN(TN const  * src);                                                           \
   /*return value absolutely doesn't matter but it need to be the same type with memcpy*/                                                                                                 \
   static inline void* cpyFunc##UCN(void * dest, const void * src, size_t n)                                \
   {                                                                                                    \
        *((TN *)dest) = copy##UCN((TN const *)src);                                                              \
        return NULL;                                                                                        \
   }                                                                                    \
                                                                                        \
     void destruct##UCN(TN * el);                                                                                   \
    static inline void destrFunc##UCN(void * el)                                        \
    {                                                                                   \
         destruct##UCN((TN*)el);                                                                               \
    }                                                                                                                                                                  \
     TN move##UCN(TN * el);                                                                                                                                          \
      static inline void* moveFunc##UCN(void * dest, void * src, size_t n)                                                                                              \
      {                                                                                                                                                                \
           *((TN *)dest) = move##UCN((TN*)src);                                                                                                                        \
           return NULL;                                                             \
      }                                          \
      bool equal##UCN(TN const * a, TN const * b);\
    static inline bool equalFunc##UCN(const void * a, const void * b, int num)\
    {\
        return equal##UCN((TN const *)a, (TN const *)b);\
    }

      /*thats needed for auto generated structures like vectors, because they have to make all their functions inline*/
#define GEN_DUMMY_FUNCS_FOR_STRUCT_TYPE_WITH_INLINE_DECLARATION(TN, UCN) \
         static inline TN copy##UCN(TN const * src);                                                           \
   /*return value absolutely doesn't matter but it need to be the same type with memcpy*/                                                                                                 \
   static inline void* cpyFunc##UCN(void * dest, const void * src, size_t n)                                \
   {                                                                                                    \
        *((TN *)dest) = copy##UCN((TN const *)src);                                                              \
        return NULL;                                                                                        \
   }                                                                                    \
                                                                                        \
     static inline void destruct##UCN(TN * el);                                                                                   \
    static inline void destrFunc##UCN(void * el)                                        \
    {                                                                                   \
         destruct##UCN((TN*)el);                                                                               \
    }                                                                                                                                                                  \
     static inline TN move##UCN(TN * el);                                                                                                                                          \
      static inline void* moveFunc##UCN(void * dest, void * src, size_t n)                                                                                              \
      {                                                                                                                                                                \
           *((TN *)dest) = move##UCN((TN*)src);                                                                                                                        \
           return NULL;                                                             \
      }\
    static inline bool equal##UCN(TN const * a, TN const * b);\
    static inline bool equalFunc##UCN(const void * a, const void * b, int num)\
    {\
        return equal##UCN((const TN*)a, (const TN*)b);\
    }


#define GEN_OTHER_USEFUL_FUNCS_TO_STRUCT_TYPE(TN, UCN) \
    static inline void replace##UCN (TN * a, TN b) \
    {                                                  \
        destruct##UCN(a);                          \
        *a = b;\
    }                                                  \
/*GENERATE_RIGHT_VALUE_CUMULATIVE_UNARY_EXTENSIONS_SE_NAMING(TN, UCN, replace)*/                                                       \
GENERATE_RIGHT_VALUE_BINARY_EXTENSIONS(TN, UCN, equal, bool)


#define GEN_OTHER_USEFUL_FUNCS_TO_SIMPLE_TYPE(TN, UCN) \
    static inline void replace##UCN(TN * a, TN b)      \
    {                                                  \
        *a = b;\
    }                                                   \
                                                       \
                                                       \



#define DECLARE_SIMPLE_TYPE(TN, UCN) \
bool equal##UCN(TN const * a, TN const * b);                                     \
DECLARE_TYPE(TN, UCN, SIMPLE_TYPE)   \
GEN_DUMMY_FUNCS_FOR_SIMPLE_TYPE(TN, UCN) \
GEN_OTHER_USEFUL_FUNCS_TO_SIMPLE_TYPE(TN, UCN)                                   \
GENERATE_RIGHT_VALUE_BINARY_EXTENSIONS(TN, UCN, equal, bool)                                     \
typedef TN UCN;

#define DECLARE_SIMPLE_TYPE_WITH_SIMPLE_EQUAL(TN, UCN) \
static inline bool equal##UCN(TN const * a, TN const * b);\
DECLARE_SIMPLE_TYPE(TN, UCN)\
GEN_SIMPLE_EQUAL_FUNCTION(TN, UCN)                     \
typedef TN UCN##Ref;\
typedef TN UCN##_Ref;

#define DECLARE_STRUCT_TYPE(TN, UCN) \
GEN_DUMMY_FUNCS_FOR_STRUCT_TYPE(TN, UCN)                                     \
DECLARE_TYPE(TN, UCN, STRUCT_TYPE(UCN))\
GEN_OTHER_USEFUL_FUNCS_TO_STRUCT_TYPE(TN, UCN)
//HERE UCN is name of structure OF which will be POINTER. Name of type will be UCN+Ptr
#define CREATE_UNIQUE_POINTER(TN, UCN) \
GEN_DUMMY_FUNCS_FOR_POINTER_TYPE(TN, UCN##Ptr, UCN) \
GEN_DUMMY_FUNCS_FOR_STRUCT_TYPE(TN, UCN##Ptr)                                       \
DECLARE_TYPE(TN, UCN##Ptr, STRUCT_TYPE(UCN##Ptr))   \
typedef TN UCN##Ptr;

//this is for vector and etc
#define DECLARE_STRUCT_INLINE_TYPE(TN, UCN) \
GEN_DUMMY_FUNCS_FOR_STRUCT_TYPE_WITH_INLINE_DECLARATION(TN, UCN)\
DECLARE_TYPE(TN, UCN, STRUCT_TYPE(UCN))     \
GEN_OTHER_USEFUL_FUNCS_TO_STRUCT_TYPE(TN, UCN)

DECLARE_SIMPLE_TYPE_WITH_SIMPLE_EQUAL(int, Int)
DECLARE_SIMPLE_TYPE_WITH_SIMPLE_EQUAL(char, Char)
DECLARE_SIMPLE_TYPE_WITH_SIMPLE_EQUAL(bool, Bool)
DECLARE_SIMPLE_TYPE_WITH_SIMPLE_EQUAL(double, Double)
DECLARE_SIMPLE_TYPE_WITH_SIMPLE_EQUAL(long long int, LongLongInt)
DECLARE_SIMPLE_TYPE_WITH_SIMPLE_EQUAL(float, Float)
DECLARE_SIMPLE_TYPE(double complex, Complex)
typedef double complex Complex;

CREATE_UNIQUE_POINTER(int*, Int)


static inline bool areSameTypes(const TypePresenterContainer * a, const TypePresenterContainer * b)
{
    return strcmp(a->type_name, b->type_name) == 0;
}



#define SIMPLE_TYPE_COPY(UCN, ARG) (*(ARG))
#define SIMPLE_TYPE_MOVE(UCN, ARG) (*(ARG))
#define SIMPLE_TYPE_DESTRUCT(UCN, ARG) ;
#define SIMPLE_TYPE_COPY_RV(UCN, ARG) (ARG)
#define SIMPLE_TYPE_MOVE_RV(UCN, ARG) (ARG)
#define SIMPLE_TYPE_REPLACE(UCN, LEFT, RIGHT) *LEFT = RIGHT

#define STRUCT_TYPE_COPY(UCN, ARG) copy##UCN(ARG)
#define STRUCT_TYPE_MOVE(UCN, ARG) move##UCN(ARG)
#define STRUCT_TYPE_DESTRUCT(UCN, ARG) destruct##UCN(ARG)
#define STRUCT_TYPE_COPY_RV(UCN, ARG) copy##UCN##RV(ARG)
#define STRUCT_TYPE_MOVE_RV(UCN, ARG) move##UCN##RV(ARG)
#define STRUCT_TYPE_REPLACE(UCN, LEFT, RIGHT) replace##UCN(LEFT, RIGHT)





#endif //FIBONACHY_NIM_TYPE_DECLARATION_H
