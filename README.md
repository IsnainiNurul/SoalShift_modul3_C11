Soal Shift Modul 3

Isnaini Nurul KurniaSari (05111740000010)

Argo Galih Pribadi       (05111740000150)

**_Soal 1_**

Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan

Contoh:

./faktorial 5 3 4

3! = 6

4! = 24

5! = 120

Berikut ini adalah Source Code dan Penjelasan:

```#include<pthread.h>
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
    printf("%d! = %lld\n", arr[a], hasil[arr[a]]);//fungsi untuk print hasil
    a++;
   }
}
``` 
**Penjelasan**

1. Sorting

```void Sorting(int array[], int n) // menggunakan sorting BubbleSort
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
```
- Kami menggunakan sorting BubbleSort dan kami urutkan secara ascending, kami juga menggunakan fungsi swap.


2. Fungsi Faktorial, berikut ini adalah fungsi faktorial yang kami gunakan:

```oid* faktorial(void* fact)//menggunakan fungsi faktorial
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
```

3. Fungsi pada Int Main

```int panjang=count-1;```

- terdapat count yang harus dikurang satu karena jika tdk dikurang maka ./(namafile) akan terhitung dalam proses 

```arr[a]= atoi (string[a]);```

- ini adalah syntax atoi yang berfungsi untuk mengubah sring menjadi sebuah integer

```pthread_create(&(tid[a]),NULL,&faktorial,&arr[a]);```

- adalah perintah untuk melakukan perintah secara parallel (bersama-sama).Membuat thread agar bisa menjalankannya perintah secara parallel (banyak input).

``` pthread_join(tid[a],NULL);```

- perintah ini  menggunakan join thread agar program selesainya bersama (parallel).



**_Soal 2_**

Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi sebagai berikut:

- Terdapat 2 server: server penjual dan server pembeli

- 1 server hanya bisa terkoneksi dengan 1 client

- Server penjual dan server pembeli memiliki stok barang yang selalu sama

- Client yang terkoneksi ke server penjual hanya bisa menambah stok

- Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1

- Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok--

- Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1

- Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok

- Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”

- Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”

- Server penjual akan mencetak stok saat ini setiap 5 detik sekali

- Menggunakan thread, socket, shared memory

**Penjelasan dan Source Code**

1. Source Code untuk client-pembeli

```#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8008
  
int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    char beli[10];

    while(1){

        scanf("%s",beli);
        send(sock , beli , strlen(beli) , 0 );

        valread = read( sock , buffer, 1024);
        printf("%s\n",buffer );

        memset(buffer,0,sizeof(buffer));
        
    }
    return 0;
}

```

2. Source Code untuk server-pembeli

```
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define PORT 8008

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *membeli = "Berhasil membeli";
    char *habis = "Barangnya habis shay";
    key_t key = 1234;
    int *jumlah_barang;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    jumlah_barang = shmat(shmid, NULL, 0);

    *jumlah_barang = 1;
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    while(1){
        printf("%d\n", *jumlah_barang);
        valread = read( new_socket , buffer, 1024);
        printf("%s\n",buffer );
        if(strcmp(buffer,"beli")==0){
            if(*jumlah_barang > 0){
                *jumlah_barang = *jumlah_barang -1;
                send(new_socket , membeli, strlen(membeli),0);
            }
            else {
                send(new_socket, habis, strlen(habis),0);
            }
        }

    }
    return 0;
}
```

3. Source Code untuk client-penjual

```#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define PORT 8082

int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
  
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    char tambah[10];

    while(1){
        scanf("%s",tambah);
        send(sock , tambah , strlen(tambah) , 0 );
        valread = read( sock , buffer, 1024);
        printf("%s\n",buffer );
        memset(buffer,0,sizeof(buffer));
        
    }
    return 0;
}

```

4. Source Code untuk server-penjual

```#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#define PORT 8082

pthread_t tid[1];
key_t key = 1234;
int *jumlah_barang;

void* count(void* ptr){
    int num;
    while(1){
        num = *jumlah_barang;
        printf("Jumlah Barang sekarang : %d \n", num );
        sleep(5);
    }
}

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *menambah = "Berhasil menambah";
    char *salah = "Kata kunci salah";

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    jumlah_barang = shmat(shmid, NULL, 0);

    *jumlah_barang = 1;
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    printf("Server Mulai");

    int th = pthread_create(&(tid[1]),NULL,count,NULL);

//    close(server_fd);
    while(1){

        valread = read( new_socket , buffer, 1024);

        if (strcmp(buffer,"tambah")==0){
            *jumlah_barang = *jumlah_barang + 1;
            send(new_socket , menambah , strlen(menambah) , 0 );
            
        }
        else {
            send(new_socket , salah , strlen(salah) , 0 );
        }
    }
    return 0;
}
```

