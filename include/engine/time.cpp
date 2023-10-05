#include <engine/time.hpp>

// call when update loop is start
void engine::Time::frameStart()
{
    start = std::chrono::high_resolution_clock::now();
}

// call when udpate loop is end
void engine::Time::frameEnd()
{
    // calculating the total time taken for one frame
    std::chrono::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds microSeconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    deltaTime = (double)microSeconds.count() / 1000000.0;
    runTime += deltaTime;
    diffTime += deltaTime;

    if(diffTime >= 1.0f)
    {
        lastFPS = currentFPS;
        currentFPS = 1;
        diffTime = 0.0;
    }
    else currentFPS++;
}

// get delta time
double engine::Time::getDeltaTime()
{
    return deltaTime;
}

// get last fps
int engine::Time::getLastFPS()
{
    return lastFPS;
}

// get total run time of the application
double engine::Time::getRunTime()
{
    return runTime;
}