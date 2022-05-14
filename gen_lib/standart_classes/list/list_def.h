#ifndef LIST_DEF_H
#define LIST_DEF_H

#include "list_node_def.h"
#include "list_general_type.h"
#define PREPARE_LIST(UCN0, TYPE0, ARITHM_TYPE0)\
                                                                                                             \
                                                                                                             \
                                                                                                             \
                                                                                                             \
/*эта строчка должна быть в list_def, но не в list_general_type*/                  \
MAKE_LISTNODE(UCN0, TYPE0##_TEMPLATE, TYPE0##_TEMPLATE)                                                  \
                                                                                                             \
struct List##UCN0##_struct {                                                                                 \
    List##UCN0##Node * first_element;                                                                        \
    List##UCN0##Node * last_element;                                                                         \
    int size;                                                                                                \
} ;                                                                                                          \
typedef List##UCN0 ListRef##UCN0;                                                                            \
typedef List##UCN0 List##UCN0##_Ref;                                                                         \
                                                                                                             \
static inline List##UCN0 defaultList##UCN0();                                                                \
static inline void pushBackToList##UCN0(List##UCN0 * list, const UCN0 * dat);                                \
static inline void pushFrontToList##UCN0(List##UCN0 * list, const UCN0 * dat);                               \
                                                                                                             \
