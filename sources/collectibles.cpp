#include "collectibles.hpp"

int Cosmic::Collectibles::getCount()
{
    return counts;
}

void Cosmic::Collectibles::update()
{
    glm::vec2 targetPos = target->getPosition(true);
    glm::vec2 pos = transform->getPosition(true);

    if(glm::length(targetPos - pos) >= maxLength) getActor()->setDestroy();
}

void Cosmic::Collectibles::onDestroy()
{
    counts--;
}