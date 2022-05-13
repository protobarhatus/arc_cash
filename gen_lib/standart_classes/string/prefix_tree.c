#include "prefix_tree.h"

#define SUFFIX_TREE_NODE_CHILDS_AMOUNT 128



PrefixTreeNode constructBlankNode()
{
    PrefixTreeNode node;
    node.is_active = true;
    node.is_end = false;
    node.suffix_ref = NULL;
    node.nodes = calloc(SUFFIX_TREE_NODE_CHILDS_AMOUNT, sizeof(PrefixTreeNode));
    node.previous = NULL;
    node.transcend_here_symbol = (char)-1;
    node.pattern_number = -1;

    return node;
}
PrefixTreeNode * locateBlankNode()
{
    PrefixTreeNode * node = calloc(1, sizeof(PrefixTreeNode));
    *node = constructBlankNode();
    return node;
}

void setNodeAsEnd(PrefixTreeNode * node, int pattern_number)
{
    node->is_end = true;
    node->pattern_number = pattern_number;
}

PrefixTreeNode * subNodeAtPrefixTreeNode(PrefixTreeNode * tree, char sym)
{
    return &tree->nodes[sym];
}




static bool stringIsInSampleUpTo(const String * pref, const String * sample, int up_to_ind)
{
    if (pref->length <= up_to_ind)
        return false;
    for (int i = up_to_ind; i >= 0; --i)
    {
        if (*catString(pref, i) != *catString(sample, i))
            return false;
    }
    return true;
}

//node is made by locateNode. Its subnode are just calloced, so is_active is false.
//but it strongly requires vec to be sorted by lessByStream rule
static int buildSubNode(PrefixTreeNode * node, VectorPairStringInt * vec, int vec_start, int cur_process_index)
{
    int vec_index = vec_start;
    if (cur_process_index == 0)
    {
        //vec_index == 0 then
        int v_size = getSizeVectorPairStringInt(vec);
        while (vec_index < v_size)
        {
            String* cur_str = &atVectorPairStringInt(vec, vec_index)->first;
            if (cur_str->length == 0)
            {
                ++vec_index;
                continue;
            }
            char cur_sym = *atString(cur_str, 0);

            *subNodeAtPrefixTreeNode(node, cur_sym) = constructBlankNode();
            vec_index = buildSubNode(subNodeAtPrefixTreeNode(node, cur_sym), vec, vec_index, 1);
        }
        return v_size;
    }
    else
    {
        int v_size = getSizeVectorPairStringInt(vec);
        char node_sym = *atString(&atVectorPairStringInt(vec, vec_start)->first, cur_process_index - 1);
        String* node_str = &atVectorPairStringInt(vec, vec_start)->first;
        String * cur_str = &atVectorPairStringInt(vec, vec_index)->first;
        while (vec_index < v_size
            && stringIsInSampleUpTo(cur_str = &atVectorPairStringInt(vec, vec_index)->first, node_str, cur_process_index - 1))
        {

            if (cur_str->length == cur_process_index)
            {
                setNodeAsEnd(node, atVectorPairStringInt(vec, vec_index)->second);
                ++vec_index;
                continue;
            }
            char cur_sym = *atString(cur_str, cur_process_index);
            PrefixTreeNode * cur_node = subNodeAtPrefixTreeNode(node, cur_sym);
            *cur_node = constructBlankNode();
            vec_index = buildSubNode(cur_node, vec, vec_index, cur_process_index + 1);
        }
        return vec_index;

    }
}


static void connectBackwards(PrefixTreeNode * node)
{
    for (int i = 0; i < SUFFIX_TREE_NODE_CHILDS_AMOUNT; ++i)
    {
        if (node->nodes[i].is_active)
        {
            node->nodes[i].transcend_here_symbol = (char)i;
            node->nodes[i].previous = node;
            connectBackwards(&node->nodes[i]);
        }
    }
}

static void assignSuffixRefForExactNode(PrefixTreeNode * node)
{
    if (node->suffix_ref != NULL)
        return;
    if (node->previous == NULL)
    {
        node->suffix_ref = node;
        return;
    }
    if (node->previous->suffix_ref == NULL)
        assignSuffixRefForExactNode(node->previous);
    if (node->previous->previous == NULL)
    {
        node->suffix_ref = node->previous;
        return;
    }

    PrefixTreeNode * prepretend = node->previous->suffix_ref;
    while (prepretend->previous != NULL && !prepretend->nodes[node->transcend_here_symbol].is_active)
    {
        if (prepretend->suffix_ref == NULL)
            assignSuffixRefForExactNode(prepretend);
        prepretend = prepretend->suffix_ref;
    }

    if (prepretend->nodes[node->transcend_here_symbol].is_active)
    {
        assert(&prepretend->nodes[node->transcend_here_symbol] != node);
        node->suffix_ref = &prepretend->nodes[node->transcend_here_symbol];
    }
    else
        node->suffix_ref = prepretend;
}

