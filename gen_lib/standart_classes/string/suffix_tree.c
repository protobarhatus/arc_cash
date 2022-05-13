#include "suffix_tree.h"
#define SUFFIX_TREE_NODE_CHILDS_AMOUNT (ALPHABET_SIZE + 1)
#define SUFFIX_TREE_NODE_FIN 2000000000
//#define ALPHABET_START 0

bool equalSuffixTreeNodePointer(const SuffixTreeNodePointer * a, const SuffixTreeNodePointer * b)
{
    return *a == *b;
}

void destructSuffixTreeNode(SuffixTreeNode * node)
{
    assert(node != NULL);
    if (node->next_nodes != NULL)
    {
        for (int i = 0; i < SUFFIX_TREE_NODE_CHILDS_AMOUNT; ++i)
        {
            destructSuffixTreeNode(&node->next_nodes[i]);
        }
        free(node->next_nodes);
        node->next_nodes = NULL;
    }
    node->string;
    destructVectorSuffixTreeNodePointer(&node->prefix_refs);
}

SuffixTreeNode moveSuffixTreeNode(SuffixTreeNode * node)
{
    SuffixTreeNode res;
    res.next_nodes = node->next_nodes;
    res.string = node->string;
    node->next_nodes = NULL;
    res.start_position = node->start_position;
    res.end_position = node->end_position;
    res.suff_ref = node->suff_ref;
    res.prefix_refs = moveVectorSuffixTreeNodePointer(&node->prefix_refs);
    return res;

}

bool isSuffixTreeNodeActive(const SuffixTreeNode * node)
{
    return node->string != NULL;
}



SuffixTreeNode createSuffixTreeNode(int start_pos, int end_pos, const String * str, const VectorSuffixTreeNodePointer * prefix_refs)
{
    SuffixTreeNode res;
    res.next_nodes = calloc(SUFFIX_TREE_NODE_CHILDS_AMOUNT, sizeof(SuffixTreeNode));
    assert(res.next_nodes != NULL);
    res.start_position = start_pos;
    res.end_position = end_pos;
    res.string = str;
    res.suff_ref = NULL;
    if (prefix_refs != NULL)
        res.prefix_refs = copyVectorSuffixTreeNodePointer(prefix_refs);
    else
        res.prefix_refs = defaultVectorSuffixTreeNodePointer(0, NULL);
    return res;
}
SuffixTreeNode createSuffixTreeNodeRV(int start_pos, int end_pos, const String * str,
                                      VectorSuffixTreeNodePointer prefix_refs)
{
    SuffixTreeNode res;
    res.next_nodes = calloc(SUFFIX_TREE_NODE_CHILDS_AMOUNT, sizeof(SuffixTreeNode));
    assert(res.next_nodes != NULL);
    res.start_position = start_pos;
    res.end_position = end_pos;
    res.string = str;
    res.suff_ref = NULL;

    res.prefix_refs = moveVectorSuffixTreeNodePointer(&prefix_refs);
    return res;
}

struct ActivePoint_struct
{
    SuffixTreeNode * active_node;
    char active_edge;
    int active_len;
};
typedef struct ActivePoint_struct ActivePoint;

static char atExtString(const String * str, int index)
{
    assert(index <= str->length);
    if (index == str->length)
        return '\0';
    return *catString(str, index);
}

static char atNodeString(SuffixTreeNode * node, int index)
{
    return atExtString(node->string, index + node->start_position);
}

int ctoi(char sym)
{
    assert(sym >= ALPHABET_START || sym == '\0');
    assert(sym < ALPHABET_START + ALPHABET_SIZE || sym == '\0');
    if (sym == '\0')
        return 0;
    else
        return sym - ALPHABET_START + 1;
}

static bool canAddVertex(ActivePoint * point, char sym)
{
    //if (!isSuffixTreeNodeActive(&point->active_node->next_nodes[ctoi(sym)]))
    //    return true;
    if (point->active_edge == '\0')
        return !isSuffixTreeNodeActive(&point->active_node->next_nodes[ctoi(sym)]);

    return isSuffixTreeNodeActive(&point->active_node->next_nodes[ctoi(point->active_edge)]) &&
           atNodeString(&point->active_node->next_nodes[ctoi(point->active_edge)], point->active_len) != sym;
}

int insertionNodesLength(ActivePoint * active_point)
{
    return active_point->active_node->next_nodes[ctoi(active_point->active_edge)].end_position
           - active_point->active_node->next_nodes[ctoi(active_point->active_edge)].start_position;
}

