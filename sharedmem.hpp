#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>

#include <thread>
#include <chrono>

struct Data{
    std::mutex m;
    std::chrono::time_point<std::chrono::system_clock> timestamp;
    int my_data;
};

void* createShmem(key_t id);

void* getShmem(key_t id);

void killShmem(key_t id);