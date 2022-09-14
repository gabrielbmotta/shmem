#include "sharedmem.hpp"
#include <iostream>

void* createShmem(key_t key)
{
    int shmid = shmget(key, sizeof(Data), 0644|IPC_CREAT);
    if (shmid == -1) {
        std::cerr<<"Invalid shared mem id.\n";
        exit(1);
    }

    void* shmp = shmat(shmid, NULL, 0);

    if (shmp == (void *) -1) {
        std::cerr<<"Invalid shared mem pointer.\n";
        exit(1);
    }

    return shmp;
}

void* getShmem(key_t key)
{
    int shmid = shmget(key, sizeof(Data), 0644);
    if (shmid == -1) {
        std::cerr<<"Invalid shared mem id.\n";
        exit(1);
    }

    void* shmp = shmat(shmid, NULL, 0);

    if (shmp == (void *) -1) {
        std::cerr<<"Invalid shared mem pointer.\n";
        exit(1);
    }

    return shmp;
}

void killShmem(key_t key)
{
    int shmid = shmget(key, sizeof(Data), 0644);
    if (shmid == -1) {
        std::cerr<<"Invalid shared mem id.\n";
        exit(1);
    }
    shmctl(shmid, IPC_RMID, NULL);
}