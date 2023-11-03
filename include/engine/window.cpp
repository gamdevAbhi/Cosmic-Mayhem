#include <engine/window.hpp>

// get the window width and height
std::tuple<int, int> Engine::Window::getSize()
{
    std::tuple<int, int> size = std::make_tuple(0, 0);
    glfwGetWindowSize(glfwWindow, &std::get<0>(size), &std::get<1>(size));
    return size;
}

// forcing window to close
void Engine::Window::makeWindowClose()
{
    glfwSetWindowShouldClose(glfwWindow, true);
}

// constructor
Engine::Window::Window(const char* title, int width, int height)
{
    // giving hint to glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    // making sure if given width, height is right
    if(width > screen_width) width = screen_width;
    if(height > screen_height) height = screen_height;

    glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    
    // handling null cases 
    if(glfwWindow == NULL)
    {
        std::cout << "GLFW didn't create a window" << std::endl;
        close();
    }

    // calculating the difference between screen size and given window size
    int diffX = screen_width - width;
    int diffY = screen_height - height;

    // moving the window to screen center
    glfwSetWindowPos(glfwWindow, diffX / 2, diffY / 2);

    glfwMakeContextCurrent(glfwWindow);

    bool glLoadStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    // handling the error cases
    if(glLoadStatus == false)
    {
        std::cout << "GLAD didn't load" << std::endl;
        close();
    }

    // enabling depth test and blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0, 0, width, height);
}

// call at the start of new frame for clearing the frame
void Engine::Window::clearWindow()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

// call every end of update loop for swapping buffers and to process all depended 
void Engine::Window::updateWindow()
{
    glfwPollEvents();
    glfwSwapBuffers(glfwWindow);
}

// close the window and terminating glfw
void Engine::Window::close()
{
    glfwDestroyWindow(glfwWindow);
    glfwTerminate();
}

// check if window should close or not
bool Engine::Window::shouldClose()
{
    if(glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(glfwWindow, true);
    }

    return glfwWindowShouldClose(glfwWindow);
}