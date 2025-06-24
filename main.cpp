#include <iostream>
#include <thread>

#include "logger.h"
void log(int i) {
    LOG_INFO("Well this is a debug line %d", i);
}
int main() {
    unsigned int num_threads = {std::thread::hardware_concurrency()*10};
    std::thread workers[num_threads];
    for(unsigned int i = 0; i < num_threads; i++){
        workers[i] = std::thread(log, i);
    }
    for(unsigned int i = 0; i < num_threads; i++){
        workers[i].join();
    }
}