#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <error.h>

#define PROCESS_MAX 3
#define PAUSE printf("press  enter to continue \n");fgetc(stdin);

typedef struct mlist{
    int val;
    struct mlist* next;
} mlist; 

int main(void){
    int shmid=shmget(ftok("/mnt/c/ipc_shm/a",'a'),1024,IPC_CREAT|0666);
    if(shmid==-1){perror("error");PAUSE return -1;}
    mlist* shmaddr=(mlist*)shmat(shmid,NULL,SHM_EXEC);
    (*shmaddr).val=1;
    (*shmaddr).next=NULL;

    printf("val:%d\n",(*shmaddr).val);

    // int process=fork();
    // if(process==0)
    // {
    //     return 0;
    // }

    shmdt(shmaddr);
    PAUSE;
    // system("pause");
    return 0;
}