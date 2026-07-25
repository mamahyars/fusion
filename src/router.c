#include <stdio.h>

#include "../include/router.h"


NetworkInterface* select_best_interface(
    NetworkInterface *list,
    int count
)
{
    NetworkInterface *best = NULL;


    for (int i = 0; i < count; i++)
    {
        if (!list[i].active)
            continue;


        if (best == NULL ||
            list[i].speed > best->speed)
        {
            best = &list[i];
        }
    }


    return best;
}