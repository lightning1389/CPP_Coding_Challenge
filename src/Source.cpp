#include <thread>
#include <iostream>
#include "producerAndConsumer.h"
#include <mutex>



int main()
{
	typedef Queue<int> QueueInts;
	typedef Queue<float> QueueFloats;
	QueueInts queue(7);						// Queue created with 7 elements
	std::thread produce1(produce<int>, std::ref(queue));	
	std::thread consume1(consume<int>, std::ref(queue));
	std::thread produce2(produce<int>, std::ref(queue));	
	std::thread consume2(consume<int>, std::ref(queue));

	produce1.join();
	consume1.join(); 
	
	produce2.join();
	consume2.join(); 
	
	queue.printfQueue(); 

	getchar();
	return 0;
}