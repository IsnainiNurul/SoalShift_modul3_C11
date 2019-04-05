#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <termios.h>

int bilangan=0, status = 1;
int lawan = 100, sehat =300, lapar = 200, bersih =100, makanan = 100;
int stok = 100, mandi = 0, pilihan = 0;
char monster[] = ".";
pthread_t tid[9];//inisialisasi array untuk menampung thread dalam kasusu ini ada 2 thread
char print[]=""; //="print";

int mygetch(void)
{
   struct termios oldt,
   newt;
   int ch;
   tcgetattr( STDIN_FILENO, &oldt );
   newt = oldt;
   newt.c_lflag &= ~( ICANON | ECHO );
   tcsetattr( STDIN_FILENO, TCSANOW, &newt );
   ch = getchar();
   tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
   return ch;
}

void* playandcount(void *arg)
{
    unsigned long i=0;
    pthread_t id=pthread_self();
    int iter, *value;
    key_t key = 1234;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);   
    *value = stok; 
    if(pthread_equal(id,tid[0]))//thread untuk menjalankan counter
    {
	    printf("Nama Monster = ");
	    while(status){
    	if(pilihan != 51 && pilihan !=52 && monster[0]!='.')//ketika pilihan bukan ketiga dan bukan pilihan kedua
	    {
	      system("clear");
	      printf("\nStand by Mode \n1.Health: %d \n2.Hunger: %d \n3.Hygine : %d \n4.Food left : %d\n Bath will be ready in %d s\n",sehat,lapar,bersih,makanan,mandi);
	      printf("Choices \n1.Eat \n2.Bath \n3.Battle \n4.Shop \n5.Exit\n");  
	      printf("Pilihan = ");
	      if(pilihan == 53)exit(0);
	    }
	    }
    }
    else if(pthread_equal(id,tid[1]))
      {	
	    while(status)
	     {
     	  if(pilihan !=51)//bilangan asci pilihan ketiga
	     {
	    sleep(10);
    	if(lapar>0)
	    lapar = lapar - 5;
	    else 
	    {
	      printf("GAME OVER");
	      exit(0);	
	    }
	    }
	    }
	  }
      else if(pthread_equal(id,tid[2]))
      {	
	      while(status)
	    {
	    if(pilihan != 51)
	    {
	     sleep(30);
	     bersih = bersih - 10;
	     if(bersih <= 0)
	      {
	        printf("GAME OVER");
	        exit(0);
	      }
	      }
	      }
      }
        else if(pthread_equal(id,tid[3]))
        {	
      	while(status){
	      if(pilihan != 51){
	      sleep(10);
	      sehat = sehat + 5;
	      if(sehat<=0){
	      printf("GAME OVER");
	      exit(0);
	      }
	      }
	      }	
      }
        else if(pthread_equal(id,tid[4]))
        {	
	        while(status){	
        	if(mandi!=0)
	        mandi = mandi - 1 ;
	        sleep(1);
	      }
       }

	      else if(pthread_equal(id,tid[5]))
        {	
        	while(status){
	        if(makanan!=0)
	        if(pilihan == 49){
	        lapar = lapar + 15;
	        makanan = makanan - 15;
	        pilihan = 0;
	        if(makanan <0)makanan = 0;
	        sleep(1);
	      }
	      }
        }
      	else if(pthread_equal(id,tid[6]))
        {	
	        while(status){
	        if(pilihan == 50){
	        if(mandi == 0){
	        bersih = bersih + 30;		
	        mandi = 20;
	        pilihan = 0;
      	}
	      }
	      }
	      }
	      else if(pthread_equal(id,tid[7]))
        {	
	      int pilih;
	      while(status){
	      int tarung = 1;
	      if(pilihan == 51){
		    while(tarung == 1){	
	      system("clear");
		    printf("Kesehatan Monster = %d\n",sehat);
		    printf("Kesehatan Musuh = %d\n",lawan);
		    printf("Choices \n1. Menyerang \n2. Lari\n");
		    pilih = mygetch();
		    if(pilih == 49){
			  sehat = sehat - 20;
			  lawan = lawan - 20;
			  if(sehat <=0){
				printf("Anda Kalah\n");
				tarung = 0;
				pilihan = 0;
			  }
			    else if(lawan<=0){
				   printf("Anda Menang\n");
				   tarung = 0;
				   pilihan = 0;
				   lawan = 100;
			  }
		}		
		else {	
		pilihan = 0;
		tarung = 0;
		}
		}
	}
	}	
	}
	else if(pthread_equal(id,tid[8]))
    {	
	int pilih;
	while(status){
	int tarung = 1;
	if(pilihan == 52){
		while(tarung == 1){
		
	  system("clear");
		printf("Shop Food Stock = %d\n",*value);
		printf("Your Food Stock = %d\n",makanan);
		printf("Choices \n1. Buy \n2. Back\n");
		pilih = mygetch();
		if(pilih == 49){
			makanan = makanan + 20;
			*value = *value - 20;
			if(*value <=0){
				printf("Stok Habis\n");
				tarung = 0;
				pilihan = 0;
			}
		}		
		else {	
		pilihan = 0;
		tarung = 0;
		}
		}	
	}
	}
	}
	else if(pthread_equal(id,tid[9]))
    {	
	scanf("%c",monster);
	while(status){
	if(pilihan != 51 && pilihan !=52 && monster[0] != '.')
	pilihan = mygetch();
	
	}
}
}

int main(void)
{		
    int i=0;
    int error;
    while(i<10)//looping membuat thread 2x
    {
        error=pthread_create(&(tid[i]),NULL,&playandcount,NULL);//membuat thread
        if(error!=0)//cek error
        {
            printf("\n can't create thread : [%s]",strerror(error));
        }
        i++;
    }
    	pthread_join(tid[0],NULL), (tid[1],NULL), (tid[2],NULL),(tid[3],NULL), (tid[4],NULL), 		(tid[5],NULL), (tid[6],NULL), (tid[7],NULL),(tid[8],NULL), (tid[9],NULL);
    	return 0;
}