**Penjelasan :**

- Disini kita akan membuat client-pembeli, client-penjual, server-pembeli, serta server-penjual.

- Kita membuat client-pembeli yang nantinya akan membeli barang dan kita juga menggunakan server-pembeli.dan ketika client
pembeli, ketika scan "beli" maka akan di send ke server dan menerima pesan dari server pembeli.server pembeli nantinya akan
meread "beli" tersebut, dan ketika stok masih ada, maka akan berkurang 1 jumlah stock barangnya dan mengirim pesan pada client 
bahwa telah terbeli stock barang tersebut.

- client penjual ketika men-scan "tambah" maka akan di send ke server, menerima pesan dari server dan meng-print stok yang ada
setiap 5 detik -server penjual meread tambah, maka jumlah +1 dan mengirim pesan berhasil menambah pada client.


**Soal 3**

Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang

berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan 

Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan 

iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau 

membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi 

sebagai berikut:

- Terdapat 2 karakter Agmal dan Iraj

- Kedua karakter memiliki status yang unik

- Agmal mempunyai WakeUp_Status, di awal program memiliki status 0

- Iraj memiliki Spirit_Status, di awal program memiliki status 100

- Terdapat 3 Fitur utama

- All Status, yaitu menampilkan status kedua sahabat

Ex: 

Agmal WakeUp_Status = 75 

Iraj Spirit_Status = 30

“Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point

“Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point

- Terdapat Kasus yang unik dimana:

- Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik 
(Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)

- Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
Program akan berhenti jika Salah Satu :
WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)

- Syarat Menggunakan Lebih dari 1 Thread

**Source Code dan Penjelasan**


