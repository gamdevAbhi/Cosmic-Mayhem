#include <engine/window.hpp>

engine::Window::Window(const char* title, int width, int height)
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

    // enabling depth test
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);
}

// call every end of update loop for swapping buffers and to process all depended 
void engine::Window::updateWindow()
{
    glfwPollEvents();
    glfwSwapBuffers(glfwWindow);
}

// close the window and terminating glfw
void engine::Window::close()
{
    glfwDestroyWindow(glfwWindow);
    glfwTerminate();
    free(glfwWindow);
}

// get the window width and height
std::tuple<int, int> engine::Window::getSize()
{
    std::tuple<int, int> size = std::make_tuple(0, 0);
    glfwGetWindowSize(glfwWindow, &std::get<0>(size), &std::get<1>(size));
    return size;
}

// check if window should close or not
bool engine::Window::shouldClose()
{
    if(glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(glfwWindow, true);
    }

    return glfwWindowShouldClose(glfwWindow);
}

// forcing window to close
void engine::Window::makeWindowClose()
{
    glfwSetWindowShouldClose(glfwWindow, true);
}

// get glfw window
GLFWwindow* engine::Window::getWindow()
{
    return glfwWindow;
}