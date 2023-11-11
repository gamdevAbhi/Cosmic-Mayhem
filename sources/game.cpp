#include <engine/gameloop.hpp>

#include "spritemanager.hpp"
#include "scenemanager.hpp"

void initializeRelation()
{
    // creating tags for colliders
    int spaceship = Engine::ColliderManager::addTag("Space Ship", false);
    int bullet = Engine::ColliderManager::addTag("Bullet", false);
    int collectibles = Engine::ColliderManager::addTag("Collectibles", false);
    int asteroid = Engine::ColliderManager::addTag("Asteroid", true);
    // adding relations to the tags
    Engine::ColliderManager::addRelation(spaceship, collectibles);
    Engine::ColliderManager::addRelation(spaceship, asteroid);
    Engine::ColliderManager::addRelation(bullet, asteroid);
}

int main()
{
    // for hiding the console
    // console is not hidden by default
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    // initializing the game engine
    // always call it before using any game engine features
    Engine::GameLoop::initialize("Cosmic Mayhem");
    // initialize colliders relation
    // will only check collision based on relation
    // relation can improve performance as it ignore unnecessary collision checks
    initializeRelation();
    // loading sprites so we can use it in other places
    Cosmic::SpriteManager::loadSprites();
    // loading tech scene
    Cosmic::SceneManager::loadTechScene();
    // begin start the gameloop
    Engine::GameLoop::begin();
    // checking if game terminated succesfully
    std::cout << std::endl << "Succesfully Close ..." << std::endl;
    return 0;
}