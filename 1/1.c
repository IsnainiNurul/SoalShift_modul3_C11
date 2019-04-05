#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>

int arr[10000];
pthread_t tid[50];
int val;

void* faktorial(void* args){
    unsigned long long fctr=1;
	long long faktorial = 1;
	int temp;
	temp = val;
	while(val!=0){
		faktorial = faktorial * val;
		val = val - 1;
	}
	printf(" %d! Hasil Faktorial = %lld\n",temp,faktorial);
	
	}


void swap(int *ab, int *cd) 
{ 
    int simpan = *ab; 
    *ab = *cd; 
    *cd = simpan; 
} 

void sort(int arr[]){
  for(int i=0; arr[i]!='\0'; ++i)
  {
   for(int j=i+1;arr[j]!='\0';++j)
   {
     if(arr[i] > arr[j])
     {
	swap(&arr[i],&arr[j]);
     }
    }
   }
}

int main(){
  int i=0, j=0,order,x;
  char temp;
  do {
      scanf("%d%c", &arr[i], &temp);
      i++;
  } while(temp != '\n');
	sort(arr);
   j=0;
   
  while(arr[j]!='\0') {
    val = arr[j];
	order=arr[j];
	pthread_create(&tid[order], NULL, &faktorial,(void *)&val);
	pthread_join(tid[order],NULL);
    j=j+1;
  }
    
    return 0;
}

