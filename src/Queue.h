#pragma once

#include <iostream>
#include <mutex>
#include <condition_variable>

const int Zero = 0;


template<typename T>
class Queue
{
	std::condition_variable condition;
	unsigned int capacity = 0;	// Max capacity
	T *arr;
	int head = 0, tail = 0;
	int size = 0;	// actual size
	int count = 0;	// 
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

template<typename T>
void Queue<T>::Push(T element)
{
	std::unique_lock<std::mutex> mlock(mtx);
	// check if there is still enough space 
	if (queue_->size == queue_->capacity)
	{
		// FULL 
			condition.wait(mlock);   // (4)		
	}
	else
	{
		queue_->tail = queue_->tail % queue_->capacity;
		queue_->arr[queue_->tail] = element;
		queue_->tail += 1; // nothing on tail now (as tail+1)
		queue_->size += 1;
		condition.notify_one();
	}

}


template<typename T>
T Queue<T>::Pop()
{
	std::unique_lock<std::mutex> mlock(mtx);
	T temp = queue_->arr[queue_->head]; 


	// check if there are any elements 
	if (queue_->size == Zero)
	{
		// empty 
			condition.wait(mlock);

	}
	else
	{
		temp = queue_->arr[queue_->head]; 
		queue_->arr[queue_->head] = 0 ; 

		queue_->head = queue_->head % queue_->capacity;
		queue_->head += 1;
		queue_->size -= 1;	// one slot free
		condition.notify_one();

	}

	return temp;
}



template <typename T>
Queue <T>::~Queue()
{
	free(queue_);
}



template<typename T>
const int  Queue<T>::Count()	//is the max number reached
{
	return (queue_->capacity);
}



template<typename T>
const int  Queue<T>::Size()
{
	return (queue_->size);
}

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
