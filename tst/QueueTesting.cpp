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
    QueueInts queue(10000);	
    EXPECT_EQ (queue.Size(),   0); 
    std::thread produce(produce<int>, std::ref(queue));
	std::thread consume(consume<int>, std::ref(queue));
    produce.join();
	consume.join(); 	
    EXPECT_EQ (queue.Size(),   0); 
}
