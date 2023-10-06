#include <engine/resources.hpp>

// get the current executable path
std::string engine::Resources::get_current_dir()
{
    char buff[MAX_PATH];
    GetModuleFileNameA(NULL, buff, MAX_PATH);
    std::string::size_type pos = std::string(buff).find_last_of("\\/");
    return std::string(buff).substr(0, pos);
}

// get the file contents in string
std::string engine::Resources::get_file_content(std::string relative_file_path)
{
    // opening the file
    std::ifstream file;
    std::string file_full_path = get_current_dir() + relative_file_path;

    file.open(file_full_path);

    // checking if file is open
    if(file.is_open())
    {
        std::string content;
        std::string line;

        // storing file content
        while(file)
        {
            std::getline(file, line);
            content += line + "\n";
            if(file.eof()) break;
        }

        content += "\0";
        file.close();
        return content;
    }
    else
    {
        // in case file not found or openned
        std::cout << "Can't Read : " + file_full_path << std::endl;
        throw;
    }
}