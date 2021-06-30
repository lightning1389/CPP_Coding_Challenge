
# Description 
Thank you very much for the interesting challenge - it was a pleasure and pain at the same time :)

## Prerequisite
For the purpose of compilation, I have added the prerequisites in the following list: 

- Cmake 3.20
- windows machine (sleep method - can be excluded) 
- MinGW64 - Google Test Library, relies on it- otherwise, the program would still work with MinGW

## Installation

As you are already on my Github page please checkout the folder with: 

```bash
git clone --recursive https://github.com/lightning1389/CPP_Coding_Challenge.git
```

## Usage
In order to build the project you just need to create the CMake environment: 


```Cmake
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"
```

and to finally build the executables, please execute the following command: 

```GNU
make all
```
voilà, the executables are located in build/src and build/tst, respectively.


## Known Issues
There can only be one outstanding pop or push transaction.

## Performance

Performance-wise there are many points that are worth mentioning: 

Through the circular array usage, the insertion and deletion /Push&Pop are linear: 
- Push 0(1)
- Push 0(1)

Nevertheless, through the usage of mutex Locks, the time can be increased.
Another point worth mentioning: 

- The interface only allows copies to be transferred, instead of the actual object. A good solution would be r-value reference, like: 

```CPP
  void push(T&& element)
```
- the mutex locks costs a lot of runtimes and probably a single-threaded for each queue will be a better choice - after all a queue is a bottle-neck. 


## License
open license
