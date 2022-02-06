#ifndef MY_LIB_H
#define MY_LIB_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string>
#include <stdexcept>

#include "mycamera.h"

struct GLFWTerminator {
    ~GLFWTerminator() {
        glfwTerminate();
    }
};

class path_exception : virtual public std::runtime_error
{
public:
    explicit path_exception(const char* _message, const char* _path);
    explicit path_exception(const char* _message, const std::string& _path);

    const char* path() const {
        return m_path;
    }

    ~path_exception() override {
        delete[] m_path;
    }

private:
    char* m_path;
};

class GLObjectError : virtual public std::runtime_error
{
    using super = std::runtime_error;
public:
    GLObjectError(GLuint _obj_id, const char* _message)
        : super(_message), m_obj_id(_obj_id) {}
    GLObjectError(GLuint _obj_id, const std::string& _message)
        : super(_message), m_obj_id(_obj_id) {}

    GLuint get_id() {
        return m_obj_id;
    }

private:
    GLuint m_obj_id;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);
void processInput2(GLFWwindow* window, MyCamera&, float speed);

std::string gulp(std::istream& in);

void init(int major, int minor);
void gladLoad();
GLFWwindow* initWindow(int width, int height, const char* title);

#endif // MY_LIB_H