GENERATE_RIGHT_VALUE_CUMULATIVE_UNARY_EXTENSION(List##UCN0, UCN0, pushBackToList##UCN0)                      \
GENERATE_RIGHT_VALUE_CUMULATIVE_UNARY_EXTENSION(List##UCN0, UCN0, pushFrontToList##UCN0)                     \
                                                                                                             \
static inline List##UCN0 copyList##UCN0(const List##UCN0 * list);                                            \
static inline List##UCN0 moveList##UCN0(List##UCN0 * list);                                                  \
static inline bool equalList##UCN0(const List##UCN0 * a, const List##UCN0 * b);                              \
                                                                                                             \
static inline void destructList##UCN0(List##UCN0 * list);                                                    \
                                                                                                             \
DECLARE_STRUCT_TYPE(List##UCN0, List##UCN0)                                                                  \
                                                                                                             \
typedef List##UCN0##Node* List##UCN0##Iterator;                                                              \
typedef List##UCN0##Node* List##UCN0##ReverseIterator;                                                       \
typedef List##UCN0##Node const * List##UCN0##ConstIterator;                                                  \
typedef List##UCN0##Node const * List##UCN0##ConstReverseIterator;                                           \
                                                                                                             \
static inline List##UCN0##Iterator eraseList##UCN0##Node(List##UCN0##Iterator it);                           \
                                                                                                             \
static inline List##UCN0##Iterator endList##UCN0(List##UCN0 * list);                                         \
static inline List##UCN0##ReverseIterator rendList##UCN0(List##UCN0 * list);                                 \
static inline List##UCN0##ConstIterator cendList##UCN0(const List##UCN0 * list);                             \
static inline List##UCN0##ConstReverseIterator crendList##UCN0(const List##UCN0 * list);                     \
                                                                                                             \
static inline List##UCN0##Iterator beginList##UCN0(List##UCN0 * list);                                       \
static inline List##UCN0##ReverseIterator rbeginList##UCN0(List##UCN0 * list);                               \
static inline List##UCN0##ConstIterator cbeginList##UCN0(const List##UCN0 * list);                           \
static inline List##UCN0##ConstReverseIterator crbeginList##UCN0(const List##UCN0 * list);                   \
                                                                                                             \
static inline List##UCN0##Iterator iterateList##UCN0(List##UCN0##Iterator it);                               \
static inline List##UCN0##ReverseIterator riterateList##UCN0(List##UCN0##ReverseIterator it);                \
static inline List##UCN0##ConstIterator citerateList##UCN0(List##UCN0##ConstIterator it);                    \
static inline List##UCN0##ConstReverseIterator criterateList##UCN0(List##UCN0##ConstReverseIterator it);     \
                                                                                                             \
static inline List##UCN0##Iterator findInList##UCN0(List##UCN0 * list, UCN0##_Ref findable);                 \
static inline List##UCN0##ConstIterator findInCList##UCN0(const List##UCN0 * list, UCN0##_Ref findable);     \
                                                                                                             \
static inline void moveNodeToEndList##UCN0(List##UCN0 * list, List##UCN0##Iterator node);                    \
                                                                                                             \
                                                                                                                             \
                                                                                                                             \
                                                                                                                             \
static inline List##UCN0 defaultList##UCN0()                                                                                 \
{                                                                                                                            \
    List##UCN0 res;                                                                                                          \
    res.first_element = NULL;                                                                                                \
    res.last_element = NULL;                                                                                                 \
    res.size = 0;                                                                                                            \
    return res;                                                                                                              \
}                                                                                                                            \
                                                                                                                             \
static inline void pushBackToList##UCN0(List##UCN0 * list, const UCN0 * dat)                                                 \
{                                                                                                                            \
    if (list->size == 0)                                                                                                     \
    {                                                                                                                        \
        list->first_element = calloc(1, sizeof(List##UCN0##Node));                                                           \
        *list->first_element = defaultList##UCN0##Node(dat, list);                                                           \
        list->last_element = list->first_element;                                                                            \
        ++list->size;                                                                                                        \
    }                                                                                                                        \
    else                                                                                                                     \
    {                                                                                                                        \
        List##UCN0##Node * new_node = calloc(1, sizeof(List##UCN0##Node));                                                   \
        assert(new_node);                                                                                                    \
        *new_node = defaultList##UCN0##Node(dat, list);                                                                      \
        connectList##UCN0##Nodes(list->last_element, new_node);                                                              \
        list->last_element = list->last_element->next;                                                                       \
        ++list->size;                                                                                                        \
    }                                                                                                                        \
}                                                                                                                            \
                                                                                                                             \
static inline void pushFrontToList##UCN0(List##UCN0 * list, const UCN0 * dat)                                                \
{                                                                                                                            \
    if (list->size == 0)                                                                                                     \
    {                                                                                                                        \
        pushBackToList##UCN0(list, dat);                                                                                     \
        return;                                                                                                              \
    }                                                                                                                        \
    else                                                                                                                     \
    {                                                                                                                        \
        List##UCN0##Node * new_node = calloc(1, sizeof(List##UCN0##Node));                                                   \
        assert(new_node);                                                                                                    \
        *new_node = defaultList##UCN0##Node(dat, list);                                                                      \
        connectList##UCN0##Nodes(new_node, list->first_element);                                                             \
        list->first_element = list->first_element->prev;                                                                     \
        ++list->size;                                                                                                        \
    }                                                                                                                        \
}                                                                                                                            \
                                                                                                                             \
static inline List##UCN0 copyList##UCN0(const List##UCN0 * list)                                                             \
{                                                                                                                            \
    List##UCN0 res = defaultList##UCN0();                                                                                    \
    for (List##UCN0##ConstIterator it = cbeginList##UCN0(list); it != cendList##UCN0(list); it = citerateList##UCN0(it))     \
    {                                                                                                                        \
        pushBackToList##UCN0(&res, it->data);                                                                                \
    }                                                                                                                        \
    return res;                                                                                                              \
}                                                                                                                            \
static inline List##UCN0 moveList##UCN0(List##UCN0 * list)                                                                   \
{                                                                                                                            \
    List##UCN0 res = *list;                                                                                                  \
    list->size = 0;                                                                                                          \
    list->first_element = NULL;                                                                                              \
    list->last_element = NULL;                                                                                               \
    return res;                                                                                                              \
}                                                                                                                            \
static inline bool equalList##UCN0(const List##UCN0 * a, const List##UCN0 * b)                                               \
{                                                                                                                            \
    if (a->size != b->size)                                                                                                  \
        return false;                                                                                                        \
    for (List##UCN0##ConstIterator it1 = cbeginList##UCN0(a),                                                                \
            it2 = cbeginList##UCN0(b); it1 != cendList##UCN0(a);                                                             \
                it1 = citerateList##UCN0(it1), it2 = citerateList##UCN0(it2))                                                \
    {                                                                                                                        \
        if (!equal##UCN0(it1->data, it2->data))                                                                              \
            return false;                                                                                                    \
    }                                                                                                                        \
    return true;                                                                                                             \
}                                                                                                                            \
                                                                                                                             \
static inline void destructList##UCN0(List##UCN0 * list)                                                                     \
{                                                                                                                            \
    List##UCN0##Iterator it = beginList##UCN0(list);                                                                         \
    if (it == NULL)                                                                                                          \
        return;                                                                                                              \
    while (it != endList##UCN0(list))                                                                                        \
    {                                                                                                                        \
        List##UCN0##Iterator next = it->next;                                                                                \
        takeOutList##UCN0##Node(it);                                                                                         \
        destructList##UCN0##Node(it);                                                                                        \
        free(it);                                                                                                            \
        it = next;                                                                                                           \
    }                                                                                                                        \
                                                                                                                             \
}                                                                                                                            \
                                                                                                                             \
static inline List##UCN0##Iterator eraseList##UCN0##Node(List##UCN0##Iterator it)                                            \
{                                                                                                                            \
    List##UCN0##Iterator ret = it->next;                                                                                     \
    it->list->size -= 1;                                                                                                     \
    if (it->prev == NULL)                                                                                                    \
        it->list->first_element = it->next;                                                                                  \
    if (it->next == NULL)                                                                                                    \
        it->list->last_element = it->prev;                                                                                   \
    takeOutList##UCN0##Node(it);                                                                                             \
    destructList##UCN0##Node(it);                                                                                            \
    free(it);                                                                                                                \
    return ret;                                                                                                              \
}                                                                                                                            \
                                                                                                                             \
                                                                                                                             \
static inline List##UCN0##Iterator endList##UCN0(List##UCN0 * list)                                                          \
{                                                                                                                            \
    return NULL;                                                                                                             \
}                                                                                                                            \
static inline List##UCN0##ReverseIterator rendList##UCN0(List##UCN0 * list)                                                  \
{                                                                                                                            \
    return NULL;                                                                                                             \
}                                                                                                                            \
static inline List##UCN0##ConstIterator cendList##UCN0(const List##UCN0 * list)                                              \
{                                                                                                                            \
    return NULL;                                                                                                             \
}                                                                                                                            \
static inline List##UCN0##ConstReverseIterator crendList##UCN0(const List##UCN0 * list)                                      \
{                                                                                                                            \
    return NULL;                                                                                                             \
}                                                                                                                            \
static inline List##UCN0##Iterator beginList##UCN0(List##UCN0 * list)                                                        \
{                                                                                                                            \
    return list->first_element;                                                                                              \
}                                                                                                                            \
static inline List##UCN0##ReverseIterator rbeginList##UCN0(List##UCN0 * list)                                                \
{                                                                                                                            \
    return list->last_element;                                                                                               \
}                                                                                                                            \
static inline List##UCN0##ConstIterator cbeginList##UCN0(const List##UCN0 * list)                                            \
{                                                                                                                            \
    return list->first_element;                                                                                              \
}                                                                                                                            \
static inline List##UCN0##ConstReverseIterator crbeginList##UCN0(const List##UCN0 * list)                                    \
{                                                                                                                            \
    return list->last_element;                                                                                               \
}                                                                                                                            \
static inline List##UCN0##Iterator iterateList##UCN0(List##UCN0##Iterator it)                                                \
{                                                                                                                            \
    assert(it != NULL);                                                                                                      \
    return it->next;                                                                                                         \
}                                                                                                                            \
static inline List##UCN0##ReverseIterator riterateList##UCN0(List##UCN0##ReverseIterator it)                                 \
{                                                                                                                            \
    assert(it != NULL);                                                                                                      \
    return it->prev;                                                                                                         \
}                                                                                                                            \
static inline List##UCN0##ConstIterator citerateList##UCN0(List##UCN0##ConstIterator it)                                     \
{                                                                                                                            \
    assert(it != NULL);                                                                                                      \
    return it->next;                                                                                                         \
}                                                                                                                            \
static inline List##UCN0##ConstReverseIterator criterateList##UCN0(List##UCN0##ConstReverseIterator it)                      \
{                                                                                                                            \
    assert(it != NULL);                                                                                                      \
    return it->prev;                                                                                                         \
}                                                                                                                            \
static inline List##UCN0##Iterator findInList##UCN0(List##UCN0 * list, UCN0##_Ref findable)                                  \
{                                                                                                                            \
    for (List##UCN0##Iterator it = beginList##UCN0(list);                                                                    \
            it != endList##UCN0(list);                                                                                       \
                it = iterateList##UCN0(it))                                                                                  \
    {                                                                                                                        \
        if (equal##UCN0(it->data, &findable))                                                                                \
            return it;                                                                                                       \
    }                                                                                                                        \
    return endList##UCN0(list);                                                                                              \
}                                                                                                                            \
static inline List##UCN0##ConstIterator findInCList##UCN0(const List##UCN0 * list, UCN0##_Ref findable)                      \
{                                                                                                                            \
    for (List##UCN0##ConstIterator it = cbeginList##UCN0(list);                                                              \
         it != cendList##UCN0(list);                                                                                         \
         it = citerateList##UCN0(it))                                                                                        \
    {                                                                                                                        \
        if (equal##UCN0(it->data, &findable))                                                                                \
            return it;                                                                                                       \
    }                                                                                                                        \
    return cendList##UCN0(list);                                                                                             \
}                                                                                                                            \
                                                                                                                             \
static inline void moveNodeToEndList##UCN0(List##UCN0 * list, List##UCN0##Iterator node)                                     \
{                                                                                                                            \
    if (list->size == 1)                                                                                                     \
        return;                                                                                                              \
    if (list->first_element == node)                                                                                         \
        list->first_element = node->next;                                                                                    \
    takeOutList##UCN0##Node(node);                                                                                           \
    list->last_element->next = node;                                                                                         \
    node->prev = list->last_element;                                                                                         \
    list->last_element = node;                                                                                               \
                                                                                                                             \
}                                                                                                                            \


#define MAKE_LIST(UCN0, TYPE0, ARITHM_TYPE0) PREPARE_LIST(UCN0, TYPE0, ARITHM_TYPE0)


#endif
