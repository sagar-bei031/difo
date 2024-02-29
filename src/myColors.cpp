#include "myColors.hpp"
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>

void print_colored_text(const std::string &text, const std::string &color) 
{
    std::cout << color << text << COLOR_RESET << std::endl;
}

std::string get_file_color(const std::string &filename, bool is_hidden)
{
    struct stat file_stat;
    if (stat(filename.c_str(), &file_stat) != 0)
    {
        // Error occurred while retrieving file information
        return COLOR_FAINT_WHITE;
    }

    if (S_ISDIR(file_stat.st_mode))
    {
        if (is_hidden)
        {
            return COLOR_HIDDEN_FOLDER;
        }
        else
        {
            return COLOR_FOLDER;
        }
    }
    else if (access(filename.c_str(), X_OK) == 0)
    {
        if (is_hidden)
        {
            return COLOR_HIDDEN_EXECUTABLE;
        }
        else
        {
            return COLOR_EXECUTABLE;
        }
    }
    else if (S_ISREG(file_stat.st_mode))
    {
        if (is_hidden)
        {
            return COLOR_HIDDEN_FILE;
        }
        else
        {
            return COLOR_FILE;
        }
    }
    else
    {
        if (is_hidden)
        {
            return COLOR_FAINT_WHITE; // Hidden, not a file or directory
        }
        else
        {
            return COLOR_FAINT_WHITE; // Not hidden, not a file or directory
        }
    }
}
