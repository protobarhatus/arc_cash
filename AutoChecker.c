

#include "AutoChecker.h"

HashTableInt ditListToHashTable(const ComArr * comar, const DirList * list) {

    HashTableInt res = defaultHashTableInt();
    for (DirListIterator it = firstDirList(list); it != endDirList(); it = iterateDirList(comar, it))
        addElementHashTableInt(&res, nodeData(comar, it)->page);
    return res;
}

CashLog defaultCashLog(const ArcCash * cash) {

    CashLog res;
    res.T1 = ditListToHashTable(cash->dlc_store, &cash->T1);
    res.T2 = ditListToHashTable(cash->dlc_store, &cash->T2);
    res.B1 = ditListToHashTable(cash->dlc_store, &cash->B1);
    res.B2 = ditListToHashTable(cash->dlc_store, &cash->B2);
    return res;
}

void destructCashLog(CashLog * log) {

    destructHashTableInt(&log->T1);
    destructHashTableInt(&log->T2);
    destructHashTableInt(&log->B1);
    destructHashTableInt(&log->B2);
}

Checker initializeChecker(const ArcCash * cash) {

    Checker res;
    res.old = defaultCashLog(cash);
    res.c = cash->c;
    return res;
}

void setAnswer(Checker * ch, bool ans, int page) {

    ch->answer = ans;
    ch->page = page;
}

static bool inTable(int what, HashTableInt * table) {

    return !isEndHashTableInt(table, atHashTableInt(table, what));
}

static bool inLog(int what, CashLog * log) {

    return inTable(what, &log->T1) || inTable(what, &log->T2) || inTable(what, &log->B1) || inTable(what, &log->B2);
}
CheckResult checkCashResult(Checker * ch, const ArcCash * cash) {

    ch->new = defaultCashLog(cash);
    if (ch->new.T1.amount_of_elements + ch->new.T2.amount_of_elements > ch->c)
        return RES_T_INVALID_SIZE;
    if (ch->new.T1.amount_of_elements + ch->new.T2.amount_of_elements + ch->new.B2.amount_of_elements + ch->new.B1.amount_of_elements
                > 2*ch->c)
        return RES_DLC_INVALID_SIZE;

    if ((inTable(ch->page, &ch->old.T1) || inTable(ch->page, &ch->old.T2)) && ch->answer == false)
        return RES_WRONG_ANSWER;
    if (!inTable(ch->page, &ch->old.T1) && !inTable(ch->page, &ch->old.T2) && ch->answer == true)
        return RES_WRONG_ANSWER;

    if (inLog(ch->page, &ch->old) && !inTable(ch->page, &ch->new.T2))
        return RES_T2_MISS;
    if (!inLog(ch->page, &ch->old) && !inTable(ch->page, &ch->new.T1))
        return RES_T1_MISS;
    return RES_OK;
}

void destructChecker(Checker * ch) {

    destructCashLog(&ch->old);
    destructCashLog(&ch->new);
}

CheckResult checkInput(ArcCash * cash, int page, bool print) {

    Checker checker = initializeChecker(cash);
    setAnswer(&checker, checkOutPageArcCash(cash, page), page);
    deactArcCash(cash);
    printfCashState(cash);
    CheckResult res = checkCashResult(&checker, cash);
    destructChecker(&checker);
    return res;
}