bool isActivePointExceedesNode(ActivePoint * active_point)
{
    return active_point->active_len > insertionNodesLength(active_point) &&
           isSuffixTreeNodeActive(&active_point->active_node->next_nodes[ctoi(active_point->active_edge)]);
}

bool isActivePointOnEndOfItsNode(ActivePoint * active_point)
{
    return active_point->active_len == insertionNodesLength(active_point) &&
    isSuffixTreeNodeActive(&active_point->active_node->next_nodes[ctoi(active_point->active_edge)]);
}

void normalizeActivePoint(ActivePoint * active_point, const String * string, int last_sym_index)
{
    assert(isSuffixTreeNodeActive(active_point->active_node));

    while (isActivePointExceedesNode(active_point))
    {
        active_point->active_node = &active_point->active_node->next_nodes[ctoi(active_point->active_edge)];

        //active_point->active_edge = '\0';
        active_point->active_len -= active_point->active_node->end_position - active_point->active_node->start_position;
        active_point->active_edge = *catString(string, last_sym_index - active_point->active_len + 1);
    }
    if (isActivePointOnEndOfItsNode(active_point))
    {
        active_point->active_node = &active_point->active_node->next_nodes[ctoi(active_point->active_edge)];
        active_point->active_edge = '\0';
        active_point->active_len = 0;
    }
    if (active_point->active_len == 0)
        active_point->active_edge = '\0';
    assert(isSuffixTreeNodeActive(active_point->active_node));
}

void swapSuffixTreeNodePtr(SuffixTreeNode ** a, SuffixTreeNode **b)
{
    SuffixTreeNode *t = *a;
    *a = *b;
    *b = t;
}

SuffixTreeNode * addSuffixSymbol(ActivePoint * active_point, const String * str, int sym_ind, SuffixTreeNode * root,
                                 int * remainder)
{
    char sym = atExtString(str, sym_ind);

    if (canAddVertex(active_point, sym))
    {
        SuffixTreeNode * inserted = (active_point->active_edge == '\0' ? &active_point->active_node->next_nodes[ctoi(
                sym)] :
                &active_point->active_node->next_nodes[ctoi(active_point->active_edge)]);
        SuffixTreeNode * real_inserted;
        if (isSuffixTreeNodeActive(&active_point->active_node->next_nodes[ctoi(active_point->active_edge)]))
        {
            int old_end = inserted->end_position;
            inserted->end_position = inserted->start_position + active_point->active_len;
            assert(old_end > inserted->end_position);
            SuffixTreeNode at_ext_string_node = createSuffixTreeNodeRV(inserted->end_position, old_end, str,
                                                                       moveVectorSuffixTreeNodePointer(&inserted->prefix_refs));


            swapSuffixTreeNodePtr(&inserted->next_nodes, &at_ext_string_node.next_nodes);
            //swapSuffixTreeNodePtr(&inserted->suff_ref, &at_ext_string_node.suff_ref);
            at_ext_string_node.suff_ref = inserted->suff_ref;

            SuffixTreeNode sym_string_node = createSuffixTreeNode(sym_ind, SUFFIX_TREE_NODE_FIN, str, NULL);


            inserted->next_nodes[ctoi(atExtString(str, inserted->end_position))] = moveSuffixTreeNode(&at_ext_string_node);
            SuffixTreeNode * splited_node_end = &inserted->next_nodes[ctoi(atExtString(str, inserted->end_position))];
            for (int i = 0; i < splited_node_end->prefix_refs.size; ++i)
                assert(isSuffixTreeNodeActive(*catVectorSuffixTreeNodePointer(&splited_node_end->prefix_refs, i)));
            for (int i = 0; i < splited_node_end->prefix_refs.size; ++i)
                (*atVectorSuffixTreeNodePointer(&splited_node_end->prefix_refs, i))->suff_ref = splited_node_end;
            if (inserted->suff_ref != NULL)
            {
                for (int i = 0; i < inserted->suff_ref->prefix_refs.size; ++i)
                {
                    if ((*atVectorSuffixTreeNodePointer(&inserted->suff_ref->prefix_refs, i)) == inserted)
                    {
                        (*atVectorSuffixTreeNodePointer(&inserted->suff_ref->prefix_refs, i)) =
                                &inserted->next_nodes[ctoi(atExtString(str, inserted->end_position))];
                        break;
                    }

                }
                //inserted->suff_ref->prefix_ref = &inserted->next_nodes[ctoi(atExtString(str, inserted->end_position))];
            }
            //prefix_refs vere moved above
            inserted->prefix_refs = defaultVectorSuffixTreeNodePointer(0, NULL);
            inserted->suff_ref = NULL;


            inserted->next_nodes[ctoi(sym)] = moveSuffixTreeNode(&sym_string_node);

            --(*remainder);

            assert(inserted->end_position > inserted->start_position);

            //inserted = &inserted->next_nodes[ctoi(sym)];
        }
        else
        {

            *inserted = createSuffixTreeNode(sym_ind, SUFFIX_TREE_NODE_FIN, str, NULL);
             inserted = active_point->active_node;
            --(*remainder);
        }
        //if (active_point->active_edge == '\0')
        //    inserted = active_point->active_node;
        if (active_point->active_node == root)
        {
            active_point->active_edge = (sym_ind - *remainder + 1 <= sym_ind ?
                    atExtString(str, sym_ind - *remainder + 1) : '\0');
            if (active_point->active_len > 0)
                --active_point->active_len;

            normalizeActivePoint(active_point, root->string, sym_ind - 1);
        }
        else if (active_point->active_node->suff_ref != NULL)
        {
            assert(isSuffixTreeNodeActive(active_point->active_node->suff_ref));
            active_point->active_node = active_point->active_node->suff_ref;

            normalizeActivePoint(active_point, root->string, sym_ind - 1);

            assert(isSuffixTreeNodeActive(active_point->active_node));


        }
        else
        {
            active_point->active_node = root;
            active_point->active_len = *remainder - 1;
            if (active_point->active_len < 0)
                active_point->active_len = 0;
            active_point->active_edge = atExtString(str, sym_ind - active_point->active_len);
            normalizeActivePoint(active_point, root->string, sym_ind - 1);
        }


        return inserted;

    }
    else
    {
        if (active_point->active_edge == '\0')
            active_point->active_edge = sym;
        ++active_point->active_len;

        normalizeActivePoint(active_point, root->string, sym_ind);
        return NULL;
    }
}

