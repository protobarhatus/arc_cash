#ifndef FIBONACHY_NIM_SUFFIX_TREE_H
#define FIBONACHY_NIM_SUFFIX_TREE_H

//suffix tree is build by Ukkenen's algorithm
//description was readen here https://habr.com/ru/post/111675/
//in buildSuffixTree go through all symbols adding extending suffix tree to them
//in doAStepToAddToSuffixTree we apply that symbol and either just move active point (if cannot initialize insertion) remembering that
//we have to add it in future either add all remembered symbols
//last symbol to add is '\0' and it closes all branches

#include "string.h"
#include "vector/vector.h"
#include "graph_work/tree_to_graphwiz_translation.h"

struct SuffixTreeNode_struct;
//suffix ptr is reserved for unique_ptr style pointers.
typedef struct SuffixTreeNode_struct * SuffixTreeNodePointer;

bool equalSuffixTreeNodePointer(const SuffixTreeNodePointer * a, const SuffixTreeNodePointer * b);
MAKE_VECTOR(SuffixTreeNodePointer, SIMPLE, SIMPLE)

struct SuffixTreeNode_struct
{
    struct SuffixTreeNode_struct * next_nodes;
    int start_position;
    int end_position;
    const String* string;
    struct SuffixTreeNode_struct * suff_ref;
    //who has suff_ref on this object
    VectorSuffixTreeNodePointer prefix_refs;

};
typedef struct SuffixTreeNode_struct SuffixTreeNode;

void destructSuffixTreeNode(SuffixTreeNode * node);
SuffixTreeNode moveSuffixTreeNode(SuffixTreeNode * node);
bool isSuffixTreeNodeActive(const SuffixTreeNode * node);

struct SuffixTree_struct
{
    SuffixTreeNode start_node;
    String* string;
};
typedef struct SuffixTree_struct SuffixTree;


SuffixTree buildSuffixTree(const String * str);
SuffixTree destructSuffixTree(SuffixTree * str);

VectorInt findSubstringsBySuffixTree(const SuffixTree * tree, const String * sub);
VectorPairIntInt findPatternsBySuffixTree(const SuffixTree * tree, const VectorString * patterns);


String void_getSuffixTreeNodeName(const void * node);
String void_getSuffixTreeNodeLabel(const void * node);
const void * void_indexateNextSuffixTreeNode(const void * node, void ** iterator);
void * void_getSuffixTreeNodeIterator(const void * node);
const void * void_getAdditionalRef(const void * node, void ** iterator);
void * void_getAdditionalRefToSuffixTreeNodeIterator(const void * node);

TreeAPI getSuffixTreeApi();
#endif //FIBONACHY_NIM_SUFFIX_TREE_H
