
#ifndef FIBONACHY_NIM_LIST_NODE_GENERAL_TYPE_H
#define FIBONACHY_NIM_LIST_NODE_GENERAL_TYPE_H

#include "types_and_functions_declarations/general_type.h"

struct List_struct;
typedef struct List_struct List;

struct  ListNode_struct
{
    GeneralType * data;
    struct ListNode_struct * next;
    struct ListNode_struct * prev;

    struct List_struct * list;
};
typedef struct ListNode_struct ListNode;

ListNode defaultListNode(const GeneralType * data, List * list);

void destructListNode(ListNode * node);
void connectListNodes(ListNode * prev, ListNode * next);
ListNode copyListNode(const ListNode * node);
ListNode moveListNode(const ListNode * node);

void disconnectListNodeFromPreviousBySplitting(ListNode * node);
void disconnectListNodeFromNextBySplitting(ListNode * node);
void takeOutListNode(ListNode * node);



#endif //FIBONACHY_NIM_LIST_NODE_GENERAL_TYPE_H
