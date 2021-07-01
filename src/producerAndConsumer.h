#pragma once
#include "Queue.h"
#include <chrono>
/*
 ***********************************************************************************************************************
 * Tester template function
 ***********************************************************************************************************************
 */
/**
 * Tester Program that includes a preset of values
 * can be rewritten to hold user defined values 
 */

/**
 * Produce 
 * can be rewritten to hold user defined values 
 */
template <class T>
void produce(Queue<T>& queue) {
	srand (time(NULL));
	int iSecret =  rand() % 50 + 1;
	queue.Push(10);
	queue.Push(20);
	queue.Push(30);
	// just for testing purpose outside the function 
	std::this_thread::sleep_for (std::chrono::microseconds(iSecret));
	queue.Push(40);
	queue.Push(50);
	std::this_thread::sleep_for (std::chrono::microseconds(iSecret));
	queue.Push(60);
	queue.Push(70);
	queue.Push(80);
}

/**
 * Consume 
 * can be rewritten to hold user defined values 
 */
template <class T>
void consume(Queue<T>& queue) {
	srand (time(NULL));
	int iSecret =  rand() % 50 + 1;
	queue.Pop();
	queue.Pop();
	queue.Pop();
	std::this_thread::sleep_for (std::chrono::microseconds(iSecret));
	queue.Pop();
	std::this_thread::sleep_for (std::chrono::microseconds(iSecret));
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();

}