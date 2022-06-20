#ifndef FIBONACHY_NIM_PAGE_H
#define FIBONACHY_NIM_PAGE_H

#include <stdbool.h>

#define PAGE_SIZE 60

typedef struct {
    int number;
    char *data;
} Page;

typedef Page Page_Ref;
typedef Page PageRef;

Page copyPage(const Page *page);
Page movePage(Page *page);
void destructPage(Page *page);
bool equalPage(const Page *a, const Page *b);
Page defaultPage(int num, const char *data);

#endif // FIBONACHY_NIM_PAGE_H
