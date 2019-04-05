#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <stdlib.h>

void main()
{
        key_t key = 1234;
        int *nilai, choose, jalan =1;
        int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
	while(jalan=1)
	{
	   nilai = shmat(shmid, NULL, 0);
	   printf("Food Stock = %d\n1.Restock\n2.Exit\n",*nilai);
	   scanf("%d",&choose);        
		if(choose==1)
		{ 
		*nilai = *nilai + 10;
		}
		else if (choose==2)
		exit(0);
	}       
	shmdt(nilai);
        shmctl(shmid, IPC_RMID, NULL);
}
