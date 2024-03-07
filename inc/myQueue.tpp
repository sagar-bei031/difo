/**
 ******************************************************************************
 * @file    myQueue.tpp
 * @brief   Implementation of the Queue class template for managing a queue data structure.
 * @author  Arun, Sagar, Saurav
 * @date    March 7, 2024
 ******************************************************************************
 */

#include "myQueue.hpp"
#include <iostream>

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
