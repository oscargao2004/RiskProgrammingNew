#include "Player.h"
#include "Country.h"

int Player::armies()
{
    return _numArmies;
}

void Player::addArmies(int num)
{
    _numArmies += num;
}

void Player::subtractArmies(int num)
{
    _numArmies -= num;
}

void Player::setArmies(int num)
{
    _numArmies = num;
}

std::vector<Country*> Player::ownedCountries()
{
    return _ownedCountries;
}

int Player::numOwnedCountries()
{
    return _ownedCountries.size();
}

void Player::deploy(Country &country, int num)
{
    try
    {
        if (num <= _numArmies)
        {
            _numArmies -= num;
            country._deployedArmies += num;

            std::cout << "Successfully deployed " << num << " armies to " << country._name << std::endl;
        }
        else
        {
            throw std::runtime_error("You cannot deploy more armies than you have, try again.\n");
        }
    }
    catch (const std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;

        int choice;
        std::cin >> choice;
        deploy(country, choice);
    }
}

