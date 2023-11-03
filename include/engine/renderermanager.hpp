#ifndef ENGINE_RENDERER_MANAGER_HPP
#define ENGINE_RENDERER_MANAGER_HPP

#include <engine/spriterenderer.hpp>
#include <engine/billboard.hpp>

namespace Engine
{
    class RendererManager
    {
    public:
        static int getLastRenderCount();
    protected:
        inline static std::vector<SpriteRenderer*> sprites;
        inline static std::vector<Billboard*> billboards;
        inline static int count = 0;
        static void initialize();
        static void findRenderers();
        static void drawWorld();
        static void drawScreen();
    friend class GameLoop;
    };
}

#endif