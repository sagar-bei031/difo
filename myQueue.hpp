#pragma once

#include <iostream>
#include <fstream>
#include <thread>

template <typename T, int MAX_SIZE = 1024>
class Queue
{
private:
    int front;
    int rear;
    T items[MAX_SIZE];

public:
    Queue() : front(-1), rear(-1) {}

    bool is_empty()
    {
        return front == -1;
    }

    bool is_full()
    {
        return rear == MAX_SIZE - 1;
    }

    void enqueue(T item)
    {
        if (is_full())
        {
            std::cout << "Queue is full. Enqueue operation blocked.\n";
            return;
        }

        if (is_empty())
        {
            front = 0;
        }

        items[++rear] = item;
    }

    T dequeue()
    {
        if (is_empty())
        {
            std::cout << "Queue is empty. Cannot dequeue.\n";
            return T(); // Return a default-initialized value
        }

        T item = items[front];

        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else
        {
            ++front;
        }

        return item;
    }

    void clear()
    {
        front = -1;
        rear = -1;
    }
};
void print_content_with_slide(const std::string &file_path, float slide_speed)
{
    std::ifstream file(file_path);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return;
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
                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(10 / slide_speed))); // Adjust sleep duration based on slide speed
            }
        }
        queue.enqueue(character);
    }

    // Flush remaining characters in the queue
    while (!queue.is_empty())
    {
        std::cout << queue.dequeue();
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(10 / slide_speed))); // Adjust sleep duration based on slide speed
    }
    std::cout << std::endl;
}
