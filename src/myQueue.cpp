#include "myQueue.hpp"
#include <iostream>
#include <fstream>
#include <thread>

template <typename T, int MAX_SIZE>
Queue<T, MAX_SIZE>::Queue() : front(-1), rear(-1) {}

template <typename T, int MAX_SIZE>
bool Queue<T, MAX_SIZE>::is_empty()
{
    return front == -1;
}

template <typename T, int MAX_SIZE>
bool Queue<T, MAX_SIZE>::is_full()
{
    return rear == MAX_SIZE - 1;
}

template <typename T, int MAX_SIZE>
void Queue<T, MAX_SIZE>::enqueue(T item)
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

template <typename T, int MAX_SIZE>
T Queue<T, MAX_SIZE>::dequeue()
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

template <typename T, int MAX_SIZE>
void Queue<T, MAX_SIZE>::clear()
{
    front = -1;
    rear = -1;
}

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
