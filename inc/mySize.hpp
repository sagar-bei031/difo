/**
 ******************************************************************************
 * @file    mySize.hpp
 * @brief   Declarations of functions for printing directory sizes and drawing size bars.
 * @author  Arun, Sagar, Saurav
 * @date    March 7, 2024
 ******************************************************************************
 */

#pragma once

#include <string>

/**
 * @brief Print the size of a directory.
 *
 * This function prints the size of the specified directory.
 *
 * @param directory The path to the directory.
 * @param max_size The maximum size to consider.
 * @param show_hidden Whether to include hidden files and directories in the size calculation.
 */
void print_size(const std::string &directory, long long max_size, bool show_hidden);

/**
 * @brief Draw a size bar for a directory.
 *
 * This function draws a visual representation of the size of the specified directory.
 *
 * @param show_hidden Whether to include hidden files and directories in the size calculation.
 * @param path The path to the directory.
 */
void draw_size_bar(bool show_hidden, const std::string &path);
