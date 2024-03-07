#include "mySlide.hpp"
#include "myQueue.hpp"
#include "myTypeDef.h"
#include <iostream>
#include <fstream>
#include <thread>

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
