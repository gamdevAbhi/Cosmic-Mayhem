#include <engine/handler.hpp>

void Engine::Handler::debug(std::string message, std::string senderName)
{
    std::cout << "Debug : " << std::endl;
    std::cout << "Sender : " << senderName << std::endl;
    std::cout << "Message :" << std::endl;
    std::cout << message << std::endl;
    std::cout << std::endl;
}

void Engine::Handler::error(std::string message, std::string senderName)
{
    std::cout << "Debug : " << std::endl;
    std::cout << "Sender : " << senderName << std::endl;
    std::cout << "Message :" << std::endl;
    std::cout << message << std::endl;
    std::cout << std::endl;

    gameWindow->makeWindowClose();
}