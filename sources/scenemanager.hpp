#ifndef COSMIC_SCENE_MANAGER_HPP
#define COSMIC_SCENE_MANAGER_HPP

#include <engine/gameloop.hpp>

#include "starmanager.hpp"
#include "countdown.hpp"
#include "shiphandler.hpp"
#include "follower.hpp"
#include "starmanager.hpp"
#include "collectiblemanager.hpp"
#include "asteroidmanager.hpp"
#include "button.hpp"

namespace Cosmic
{
    class SceneManager
    {
    public:
        inline static int lastGameScore = 0;
        static void loadTechScene();
        static void loadMenuScene();
        static void loadGameScene();
        static void loadGameOverScene();
    };
}

#endif