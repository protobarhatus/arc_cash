
#ifndef FIBONACHY_NIM_AUTOCHECKER_H
#define FIBONACHY_NIM_AUTOCHECKER_H

#include "arc_cash.h"
#include "hashtable/hash_table.h"

typedef struct {

    HashTableInt T1, T2, B1, B2;
} CashLog;

CashLog defaultCashLog(const ArcCash * cash);
void destructCashLog(CashLog * log);

typedef enum {
    RES_OK,
    RES_T_INVALID_SIZE,
    RES_DLC_INVALID_SIZE,
    RES_T1_MISS,
    RES_T2_MISS,
    RES_WRONG_ANSWER
} CheckResult;

typedef struct {
    CashLog old;
    CashLog new;
    int c;
    bool answer;
    int page;
} Checker;

Checker initializeChecker(const ArcCash * cash);
void setAnswer(Checker * ch, bool ans, int page);
CheckResult checkCashResult(Checker * ch, const ArcCash * cash);
void destructChecker(Checker * ch);

CheckResult checkInput(ArcCash * cash, int page, bool print_cash);
#endif //FIBONACHY_NIM_AUTOCHECKER_H
