#ifndef FIBONACHY_NIM_GENERAL_TYPE_H
#define FIBONACHY_NIM_GENERAL_TYPE_H
//in complex structures on unknown type like matrix it is very inconvenient to write it's logic on some void pointers.
//so, it may use this type that give all functions connected to all types of containers
//GeneralType on GeneralType is uknown behaviour and not recommended
#include "type_declaration.h"
#include "functions_extensions.h"
#include "arithmetic_type_declaration.h"
#include "complete_type_container.h"
//#include "../vector/vector.h"
//#include "../linear_algebra_elements/vector_algebraic_addendum.h"

//null and unit functions meant to be without any arguments in arithmetic_type_declaration. But, since there is no way
//to define a singular null or one value for different types, GeneralType has no way to make its value in these functions
//so, nullGeneralType() and unitGeneralType() returns object in uncertainty state. It will resolve it state into normal value
//as soon as it will able to: in any function where its argument and other argument has defined type
//(even with const breaking)
//If all arguments of function still don't know their types, then it will define special state of result object if can,
//or throw an assert otherwise.
//for example, sqrt from special states of null or ones is still null or ones,
//adding null to any x is some x
//but adding one to any x (aside null) will result in assert
//For user the best approach is to define its type as soon as possible with explicit defineStateForGeneralType() function
//or use nullGeneralTypeOfCertainType, unitGeneralTypeOfCertainType

//For this reason const marker DOES NOT guarantees that object will be unchangeable and even that there will be no callocs
enum GeneralTypeSpecialState_enum
{
    GENERAL_TYPE_SPECIAL_STATE_NONE,
    GENERAL_TYPE_SPECIAL_STATE_NULL,
    GENERAL_TYPE_SPECIAL_STATE_UNIT
};
typedef enum GeneralTypeSpecialState_enum GeneralTypeSpecialState;
struct GeneralType_struct
{
    CompleteTypePresenter type;
    void * data;
    GeneralTypeSpecialState state;

};
typedef struct GeneralType_struct GeneralType;

typedef GeneralType Type1;
typedef GeneralType Type2;
typedef GeneralType Type3;
typedef GeneralType Type4;
typedef GeneralType Type5;

typedef GeneralType GeneralTypeRef;
typedef Type1 Type1Ref;
typedef Type2 Type2Ref;
typedef Type3 Type3Ref;
typedef Type4 Type4Ref;
typedef Type5 Type5Ref;

typedef GeneralType GeneralType_Ref;
typedef Type1 Type1_Ref;
typedef Type2 Type2_Ref;
typedef Type3 Type3_Ref;
typedef Type4 Type4_Ref;
typedef Type5 Type5_Ref;

#define TEMPLATE_TYPE_GeneralType STRUCT
#define TEMPLATE_TYPE_Type1 STRUCT
#define TEMPLATE_TYPE_Type2 STRUCT
#define TEMPLATE_TYPE_Type3 STRUCT
#define TEMPLATE_TYPE_Type4 STRUCT
#define TEMPLATE_TYPE_Type5 STRUCT

#define STRUCT_TEMPLATE STRUCT
#define SIMPLE_TEMPLATE SIMPLE


GeneralType defaultGeneralType(void * data, CompleteTypePresenter type);
#define defaultType1 defaultGeneralType
#define defaultType2 defaultGeneralType
#define defaultType3 defaultGeneralType
#define defaultType4 defaultGeneralType
#define defaultType5 defaultGeneralType




GeneralType copyGeneralType(const GeneralType * cop);
#define copyType1 copyGeneralType
#define copyType2 copyGeneralType
#define copyType3 copyGeneralType
#define copyType4 copyGeneralType
#define copyType5 copyGeneralType



GeneralType moveGeneralType(GeneralType * mov);
#define moveType1 moveGeneralType
#define moveType2 moveGeneralType
#define moveType3 moveGeneralType
#define moveType4 moveGeneralType
#define moveType5 moveGeneralType





