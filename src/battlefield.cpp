#include <algorithm>
#include <iostream>
#include <chrono>
#include "battlefield.h"

BattleField::~BattleField()
{
    // set up thread barrier before this object is destroyed
    std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
        t.join();
    });
}
