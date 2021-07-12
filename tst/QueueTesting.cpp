#include "gtest/gtest.h"
#include "Queue.h"
#include <thread>
#include "producerAndConsumer.h"
#include <iostream>


TEST(SimplePushPop, test1) {
    EXPECT_EQ (6,   6);  // 7 Push - 3 Pops = 4

    typedef Queue<int> QueueInts;
	typedef Queue<float> QueueFloats;
    QueueInts queue(8);	
    queue.Push(10);
	queue.Push(20);
	queue.Push(30);
	queue.Push(40);
	queue.Push(50);
	queue.Push(60);
	queue.Push(70);
    EXPECT_EQ (queue.Size(),  7);
    queue.Pop();
	queue.Pop();
	queue.Pop();
    EXPECT_EQ (queue.Size(),   4);
    EXPECT_EQ (queue.Count(),   8);  // 7 Push - 3 Pops = 4
    
}

TEST(Sanity_Test, test2) {
    // Sanity tests
    typedef Queue<int> QueueInts;
	typedef Queue<float> QueueFloats;
    QueueInts queue(10000);	
    EXPECT_EQ (queue.Count(),   10000);
}

TEST(MultithreadedApplication, test2) {
    // multi threaded application test
    typedef Queue<int> QueueInts;
	typedef Queue<float> QueueFloats;
    QueueInts queue(9);	
    EXPECT_EQ (queue.Size(),   0); 
    std::thread produce1(produce<int>, std::ref(queue));
	std::thread consume1(consume<int>, std::ref(queue));
    std::thread produce2(produce<int>, std::ref(queue));
	std::thread consume2(consume<int>, std::ref(queue));
    // Multithreaded Application with produce pushing nearly twice as much as array size
    produce1.join();    // Queue will be full!
    produce2.join();    // multipile data being stalled
	consume1.join(); 	// threads need to wait in order to work on the data
	consume2.join(); 	

    EXPECT_EQ (queue.Size(),   0); 
}
