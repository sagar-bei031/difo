/**
 ******************************************************************************
 * @file    mySlide.hpp
 * @brief   Declarations of functions for printing content with sliding animation from a file. 
 *          Content is printed line by line with a sliding effect controlled by slide speed. 
 *          Useful for displaying text in a presentation or slideshow. 
 * @author  Arun, Sagar, Saurav
 * @date    March 7, 2024
 ******************************************************************************
 */

#pragma once

#include <string>

/**
 * @brief Print content from a file with sliding animation.
 *
 * This function reads the content from the specified file and prints it line by line 
 * with a sliding effect controlled by the slide speed parameter.
 *
 * @param file_path The path to the file containing the content to be printed.
 * @param slide_speed The speed of the sliding animation, in seconds per line.
 */
void print_content_with_slide(const std::string &file_path, float slide_speed);
