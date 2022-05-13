#pragma once

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>

#define SAFEMODE

#define NLISTS 4
#define FREE_END -1
#define DESTROYED_COM_ARR -4
#define NO_PERMISSION_ADDR 1

enum FICT_IDX {T1_FICT_IDX = 0, B1_FICT_IDX = 1, T2_FICT_IDX = 2, B2_FICT_IDX = 3};

typedef struct {
    char *page;
    int ident;
} PageId;

typedef struct {
    int next;
    int prev;
    PageId page;
} Node;

typedef struct {
    int capacity;
    int free_list_head;
    Node *data;
} ComArr;

typedef struct {
    int size;
    int fict;
    ComArr *common_arr;
} DirList;

ComArr initComArr(int c);
ComArr copyComArr(const ComArr *src);
void destrComArr(ComArr *common_arr);

DirList getT1(ComArr *common_arr);
DirList getT2(ComArr *common_arr);
DirList getB1(ComArr *common_arr);
DirList getB2(ComArr *common_arr);
DirList copyDirList(const DirList *src);

int sizeDirList(const DirList *list);
