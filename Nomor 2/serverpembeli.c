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