```#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

pthread_t tid1, tid2;// inisalisasi pthread
int wk_stat=0;// wakeup status
int sp_stat=100;//kondisi awal untuk spirit status sesuai dengan soal 
int fitur;// pilihan menu untuk menjalankan no 1/2/3
int agflag=0;//menandai ketika agmal bangun ag flag akan bertambah 1
int irflag=0;//menandai iraj ketika iraj bangun ag flag akan bertambah 1

void *t_agmal(){//untuk agmal
    while(1)
    {
        if(fitur == 2) // jika pilihan fitur menu memilih nomor 2
        {
            wk_stat += 15;// maka wakeup status agmal akan bertambah 15
            printf("\nWakeup_status Agmal %d\n", wk_stat);
            agflag += 1;// agflag akan bertambah 1
            irflag = 0;// dan irflag akan direset dari 0
            fitur = 0;// pilihan menu diriset mulai dari 0 lagi 
        }
        if(irflag == 3)// jika irflag sudah 3(memanggil Agmal Ayo Bangun sebanyak 3 kali)
        {
            printf("\nFitur Agmal Ayo Bangun disabled 10 s\n");// maka Agmal Ayo Bangun disable selama 1 detik
            sleep(10);// dan akan disleep selama 10 detik
            irflag = 0;// direset menjadi 0 lagi 
        }

    }
}

void *t_iraj(){// untuk iraj
    while(1)
    {
        if(fitur == 3)// jika pilihan menu 3
        {
            sp_stat -= 20;//maka spirit status berkurang 20 ketika kita memilih no 3 yaitu Iraj Ayo Tidur
            printf("\nSpirit_status Iraj %d\n", sp_stat);
            irflag += 1;// dan irflag akan bertambah 1
            agflag = 0;// direset menjadi 0 lagi mulai awal
            fitur = 0;// direset menjadi 0 lagi mulai dari awal
        }
        if(agflag == 3)// jila agflag sudah sebanyak 3 kali 
        {
            printf("\nFitur Iraj Ayo Tidur disabled 10 s\n");
            sleep(10);// fitur Iraj Ayo Tidur akan disable selama 10 detik
            agflag = 0;//agflag diset menjadi awal yaitu 0 lagi
        }

    }
}

int main(){

    pthread_create(&(tid1), NULL, &t_agmal, NULL);
    pthread_create(&(tid2), NULL, &t_iraj, NULL);

    while(1){
        if(wk_stat >= 100)// jika wk_stat kurang dari smaa dengan 100 
        {
            printf("\nAgmal Terbangun, mereka bangun pagi dan berolahraga\n");// akan mencetak hasilnya
            return 0;
        }
        if(sp_stat <= 0)// jika sp_stat kurang dari sama dengan 0 
        {
            printf("\nIraj ikut tidur, dan bangun kesiangan bersama Agmal\n");// akan mencetak hasilnya
            return 0;
        }

        printf("\n1. All Status\t 2. Agmal Ayo Bangun\t 3. Iraj Ayo Tidur\n");//pilihan fitur menu 
        scanf("%d", &fitur);

        if(fitur == 1)// untuk mencetak fitur All Status
        {
            printf("\nAgmal WakeUp_Status = %d\n", wk_stat);
            printf("Iraj Spirit_Status = %d\n", sp_stat);
        }
    }

    return 0;
}```
```


**Soal 4**

Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip 

- Dengan Syarat : 

- Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama

- Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama

- Ketika Mengekstrak file .zip juga harus secara bersama-sama

- Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”

- Wajib Menggunakan Multithreading

- Boleh menggunakan system

**Source Code dan Penjelasan**

```
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
```


**Soal 5**

Angga, adik Jiwang akan berulang tahun yang ke sembilan pada tanggal 6 April besok. Karena lupa menabung, Jiwang tidak mempunyai 

uang sepeserpun untuk membelikan Angga kado. Kamu sebagai sahabat Jiwang ingin membantu Jiwang membahagiakan adiknya sehingga 

kamu menawarkan bantuan membuatkan permainan komputer sederhana menggunakan program C. Jiwang sangat menyukai idemu tersebut. 

Berikut permainan yang Jiwang minta. 

Pemain memelihara seekor monster lucu dalam permainan. Pemain dapat  memberi nama pada monsternya.

Monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 10 detik.Ketika 

hunger status mencapai angka nol, pemain akan kalah. Hunger status dapat bertambah 15 apabila pemain memberi makan kepada 

monster, tetapi banyak makanan terbatas dan harus beli di Market.

Monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. Ketika hygiene status mencapai 

angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. Pemain dapat memandikannya 

setiap 20 detik(cooldownnya 20 detik).

Monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi)daa 5 setiap 10 detik 

ketika monster dalam keadaan standby.

Monster pemain dapat memasuki keadaan battle. Dalam keadaan ini, food status(fitur b), hygiene status'(fitur c), dan ‘regenerasi’

(fitur d) tidak akan berjalan. Health status dari monster dimulai dari darah saat monster pemain memasuki battle. Monster pemain 

akan bertarung dengan monster NPC yang memiliki darah 100. Baik monster pemain maupun NPC memiliki serangan sebesar 20. Monster 

pemain dengan monster musuh akan menyerang secara bergantian.

Fitur shop, pemain dapat membeli makanan sepuas-puasnya selama stok di toko masih tersedia.

Pembeli (terintegrasi dengan game)

Dapat mengecek stok makanan yang ada di toko.

Jika stok ada, pembeli dapat membeli makanan.

Penjual (terpisah)

Bisa mengecek stok makanan yang ada di toko

Penjual dapat menambah stok makanan.

Spesifikasi program:

Program mampu mendeteksi input berupa key press. (Program bisa berjalan tanpa perlu menekan tombol enter)

Program terdiri dari 3 scene yaitu standby, battle, dan shop.

Pada saat berada di standby scene, program selalu menampilkan health status, hunger status, hygiene status, stok makanan tersisa, 

dan juga status kamar mandi (“Bath is ready” jika bisa digunakan, “Bath will be ready in [bath cooldown]s” jika sedang cooldown). 

Selain itu program selalu menampilkan 5 menu, yaitu memberi makan, mandi, battle, shop, dan exit. Contoh :

Standby Mode

Health : [health status]

Hunger : [hunger status]

Hygiene : [hygiene status]

Food left : [your food stock]

Bath will be ready in [cooldown]s

Choices

Eat

Bath

Battle

Shop

Exit

Pada saat berada di battle scene, program selalu menampilkan health status milik pemain dan monster NPC. Selain itu, program 

selalu menampilkan 2 menu yaitu serang atau lari. Contoh :


Battle Mode

Monster’s Health : [health status]

Enemy’s Health : [enemy health status]

Choices

Attack

Run

Pada saat berada di shop scene versi pembeli, program selalu menampilkan food stock toko dan milik pemain. Selain itu, program 

selalu menampilkan 2 menu yaitu beli dan kembali ke standby scene. Contoh :

        Shop Mode
        Shop food stock : [shop food stock]
        Your food stock : [your food stock]
        Choices
Buy

Back

Pada program penjual, program selalu menampilkan food stock toko. Selain itu, program juga menampilkan 2 menu yaitu restock dan exit. Contoh :

Shop

Food stock : [shop food stock]

Choices

Restock

Exit

Pastikan terminal hanya mendisplay status detik ini sesuai scene terkait (hint: menggunakan system(“clear”))

Berikut ini adalah source code dan penjelasan :
* Disini kami menggunakan pthread untuk Thread merupakan sebuah alur kontrol proses yang dapat dijadwalkan pengeksekusiannya oleh sistem operasi. Selanjutnya, bayangkan sebuah program main mempunyai berbagai prosedur (fungsi) dan fungsi-fungsi tersebut dapat dijalankan secara serentak dan atau bebas dijalankan oleh sistem operasi, sehingga pthread sangat diperlukan.
* Dan disini kami menggunakan 9 pthread (yang nantinya akan menampung thread tersebut.
* Penjelasan source code dibawah ini, perintah ini untuk melakukan getch yaitu untuk menginputkan integer tanpa perintah enter.

**Source Code dan Penjelasan**

```
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>

