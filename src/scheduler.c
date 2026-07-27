#include "../include/scheduler.h"

static int current = 0;

int select_link()
{
    current ^= 1;
    return current;
}