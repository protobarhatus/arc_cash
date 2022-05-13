set(STRING cstring_func.h
        cstring_func.c
        prefix_tree.h
        prefix_tree.c
        ../string/string.c
        ../string/string.h
        suffix_tree.h
        suffix_tree.c)

list(TRANSFORM STRING PREPEND string/)


add_definitions(-DALPHABET_SIZE=26 -DALPHABET_START='a')