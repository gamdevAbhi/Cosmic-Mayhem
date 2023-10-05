#ifndef RESOURCES_H
#define RESOURCES_H

#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

namespace engine
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