int bilangan=0, status = 1;
int lawan = 100, sehat =300, lapar = 200, bersih =100, makanan = 100;
int stok = 100, mandi = 0, pilihan = 0;
char monster[] = "";
pthread_t tid[9];//inisialisasi array untuk menampung thread dalam kasusu ini ada 2 thread
char print[]=""; //="print";

int mygetch(void)//diklik lgsung enter mengirimkan input tanpa enter
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
	scanf("%s",monster);
	while(status)
	{
    	if(pilihan != 51 && pilihan !=52)
	{
	system("clear");
	printf("\n1.Health: %d \n2.Hunger: %d \n3.Hygiene : %d \n4.Food left : %d\n Mandi akan siap dalam waktu %d detik\n",sehat,lapar,bersih,makanan,mandi);
	printf("Pilihan \n 1.Eat \n 2.Bath \n 3.Battle \n 4.Shop \n 5.Exit\n");
	printf("Pilihan = ");
	pilihan=mygetch();
	if(pilihan == 53)exit(0);
	}
	}

    }

    else if(pthread_equal(id,tid[1]))
    {	
	while(status){
	
     //code here Lapar
     if(pilihan !=51){//ketika pilihannya  selain 3
    	 if(lapar>0)
	 	lapar = lapar - 5;//tiap 10 detik
		 else {
		 printf("GAME OVER");
		 exit(0);	
		 }
		 sleep(10);
		}
	}
	}
	
	
	
    else if(pthread_equal(id,tid[2]))
    {	
	
	while(status){
		//Code here HYGIENE
		if(pilihan != 51){
			bersih = bersih - 10;//tiap 30 detik
			if(bersih <= 0){
				printf("GAME OVER");
				exit(0);
			}
			sleep(30);
		}
	}

}
    else if(pthread_equal(id,tid[3]))
    {	
	
	while(status){
	//Code Here Healt
	if(pilihan != 51){
	
		sehat = sehat + 5;
		if(sehat<=0){
			printf("GAME OVER");
			exit(0);
		}
		sleep(10);
	}
	}
	
}
   else if(pthread_equal(id,tid[4]))
    {	
	
	while(status){
	//Code Here	
	if(mandi!=0)
	mandi = mandi - 1 ;
	sleep(1);
	}
        }

	else if(pthread_equal(id,tid[5]))
    {	
	
	while(status){
	//Code Here
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
	//Code Here
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
	//Code Here
	
	int tarung = 1;
	if(pilihan == 51){
		while(tarung == 1){
		
	system("clear");
		printf("Kesehatan Monster = %d\n",sehat);
		printf("Kesehatan Musuh = %d\n",lawan);
		printf("Choices \n1. Menyerang \n2. Lari\n");
		pilih = mygetch();
		//scanf("%d",&pilih);
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
	//Code Here
	
	int tarung = 1;
	if(pilihan == 52){
		while(tarung == 1){
		
	system("clear");
		printf("Shop Food Stock = %d\n",*value);
		printf("Your Food Stock = %d\n",makanan);
		printf("Choices \n1. Buy \n2. Back\n");
		//scanf("%d",&pilih);
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
    	pthread_join(tid[0],NULL), (tid[1],NULL), (tid[2],NULL),(tid[3],NULL), (tid[4],NULL), 		(tid[5],NULL), (tid[6],NULL), (tid[7],NULL),(tid[8],NULL);
    	return 0;
}
```



