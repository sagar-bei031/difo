/**
 ******************************************************************************
 * @file    myColors.cpp
 * @brief   Implementation of functions for handling colored text output and determining file colors.
 * @author  Arun, Sagar, Saurav
 * @date    March 7, 2024
 ******************************************************************************
 */

#include "myColors.hpp"
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>

/**
 * @brief Print colored text to the console.
 *
 * This function prints the given text in the specified color.
 *
 * @param text The text to be printed.
 * @param color The color to be used for printing.
 */
void print_colored_text(const std::string &text, const std::string &color) 
{
    std::cout << color << text << COLOR_RESET;
}

/**
 * @brief Get the color for a file based on its name and visibility.
 *
 * This function determines the appropriate color for a file based on its name and visibility.
 *
 * @param filename The name of the file.
 * @param is_hidden A boolean indicating whether the file is hidden or not.
 * @return The color code for the file.
 */
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
            return COLOR_FAINT_WHITE;
        }
        else
        {
            return COLOR_FAINT_WHITE;
        }
    }
}
