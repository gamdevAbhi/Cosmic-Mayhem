#ifndef ENGINE_RESOURCES_H
#define ENGINE_RESOURCES_H

#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

namespace Engine
{
    // geting resources in the game resouces folder
    class Resources
    {
    public: 
        static std::string get_current_dir();
        static std::string get_file_content(std::string relative_file_path);
    };
}

#endif