void doAStepToAddToSuffixTree(ActivePoint * point, SuffixTreeNode * root, const String * string, int last_step_sym, int * remainder)
{
    SuffixTreeNode * inserted_on_last_step = NULL;
    char sym = atExtString(string, last_step_sym);
    int counter = 0;
    do
    {
        SuffixTreeNode *inserted = addSuffixSymbol(point, string, last_step_sym, root, remainder);
        if (inserted != NULL)
            assert(isSuffixTreeNodeActive(inserted));
        if (inserted != NULL && inserted_on_last_step != NULL && inserted != root && inserted != inserted_on_last_step
        &&inserted_on_last_step->suff_ref == NULL)
        {
            inserted_on_last_step->suff_ref = inserted;
            pushBackVectorSuffixTreeNodePointerRV(&inserted->prefix_refs, inserted_on_last_step);

        }
#ifdef VISUALIZE
        String name = defaultString("stage/st_");
        concatToStringRV(&name, intToStringInBase(last_step_sym, 10));
        concatToStringRV(&name, defaultString("_"));
        concatToStringRV(&name, intToStringInBase(counter, 10));
        showTreeInGraphwiz(root, name.string, getSuffixTreeApi());
        destructString(&name);
#endif
        counter += 1;


        inserted_on_last_step = inserted;

    } while (*remainder > 0 && (inserted_on_last_step != NULL || sym == '\n'));
}

SuffixTree buildSuffixTree(const String * str)
{
    SuffixTree res;
    res.string = calloc(1, sizeof(String));
    *res.string = copyString(str);
    res.start_node = createSuffixTreeNode(-1, -1, str, NULL);
    ActivePoint active_point;
    active_point.active_node = &res.start_node;
    active_point.active_edge = '\0';
    active_point.active_len = 0;


    int remainder = 0;

    for (int i = 0; i <= str->length; ++i)
    {
        ++remainder;
        doAStepToAddToSuffixTree(&active_point, &res.start_node, res.string, i, &remainder);
    }

    return res;
}

SuffixTree destructSuffixTree(SuffixTree * str)
{
    assert(str != NULL);
    destructSuffixTreeNode(&str->start_node);
    if (str->string != NULL)
        destructString(str->string);
    free(str->string);
}

bool isSuffixTreeNodesEnd(const SuffixTreeNode * node)
{
    return node->end_position == SUFFIX_TREE_NODE_FIN || isSuffixTreeNodeActive(&node->next_nodes[ctoi('\0')]);
}
static void deepScanOfSuffixTreeNodes(const SuffixTreeNode * current, VectorInt * depth, int str_len, int line_depth)
{
    if (isSuffixTreeNodesEnd(current))
    {
        pushBackVectorIntRV(depth, str_len - line_depth - 1);
    }
    if (current->next_nodes == NULL)
        return;
    for (int i = 1; i < SUFFIX_TREE_NODE_CHILDS_AMOUNT; ++i)
    {
        SuffixTreeNode * next = &current->next_nodes[i];
        if (isSuffixTreeNodeActive(next))
            deepScanOfSuffixTreeNodes(next, depth, str_len, line_depth + min(next->end_position, str_len) - next->start_position);
    }

}