static void assignSuffixesForAllNodes(PrefixTreeNode * node)
{
    assignSuffixRefForExactNode(node);
    for (int i = 0; i < SUFFIX_TREE_NODE_CHILDS_AMOUNT; ++i)
    {
        if (node->nodes[i].is_active)
        {
            assignSuffixesForAllNodes(&node->nodes[i]);
        }
    }
}

static int lessStringIntPairForPrefixTreeComparator(const void * pa, const void * pb)
{
    const PairStringInt * a = pa;
    const PairStringInt * b = pb;
    return lessStringByStreamAlphabet(&a->first, &b->first);
}

PrefixTree buildPrefixTree(const VectorString * strings)
{
    VectorPairStringInt strings_with_indexes = defaultVectorPairStringInt(strings->size, NULL);
    for (int i = 0; i < strings->size; ++i)
        *atVectorPairStringInt(&strings_with_indexes, i) = defaultPairStringIntLVRV(catVectorString(strings, i), i);

    sortVectorPairStringInt(&strings_with_indexes, &lessStringIntPairForPrefixTreeComparator);
    PrefixTree tree;
    tree.root = locateBlankNode();
    tree.current = tree.root;
    buildSubNode(tree.root, &strings_with_indexes, 0, 0);
    connectBackwards(tree.root);
    assignSuffixesForAllNodes(tree.root);


    destructVectorPairStringInt(&strings_with_indexes);
    return tree;

}
PrefixTree buildPrefixTreeRV(VectorString strings)
{
    buildPrefixTree(&strings);
    destructVectorString(&strings);
}




void recursiveWriteWords(const PrefixTreeNode * tree, const String * prev)
{
    if (tree->is_end)
        printf("%s\n", prev->string);
    for (int i = 0; i < SUFFIX_TREE_NODE_CHILDS_AMOUNT; ++i)
    {
        if (tree->nodes[i].is_active)
        {
            String next_str = concatStringLVRV(prev, stringFromChar((char)i));
            recursiveWriteWords(&tree->nodes[i], &next_str);
            destructString(&next_str);
        }
    }
}

void writeTreeWords(const PrefixTree * tree)
{
    String empt = createString(0);
    recursiveWriteWords(tree->current, &empt);
    destructString(&empt);
}

void destructPrefixTreeNode(PrefixTreeNode * node)
{
    for (int i = 0; i < SUFFIX_TREE_NODE_CHILDS_AMOUNT; ++i)
    {
        if (node->nodes[i].is_active)
            destructPrefixTreeNode(&node->nodes[i]);
    }
    free(node->nodes);
    node->nodes = NULL;
    node->is_active = false;
}

bool equalPrefixTreeNode(const PrefixTreeNode * a, const PrefixTreeNode * b)
{
    //idk how they suppose to compare so lets by pointer
    return a == b;
}

PrefixTree copyPrefixTree(const PrefixTree * cop)
{
    //why copy it is needed
    //(problem function is needed for DECLARE_STRUCT. (but the system as a whole is kinda outdated and actually dont matter for
    //templates generation but better keep it)
    assert(false);

}

PrefixTree movePrefixTree(PrefixTree * mov)
{
    PrefixTree res;
    res.root = movePrefixTreeNodePtr(&mov->root);
    res.current = mov->current;
    mov->root = NULL;
    mov->current = NULL;
    return res;
}

void destructPrefixTree(PrefixTree * tree)
{
    destructPrefixTreeNodePtr(&tree->root);
    tree->root = NULL;
    tree->current = NULL;
}
bool equalPrefixTree(const PrefixTree * a, const PrefixTree * b)
{
    //same as with copy, kinda meaningless
    return a == b;
}



bool processSymbolByPrefixTree(PrefixTree * tree, char sym)
{
    if (tree->current->nodes[sym].is_active)
    {
        tree->current = &tree->current->nodes[sym];
        if (tree->current->suffix_ref->is_end && !tree->current->is_end)
        {
            tree->current = tree->current->suffix_ref;
            return true;
        }
        return tree->current->is_end;
    }
    while (tree->current->previous != NULL)
    {
        tree->current = tree->current->suffix_ref;
        if (tree->current->nodes[sym].is_active)
        {
            tree->current = &tree->current->nodes[sym];
            return tree->current->is_end;
        }
    }
    return false;
}

String restoreStringToNode(const PrefixTreeNode * current)
{
    String str = createString(0);
    PrefixTreeNode const * cur_node = current;
    while (cur_node->previous != NULL)
    {
        replaceString(&str, concatStringLVRV(&str, stringFromChar(cur_node->transcend_here_symbol)));
        cur_node = cur_node->previous;
    }
    reverseOnString(&str);
    return str;
}

void resetPrefixTree(PrefixTree * t)
{
    t->current = t->root;
}