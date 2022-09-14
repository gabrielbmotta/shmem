#include "sharedmem.hpp"

#include <iostream>

#define SHM_KEY 0x1444

int main()
{
    void* shmp = createShmem(SHM_KEY);

    Data initData;
    memcpy(shmp, &initData, sizeof(Data));

    for(int i = 0; i < 100000; ++i){
        auto* data = (Data*)shmp;
        data->m.lock();
        data->my_data = i;
        data->timestamp = std::chrono::system_clock::now();
        data->m.unlock();
        sleep(3);
    }
    killShmem(SHM_KEY);
}