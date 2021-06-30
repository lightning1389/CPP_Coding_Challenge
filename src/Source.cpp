#include <thread>
#include <iostream>
#include "producerAndConsumer.h"
#include <mutex>



int main()
{
	typedef Queue<int> QueueInts;
	typedef Queue<float> QueueFloats;
	QueueInts queue(7);	
	std::thread produce(produce<int>, std::ref(queue));
	std::thread consume(consume<int>, std::ref(queue));
	produce.join();
	consume.join(); 
	getchar();
	return 0;
}