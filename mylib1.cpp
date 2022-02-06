#include "mylib1.h"


#include <iostream>

#define BUF_SIZE 4096

using namespace std;

path_exception::path_exception(const char* _message, const char* _path)
    : runtime_error(_message)
{
    size_t len = strlen(_path);
    m_path = new char[len + 1];
    copy(_path, _path + len + 1, m_path);
}

path_exception::path_exception(const char* _message, const std::string& _path)
    : runtime_error(_message), m_path{ new char[_path.size() + 1]}
{
    copy(_path.begin(), _path.end(), m_path);
    m_path[_path.size()] = '\0';
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void processInput2(GLFWwindow* window, MyCamera& camera, float speed)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.forward(speed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.backward(speed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.goleft(speed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.goright(speed);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.upper(speed);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.lower(speed);
}

std::string gulp(std::istream& in)
{
    std::string ret;
    char buffer[BUF_SIZE];
    while (in.read(buffer, sizeof(buffer)))
        ret.append(buffer, sizeof(buffer));
    ret.append(buffer, in.gcount());
    return ret;
}

void init(int major, int minor)
{
    if (GLFW_FALSE == glfwInit()) // √ ±‚»≠
        throw exception("faild to initialize GLFW\n");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void gladLoad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw exception("faild to initialize GLAD\n");
}

GLFWwindow* initWindow(int width, int height, const char* title)
{
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
        throw exception("faild to create window\n");

    return window;
}