void destructGeneralType(GeneralType * obj);
#define destructType1 destructGeneralType
#define destructType2 destructGeneralType
#define destructType3 destructGeneralType
#define destructType4 destructGeneralType
#define destructType5 destructGeneralType



bool equalGeneralType(const GeneralType * a, const GeneralType * b);
#define equalType1 equalGeneralType
#define equalType2 equalGeneralType
#define equalType3 equalGeneralType
#define equalType4 equalGeneralType
#define equalType5 equalGeneralType




DECLARE_STRUCT_TYPE(GeneralType, GeneralType)

DECLARE_STRUCT_TYPE(Type1, Type1);
DECLARE_STRUCT_TYPE(Type2, Type2);
DECLARE_STRUCT_TYPE(Type3, Type3);
DECLARE_STRUCT_TYPE(Type4, Type4);
DECLARE_STRUCT_TYPE(Type5, Type5);


GeneralType addGeneralType(const GeneralType * a, const GeneralType * b);
#define addType1 addGeneralType
#define addType2 addGeneralType
#define addType3 addGeneralType
#define addType4 addGeneralType
#define addType5 addGeneralType


GeneralType subGeneralType(const GeneralType * a, const GeneralType * b);
#define subType1 subGeneralType
#define subType2 subGeneralType
#define subType3 subGeneralType
#define subType4 subGeneralType
#define subType5 subGeneralType



GeneralType multGeneralType(const GeneralType * a, const GeneralType * b);
#define multType1 multGeneralType
#define multType2 multGeneralType
#define multType3 multGeneralType
#define multType4 multGeneralType
#define multType5 multGeneralType



GeneralType divGeneralType(const GeneralType * a, const GeneralType * b);
#define divType1 divGeneralType
#define divType2 divGeneralType
#define divType3 divGeneralType
#define divType4 divGeneralType
#define divType5 divGeneralType



void addToGeneralType(GeneralType * a, const GeneralType * b);
#define addToType1 addToGeneralType
#define addToType2 addToGeneralType
#define addToType3 addToGeneralType
#define addToType4 addToGeneralType
#define addToType5 addToGeneralType



void subToGeneralType(GeneralType * a, const GeneralType * b);
#define subToType1 subToGeneralType
#define subToType2 subToGeneralType
#define subToType3 subToGeneralType
#define subToType4 subToGeneralType
#define subToType5 subToGeneralType


void multToGeneralType(GeneralType * a, const GeneralType * b);
#define multToType1 multToGeneralType
#define multToType2 multToGeneralType
#define multToType3 multToGeneralType
#define multToType4 multToGeneralType
#define multToType5 multToGeneralType



void divToGeneralType(GeneralType * a, const GeneralType * b);
#define divToType1 divToGeneralType
#define divToType2 divToGeneralType
#define divToType3 divToGeneralType
#define divToType4 divToGeneralType
#define divToType5 divToGeneralType



GeneralType sqrtGeneralType(const GeneralType * a);
#define sqrtType1 sqrtGeneralType
#define sqrtType2 sqrtGeneralType
#define sqrtType3 sqrtGeneralType
#define sqrtType4 sqrtGeneralType
#define sqrtType5 sqrtGeneralType



GeneralType minusGeneralType(const GeneralType * a);
#define minusType1 minusGeneralType
#define minusType2 minusGeneralType
#define minusType3 minusGeneralType
#define minusType4 minusGeneralType
#define minusType5 minusGeneralType


//better not use this functions if possible but they are needed for arithmetic type declaration and some generated code like vector addendum may call it
GeneralType nullGeneralType();
#define nullType1 nullGeneralType
#define nullType2 nullGeneralType
#define nullType3 nullGeneralType
#define nullType4 nullGeneralType
#define nullType5 nullGeneralType



GeneralType unitGeneralType();
#define unitType1 unitGeneralType
#define unitType2 unitGeneralType
#define unitType3 unitGeneralType
#define unitType4 unitGeneralType
#define unitType5 unitGeneralType



