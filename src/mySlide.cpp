/**
 ******************************************************************************
 * @file    mySlide.cpp
 * @brief   Implementation of functions for printing content with sliding animation from a file.
 *          Content is printed line by line with a sliding effect controlled by slide speed.
 *          Useful for displaying text in a presentation or slideshow.
 * @author  Arun, Sagar, Saurav
 * @date    March 7, 2024
 ******************************************************************************
 */

#include "mySlide.hpp"
#include "myQueue.hpp"
#include "myTypeDef.h"
#include <iostream>
#include <fstream>
#include <thread>

/**
 * @brief Print content from a file with sliding animation.
 *
 * This function reads the content from the specified file and prints it line by line
 * with a sliding effect controlled by the slide speed parameter.
 *
 * @param file_path The path to the file containing the content to be printed.
 * @param slide_speed The speed of the sliding animation, in seconds per line.
 */
void print_content_with_slide(const std::string &file_path, float slide_speed)
{
    std::ifstream file(file_path);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << file_path << std::endl;
        exit(OPEN_FAILURE);
    }

    char character;
    Queue<char> queue;

    while (file.get(character))
    {
        if (queue.is_full())
        {
            while (!queue.is_empty())
            {
                std::cout << queue.dequeue();
                std::cout.flush();
                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(20 / slide_speed)));
            }
        }
        queue.enqueue(character);
    }

    // Flush remaining characters in the queue
    while (!queue.is_empty())
    {
        std::cout << queue.dequeue();
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(20 / slide_speed)));
    }
    std::cout << std::endl;
}
