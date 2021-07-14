#include <thread>
#include <iostream>
#include "producerAndConsumer.h"
#include <mutex>



int main()
{
    typedef Queue<int> QueueInts;
    typedef Queue<float> QueueFloats;
    QueueInts queue(8);                        // Queue created with 7 elements
    std::thread produce1(produce<int>, std::ref(queue));    
    std::thread consume1(consume<int>, std::ref(queue));
    produce1.join();
    consume1.join(); 
    std::cout << "Result of Queue "; 
    queue.printfQueue(); 
    std::cout << std::endl << std::endl; 
    
    std::cout << "Result of queue copy constructor "; 
    QueueInts queuecopied(queue);             // copy constructor
    queuecopied.printfQueue(); 
    std::cout << std::endl << std::endl; 


    std::cout << "Result of queue copy assignment " ; 
    QueueInts queueAssigned = queue;         // copy assignment
    queueAssigned.printfQueue(); 
    std::cout << std::endl << std::endl; 


    std::cout << "Result of queue copy move operator ";  
    QueueInts queueMoved = std::move(queue); // calls implicit move constructor
    queueMoved.printfQueue(); 
    std::cout << std::endl << std::endl; 

    
    getchar();
    return 0;
}