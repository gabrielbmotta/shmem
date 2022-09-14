#include "sharedmem.hpp"

#include <iostream>

#define SHM_KEY 0x1444

int main()
{
    void* shmp = getShmem(SHM_KEY);
    auto my_timestamp = std::chrono::system_clock::now();

    while(true){
        auto* data = (Data*)shmp;
        data->m.lock();
        if (data->timestamp > my_timestamp){
            std::cout << "New Data: " << data->my_data << "\n";
            my_timestamp = data->timestamp;
        }
        data->m.unlock();
        
        sleep(1);
    }
}