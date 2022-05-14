#include "arc_cash.h"
#include "user_interacts/user_interactions.h"
#include "AutoChecker.h"
int main()
{
    setbuf(stdout, 0);
    int c = scanfInt();
    ArcCash cash = defaultArcCash(c, 1000);
    while(true)
    {
        int x = scanfInt();
        if (x == -1)
            break;
        /*Page p = defaultPage(x, NULL);
        if (checkOutPageArcCash(&cash, x))
        {
            printf("Cash hit\n");
        }
        else
        {
            printf("Cash miss, added\n");
        }
        printfCashState(&cash);
        deactArcCash(&cash);*/

        if (checkInput(&cash, x, true) == RES_OK)
        {
            printf("\nOK\n");
        }
        else
            printf("SHIT\n");
    }
    destructArcCash(&cash);
}
