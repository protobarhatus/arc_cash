#ifndef FIBONACHY_NIM_PREFIX_TREE_H
#define FIBONACHY_NIM_PREFIX_TREE_H

//#include "string.h"
//for some reason clion shows errors when take it away
#include "string.h"

#include <stdbool.h>
#include "vector/vector.h"
#include "string.h"

struct PrefixTreeNode_struct
{
    //hidden but its array.
    //owns
    struct PrefixTreeNode_struct * nodes;
    //thats refs
    struct PrefixTreeNode_struct * suffix_ref;
    struct PrefixTreeNode_struct * previous;

    bool is_end;
    bool is_active;
    char transcend_here_symbol;
    int pattern_number;
};
typedef struct PrefixTreeNode_struct PrefixTreeNode;

PrefixTreeNode * locateBlankNode();
PrefixTreeNode * subNodeAtPrefixTreeNode(PrefixTreeNode * node, char sym);
void setNodeAsEnd(PrefixTreeNode * node, int pattern_number);

void destructPrefixTreeNode(PrefixTreeNode * node);
bool equalPrefixTreeNode(const PrefixTreeNode * a, const PrefixTreeNode * b);

CREATE_UNIQUE_POINTER(PrefixTreeNode*, PrefixTreeNode);

struct PrefixTree_struct
{
    PrefixTreeNodePtr root;
    //ref
    PrefixTreeNode* current;
};
typedef struct PrefixTree_struct PrefixTree;

#include "string.h"

PrefixTree buildPrefixTree(const VectorString * strings);
PrefixTree buildPrefixTreeRV(VectorString strings);

PrefixTree copyPrefixTree(const PrefixTree * cop);
PrefixTree movePrefixTree( PrefixTree * mov);
void destructPrefixTree(PrefixTree * tree);
bool equalPrefixTree(const PrefixTree * a, const PrefixTree * b);

void resetPrefixTree(PrefixTree * t);

DECLARE_STRUCT_TYPE(PrefixTree, PrefixTree);

void writeTreeWords(const PrefixTree * tree);

//true if found end of some pattern
bool processSymbolByPrefixTree(PrefixTree * tree, char sym);

String restoreStringToNode(const PrefixTreeNode * tree);
#endif //FIBONACHY_NIM_PREFIX_TREE_H
