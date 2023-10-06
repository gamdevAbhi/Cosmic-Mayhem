#ifndef ENGINE_TIME_HPP
#define ENGINE_TIME_HPP

#include <chrono>

namespace engine
{
    // handle time in the game
    class Time
    {
    public:
        inline static float timeScale = 1.0f;
        static double getDeltaTime();
        static double getRunTime();
        static int getLastFPS();
    private:
        static void frameStart();
        static void frameEnd();
        inline static int currentFPS = 0, lastFPS = 0;
        inline static double deltaTime = 0.0f, runTime = 0.0f, diffTime = 0.0f;
        inline static std::chrono::time_point start = std::chrono::high_resolution_clock::now();
    };
}

#endif