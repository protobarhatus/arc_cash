#ifndef LIST_NODE_DEF_H
#define LIST_NODE_DEF_H

#include "types_and_functions_declarations/general_type.h"
#include "list_node_general_type.h"
#define PREPARE_LISTNODE(UCN0, TYPE0, ARITHM_TYPE0)\
                                                                                                   \
                                                                                                   \
                                                                                                   \
                                                                                                   \
                                                                                                   \
                                                                                                   \
struct List##UCN0##_struct;                                                                        \
typedef struct List##UCN0##_struct List##UCN0;                                                     \
                                                                                                   \
struct  List##UCN0##Node_struct                                                                    \
{                                                                                                  \
    UCN0 * data;                                                                                   \
    struct List##UCN0##Node_struct * next;                                                         \
    struct List##UCN0##Node_struct * prev;                                                         \
                                                                                                   \
    struct List##UCN0##_struct * list;                                                       \
};                                                                                                 \
typedef struct List##UCN0##Node_struct List##UCN0##Node;                                           \
                                                                                                   \
static inline List##UCN0##Node defaultList##UCN0##Node(const UCN0 * data, List##UCN0 * list);      \
                                                                                                   \
static inline void destructList##UCN0##Node(List##UCN0##Node * node);                              \
static inline void connectList##UCN0##Nodes(List##UCN0##Node * prev, List##UCN0##Node * next);     \
static inline List##UCN0##Node copyList##UCN0##Node(const List##UCN0##Node * node);                \
static inline List##UCN0##Node moveList##UCN0##Node(const List##UCN0##Node * node);                \
                                                                                                   \
static inline void disconnectList##UCN0##NodeFromPreviousBySplitting(List##UCN0##Node * node);     \
static inline void disconnectList##UCN0##NodeFromNextBySplitting(List##UCN0##Node * node);         \
static inline void takeOutList##UCN0##Node(List##UCN0##Node * node);                               \
                                                                                                   \
                                                                                                   \
                                                                                                   \
                                                                                                   \
                                                                                                  \
                                                                                                  \
static inline List##UCN0##Node defaultList##UCN0##Node(const UCN0 * data, List##UCN0 * list)      \
{                                                                                                 \
    List##UCN0##Node node;                                                                        \
    node.data = calloc(1, sizeof(UCN0));                                                          \
    assert(node.data);                                                                            \
    *node.data = TYPE0##_TYPE_COPY(UCN0, data);                                                   \
    node.prev = NULL;                                                                             \
    node.next = NULL;                                                                             \
    node.list = list;                                                                             \
    return node;                                                                                  \
}                                                                                                 \
                                                                                                  \
static inline void destructList##UCN0##Node(List##UCN0##Node * node)                              \
{                                                                                                 \
    takeOutList##UCN0##Node(node);                                                                \
    TYPE0##_TYPE_DESTRUCT(UCN0, node->data);       \
    free(node->data);                                                   \
}                                                                                                 \
                                                                                                  \
static inline void connectList##UCN0##Nodes(List##UCN0##Node * prev, List##UCN0##Node * next)     \
{                                                                                                 \
    assert(prev->next == NULL);                                                                   \
    assert(next->prev == NULL);                                                                   \
    prev->next = next;                                                                            \
    next->prev = prev;                                                                            \
}                                                                                                 \
                                                                                                  \
static inline void disconnectList##UCN0##NodeFromPreviousBySplitting(List##UCN0##Node * node)     \
{                                                                                                 \
    if (node->prev == NULL)                                                                       \
        return;                                                                                   \
    assert(node->prev->next == node);                                                             \
    node->prev->next = NULL;                                                                      \
    node->prev = NULL;                                                                            \
                                                                                                  \
}                                                                                                 \
                                                                                                  \
static inline void disconnectList##UCN0##NodeFromNextBySplitting(List##UCN0##Node * node)         \
{                                                                                                 \
    if (node->next == NULL)                                                                       \
        return;                                                                                   \
    assert(node->next->prev == node);                                                             \
    node->next->prev = NULL;                                                                      \
    node->next = NULL;                                                                            \
}                                                                                                 \
                                                                                                  \
static inline void takeOutList##UCN0##Node(List##UCN0##Node * node)                               \
{                                                                                                 \
    if (node->prev != NULL)                                                                       \
    {                                                                                             \
        assert(node->prev->next == node);                                                         \
        node->prev->next = node->next;                                                            \
    }                                                                                             \
    if (node->next != NULL)                                                                       \
    {                                                                                             \
        assert(node->next->prev == node);                                                         \
        node->next->prev = node->prev;                                                            \
    }                                                                                             \
    node->prev = NULL;                                                                            \
    node->next = NULL;                                                                            \
}                                                                                                 \
/*its forbidden*/                                                                                 \
static inline List##UCN0##Node copyList##UCN0##Node(const List##UCN0##Node * node)                \
{                                                                                                 \
    assert(false);                                                                                \
}                                                                                                 \
/*its also forbidden*/                                                                            \
static inline List##UCN0##Node moveList##UCN0##Node(const List##UCN0##Node * node)                \
{                                                                                                 \
    assert(false);                                                                                \
}                                                                                                 \
                                                                                                  \


#define MAKE_LISTNODE(UCN0, TYPE0, ARITHM_TYPE0) PREPARE_LISTNODE(UCN0, TYPE0, ARITHM_TYPE0)







#endif
