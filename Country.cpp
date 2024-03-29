#include "Country.h"

void Country::deployArmies(int num)
{
    _deployedArmies += num;
}

Player* Country::owner()
{
    return &_owner;
}

Continent Country::continent()
{
    return _continent;
}
