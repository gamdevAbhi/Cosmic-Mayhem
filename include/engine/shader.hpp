#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H

#define SHADER_NO_ERROR -1
#define VERTEX_ERROR    0
#define FRAGMENT_ERROR  1
#define LINK_ERROR      2

#include <glad/glad.h>
#include <engine/resources.hpp>
#include <iostream>

namespace Engine
{
    // shader class for render actor
    class Shader
    {
    public:
        Shader(std::string vertex_relative_path, std::string fragment_relative_path);
        void use();
        int getStatus();
        ~Shader();
    private:
        GLuint program;
        int status;
        bool attach(const char* source_code, GLenum shader_type);
        bool checkShaderStatus(GLuint shader);
        bool checkLinkStatus();
    };
}

#endif