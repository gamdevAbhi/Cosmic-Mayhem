#include "starmanager.hpp"

void Cosmic::StarManager::start()
{
    origin = glm::vec3(0.f);
    target = Engine::Actor::getActor("Space Ship")->getComponent<Engine::Transform>();
    camera = Engine::Camera::getRenderCamera();

    glm::vec2 boundary = camera->getBoundary();
    glm::vec2 difference(2.f * boundary.x, 2.f * boundary.y);

    // creating star region for north west, north and north east
    createRegion(nwStars, origin.x - difference.x, origin.y + difference.y, boundary.x, boundary.y);
    createRegion(nStars, origin.x, origin.y + difference.y, boundary.x, boundary.y);
    createRegion(neStars, origin.x + difference.x, origin.y + difference.y, boundary.x, boundary.y);
    // creating star region for west, center and east
    createRegion(wStars, origin.x - difference.x, origin.y, boundary.x, boundary.y);
    createRegion(cStars, origin.x, origin.y, boundary.x, boundary.y);
    createRegion(eStars, origin.x + difference.x, origin.y, boundary.x, boundary.y);
    // creating star region for south west, south and south east
    createRegion(swStars, origin.x - difference.x, origin.y - difference.y, boundary.x, boundary.y);
    createRegion(sStars, origin.x, origin.y - difference.y, boundary.x, boundary.y);
    createRegion(seStars, origin.x + difference.x, origin.y - difference.y, boundary.x, boundary.y);

    // adjusting top, bottom, left, right
    top = origin.y + boundary.y;
    bottom = origin.y - boundary.y;
    left = origin.x - boundary.x;
    right = origin.x + boundary.x;
}

void Cosmic::StarManager::update()
{
    glm::vec3 pos = target->getWorldPosition();
    glm::vec2 boundary = camera->getBoundary();
    glm::vec2 difference(2.f * boundary.x, 2.f * boundary.y);

    if(pos.x > right)
    {
        // creating new origin
        origin = glm::vec3(right + boundary.x, origin.y, 0.f);
        // removing unnecessary regions
        removeRegion(nwStars);
        removeRegion(wStars);
        removeRegion(swStars);
        // swaping the regions
        nwStars = nStars;
        wStars = cStars;
        swStars = sStars;
        nStars = neStars;
        cStars = eStars;
        sStars = seStars;
        // creating new regions
        neStars.clear();
        eStars.clear();
        seStars.clear();
        createRegion(neStars, origin.x + difference.x, origin.y + difference.y, boundary.x, boundary.y);
        createRegion(eStars, origin.x + difference.x, origin.y, boundary.x, boundary.y);
        createRegion(seStars, origin.x + difference.x, origin.y - difference.y, boundary.x, boundary.y);
        // adjusting top, bottom, left, right
        top = origin.y + boundary.y;
        bottom = origin.y - boundary.y;
        left = origin.x - boundary.x;
        right = origin.x + boundary.x;
    }
    else if(pos.x < left)
    {
        // creating new origin
        origin = glm::vec3(left - boundary.x, origin.y, 0.f);
        // removing unnecessary regions
        removeRegion(neStars);
        removeRegion(eStars);
        removeRegion(seStars);
        // swaping the regions
        neStars = nStars;
        eStars = cStars;
        seStars = sStars;
        nStars = nwStars;
        cStars = wStars;
        sStars = swStars;
        // creating new regions
        nwStars.clear();
        wStars.clear();
        swStars.clear();
        createRegion(nwStars, origin.x - difference.x, origin.y + difference.y, boundary.x, boundary.y);
        createRegion(wStars, origin.x - difference.x, origin.y, boundary.x, boundary.y);
        createRegion(swStars, origin.x - difference.x, origin.y - difference.y, boundary.x, boundary.y);
        // adjusting top, bottom, left, right
        top = origin.y + boundary.y;
        bottom = origin.y - boundary.y;
        left = origin.x - boundary.x;
        right = origin.x + boundary.x;
    }

    if(pos.y > top)
    {
        // creating new origin
        origin = glm::vec3(origin.x, top + boundary.y, 0.f);
        // removing unnecessary regions
        removeRegion(swStars);
        removeRegion(sStars);
        removeRegion(seStars);
        // swaping the regions
        swStars = wStars;
        sStars = cStars;
        seStars = eStars;
        wStars = nwStars;
        cStars = nStars;
        eStars = neStars;
        // creating new regions
        nwStars.clear();
        nStars.clear();
        neStars.clear();
        createRegion(nwStars, origin.x - difference.x, origin.y + difference.y, boundary.x, boundary.y);
        createRegion(nStars, origin.x, origin.y + difference.y, boundary.x, boundary.y);
        createRegion(neStars, origin.x + difference.x, origin.y + difference.y, boundary.x, boundary.y);
        // adjusting top, bottom, left, right
        top = origin.y + boundary.y;
        bottom = origin.y - boundary.y;
        left = origin.x - boundary.x;
        right = origin.x + boundary.x;
    }
    else if(pos.y < bottom)
    {
        // creating new origin
        origin = glm::vec3(origin.x, bottom - boundary.y, 0.f);
        // removing unnecessary regions
        removeRegion(nwStars);
        removeRegion(nStars);
        removeRegion(neStars);
        // swaping the regions
        nwStars = wStars;
        nStars = cStars;
        neStars = eStars;
        wStars = swStars;
        cStars = sStars;
        eStars = seStars;
        // creating new regions
        swStars.clear();
        sStars.clear();
        seStars.clear();
        createRegion(swStars, origin.x - difference.x, origin.y - difference.y, boundary.x, boundary.y);
        createRegion(sStars, origin.x, origin.y - difference.y, boundary.x, boundary.y);
        createRegion(seStars, origin.x + difference.x, origin.y - difference.y, boundary.x, boundary.y);
        // adjusting top, bottom, left, right
        top = origin.y + boundary.y;
        bottom = origin.y - boundary.y;
        left = origin.x - boundary.x;
        right = origin.x + boundary.x;
    }
}

void Cosmic::StarManager::createRegion(std::vector<Engine::Actor*>& vec, float x, float y, float top, float right)
{
    int regionMax = min + std::rand() % (max - min);

    while(vec.size() < regionMax)
    {
        glm::vec3 origin(0.f);
        origin.x = (x - top) + ((std::rand() % 100) / 100.f) * (top * 2.f);
        origin.y = (y - right) + ((std::rand() % 100) / 100.f) * (right * 2.f);
        
        Engine::Actor* star = Engine::Actor::createActor("star");
        Engine::SpriteRenderer* renderer = star->addComponent<Engine::SpriteRenderer>();
        renderer->setOrder(2);
        
        star->getComponent<Engine::Transform>()->setWorldPosition(origin);
        star->getComponent<Engine::Transform>()->setWorldScale(glm::vec3(0.15f, 0.15f, 1.f));
        
        if(std::rand() % 100 > 50) renderer->setSprite(SpriteManager::star);
        else renderer->setSprite(SpriteManager::brightStar);

        vec.push_back(star);
    }
}

void Cosmic::StarManager::removeRegion(std::vector<Engine::Actor*>& vec)
{
    for(int i = 0; i < vec.size(); i++) vec[i]->setDestroy();

    vec.clear();
}