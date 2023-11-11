#include "health.hpp"

void Cosmic::Health::setHealth(int value)
{
    maxHealth = value;
    health = value;
}

void Cosmic::Health::addHealth(int value)
{
    health += value;
    if(health > maxHealth) health = maxHealth;
}

void Cosmic::Health::addDamage(int value)
{
    health -= value;
    if(health < 0) health = 0;
}

int Cosmic::Health::getHealth()
{
    return health;
}

void Cosmic::Health::update()
{
    if(health <= 0 && shouldDestroy) getActor()->setDestroy(true);
}