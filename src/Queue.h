#pragma once

#include <iostream>
#include <mutex>
#include <condition_variable>

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
private: 
	std::condition_variable condition;
	unsigned int capacity = 0;	// Max capacity
	T *arr;
	int i = 0; 
	int head = 0, tail = 0;
	int size = 0;	// actual size
	int count = 0;	
	Queue* queue_;
	Queue() {};	
	std::mutex mtx;  // protects the Queue

public:
	void Push(T element);
	T Pop();
	const int Count();	// Amount of elements stored now
	const int Size();	// Max number of elements
	void printfQueue();
	Queue(int size);
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
Queue <T>::Queue(int size)
{
	Queue* queue = new Queue();
	queue->capacity = size;
	queue->head = queue->size = 0;
	queue->tail = 0;
	queue->arr = new T[size];
	queue_ = queue;
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
	while (queue_->size == queue_->capacity)
	{
		// FULL 
		condition.wait(mlock);   // (4)		
	}


	queue_->tail = queue_->tail % queue_->capacity;
	queue_->arr[queue_->tail] = element;
	queue_->tail += 1; // nothing on tail now (as tail+1)
	queue_->size += 1;
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
	while (queue_->size == Zero)
	{
		// empty 
		condition.wait(mlock);
	}
	T temp;
	temp = queue_->arr[queue_->head]; 
	queue_->arr[queue_->head] = 0 ; 

	queue_->head = queue_->head % queue_->capacity;
	queue_->head += 1;
	queue_->size -= 1;	// one slot free
	mlock.unlock();
	condition.notify_one();
	return temp;
}


/**
 * User defined Destructor
 * Free the memory
 */
template <typename T>
Queue <T>::~Queue()
{
	delete(queue_);
}

/**
 * Count
 * returns the max number of elements in the Queue == Capacity
 */
template<typename T>
const int  Queue<T>::Count()	
{
	return (queue_->capacity);
}


/**
 * Size
 * Returns the current size of used Queue spots
 */
template<typename T>
const int  Queue<T>::Size()
{
	return (queue_->size);
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
	for (int i = 0; i < queue_->capacity; i++)
	{
		std::cout << queue_->arr[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "H & T: " << queue_->head << " " << queue_->tail << "; ";
	std::cout << "size of queue " << queue_->size << std::endl;
}