VectorInt findSubstringsBySuffixTree(const SuffixTree * tree, const String * sub)
{
    const SuffixTreeNode * current = &tree->start_node;
    int act_len = current->end_position;
    for (int i = 0; i < sub->length; ++i)
    {
        char sym = *catString(sub, i);
        if (act_len == current->end_position)
        {
            if (isSuffixTreeNodeActive(&current->next_nodes[ctoi(sym)]))
            {
                current = &current->next_nodes[ctoi(sym)];
                act_len = current->start_position + 1;
            }
            else
                return defaultVectorInt(0, NULL);
        }
        else
        {
            char next_sym = atExtString(tree->string, act_len);
            if (next_sym != atExtString(sub, i))
                return defaultVectorInt(0, NULL);
            ++act_len;
        }
    }
    int syms_to_node_end = min(current->end_position, tree->string->length) - act_len;

    VectorInt res = defaultVectorInt(0, NULL);
    deepScanOfSuffixTreeNodes(current, &res, tree->string->length, syms_to_node_end + sub->length - 1);

    return res;

}
VectorPairIntInt findPatternsBySuffixTree(const SuffixTree * tree, const VectorString * patterns)
{
    VectorPairIntInt res = defaultVectorPairIntInt(0, NULL);
    for (int i = 0; i < getSizeVectorString(patterns); ++i)
    {
        VectorInt curres = findSubstringsBySuffixTree(tree, catVectorString(patterns, i));
        sortVectorInt(&curres, &intLessComparator);
        for (int j = 0; j < getSizeVectorInt(&curres); ++j)
            pushBackVectorPairIntIntRV(&res,
                                   defaultPairIntIntRVLV(i, atVectorInt(&curres, j)));
        destructVectorInt(&curres);
    }
    return res;
}


String void_getSuffixTreeNodeName(const void * vnode)
{
    const SuffixTreeNode * node = vnode;
    return stringConcatMany(defaultString("["), intToString(node->start_position),
                            defaultString("; "),
                            (node->end_position == SUFFIX_TREE_NODE_FIN ? defaultString("inf") : intToString(node->end_position)),
                            defaultString(")"), terminateString());
}
String void_getSuffixTreeNodeLabel(const void * snode)
{
    const SuffixTreeNode * node = snode;
    String label = createString(min(node->end_position, node->string->length) - node->start_position);
    for (int i = 0; i < label.length; ++i)
        *atString(&label, i) = *catString(node->string, node->start_position + i);
    return label;
}

const void * void_indexateNextSuffixTreeNode(const void * node, void ** iterator)
{
    void * return_value;
    int *it = iterator;
    if (*it < SUFFIX_TREE_NODE_CHILDS_AMOUNT)
        return_value = &((SuffixTreeNode*)node)->next_nodes[*it];
    else
        return_value = NULL;

    do
    {
        ++(*it);
    } while (*it < SUFFIX_TREE_NODE_CHILDS_AMOUNT && !isSuffixTreeNodeActive(&((SuffixTreeNode*)node)->next_nodes[*it]));

    return return_value;
}

void * void_getSuffixTreeNodeIterator(const void * node)
{
    void * it = -1;
    void_indexateNextSuffixTreeNode(node, &it);
    return it;
}
const void * void_getAdditionalRef(const void * node, void ** iterator)
{
    if (! (*(bool*)iterator))
    {
        if (((SuffixTreeNode*)node)->suff_ref != NULL)
             assert(isSuffixTreeNodeActive(((SuffixTreeNode*)node)->suff_ref));
        *((bool*)iterator) = true;
        return ((SuffixTreeNode*)node)->suff_ref;
    }
    else
        return NULL;
}

void * void_getAdditionalRefToSuffixTreeNodeIterator(const void * node)
{
    bool *iterator = false;

    return iterator;
}

TreeAPI getSuffixTreeApi()
{
    TreeAPI api = {&void_getSuffixTreeNodeName,
                   &void_getSuffixTreeNodeLabel,
                   &void_indexateNextSuffixTreeNode,
                   &void_getSuffixTreeNodeIterator,
                   &void_getAdditionalRef,
                   &void_getAdditionalRefToSuffixTreeNodeIterator,
                   NULL,
                   NULL};
    return api;
}