bool isNullGeneralType(const GeneralType * a);
#define isNullType1 isNullGeneralType
#define isNullType2 isNullGeneralType
#define isNullType3 isNullGeneralType
#define isNullType4 isNullGeneralType
#define isNullType5 isNullGeneralType


DECLARE_TYPE_AS_ARITHMETIC(GeneralType, GeneralType)
DECLARE_TYPE_AS_ARITHMETIC(Type1, Type1)
DECLARE_TYPE_AS_ARITHMETIC(Type2, Type2)
DECLARE_TYPE_AS_ARITHMETIC(Type3, Type3)
DECLARE_TYPE_AS_ARITHMETIC(Type4, Type4)
DECLARE_TYPE_AS_ARITHMETIC(Type5, Type5)



void printfGeneralType(const GeneralType * type);
#define printfType1 printfGeneralType
#define printfType2 printfGeneralType
#define printfType3 printfGeneralType
#define printfType4 printfGeneralType
#define printfType5 printfGeneralType


GeneralType scanfGeneralType();
#define scanfType1 scanfGeneralType
#define scanfType2 scanfGeneralType
#define scanfType3 scanfGeneralType
#define scanfType4 scanfGeneralType
#define scanfType5 scanfGeneralType


DECLARE_IO_TYPE(GeneralType, GeneralType);
DECLARE_IO_TYPE(Type1, Type1)
DECLARE_IO_TYPE(Type2, Type2)
DECLARE_IO_TYPE(Type3, Type3)
DECLARE_IO_TYPE(Type4, Type4)
DECLARE_IO_TYPE(Type5, Type5)

GeneralType nullGeneralTypeOfCertainType(CompleteTypePresenter type);
GeneralType unitGeneralTypeOfCertainType(CompleteTypePresenter type);

void defineStateForGeneralType(GeneralType * obj, CompleteTypePresenter type);
#define defineStateForType1 defineStateForGeneralType
#define defineStateForType2 defineStateForGeneralType
#define defineStateForType3 defineStateForGeneralType
#define defineStateForType4 defineStateForGeneralType
#define defineStateForType5 defineStateForGeneralType

//здесь бы тоже подобные дефайны но пока пофиг
#define MAKE_GENERAL_TYPE_TRANSLATION_FUNCTIONS(TN, UCN) \
static inline GeneralType getGeneralTypeOn##UCN##Copied(const TN * val) {\
    TN * new_val = malloc(TYPE_##UCN()->element_size);   \
    *new_val = copy##UCN(val);\
    return defaultGeneralType((void*)new_val, GET_COMPLETE_TYPE_PRESENTER(UCN));                                                        \
}                                                        \
static inline GeneralType getGeneralTypeOn##UCN##RV(TN val) {\
    TN * new_val = malloc(TYPE_##UCN()->element_size);   \
    *new_val = move##UCN(&val);                           \
    return defaultGeneralType((void*)new_val, GET_COMPLETE_TYPE_PRESENTER(UCN));\
}\
static inline GeneralType getGeneralTypeOn##UCN##Moved(TN * val) {\
    return defaultGeneralType((void*)val, GET_COMPLETE_TYPE_PRESENTER(UCN));\
}                                                        \
static inline TN * atGeneralType##UCN(GeneralType * obj)               \
{                                                        \
    return (TN*)obj->data;                                                        \
}                                                        \
static inline const TN * catGeneralType##UCN(const GeneralType * obj)        \
{\
    return (const TN*)obj->data;                                                         \
}


MAKE_GENERAL_TYPE_TRANSLATION_FUNCTIONS(int, Int)

MAKE_GENERAL_TYPE_TRANSLATION_FUNCTIONS(double, Double)








//to forbid
static inline GeneralType getGeneralTypeOnGeneralTypeCopied(const GeneralType * val) {
    assert(false);
}




#endif //FIBONACHY_NIM_GENERAL_TYPE_H
