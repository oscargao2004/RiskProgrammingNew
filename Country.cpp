#include "Country.h"

void Country::deployArmies(int num)
{
    _deployedArmies += num;
}

std::vector<Country*> Country::adjCountries()
{
    return _adjCountries;
}

Player* Country::owner()
{
    return &_owner;
}

void Country::setOwner(Player& p)
{   
    for (int i = 0; i < _owner.ownedCountries().size(); i++)
    {
        if (_owner.ownedCountries()[i] == this)
        {
            _owner._ownedCountries.erase(_owner._ownedCountries.begin() + i);
        }
    }
    p._ownedCountries.push_back(this);
    _owner = p;
}

Continent Country::continent()
{
    return _continent;
}
