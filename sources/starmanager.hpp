#ifndef COSMIC_STARMANAGER_HPP
#define COSMIC_STARMANAGER_HPP

#include <engine/gameloop.hpp>

#include "spritemanager.hpp"

namespace Cosmic
{
    class StarManager : public Engine::Component
    {
    public:
        void initialize(Engine::Transform* target);
    protected:
        int min = 10, max = 20;
        float top, bottom, left, right;
        glm::vec3 origin;
        Engine::Transform* target;
        Engine::Camera* camera;
        std::vector<Engine::Actor*> nwStars;
        std::vector<Engine::Actor*> nStars;
        std::vector<Engine::Actor*> neStars;
        std::vector<Engine::Actor*> wStars;
        std::vector<Engine::Actor*> cStars;
        std::vector<Engine::Actor*> eStars;
        std::vector<Engine::Actor*> swStars;
        std::vector<Engine::Actor*> sStars;
        std::vector<Engine::Actor*> seStars;
        void update();
        void createRegion(std::vector<Engine::Actor*>& vec, float x, float y, float top, float right);
        void removeRegion(std::vector<Engine::Actor*>& vec);
    };
}

#endif