#include <engine/input.hpp>

engine::Input::Input(Window& window)
{
    this->window = &window;

    // adding key value pair for keyboard input and mouse input
    keyboardInputs[GLFW_KEY_SPACE] = KEY_RELEASE;

    for(int i = GLFW_KEY_0; i <= GLFW_KEY_9; i++)   keyboardInputs[i] = KEY_RELEASE;
    for(int i = GLFW_KEY_A; i <= GLFW_KEY_Z; i++)   keyboardInputs[i] = KEY_RELEASE;

    keyboardInputs[GLFW_KEY_GRAVE_ACCENT] = KEY_RELEASE;
    keyboardInputs[GLFW_KEY_ESCAPE] = KEY_RELEASE;
    keyboardInputs[GLFW_KEY_ENTER] = KEY_RELEASE;
    keyboardInputs[GLFW_KEY_TAB] = KEY_RELEASE;
    keyboardInputs[GLFW_KEY_RIGHT] = KEY_RELEASE;
    keyboardInputs[GLFW_KEY_LEFT] = KEY_RELEASE;
    keyboardInputs[GLFW_KEY_DOWN] = KEY_RELEASE;
    keyboardInputs[GLFW_KEY_UP] = KEY_RELEASE;
    keyboardInputs[GLFW_KEY_LEFT_SHIFT] = KEY_RELEASE;
    keyboardInputs[GLFW_KEY_LEFT_CONTROL] = KEY_RELEASE;
    keyboardInputs[GLFW_KEY_LEFT_ALT] = KEY_RELEASE;
    keyboardInputs[GLFW_KEY_RIGHT_SHIFT] = KEY_RELEASE;
    keyboardInputs[GLFW_KEY_RIGHT_CONTROL] = KEY_RELEASE;
    keyboardInputs[GLFW_KEY_RIGHT_ALT] = KEY_RELEASE;

    mouseInputs[GLFW_MOUSE_BUTTON_LEFT] = KEY_RELEASE;
    mouseInputs[GLFW_MOUSE_BUTTON_RIGHT] = KEY_RELEASE;
}

// give key status eg. press, hold or release
int engine::Input::getKeyStatus(int key)
{
    int action = keyboardInputs[key];
    int newAction = glfwGetKey(window->getWindow(), key);

    if(action == KEY_PRESS && newAction == KEY_PRESS
    || action == KEY_HOLD && newAction == KEY_PRESS) keyboardInputs[key] = KEY_HOLD;
    else keyboardInputs[key] = newAction;

    return keyboardInputs[key];
}

// get mouse button status eg. click, hold or release
int engine::Input::getMouseButtonStatus(int mouseButton)
{
    int action = mouseInputs[mouseButton];
    int newAction = glfwGetMouseButton(window->getWindow(), mouseButton);

    if(action == KEY_PRESS && newAction == KEY_PRESS
    || action == KEY_HOLD && newAction == KEY_PRESS) mouseInputs[mouseButton] = KEY_HOLD;
    else mouseInputs[mouseButton] = newAction;
    
    return mouseInputs[mouseButton];
}

// give mouse position
std::tuple<double, double> engine::Input::getMousePos()
{
    std::tuple<double, double> mousePos = std::make_tuple(0.0, 0.0);
    glfwGetCursorPos(window->getWindow(), &std::get<0>(mousePos), &std::get<1>(mousePos));
    return mousePos;
}