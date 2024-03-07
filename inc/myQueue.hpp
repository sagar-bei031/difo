/**
 ******************************************************************************
 * @file    myQueue.hpp
 * @brief   Definition of a templated queue data structure.
 * @author  Arun, Sagar, Saurav
 * @date    March 7, 2024
 ******************************************************************************
 */

#pragma once

/**
 * @brief Templated queue class.
 *
 * This class implements a queue data structure using templates.
 *
 * @tparam T The type of elements stored in the queue.
 * @tparam MAX_SIZE The maximum capacity of the queue (default is 128).
 */
template <typename T, int MAX_SIZE = 128>
class Queue
{
private:
    int front; /**< Index of the front element in the queue. */
    int rear; /**< Index of the rear element in the queue. */
    T items[MAX_SIZE]; /**< Array to store elements of the queue. */

public:
    /**
     * @brief Constructor.
     *
     * Initializes an empty queue.
     */
    Queue();

    /**
     * @brief Check if the queue is empty.
     *
     * @return true if the queue is empty, false otherwise.
     */
    bool is_empty();

    /**
     * @brief Check if the queue is full.
     *
     * @return true if the queue is full, false otherwise.
     */
    bool is_full();

    /**
     * @brief Add an element to the rear of the queue.
     *
     * @param item The item to be added to the queue.
     */
    void enqueue(T item);

    /**
     * @brief Remove and return the element from the front of the queue.
     *
     * @return The element removed from the front of the queue.
     */
    T dequeue();

    /**
     * @brief Clear the queue.
     *
     * Removes all elements from the queue.
     */
    void clear();
};

#include "myQueue.tpp"
