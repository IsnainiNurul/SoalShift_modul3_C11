#include<pthread.h>
#include<stdio.h>
#include<math.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

long long hasil[1000];
pthread_t tid[50];
void Sorting(int array[], int n) // menggunakan sorting BubbleSort
{ 
   int i, j, temp; 
   for (i = 1; i <= n; i++)
       for (j = i + 1; j <= n; j++){  
           if (array[i] > array[j]){// untuk fungsi swap dalam variabel
		temp = array[j];
                array[j] = array[i];
                array[i] = temp;
           }
       }
} 

void* faktorial(void* fact)//menggunakan fungsi faktorial
{
    int* masukan;
    masukan = (int*) fact; 
    int bil= *masukan;
    int i=1;
    long long temp=1;
    while(i<=bil)
    {
        temp=temp*i;
	i++;
    }
    hasil[bil]=temp;
}

int main (int count, char *string[])
{
    int panjang=count-1;//dikurang satu karena jika tdk dikurang maka ./(nama) akan terhitung
    int arr[panjang];
    int a =1;
    pthread_t tid[panjang];
    while(a<=panjang)
    {
      arr[a]= atoi (string[a]);//mengubah sring mjd sebuah integer
      a++;
    }
   a=1;
   while(a<=panjang)
    {
      pthread_create(&(tid[a]),NULL,&faktorial,&arr[a]);//melakukan perintah secara parallel (bersama)
      a++;
    }
   a=1;
   while(a<=panjang)
   {
     pthread_join(tid[a],NULL);//agar selesainya bersama (paralel)
     a++;
   }
   Sorting(arr, panjang);
   a=1;
   while(a<=panjang)
   {
    printf("%d! = %lld\n", arr[a], hasil[arr[a]]);
    a++;
   }
}
