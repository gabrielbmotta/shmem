#include "sharedmem.hpp"

#include <iostream>

#define SHM_KEY 0x1444

int main()
{
    void* shmp = createShmem(SHM_KEY);

    std::atomic<Data> init_data;
    memcpy(shmp, &init_data, sizeof(std::atomic<Data>));

    std::cout << "I output an incrementing number every 10 milliseconds.\n";

    auto* output_data_ptr = (std::atomic<Data>*)shmp;
    for(int i = 0; i < INT32_MAX; ++i){
        auto time = std::chrono::system_clock::now();
        
        std::cout <<"\t\t\t\t\t\r" << std::flush;
        std::cout << "Outputting Data: " << i;
        Data new_data;
        new_data.my_data = i;
        new_data.timestamp = time;
        
        output_data_ptr->store(new_data);

        usleep(10000);
    }
    killShmem(SHM_KEY);

    return 0;
}