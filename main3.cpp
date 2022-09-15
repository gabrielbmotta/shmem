#include "sharedmem.hpp"

#include <iostream>

#define SHM_KEY 0x1555

int main()
{
    void* shmem_ptr_input = getShmem(SHM_KEY);

    std::cout << "I check my input every 2 second and print it out.\n" << std::flush;

    auto check_time = std::chrono::system_clock::now();

    auto* input_data_ptr = (std::atomic<Data>*)shmem_ptr_input;
    while(true){
        auto data = input_data_ptr->load();
        if (data.timestamp > check_time){
            std::cout <<"\t\t\t\t\t\r" << std::flush;
            std::cout << "Incoming data: " << data.my_data << std::flush;
            check_time = data.timestamp;
        }
        
        sleep(2);
    }

    return 0;
}