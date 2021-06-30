#pragma once
#include "Queue.h"

template <class T>
void produce(Queue<T>& queue) {
	queue.Push(10);
	queue.Push(20);
	queue.Push(30);
	queue.Push(40);
	queue.Push(50);
	queue.Push(60);
	queue.Push(70);
	queue.Push(80);
}


template <class T>
void consume(Queue<T>& queue) {
	queue.Pop();
	queue.Pop();
	queue.Pop();

}