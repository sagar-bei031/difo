#pragma once

#include <string>

template <typename T, int MAX_SIZE = 128>
class Queue
{
private:
    int front;
    int rear;
    T items[MAX_SIZE];

public:
    Queue();

    bool is_empty();

    bool is_full();

    void enqueue(T item);

    T dequeue();

    void clear();
};

void print_content_with_slide(const std::string &file_path, float slide_speed);