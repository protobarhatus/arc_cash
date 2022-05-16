#ifndef FIBONACHY_NIM_AUTOCHECKER_H
#define FIBONACHY_NIM_AUTOCHECKER_H

#include "hashtable/hash_table.h"
#include "arc_cache.h"
#include "frc_cache.h"

/* this class is for checking if ArcCache algorithm is working properly and doesn't break some basic rules
 * to use, just instead of using checkOutPageArcCache and then deactArcCache call checkInput with number of next
 * page (dont need to initialize)
 *
 * also it can check FcrCache - then it should be called by checkInputFcr.
 * set of errors its a bit different
 *
 * if cache passes the checks, returns RES_OK.
 * otherwise returns these values if these checks are failed:
 * RES_ACR_T_INVALID_SIZE - if |T1| + |T2| > c - for only ARC
 * RES_ACR_DBL_INVALID_SIZE - if |L1| + |L2| > 2c - for only ARC
 *
 * RES_T1_MISS - if after checkOutPage, page, that should go to T1 didnt appear there - for both
 * RES_T2_MISS - if after checkOutPage, page, that should go to T2 didnt appear there - for both
 *
 * RES_WRONG_ANSWER - if page was located in T1 or T2, but cache didn't find it OR if page wasnt located - for both
 * in T1 or T2, but cache sad its in cache
 *
 * RES_ACR_NOT_EMPTY_B_WHILE_CASH_IS_NOT_FILLED - if |T1| + |T2| < c, but B1 or B2 is/are not empty - for only ARC
 * RES_ACR_T_ARE_NOT_C_WHILE_CASH_IS_FILLED - if |L1| + |L2| >= c, but |T1| + |T2| != c - for only ARC
 * RES_ACR_DBL_SIZE_SUDDENLY_DECREASED - if |L1|+|L2| after checkOutPage appeared LESS then if was - for only ARC
 *
 * RES_FCR_T1_WRONG_SIZE - if |T1| > p - for only FCR
 * RES_FCR_T2_WRONG_SIZE - if |T2| > c - p - for only FCR
 * RES_FCR_L_WRONG_SIZE - if |L1| > c or |L2| > c - for only FCR
 * */

typedef struct {
    HashTableInt T1, T2, B1, B2;
} CacheLog;

CacheLog defaultCacheLog(const ArcCache * cache);
CacheLog defaultCacheLogFcr(const FcrCache * cache);
void destructCacheLog(CacheLog * log);

typedef enum {
    RES_OK,
    RES_ACR_T_INVALID_SIZE,
    RES_ACR_DBL_INVALID_SIZE,
    RES_T1_MISS,
    RES_T2_MISS,
    RES_WRONG_ANSWER,
    RES_ACR_NOT_EMPTY_B_WHILE_CASH_IS_NOT_FILLED,
    RES_ACR_T_ARE_NOT_C_WHILE_CASH_IS_FILLED,
    RES_ACR_DBL_SIZE_SUDDENLY_DECREASED,

    RES_FCR_T1_WRONG_SIZE,
    RES_FCR_T2_WRONG_SIZE,
    RES_FCR_L_WRONG_SIZE,
} CheckResult;

typedef struct {
    CacheLog old;
    CacheLog new;
    int c;
    int page;
    int p;
    bool answer;
    bool is_fcr;
} Checker;

Checker initializeChecker(const ArcCache *cache);
Checker initializeFcrChecker(const FcrCache *cache);
void setAnswer(Checker *ch, bool ans, int page);
CheckResult checkCacheResult(Checker *ch, const ArcCache * cache);
CheckResult checkCacheFcrResult(Checker *ch, const FcrCache *cache);
void destructChecker(Checker *ch);

CheckResult checkInput(ArcCache *cache, int page, bool print_cache);
CheckResult checkInputFcr(FcrCache *cache, int page, bool print_cache);

#endif //FIBONACHY_NIM_AUTOCHECKER_H
