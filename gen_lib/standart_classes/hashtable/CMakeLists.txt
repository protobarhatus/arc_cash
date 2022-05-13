set(HASH_TABLE hash_table_general_type.c
        hash_table_general_type.h
        hash_table_def.h
        hash_table.h
        hash_table.c
        hashmap_general_type.h
        hashmap_general_type.c
        hashmap_def.h
        hashmap.h)


list(TRANSFORM HASH_TABLE PREPEND hashtable/)