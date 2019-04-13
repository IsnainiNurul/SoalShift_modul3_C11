#include <stdio.h>
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
}
