#pragma once
#include <iostream>
#include <mutex>
#include <condition_variable>
#include "sleep.h"



const int Zero = 0;

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
    int capacity = 0;  // Max capacity
    T *arr;
    int i = 0; 
    int head = 0, tail = 0;
    int size = 0;   // actual size
    int count = 0;  
    //Queue* queue_;
    //Queue() {};   
    std::mutex mtx;  // protects the Queue
 
public:
    void Push(T element);
    T Pop();
    const int Count();  // Amount of elements stored now
    const int Size();   // Max number of elements
    void printfQueue();
    Queue(int sizeofqueue);
    ~Queue();
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
    :capacity{sizeofqueue}
    ,head{0}
    ,size{0}
    ,tail{0}
    ,arr{new T[sizeofqueue]}
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
    while (size == capacity)
    {
        // FULL 
        condition.wait(mlock);   // (4)     
    }
 

    tail = tail % capacity;
    arr[tail] = element;
    tail += 1; // nothing on tail now (as tail+1)
    size += 1;
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
    while (size == Zero)
    {
        // empty 
        condition.wait(mlock);
    }
    T temp;
    temp = arr[head]; 
    arr[head] = 0 ; 
 
    head = head % capacity;
    head += 1;
    size -= 1;  // one slot free
    sleepcp(20); 
    mlock.unlock();
    condition.notify_one();
    return temp;
}
 

/**
 * User defined Destructor
 * Free the memory
 */
template<typename T>
Queue <T>::~Queue()
{
	delete[] arr; // use array delete to deallocate array
}

 

/**
 * Count
 * returns the max number of elements in the Queue == Capacity
 */
template<typename T>
const int  Queue<T>::Count()    
{
    return (capacity);
}
 

/**
 * Size
 * Returns the current size of used Queue spots
 */
template<typename T>
const int  Queue<T>::Size()
{
    return (size);
}
 

/**
 * Prints Queue
 * DEBUG PURPOSE ONLY
 * A simple queue function that prints out size, capacity and current Queue
 * Be aware, that even the "deleted" queue spots will be printed
 * 
 */
template<typename T>
void Queue<T>::printfQueue()
{
    for (int i = 0; i < capacity; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "H & T: " << head << " " << tail << "; ";
    std::cout << "size of queue " << size << std::endl;
}
 

