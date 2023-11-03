#include <engine/input.hpp>

void Engine::Input::initialize()
{
    // adding key value pair for keyboard input and mouse input
    keyboardInputs[GLFW_KEY_SPACE] = KEY_NONE;

    for(int i = GLFW_KEY_0; i <= GLFW_KEY_9; i++)   keyboardInputs[i] = KEY_NONE;
    for(int i = GLFW_KEY_A; i <= GLFW_KEY_Z; i++)   keyboardInputs[i] = KEY_NONE;

    keyboardInputs[GLFW_KEY_GRAVE_ACCENT] = KEY_NONE;
    keyboardInputs[GLFW_KEY_ESCAPE] = KEY_NONE;
    keyboardInputs[GLFW_KEY_ENTER] = KEY_NONE;
    keyboardInputs[GLFW_KEY_TAB] = KEY_NONE;
    keyboardInputs[GLFW_KEY_RIGHT] = KEY_NONE;
    keyboardInputs[GLFW_KEY_LEFT] = KEY_NONE;
    keyboardInputs[GLFW_KEY_DOWN] = KEY_NONE;
    keyboardInputs[GLFW_KEY_UP] = KEY_NONE;
    keyboardInputs[GLFW_KEY_LEFT_SHIFT] = KEY_NONE;
    keyboardInputs[GLFW_KEY_LEFT_CONTROL] = KEY_NONE;
    keyboardInputs[GLFW_KEY_LEFT_ALT] = KEY_NONE;
    keyboardInputs[GLFW_KEY_RIGHT_SHIFT] = KEY_NONE;
    keyboardInputs[GLFW_KEY_RIGHT_CONTROL] = KEY_NONE;
    keyboardInputs[GLFW_KEY_RIGHT_ALT] = KEY_NONE;

    mouseInputs[GLFW_MOUSE_BUTTON_LEFT] = KEY_NONE;
    mouseInputs[GLFW_MOUSE_BUTTON_RIGHT] = KEY_NONE;
}

// give key status eg. press, hold or release
int Engine::Input::getKeyStatus(int key)
{
    KeyStatus action = keyboardInputs[key];
    int newAction = glfwGetKey(window->glfwWindow, key);

    if(action == KEY_PRESS && newAction == GLFW_PRESS
    || action == KEY_HOLD && newAction == GLFW_PRESS) keyboardInputs[key] = KEY_HOLD;
    else if(newAction == GLFW_PRESS) keyboardInputs[key] = KEY_PRESS;
    else if(action != KEY_RELEASE && newAction == GLFW_RELEASE) keyboardInputs[key] = KEY_RELEASE;
    else keyboardInputs[key] = KEY_NONE; 
    
    return keyboardInputs[key];
}

// get mouse button status eg. click, hold or release
int Engine::Input::getMouseButtonStatus(int mouseButton)
{
    KeyStatus action = mouseInputs[mouseButton];
    int newAction = glfwGetMouseButton(window->glfwWindow, mouseButton);

    if(action == KEY_PRESS && newAction == GLFW_PRESS
    || action == KEY_HOLD && newAction == GLFW_PRESS) mouseInputs[mouseButton] = KEY_HOLD;
    else if(newAction == GLFW_PRESS) mouseInputs[mouseButton] = KEY_PRESS;
    else if(action != KEY_RELEASE && newAction == GLFW_RELEASE) mouseInputs[mouseButton] = KEY_RELEASE;
    else mouseInputs[mouseButton] = KEY_NONE; 
    
    return mouseInputs[mouseButton];
}

// give mouse position
glm::vec2 Engine::Input::getMousePos()
{
    double x, y;

    glfwGetCursorPos(window->glfwWindow, &x, &y);
    
    return glm::vec2(x, y);
}