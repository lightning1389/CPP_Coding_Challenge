#pragma once
#include <iostream>
#include <mutex>
#include <condition_variable>
#include "sleep.h"


/*
 ***********************************************************************************************************************
 * Class template Queue
 ***********************************************************************************************************************
 */
/**
 * Interface defined as described in the Coding challenge
 */
template<typename T>
class Queue
{
    std::condition_variable condition;
    int m_capacity{0};                                // Max capacity
    T *m_arr;
    int m_head{0}; 
    int tail{0};
    int m_size{0};                                    // actual size
    std::mutex mtx;                                   // protects the Queue
    const int Zero{0};
 
public:
    void Push(T element);
    T Pop();
    const int Count();                                // Amount of elements stored now
    const int Size();                                 // Max number of elements
    void printfQueue(); 
    Queue& operator=(Queue&& copy){                   // move assignment operator
        swap(*this, copy);
        return *this;
    }; 
    Queue(Queue&& other) noexcept;                     // move constructor
    Queue(const Queue &other);                         // copy constructor 
    Queue& operator=(Queue& copy) {                    // copy assignment operator
        if (this != &copy)                             // not a self-assignment
        {
            if (m_capacity != copy.m_capacity)         // resource cannot be reused
            {
                m_capacity = copy.m_capacity;
            }
            this->m_size = copy.m_size;
            this->tail = copy.tail;
            this->m_head = copy.m_head;
            for (int i = 0; i <= m_capacity; ++i)       // this only works for build in types
            {
                m_arr[i] = copy.m_arr[i];
            }
        }
        return *this;
    }; 
    Queue(int sizeofqueue);                             // User defined constructor 
    ~Queue();                                            // user defined destructor
};
 
/*
 ***********************************************************************************************************************
 * Function template
 ***********************************************************************************************************************
 */
/**
 * User defined constructor
 * creates a new queue and points to it via a Queue Pointer
 */
template <typename T>
Queue <T>::Queue(int sizeofqueue)
    :m_capacity{sizeofqueue}
    ,m_head{0}
    ,m_size{0}
    ,tail{0}
    ,m_arr{new T[sizeofqueue]}
    ,mtx{}
{
}


/**
 * copy constructor 
 * copies the input and puts it into another instance of queue
 */
template<typename T>
Queue<T>::Queue(const Queue& other)                     // copy constructor 
   : Queue(other.m_capacity)
{
    m_size = other.m_size; 
    m_capacity = other.m_capacity; 
    m_head = other.m_head;  
    tail = other.tail; 
    for (int i = 0; i <= m_capacity; ++i)               // this only works for build in types
    {
        m_arr[i] = other.m_arr[i];
    }

}


/** 
 * Move constructor 
 * 
 */
template <typename T>
Queue<T>::Queue(Queue&& other) noexcept
    :m_capacity{std::exchange(other.m_capacity, 0)}
    ,m_head{std::exchange(other.m_head, 0)}
    ,m_size{std::exchange(other.m_size, 0)}
    ,tail{std::exchange(other.tail, 0)}
    ,m_arr{std::exchange(other.m_arr, new T[other.Count()])}    
    ,mtx{}
{
}

/**
 * Push / Enqueue
 * Push function - element can be a template defined type
 */
template<typename T>
void Queue<T>::Push(T element)
{
    std::unique_lock<std::mutex> mlock(mtx);
    // check if there is still enough space 
    while (m_size == m_capacity)
    {
        // FULL 
        condition.wait(mlock);    
    }
    tail = tail % m_capacity;
    m_arr[tail] = element;
    tail += 1; 
    m_size += 1;
    sleepcp(20); 
    mlock.unlock();
    condition.notify_one();
}
 
/**
 * Pop/ Dequeue
 * Pop function - Element returned can be a template defined type
 */
template<typename T>
T Queue<T>::Pop()
{
    std::unique_lock<std::mutex> mlock(mtx);
 
    // check if there are any elements 
    while (m_size == Zero)
    {
        // empty 
        condition.wait(mlock);
    }
    T temp;
    temp = m_arr[m_head]; 
    m_arr[m_head] = 0 ; 
 
    m_head = m_head % m_capacity;
    m_head += 1;
    m_size -= 1;  // one slot free
    sleepcp(20); 
    mlock.unlock();
    condition.notify_one();
    return temp;
}

 

/**
 * Count
 * returns the max number of elements in the Queue == m_capacity
 */
template<typename T>
const int  Queue<T>::Count()    
{
    return (m_capacity);
}
 

/**
 * Size
 * Returns the current size of used Queue spots
 */
template<typename T>
const int  Queue<T>::Size()
{
    return (m_size);
}
 

/**
 * Prints Queue
 * DEBUG PURPOSE ONLY
 * A simple queue function that prints out size, m_capacity and current Queue
 * Be aware, that even the "deleted" queue spots will be printed
 * 
 */
template<typename T>
void Queue<T>::printfQueue()
{
    for (int i = 0; i < m_capacity; i++)
    {
        std::cout << m_arr[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "H & T: " << m_head << " " << tail << "; ";
    std::cout << "size of queue " << m_size << std::endl;
}
 

/**
 * User defined Destructor
 * Free the memory
 */
template<typename T>
Queue <T>::~Queue()
{
    delete[] m_arr; // use m_array delete to deallocate m_array
}

