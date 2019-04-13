#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>


pthread_t tid[10];

void* proses1(){
	system("ps -aux | head -10 > /home/isnaini/Documents/FolderProses1/SimpanProses1.txt");//disimpan didalam SimpanProses1.txt (Proses1) hnya untuk 10 baris saja
}

void* proses2(){
	system("ps -aux | head -10 > /home/isnaini/Documents/FolderProses2/SimpanProses2.txt");//disimpan didalam SimpanProses2.txt (Proses2) hanya 10 baris saja
}

void* zip1(){
	system("zip -j /home/isnaini/Documents/FolderProses1/KompresProses1.zip /home/isnaini/Documents/FolderProses1/SimpanProses1.txt");// kemudian file di zip dari SimpanProses1.txt ke KompresProses1.zip
	system("rm /home/isnaini/Documents/FolderProses1/SimpanProses1.txt");// untuk menghapus SimpanProses1 yang lama
	sleep(15);// disleep selama 15 detik
	printf("Menunggu selama 15 detik\n");
}

void* zip2(){
	system("zip -j /home/isnaini/Documents/FolderProses2/KompresProses2.zip /home/isnaini/Documents/FolderProses2/SimpanProses2.txt");// disimpan di dalam SimpanProses2.txt(Proses2) hanya 10 baris saja
	system("rm /home/isnaini/Documents/FolderProses2/SimpanProses2.txt");//file lama dihapus
	sleep(15);// disleep selama 15 detik
	printf("Menunggu selama 15 detik\n");
}

void* unzip1(){
	system("unzip /home/isnaini/Documents/FolderProses1/KompresProses1.zip -d /home/isnaini/Documents/FolderProses1/");// diekstrak atau di unzip di dalam FolderProses1
}

void* unzip2(){
	system("unzip /home/isnaini/Documents/FolderProses2/KompresProses2.zip -d /home/isnaini/Documents/FolderProses2/");// diekstrak atau di unzip di dalam FolderProses1
}

int main()
{	int i=2;
	int j=2;

	pthread_create(&(tid[2]),NULL,&proses1,NULL);
	pthread_create(&(tid[3]),NULL,&proses2,NULL);
	pthread_join(tid[2],NULL);
	pthread_join(tid[3],NULL);
	pthread_create(&(tid[4]),NULL,&zip1,NULL);
	pthread_create(&(tid[5]),NULL,&zip2,NULL);
	pthread_join(tid[4],NULL);
	pthread_join(tid[5],NULL);
	pthread_create(&(tid[6]),NULL,&unzip1,NULL);
	pthread_create(&(tid[7]),NULL,&unzip2,NULL);
	pthread_join(tid[6],NULL);
	pthread_join(tid[7],NULL);
}
