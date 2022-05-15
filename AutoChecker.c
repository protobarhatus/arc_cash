

#include "AutoChecker.h"
#include "fcr_cache.h"

HashTableInt ditListToHashTable(const ComArr * comar, const DirList * list) {

    HashTableInt res = defaultHashTableInt();
    for (DirListIterator it = firstDirList(list); it != endDirList(); it = iterateDirList(comar, it))
        addElementHashTableInt(&res, nodeData(comar, it)->page);
    return res;
}

CacheLog defaultCacheLog(const ArcCache * cache) {

    CacheLog res;
    res.T1 = ditListToHashTable(cache->dbl_store, &cache->T1);
    res.T2 = ditListToHashTable(cache->dbl_store, &cache->T2);
    res.B1 = ditListToHashTable(cache->dbl_store, &cache->B1);
    res.B2 = ditListToHashTable(cache->dbl_store, &cache->B2);
    return res;
}
CacheLog defaultCacheLogFcr(const FcrCache * cache) {

    CacheLog res;
    res.T1 = ditListToHashTable(cache->dbl_store, &cache->T1);
    res.T2 = ditListToHashTable(cache->dbl_store, &cache->T2);
    res.B1 = ditListToHashTable(cache->dbl_store, &cache->B1);
    res.B2 = ditListToHashTable(cache->dbl_store, &cache->B2);
    return res;
}
void destructCacheLog(CacheLog * log) {

    destructHashTableInt(&log->T1);
    destructHashTableInt(&log->T2);
    destructHashTableInt(&log->B1);
    destructHashTableInt(&log->B2);
}

Checker initializeChecker(const ArcCache * cache) {

    Checker res;
    res.old = defaultCacheLog(cache);
    res.c = cache->c;
    res.is_fcr = false;
    res.p = 0;
    return res;
}

Checker initializeFcrChecker(const FcrCache * cache) {

    Checker res;
    res.old = defaultCacheLogFcr(cache);
    res.c = cache->c;
    res.is_fcr = true;
    res.p = cache->p;
    return res;
}

void setAnswer(Checker * ch, bool ans, int page) {

    ch->answer = ans;
    ch->page = page;
}

static bool inTable(int what, HashTableInt * table) {

    return !isEndHashTableInt(table, atHashTableInt(table, what));
}

static bool inLog(int what, CacheLog * log) {

    return inTable(what, &log->T1) || inTable(what, &log->T2) || inTable(what, &log->B1) || inTable(what, &log->B2);
}

static int absL1(const CacheLog * cache) {

    return cache->T1.amount_of_elements + cache->B1.amount_of_elements;
}
static int absL2(const CacheLog * cache) {

    return cache->T2.amount_of_elements + cache->B2.amount_of_elements;
}

CheckResult checkCacheResult(Checker * ch, const ArcCache * cache) {

    assert(!ch->is_fcr);
    ch->new = defaultCacheLog(cache);
    if (ch->new.T1.amount_of_elements + ch->new.T2.amount_of_elements > ch->c)
        return RES_ACR_T_INVALID_SIZE;
    if (absL1(&ch->new) + absL2(&ch->new)
                > 2*ch->c)
        return RES_ACR_DBL_INVALID_SIZE;

    if ((inTable(ch->page, &ch->old.T1) || inTable(ch->page, &ch->old.T2)) && ch->answer == false)
        return RES_WRONG_ANSWER;
    if (!inTable(ch->page, &ch->old.T1) && !inTable(ch->page, &ch->old.T2) && ch->answer == true)
        return RES_WRONG_ANSWER;

    if (inLog(ch->page, &ch->old) && !inTable(ch->page, &ch->new.T2))
        return RES_T2_MISS;
    if (!inLog(ch->page, &ch->old) && !inTable(ch->page, &ch->new.T1))
        return RES_T1_MISS;

    if (absL1(&ch->new) + absL2(&ch->new) < ch->c) {

        if (ch->new.B1.amount_of_elements > 0 || ch->new.B2.amount_of_elements > 0)
            return RES_ACR_NOT_EMPTY_B_WHILE_CASH_IS_NOT_FILLED;
    }
    else {

        if (ch->new.T1.amount_of_elements + ch->new.T2.amount_of_elements != ch->c)
            return RES_ACR_T_ARE_NOT_C_WHILE_CASH_IS_FILLED;
    }

    if (absL1(&ch->old) + absL2(&ch->old) > absL1(&ch->new) + absL2(&ch->new))
        return RES_ACR_DBL_SIZE_SUDDENLY_DECREASED;

    return RES_OK;
}

CheckResult checkCacheFcrResult(Checker * ch, const FcrCache * cache) {

    assert(ch->is_fcr);
    ch->new = defaultCacheLogFcr(cache);

    if ((inTable(ch->page, &ch->old.T1) || inTable(ch->page, &ch->old.T2)) && ch->answer == false)
        return RES_WRONG_ANSWER;
    if (!inTable(ch->page, &ch->old.T1) && !inTable(ch->page, &ch->old.T2) && ch->answer == true)
        return RES_WRONG_ANSWER;

    if (inLog(ch->page, &ch->old) && !inTable(ch->page, &ch->new.T2))
        return RES_T2_MISS;
    if (!inLog(ch->page, &ch->old) && !inTable(ch->page, &ch->new.T1))
        return RES_T1_MISS;


    if (ch->new.T1.amount_of_elements > ch->p)
        return RES_FCR_T1_WRONG_SIZE;
    if (ch->new.T2.amount_of_elements > ch->c - ch->p)
        return RES_FCR_T2_WRONG_SIZE;
    if (absL1(&ch->new) > ch->c || absL2(&ch->new) > ch->c)
        return RES_FCR_L_WRONG_SIZE;

    return RES_OK;
}

void destructChecker(Checker * ch) {

    destructCacheLog(&ch->old);
    destructCacheLog(&ch->new);
}

CheckResult checkInput(ArcCache * cache, int page, bool print) {

    Checker checker = initializeChecker(cache);
    setAnswer(&checker, checkOutPageArcCache(cache, page), page);
    deactArcCache(cache);
    printfCacheState(cache);
    CheckResult res = checkCacheResult(&checker, cache);
    destructChecker(&checker);
    return res;
}

CheckResult checkInputFcr(FcrCache * cache, int page, bool print_cache) {

    Checker checker = initializeFcrChecker(cache);
    setAnswer(&checker, checkOutPageFcrCache(cache, page), page);
    printfFcrCacheState(cache);
    CheckResult res = checkCacheFcrResult(&checker, cache);
    destructChecker(&checker);
    return res;
}