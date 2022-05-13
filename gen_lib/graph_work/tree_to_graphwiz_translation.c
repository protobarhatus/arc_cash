#include "tree_to_graphwiz_translation.h"
#include "user_interacts/user_interactions.h"
String makeNameForTreeNode(const String * parent_name, int index)
{
    return concatStringLVRV(parent_name, concatStringRV(stringFromChar('_'), intToString(index)));
}

String getNodesInternalName(const void * node)
{
    return concatStringRV(defaultString("node"), intToStringInBase(node, 16));
}

void recursiveScanTreeForGraphwiz(const void * node, TreeAPI api,
                                  String * str, int level, const String * parent_name)
{
    int counter = 0;
    const void * next_node;

    void * iterator = api.indexator_func(node);

    if (api.name_func == NULL)
        concatToStringRV(str, concatStringRV(getNodesInternalName(node), defaultString(" [label=\"\", shape=point]\n")));
    else
        concatToStringRV(str, concatStringRV(getNodesInternalName(node),
                                             concatStringRV(defaultString(" [label=\""), concatStringRV(api.name_func(node),
                                                                                                        defaultString("\"]\n")))));

    while ((next_node = api.next_node_func(node, &iterator)) != NULL)
    {
        concatToStringRV(str, defaultString("\t"));
        concatToString(str, parent_name);
        concatToStringRV(str, defaultString(" -> "));
        String list_name = getNodesInternalName(next_node);
        concatToString(str, &list_name);
        concatToStringRV(str, defaultString(" [label=\""));
        concatToStringRV(str, api.label_func(next_node));
        concatToStringRV(str, defaultString("\"];\n"));
        recursiveScanTreeForGraphwiz(next_node, api, str, level + 1, &list_name);
        destructString(&list_name);
        ++counter;
    }

    if (api.additional_ref_func != NULL)
    {
        void * additional_ref_iterator = api.additional_ref_indexator_func(node);
        const void * add_ref;
        while ((add_ref = api.additional_ref_func(node, &additional_ref_iterator)) != NULL)
        {

            concatToStringRV(str, defaultString("\t"));
            concatToString(str, parent_name);
            concatToStringRV(str, defaultString(" -> "));
            concatToStringRV(str, getNodesInternalName(add_ref));
            concatToStringRV(str, defaultString(" [style=dashed]\n"));

        }
        if (api.destruct_additional_ref_iterator_func != NULL)
            api.destruct_additional_ref_iterator_func(&additional_ref_iterator);
    }

    if (api.destruct_indexator_func != NULL)
        api.destruct_indexator_func(&iterator);
}

String treeToGraphwiz(const void * tree, TreeAPI api)
{
    String res = defaultString("digraph G {\n");

    String par_name = getNodesInternalName(tree);
    recursiveScanTreeForGraphwiz(tree, api, &res, 0, &par_name);
    destructString(&par_name);

    concatToStringRV(&res, defaultString("}"));

    return res;

}

void showTreeInGraphwiz(const void * tree, const char * filename, TreeAPI api)
{
    String str = treeToGraphwiz(tree, api);

    String file_name = concatStringRV(defaultString(filename), defaultString(".dot"));
    String graph_name = concatStringRV(defaultString(filename), defaultString(".png"));
    saveAsFile(str.string, file_name.string);

    String command = concatStringRV(defaultString("dot -Tpng "), concatStringLVRV(&file_name, concatStringRVLV(
            defaultString(" -o "), &graph_name)));

    String actual_command = concatStringRV(defaultString("PowerShell.exe -Command \""), concatStringLVRV(&command,
                                                                                                     defaultString("\"")));
    system(actual_command.string);

    String graph_name_command = concatStringRV(defaultString("PowerShell.exe -Command \"start "), concatStringLVRV(&graph_name,
                                                                                                         defaultString("\"")));

    system(graph_name_command.string);

    destructString(&actual_command);
    destructString(&graph_name_command);

    destructString(&str);
    destructString(&file_name);
    destructString(&graph_name);
    destructString(&command);
}