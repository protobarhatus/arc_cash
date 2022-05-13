set(STANDART_CLASSES_PATH gen_lib/standart_classes/)

include(${STANDART_CLASSES_PATH}pair/CMakeLists.txt)
include(${STANDART_CLASSES_PATH}string/CMakeLists.txt)
include(${STANDART_CLASSES_PATH}hashtable/CMakeLists.txt)
include(${STANDART_CLASSES_PATH}list/CMakeLists.txt)
include(${STANDART_CLASSES_PATH}hashtable/CMakeLists.txt)

set(STANDART_CLASSES
        ${STRING}
        ${PAIR}
        ${HASH_TABLE}
        ${LIST}
        ${HASH_TABLE})

include_directories(${STANDART_CLASSES_PATH})


list(TRANSFORM STANDART_CLASSES PREPEND standart_classes/)

