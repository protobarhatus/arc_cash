#ifndef CACHEDIR_INCLUDED
#define CACHEDIR_INCLUDED

/* This module contains a bunch of utilities for creating and operating with
 * an ARC cache directory, performing the DBL(2c) replacement policy. Basically,
 * the directory consists of 4 doubly-linked cyclic lists (DirList type) with
 * ability to transfer nodes between each of them. The lists are implemented in
 * a cache-friendly style, all the the nodes are stored in a common node array
 * (ComArr type), connections between them are provided with the index system.
 * Every node contains a pointer to a data structure called PageId, which can
 * represent any possible standardized cached piece of information. Total lists
 * capacity is strictly 2c - an attempt to push more nodes will lead to an
 * immediate error. Free nodes are stored in the same directory and ordered as
 * a separate single-linked list, which provides the fastest possible way of
 * getting fresh nodes.
 * */

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

// type representing the page and its location in the cache
typedef struct {
    int page, address;
} PageId;

// enables simple overflow, invalid arguments checks etc.
// undef to slightly boost most of the funcs performed
#define SAFEMODE

typedef enum {
    FREE_END = -1,
    DESTROYED_COM_ARR = -2,
    END_OF_DIR_LIST = -3
} EXCEPTION_CODES;

// indexes of fictive nodes - each node attached to one of 4 lists
typedef enum {
    T1_FICT_IDX = 0,
    B1_FICT_IDX = 1,
    T2_FICT_IDX = 2,
    B2_FICT_IDX = 3,
    FREE_NODE   = -1
} FICT_IDX;

//standard identificator - a way to reach an exact node
typedef int DirListIterator;

// some of extern headers should include the PageId struct definition
// only pointers to PageId are used, no actual construction or destruction performed

typedef struct {
    DirListIterator next, prev;
    FICT_IDX fict;          // a marker of belonging to one of 4 lists
    PageId page;
} Node;

typedef struct {
    int sizes[4];           // respective list's sizes
    int capacity;
    DirListIterator free_list_head;     // an iterator of free-node-list head
    Node *data;
} ComArr;

typedef struct {
    DirListIterator fict;       // an iterator of a fictive node attached to this list 
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

int sizeDirList(const DirList *list);       // get a number of nodes in a list
DirListIterator pushBack(DirList *list, const PageId *page);        // pull a free node and attach it to the list's tail...
DirListIterator pushFront(DirList *list, const PageId *page);       // ...or head
void eraseNode(DirList *list, DirListIterator idx);         // delete a node from a list's chain without breaking the sequnce
void moveNodeToBegin(DirList *dest_list, DirListIterator src_idx);  // move a nove to the head position of any list
void moveNodeToEnd(DirList *dest_list, DirListIterator src_idx);    // ...or the tail position

DirListIterator endDirList();       // invalid pointer, showing that the end of the list reached or some error occured
DirListIterator firstDirList(const DirList *list);      // list's head's iterator
DirListIterator lastDirList(const DirList *list);       // ...and the tail's one
DirListIterator iterateDirList(const ComArr *common_arr, DirListIterator idx);      // get the iterator of the next node in its list
PageId *nodeData(ComArr *common_arr, DirListIterator idx);      // get the PageId pointer through the iterator of the node
bool isInDirList(DirListIterator idx, const DirList *list);     // check the belonging of some node to some list

#endif
