#pragma once

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

#define SAFEMODE        // checks for overflows, invalid arguments etc.
typedef enum {
    FREE_END = -1,
    DESTROYED_COM_ARR = -2,
    END_OF_DIR_LIST = -3
} EXCEPTION_CODES;

#define NLISTS 4
#define NO_PERMISSION_ADDR (Node *) 1

typedef enum {
    T1_FICT_IDX = 0,
    B1_FICT_IDX = 1,
    T2_FICT_IDX = 2,
    B2_FICT_IDX = 3,
    FREE_NODE   = -1
} FICT_IDX;
typedef int DirListIterator;

// some of extern headers should include the PageId struct definition
// only pointers to PageId are used, no actual construction or destruction performed

typedef struct {
    DirListIterator next;
    DirListIterator prev;
    FICT_IDX fict;
    const PageId *page;
} Node;

typedef struct {
    int capacity;
    DirListIterator free_list_head;
    Node *data;
} ComArr;

typedef struct {
    int size;
    DirListIterator fict;
    ComArr *common_arr;
} DirList;

ComArr initComArr(int c);
ComArr copyComArr(const ComArr *src);
void destrComArr(ComArr *common_arr);

DirList getT1(const ComArr *common_arr);
DirList getT2(const ComArr *common_arr);
DirList getB1(const ComArr *common_arr);
DirList getB2(const ComArr *common_arr);
DirList copyDirList(const DirList *src);

int sizeDirList(const DirList *list);
DirListIterator pushBack(DirList *list, const PageId *page);
DirListIterator pushFront(DirList *list, const PageId *page);
void eraseNode(DirList *list, DirListIterator idx);
void moveNodeToBegin(DirList *dest_list, DirListIterator src_idx);
void moveNodeToEnd(DirList *dest_list, DirListIterator src_idx);

DirListIterator endDirList();
DirListIterator firstDirList(const DirList *list);
DirListIterator lastDirList(const DirList *list);
DirListIterator iterateDirList(const ComArr *common_arr, DirListIterator idx);
const PageId *nodeData(const ComArr *common_arr, DirListIterator idx);
bool isInDirList(const DirList *list, DirListIterator idx);
