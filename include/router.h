#ifndef ROUTER_H
#define ROUTER_H

#include "interface.h"

NetworkInterface* select_best_interface(
    NetworkInterface *list,
    int count
);

#endif