#include "spritemanager.hpp"

void Cosmic::SpriteManager::loadSprites()
{
    spaceship = new Engine::Sprite("\\resources\\sprites\\Spaceship.png");
    bullet = new Engine::Sprite("\\resources\\sprites\\Bullets.png");
    backBoost = new Engine::Sprite("\\resources\\sprites\\Back Boost.png");
    frontBoost = new Engine::Sprite("\\resources\\sprites\\Front Boost.png");
    leftBoost = new Engine::Sprite("\\resources\\sprites\\Left Boost.png");
    rightBoost = new Engine::Sprite("\\resources\\sprites\\Right Boost.png");
    muzzle = new Engine::Sprite("\\resources\\sprites\\Muzzle.png");
    asteroid = new Engine::Sprite("\\resources\\sprites\\Asteroid.png");
    collectible = new Engine::Sprite("\\resources\\sprites\\Collectible.png");
}