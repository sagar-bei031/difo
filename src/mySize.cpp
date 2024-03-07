/**
 ******************************************************************************
 * @file    mySize.cpp
 * @brief   Implementation of functions for printing directory sizes and drawing size bars.
 * @author  Arun, Sagar, Saurav
 * @date    March 7, 2024
 ******************************************************************************
 */

#include "mySize.hpp"
#include "myColors.hpp"
#include "myTypeDef.h"
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

/**
 * @brief Print the size of a directory.
 *
 * This function prints the size of the specified directory along with a visual representation
 * of the sizes of directories and files within it.
 *
 * @param directory The path to the directory.
 * @param max_size The maximum size to consider.
 * @param show_hidden Whether to include hidden files and directories in the size calculation.
 */
void print_size(const std::string &directory, long long max_size, bool show_hidden)
{
    std::cout << COLOR_TEXT << "Size of directories and files in current directory:" << std::endl;
    
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int terminal_width = w.ws_col;
    int max_name_length = 0;

    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(directory.c_str())) != nullptr)
    {
        while ((entry = readdir(dir)) != nullptr)
        {
            std::string item = entry->d_name;
            if (show_hidden || item[0] != '.')
            {
                max_name_length = std::max(max_name_length, static_cast<int>(item.size()));
            }
        }
        closedir(dir);

        if ((dir = opendir(directory.c_str())) != nullptr)
        {
            while ((entry = readdir(dir)) != nullptr)
            {
                std::string item = entry->d_name;
                if (show_hidden || item[0] != '.')
                {
                    std::string full_path = directory + "/" + item;
                    struct stat st;
                    if (stat(full_path.c_str(), &st) == 0)
                    {
                        long long size = st.st_size;
                        int max_bar_length = terminal_width - max_name_length - 16; // Adjusted for spacing and units
                        int bar_length = static_cast<int>(size / static_cast<double>(max_size) * max_bar_length);
                        std::string size_str = size < 1024 ? std::to_string(size) + " bytes" : std::to_string(size / 1024.0) + " KB";
                        std::string color = get_file_color(full_path, item[0] == '.');
                        std::string color_bar = COLOR_BAR;
                        std::cout << color << std::setw(max_name_length) << std::left << item << " ";
                        std::cout << color_bar << std::string(bar_length, '=') << COLOR_TEXT << " " << size_str << std::endl;
                    }
                }
            }
            closedir(dir);
        }
    }
    else
    {
        std::cerr << "Error opening directory: " << directory << std::endl;
        exit(OPEN_FAILURE);
    }
}

/**
 * @brief Draw a size bar for a directory.
 *
 * This function draws a visual representation of the size of the specified directory.
 *
 * @param show_hidden Whether to include hidden files and directories in the size calculation.
 * @param path The path to the directory.
 */
void draw_size_bar(bool show_hidden, const std::string &path)
{
    long long max_size = 0;
    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(path.c_str())) != nullptr)
    {
        while ((entry = readdir(dir)) != nullptr)
        {
            std::string item = entry->d_name;
            if (show_hidden || item[0] != '.')
            {
                std::string full_path = path + "/" + item;
                struct stat st;
                if (stat(full_path.c_str(), &st) == 0)
                {
                    max_size = std::max(max_size, static_cast<long long>(st.st_size));
                }
            }
        }
        closedir(dir);
        print_size(path, max_size, show_hidden);
    }
    else
    {
        std::cerr << "Error opening directory: " << path << std::endl;
        exit(OPEN_FAILURE);
    }
}
