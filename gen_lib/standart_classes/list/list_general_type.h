#ifndef FIBONACHY_NIM_LIST_GENERAL_TYPE_H
#define FIBONACHY_NIM_LIST_GENERAL_TYPE_H

#include "list_node_def.h"
//эта строчка должна быть в list_def, но не в list_general_type
//MAKE_LISTNODE(GeneralType, TEMPLATE_TYPE_GeneralType, TEMPLATE_TYPE_GeneralType)

struct List_struct {
    ListNode * first_element;
    ListNode * last_element;
    int size;
} ;
typedef List ListRef;
typedef List List_Ref;

List defaultList();
void pushBackToList(List * list, const GeneralType * dat);
void pushFrontToList(List * list, const GeneralType * dat);

GENERATE_RIGHT_VALUE_CUMULATIVE_UNARY_EXTENSION(List, GeneralType, pushBackToList)
GENERATE_RIGHT_VALUE_CUMULATIVE_UNARY_EXTENSION(List, GeneralType, pushFrontToList)

List copyList(const List * list);
List moveList(List * list);
bool equalList(const List * a, const List * b);

void destructList(List * list);

DECLARE_STRUCT_TYPE(List, List)

typedef ListNode* ListIterator;
typedef ListNode* ListReverseIterator;
typedef ListNode const * ListConstIterator;
typedef ListNode const * ListConstReverseIterator;

ListIterator eraseListNode(ListIterator it);

ListIterator endList(List * list);
ListReverseIterator rendList(List * list);
ListConstIterator cendList(const List * list);
ListConstReverseIterator crendList(const List * list);

ListIterator beginList(List * list);
ListReverseIterator rbeginList(List * list);
ListConstIterator cbeginList(const List * list);
ListConstReverseIterator crbeginList(const List * list);

ListIterator iterateList(ListIterator it);
ListReverseIterator riterateList(ListReverseIterator it);
ListConstIterator citerateList(ListConstIterator it);
ListConstReverseIterator criterateList(ListConstReverseIterator it);

ListIterator findInList(List * list, GeneralType_Ref findable);
ListConstIterator findInCList(const List * list, GeneralType_Ref findable);

void moveNodeToEndList(List * list, ListIterator node);
#endif
