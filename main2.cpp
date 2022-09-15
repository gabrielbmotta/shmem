#include "sharedmem.hpp"

#include <iostream>

#define SHM_KEY1 0x1444
#define SHM_KEY2 0x1555

int main()
{
    void* shmem_ptr_input = getShmem(SHM_KEY1);
    void* shmem_ptr_output = createShmem(SHM_KEY2);

    auto check_time = std::chrono::system_clock::now();
   
    Data d;
    d.my_data = 0;
    d.timestamp = check_time;

    std::atomic<Data> init_data;
    init_data.store(d);
    memcpy(shmem_ptr_output, &init_data, sizeof(std::atomic<Data>));


    std::cout << "I check if incoming data is a multiple of 23 every .1ms, and send out a running count.\n";

    int count = 0;

    auto* input_data_ptr = (std::atomic<Data>*)shmem_ptr_input;
    
    auto* output_data_ptr = (std::atomic<Data>*)shmem_ptr_output;

    while(true){
        auto data = input_data_ptr->load();
        if (data.timestamp > check_time){
            check_time = data.timestamp;

            if(data.my_data % 23 == 0){
                Data new_data;
                new_data.my_data = ++count;
                new_data.timestamp = check_time;

                output_data_ptr->store(new_data);
            }
            std::cout <<"\t\t\t\t\t\r" << std::flush;
            std::cout << "Incoming Data: " << data.my_data << " | Outputting: " << count;
        }
        
        usleep(100);
    }

    return 0;
}