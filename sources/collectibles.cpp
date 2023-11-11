#include "collectibles.hpp"

int Cosmic::Collectibles::getCount()
{
    return counts;
}

void Cosmic::Collectibles::update()
{
    glm::vec2 targetPos = target->getWorldPosition();
    glm::vec2 pos = transform->getWorldPosition();

    if(glm::length(targetPos - pos) >= maxLength) getActor()->setDestroy(true);
}

void Cosmic::Collectibles::onDestroy()
{
    counts--;
}