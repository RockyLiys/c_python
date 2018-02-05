// 读进程shm_read.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 4096

int main()
{
    void *shm_addr = NULL;

    int shmid;
    // 使用约定的键值打开共享内存
    shmid = shmget((key_t) 1234, BUF_SIZE, IPC_CREAT);
    printf("shmid : %u\n", shmid);
    if (shmid == -1)
    {
        perror("shmget error!");
        exit(1);
    }

    // 将共享内存附加到本进程
    shm_addr = shmat(shmid, NULL, 0);
    if (shm_addr == (void *) -1)
    {
        perror("shmat error!");
        exit(1);
    }

    // 读取数据
    char tmp[BUF_SIZE];
    bzero(tmp, BUF_SIZE);
    memcpy(tmp, shm_addr, BUF_SIZE);
    printf("read from shared memory: %s\n", tmp);

    sleep(5);

    // 分离
    if (shmdt(shm_addr) == -1)
    {
        printf("shmdt error!\n");
        exit(1);
    }

    // 删除共享内存
    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {
        printf("shmctl error!\n");
        exit(1);
    }
}
