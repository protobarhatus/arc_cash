#include <malloc.h>
#include "Page.h"
#include "memory.h"
#include "stdbool.h"

Page copyPage(const Page * page)
{
    Page res;
    res.number = page->number;
    if (page->data == NULL)
        res.data = NULL;
    else
    {
        res.data = calloc(PAGE_SIZE, sizeof(char));
        memcpy(res.data, page->data, PAGE_SIZE);
    }

    return res;
}
Page movePage(Page * page)
{
    Page res;
    res.number = page->number;
    res.data = page->data;
    page->data = NULL;
    return res;
}
void destructPage(Page * page)
{
    free(page->data);
    page->data = NULL;
}
bool equalPage(const Page * a, const Page * b)
{
    return a->number == b->number;
}
Page defaultPage(int num, const char * data)
{
    Page res;
    res.number = num;
    if (data == NULL)
        res.data = NULL;
    else
    {
        res.data = calloc(PAGE_SIZE, sizeof(char));
        memcpy(res.data, data, PAGE_SIZE);
    }
    return res;
}
