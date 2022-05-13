#include "list_node_general_type.h"

ListNode defaultListNode(const GeneralType * data, List * list)
{
    ListNode node;
    node.data = calloc(1, sizeof(GeneralType));
    assert(node.data);
    *node.data = copyGeneralType(data);
    node.prev = NULL;
    node.next = NULL;
    node.list = list;
    return node;
}

void destructListNode(ListNode * node)
{
    takeOutListNode(node);
    destructGeneralType(node->data);
    free(node->data);
}

void connectListNodes(ListNode * prev, ListNode * next)
{
    assert(prev->next == NULL);
    assert(next->prev == NULL);
    prev->next = next;
    next->prev = prev;
}

void disconnectListNodeFromPreviousBySplitting(ListNode * node)
{
    if (node->prev == NULL)
        return;
    assert(node->prev->next == node);
    node->prev->next = NULL;
    node->prev = NULL;

}

void disconnectListNodeFromNextBySplitting(ListNode * node)
{
    if (node->next == NULL)
        return;
    assert(node->next->prev == node);
    node->next->prev = NULL;
    node->next = NULL;
}

void takeOutListNode(ListNode * node)
{
    if (node->prev != NULL)
    {
        assert(node->prev->next == node);
        node->prev->next = node->next;
    }
    if (node->next != NULL)
    {
        assert(node->next->prev == node);
        node->next->prev = node->prev;
    }
    node->prev = NULL;
    node->next = NULL;
}
//its forbidden
ListNode copyListNode(const ListNode * node)
{
    assert(false);
}
//its also forbidden
ListNode moveListNode(const ListNode * node)
{
    assert(false);
}

