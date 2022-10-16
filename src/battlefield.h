#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <vector>
#include <thread>


class BattleField
{
public:
    // constructor / desctructor
    ~BattleField();

protected:

    std::vector<std::thread> threads; // holds all threads that have been launched within this object
    
};

#endif