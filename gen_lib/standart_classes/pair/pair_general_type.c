#include "pair_general_type.h"

Pair defaultPair(const Type1 * t1, const Type2 * t2)
{
    Pair res;
    res.first = copyType1(t1);
    res.second = copyType2(t2);
    return res;
}
Pair defaultPairLVRV(const Type1 * t1, Type2 t2)
{
    Pair res;
    res.first = copyType1(t1);
    res.second = t2;
    return res;
}
Pair defaultPairRVLV(Type1 t1, const Type2 * t2)
{
    Pair res;
    res.first = t1;
    res.second = copyType2(t2);
    return res;
}
Pair defaultPairRV(Type1 t1, Type2 t2)
{
    Pair res;
    res.first = t1;
    res.second = t2;
    return res;
}

Pair copyPair(const Pair * p)
{
    Pair res;
    res.first = copyType1(&p->first);
    res.second = copyType2(&p->second);
    return res;

}

void destructPair(Pair * p)
{
    destructType1(&p->first);
    destructType2(&p->second);

}

Pair movePair(Pair * p)
{
    Pair res;
    res.first = moveType1(&p->first);
    res.second = moveType2(&p->second);
    return res;
}