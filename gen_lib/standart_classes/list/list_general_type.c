#include "list_general_type.h"


List defaultList()
{
    List res;
    res.first_element = NULL;
    res.last_element = NULL;
    res.size = 0;
    return res;
}

void pushBackToList(List * list, const GeneralType * dat)
{
    if (list->size == 0)
    {
        list->first_element = calloc(1, sizeof(ListNode));
        *list->first_element = defaultListNode(dat, list);
        list->last_element = list->first_element;
        ++list->size;
    }
    else
    {
        ListNode * new_node = calloc(1, sizeof(ListNode));
        assert(new_node);
        *new_node = defaultListNode(dat, list);
        connectListNodes(list->last_element, new_node);
        list->last_element = list->last_element->next;
        ++list->size;
    }
}

void pushFrontToList(List * list, const GeneralType * dat)
{
    if (list->size == 0)
    {
        pushBackToList(list, dat);
        return;
    }
    else
    {
        ListNode * new_node = calloc(1, sizeof(ListNode));
        assert(new_node);
        *new_node = defaultListNode(dat, list);
        connectListNodes(new_node, list->first_element);
        list->first_element = list->first_element->prev;
        ++list->size;
    }
}

List copyList(const List * list)
{
    List res = defaultList();
    for (ListConstIterator it = cbeginList(list); it != cendList(list); it = citerateList(it))
    {
        pushBackToList(&res, it->data);
    }
    return res;
}
List moveList(List * list)
{
    List res = *list;
    list->size = 0;
    list->first_element = NULL;
    list->last_element = NULL;
    return res;
}
bool equalList(const List * a, const List * b)
{
    if (a->size != b->size)
        return false;
    for (ListConstIterator it1 = cbeginList(a),
            it2 = cbeginList(b); it1 != cendList(a);
                it1 = citerateList(it1), it2 = citerateList(it2))
    {
        if (!equalGeneralType(it1->data, it2->data))
            return false;
    }
    return true;
}

void destructList(List * list)
{
    ListIterator it = beginList(list);
    if (it == NULL)
        return;
    while (it != endList(list))
    {
        ListIterator next = it->next;
        takeOutListNode(it);
        destructListNode(it);
        free(it);
        it = next;
    }

}

ListIterator eraseListNode(ListIterator it)
{
    ListIterator ret = it->next;
    it->list->size -= 1;
    if (it->prev == NULL)
        it->list->first_element = it->next;
    if (it->next == NULL)
        it->list->last_element = it->prev;
    takeOutListNode(it);
    destructListNode(it);
    return ret;
}


ListIterator endList(List * list)
{
    return NULL;
}
ListReverseIterator rendList(List * list)
{
    return NULL;
}
ListConstIterator cendList(const List * list)
{
    return NULL;
}
ListConstReverseIterator crendList(const List * list)
{
    return NULL;
}
ListIterator beginList(List * list)
{
    return list->first_element;
}
ListReverseIterator rbeginList(List * list)
{
    return list->last_element;
}
ListConstIterator cbeginList(const List * list)
{
    return list->first_element;
}
ListConstReverseIterator crbeginList(const List * list)
{
    return list->last_element;
}
ListIterator iterateList(ListIterator it)
{
    assert(it != NULL);
    return it->next;
}
ListReverseIterator riterateList(ListReverseIterator it)
{
    assert(it != NULL);
    return it->prev;
}
ListConstIterator citerateList(ListConstIterator it)
{
    assert(it != NULL);
    return it->next;
}
ListConstReverseIterator criterateList(ListConstReverseIterator it)
{
    assert(it != NULL);
    return it->prev;
}
ListIterator findInList(List * list, GeneralType_Ref findable)
{
    for (ListIterator it = beginList(list);
            it != endList(list);
                it = iterateList(it))
    {
        if (equalGeneralType(it->data, &findable))
            return it;
    }
    return endList(list);
}
ListConstIterator findInCList(const List * list, GeneralType_Ref findable)
{
    for (ListConstIterator it = cbeginList(list);
         it != cendList(list);
         it = citerateList(it))
    {
        if (equalGeneralType(it->data, &findable))
            return it;
    }
    return cendList(list);
}

void moveNodeToEndList(List * list, ListIterator node)
{
    if (list->size == 1)
        return;
    if (list->first_element == node)
        list->first_element = node->next;
    takeOutListNode(node);
    list->last_element->next = node;
    node->prev = list->last_element;
    list->last_element = node;

}