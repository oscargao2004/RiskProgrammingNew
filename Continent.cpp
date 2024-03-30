#include "Continent.h"

int Continent::controlValue()
{
    return _controlValue;
}

std::vector<Country*> Continent::countries()
{
    return _countries;
}


Continent::Continent()
{
}
