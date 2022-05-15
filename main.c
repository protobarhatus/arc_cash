#include "arc_cache.h"
#include "user_interacts/user_interactions.h"
#include "AutoChecker.h"
int main()
{
    setbuf(stdout, 0);
    int c = scanfInt();
    FcrCache cash = defaultFcrCache(c, 2, 1000);
    while(true)
    {
        int x = scanfInt();
        if (x == -1)
            break;
        /*Page p = defaultPage(x, NULL);
        if (checkOutPageArcCache(&cash, x))
        {
            printf("Cash hit\n");
        }
        else
        {
            printf("Cash miss, added\n");
        }
        printfCacheState(&cash);
        deactArcCache(&cash);*/
        CheckResult res;
        if ((res = checkInputFcr(&cash, x, true)) == RES_OK)
        {
            printf("\nOK\n");
        }
        else
        {
            printf("SHIT %d\n", res);
            getchar();
        }
    }
    destructFcrCache(&cash);
}
