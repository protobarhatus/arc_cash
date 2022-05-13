#ifndef FIBONACHY_NIM_TREE_TO_GRAPHWIZ_TRANSLATION_H
#define FIBONACHY_NIM_TREE_TO_GRAPHWIZ_TRANSLATION_H
#include "standart_classes/string/string.h"

//берет указатель на узел дерева и возвращает его имя.
//Имя обязательно должно быть уникальным для каждой вершины
//Представление не обязательно: если в api указатель на функцию равен NULL,
//то ноды подписываться не будут.
typedef String(*getTreeNodesName)(const void * node);
//берет указатель на узел дерева и возвращает подпись ребра, которое идет в него
typedef String(*getTreeNodesEdgeLabel)(const void * node);
//берет указатель на узел дерева и указатель на указатель на индексатор, использующийся в этом дереве. Возвращает указатель на узел,
//на который указывает индексатор и увеличивает индексатор до следующего узла
//если следующего узла нет, то возвращает NULL
//указатель на указатель используется потому что если в качестве индексатора сойдет int, то вместо аллоцирования
//можно принять за итератор сам указатель на итератор, т. е. void* приравнять к int
typedef const void*(*indexateNextNode)(const void * node, void ** indexator);
//для указателя на узел дерева выделяет память на индексатор в куче и возвращает указатель на него.
//индексатор указывает на первый лист
//удаление индексатора - ответственность принимающей стороны
typedef void*(*getFirstIndexator)(const void * node);

typedef void*(*getAdditionalRefsIterator)(const void * node);

typedef const void*(*getAdditionalRefToNode)(const void * node, void ** additional_iterator);

typedef void(*destructIndexator)(void ** iterator);

typedef void(*destructAdditionalRefIterator)(void ** iterator);

typedef struct TreeAPI_struct
{
    getTreeNodesName name_func;
    getTreeNodesEdgeLabel  label_func;
    indexateNextNode next_node_func;
    getFirstIndexator indexator_func;
    getAdditionalRefToNode additional_ref_func;
    getAdditionalRefsIterator additional_ref_indexator_func;
    destructIndexator destruct_indexator_func;
    destructAdditionalRefIterator destruct_additional_ref_iterator_func;
} TreeAPI;

String treeToGraphwiz(const void * tree, TreeAPI api);


void showTreeInGraphwiz(const void * tree, const char * filename, TreeAPI api);

#endif //FIBONACHY_NIM_TREE_TO_GRAPHWIZ_TRANSLATION_H
