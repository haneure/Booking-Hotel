#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <conio.h>


struct bookv{           //Kedua struct ini berbeda karena kami gunakan untuk membedakan kamar hotel VIP dan Reguler
    char nama[30];      //Struct bookv untuk VIP
    char code [100];
    int no;
    int durasi;
    int date;
    int month;
    int year;
    int dateo;
    int montho;
    int yearo;
    int price;
    char kodebook[10];

    struct bookv *prev, *next;

} bookv;


struct bookr{
    char nama[30];      //struct bookr untuk Reguler
    char code[100];
    int no;
    int durasi;
    int date;
    int month;
    int year;
    int dateo;
    int montho;
    int yearo;
    int price;
    char kodebook[10];

    struct bookr *prev, *next;

}bookr;

struct tree
{
    char kode[10];
    struct tree *left;
    struct tree *middle;
    struct tree *right;
};


struct Queue{
    char nama[30];
    char stat[15];
    int nokamar;
    int durasi;
    int date;
    int month;
    int year;
    int dateo;
    int montho;
    int yearo;
    int price;
    char kodebook[10];

    struct Queue *next, *mae;
};

void enqueue (struct Queue **front, char nama[30],char stat[],int nokamar,int durasi,int date,int month,int year,int dateo,int montho,int yearo,int price,char kodebook[10], struct Queue **mae)
{
    struct Queue *temp = (struct Queue*)malloc(sizeof(struct Queue));
    strcpy(temp->nama, nama);
    strcpy(temp->stat, "Unapproved");
    temp->nokamar = nokamar;
    temp->durasi = durasi;
    temp->date = date;
    temp->month = month;
    temp->year = year;
    temp->dateo = dateo;
    temp->montho = montho;
    temp->yearo = yearo;
    temp->price = price * durasi;
    strcpy(temp->kodebook, kodebook);
    temp->next = NULL;



    if(*front==NULL)
    {
        *front = temp;
        *mae = temp;
    }
    else
    {
        struct Queue *ptr = *front;
        while(ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next=temp;
    }
};

void dequeue(struct Queue **front)
{
    struct Queue *hapus = *front;
    *front = (*front)->next;
    free(hapus);
}

int isempty(struct Queue *front)
{
    if(front==NULL)
        return 1;
    return 0;
}

int depan(struct Queue *front)
{
    return front->nama;
}

void userinput(struct bookr **pala, struct bookr **ini, struct bookr **ekor, struct bookv **head, struct bookv **curr, struct bookv **tail, struct bookr **titik, struct bookv **node, int *choice, struct Queue **mae, struct Queue **queue)
{
    char nama[30];
    int nokamar=0;
    int durasi;
    int date;
    int month;
    int year;
    int dateo = 0;
    int montho = 0;
    int yearo = 0;
    int sama=0;
    //char codbook;
    int pricer;
    int pricev;
    char kodebook[10];
    int i;
    srand((unsigned int)(time(NULL)));
    char pass[6];
    char password[10];
    char stat[15];
    strcpy(stat, "Unapproved");
    int pilihan;
    int tipe;


    printf("What do you want to do ?\n");
    printf("1. Input\n");
    printf("2. Approval\n");
    printf("3. Back\n");
    printf("Your choice : ");
    scanf("%d", &pilihan);
    if(pilihan==1){
            system("cls");
            printf("Pilih Tipe Kamar : \n");                    //Kami memisahkan menu ruang reguler dan VIP, agar memisahkan insert data ke booking VIP dan booking Reguler.
            printf("1. Reguler\n");
            printf("2. VIP\n");
            printf("Pilihan : ");
            scanf("%d", &(*choice));
            fflush(stdin);

            if(*choice==1)
            {
                system("cls");
                printf("Reguler");
                printf("\nTambahan Fitur Kamar :");
                printf("\n1. Single Bed + Shower (standard) = 300.000");
                printf("\n2. Twin Bed + Shower + TV (Standard) = 500.000");
                printf("\n3. Double Bed + Shower + TV + Breakfast (Standard) = 700.000");
                printf("\nPilihan : ");
                scanf("%d", &tipe);
                fflush(stdin);
                if(tipe==1)
                {
                    pricer = 300000;
                }else if(tipe==2)
                {
                    pricer = 500000;
                }else if(tipe==3)
                {
                    pricer = 700000;
                }
                printf("\nNama\t\t\t:");                          //Input data
                scanf("%[^\n]", &nama);
                printf("No Kamar\t\t:");
                scanf("%d", &nokamar);
                printf("Lama Menginap (hari)\t:");
                scanf("%d", &durasi);
                printf("Tanggal check-in (dd-mm-yyyy) \t: ");
                scanf("%d-%d-%d", &date, &month, &year);
                dateo = date + durasi;
                montho = month;
                yearo = year;
                if(dateo>31)                            //If ini untuk menyeseuaikan agar tiap hari tidak lebih dari 31 hari
                {
                    dateo -= 31;
                    montho++;
                    if(montho>12)                       //If ini untuk menyeseuaikan agar bulan tidak lebih dari 12 bulan
                    {fflush(stdin);
                        montho -= 12;
                        yearo++;                        //Jika bulan lebih dari 12, maka artinya 1 tahun, tahun di++
                    }
                }
                fflush(stdin);

                for (i = 0; i < 1; i++) {
                    pass[i] = rand() % 9;
                    char capLetter = 'A' + (rand() % 26);
                    pass[i + 2] = capLetter;
                    char letter = 'a' + (rand() % 26);
                    pass[i + 3] = letter;
                    sprintf(kodebook, "REG-%d%c%c", pass[i], pass[i+2], pass[i + 3]);
                }
                enqueue(queue, nama, stat, nokamar, durasi, date, month, year, dateo, montho, yearo, pricer, kodebook, mae);
                //printf("front: %s\n", depan(*queue));
                //printf("%d\n", (*queue)->nokamar);
                //printf("%s\n", (*mae)->nama);
                printf("\n");
                printf("isi queue: \n");
                *mae = *queue;
                int j = 1;
                while(*mae != NULL){
                    printf("Queue %d\n", j);
                    printf("%s\n", (*mae)->nama);
                    printf("%s\n", (*mae)->stat);
                    printf("%d\n", (*mae)->nokamar);
                    printf("%d hari\n", (*mae)->durasi);
                    printf("%d-%d-%d\n", (*mae)->date, (*mae)->month, (*mae)->year);
                    printf("Rp.%d\n", (*mae)->price);
                    printf("%s\n", (*mae)->kodebook);
                    printf("\n");
                    (*mae) = (*mae)->next;
                    j++;
                }
                //printf("%s\n", (*mae)->next->nama);
                system("pause");
            }

            else if(*choice==2)                                                     //Menu untuk ruang booking VIP
            {
                system("cls");
                printf("VIP");
                printf("\nTambahan Fitur Kamar :");
                printf("\n1. Bathup + Twin Bed + TV + Breakfast(Superior) = 1.000.000");
                printf("\n2. Bathup + Queen Bed + TV + Breakfast + Dinner (Superior) = 1.200.000");
                printf("\n3. Bathup + King Bed + TV + Breakfast + Lunch + Dinner(Deluxe) = 1.400.000");
                printf("\nPilihan : ");
                scanf("%d", &tipe);
                fflush(stdin);
                if(tipe==1)
                {
                    pricev = 1000000;
                }else if(tipe==2)
                {
                    pricev = 1200000;
                }else if(tipe==3)
                {
                    pricev = 1400000;
                }
                printf("\nNama\t:");
                scanf("%[^\n]", &nama);
                fflush(stdin);
                printf("No Kamar\t:");
                scanf("%d", &nokamar);
                fflush(stdin);
                printf("Lama Menginap\t:");
                scanf("%d", &durasi);
                fflush(stdin);
                printf("Tanggal check-in (dd-mm-yyyy) = ");
                scanf("%d-%d-%d", &date, &month, &year);
                fflush(stdin);
                dateo = date + durasi;
                montho = month;
                yearo = year;
                if(dateo>31)                                                 //If ini untuk menyeseuaikan agar hari tidak lebih dari 31 hari, jika lebih, maka month ++;
                {
                    dateo -= 31;
                    montho++;
                    if(montho>12)                                           //If ini untuk menyeseuaikan agar bulan tidak lebih dari 12 bulan, jika lebih, maka year ++;
                    {fflush(stdin);
                        montho -= 12;
                        yearo++;
                    }
                }
                fflush(stdin);

                for (i = 0; i < 1; i++) {
                    pass[i] = rand() % 9;
                    char capLetter = 'A' + (rand() % 26);
                    pass[i + 2] = capLetter;
                    char letter = 'a' + (rand() % 26);
                    pass[i + 3] = letter;
                    sprintf(kodebook, "VIP-%d%c%c", pass[i], pass[i+2], pass[i + 3]);
                }
                enqueue(queue, nama, stat, nokamar, durasi, date, month, year, dateo, montho, yearo, pricev, kodebook, mae);
                //printf("front: %s\n", depan(*queue));
                //printf("%d\n", (*queue)->nokamar);
                //printf("%s\n", (*mae)->nama);
                printf("\n");
                printf("isi queue: \n");
                *mae = *queue;
                int j = 1;
                while(*mae != NULL){
                    printf("Queue %d\n", j);
                    printf("%s\n", (*mae)->nama);
                    printf("%s\n", (*mae)->stat);
                    printf("%d\n", (*mae)->nokamar);
                    printf("%d hari\n", (*mae)->durasi);
                    printf("%d-%d-%d\n", (*mae)->date, (*mae)->month, (*mae)->year);
                    printf("Rp.%d\n", (*mae)->price);
                    printf("%s\n", (*mae)->kodebook);
                    printf("\n");
                    (*mae) = (*mae)->next;
                    j++;
                }
                //printf("%s\n", (*mae)->next->nama);
                system("pause");

            }
    }
    else if (pilihan == 2){
        if((*queue) == NULL){
            printf("Queue kosong\n");
            system("pause");
            return;
        } else {
            //sistem dequeue
            system("cls");
            *mae = *queue;
            int decision;
            do
            {
                system("cls");
                printf("Nama\t\t: %s\n", (*mae)->nama);
                printf("Status\t\t: %s\n", (*mae)->stat);
                printf("No Kamar\t: %d\n", (*mae)->nokamar);
                printf("Menginap %d hari\n", (*mae)->durasi);
                printf("Tanggal check in : %d-%d-%d\n", (*mae)->date, (*mae)->month, (*mae)->year);
                printf("Biaya Penginapan : Rp.%d\n", (*mae)->price);
                printf("Kode booking     :%s\n", (*mae)->kodebook);
                printf("Huruf pertama : %c", (*mae)->kodebook[0]);
                printf("\n");
                printf("Approve Pesanan ini?\n");
                printf("1. YES\n");
                printf("2. NO\n");
                printf("3. Keluar menu Aprovval\n");
                scanf("%d", &decision);
                if (decision == 1)
                {
                    *mae = *queue;
                    system("pause");
                    if((*mae)->kodebook[0]=='V'){
                            if(*head != NULL){
                                *curr = *head;
                                do{
                                    if((*mae)->nokamar == (*curr)->no){
                                        if((*mae)->date < (*curr)->dateo && (*mae)->date > (*curr)->date){
                                            if((*mae)->month == (*curr)->montho){
                                                if((*mae)->year == (*curr)->yearo){
                                                    sama = 1;
                                                    printf("sama = %d", sama);
                                                    system("pause");
                                                    *choice = 0;
                                                }
                                            }
                                        }
                                    }
                                    *curr = (*curr)->next;
                                }while(*curr != *head);
                            }
                            if(sama != 1){
                                FILE *fp = fopen("Database VIP.txt", "a");                                      //ini File Processingnya
                                fprintf(fp, "%s#%d#%d#%d-%d-%d-Rp.%d-%s\n", (*mae)->nama, (*mae)->nokamar, (*mae)->durasi, (*mae)->date, (*mae)->month, (*mae)->year, (*mae)->price, (*mae)->kodebook);
                                fclose(fp);
                                *node = (struct bookv*)malloc(sizeof(struct bookv));                            //Memory alloc struct bookv.
                                strcpy((*node)->nama, (*mae)->nama);
                                (*node)->no = (*mae)->nokamar;
                                (*node)->durasi = (*mae)->durasi;
                                (*node)->date = (*mae)->date;
                                (*node)->month = (*mae)->month;
                                (*node)->year = (*mae)->year;
                                (*node)->prev = NULL;
                                (*node)->next = NULL;
                                (*node)->dateo = (*mae)->dateo;
                                (*node)->montho = (*mae)->montho;
                                (*node)->yearo = (*mae)->yearo;
                                (*node) -> price = (*mae)->price * (*mae)->durasi;
                                strcpy((*node)->kodebook , (*mae)->kodebook);

                                if(*head == NULL)
                                {
                                    *head = *node;
                                    *tail = *node;
                                }
                                else
                                {
                                    (*tail)->next = *node;
                                    (*node)->prev = *tail;
                                    *tail = *node;
                                }

                                printf("Please wait . . . connecting to server\n");
                                //Sleep(1000);
                                printf("\nData peminjaman ruangan telah berhasil diinput dengan status Approved\n");
                                printf("Harga kamar : Rp. %d\n\n", (*node)->price);
                                printf("Mohon jangan lupa dengan Kode Boking anda, kode booking anda adalah: %s\n\n", (*node)->kodebook);
                                dequeue(queue);
                                *mae = *queue;
                                int j = 1;
                                printf("\nHasil dequeueh: \n\n");
                                if(*queue != NULL){
                                    while(*mae != NULL){
                                        printf("Queue %d\n", j);
                                        printf("%s\n", (*mae)->nama);
                                        printf("%s\n", (*mae)->stat);
                                        printf("%d\n", (*mae)->nokamar);
                                        printf("%d hari\n", (*mae)->durasi);
                                        printf("%d-%d-%d\n", (*mae)->date, (*mae)->month, (*mae)->year);
                                        printf("Rp.%d\n", (*mae)->price);
                                        printf("%s\n", (*mae)->kodebook);
                                        printf("\n");
                                        (*mae) = (*mae)->next;
                                        j++;
                                    }
                                } else {
                                    printf("Queue kosong\n");
                                    system("pause");
                                    break;
                                }
                                (*tail)->next = *head;
                                (*head)->prev = *tail;
                            }
                            else
                            {
                                printf("Kamar sudah di reservasi oleh orang lain\n");
                            }
                            *curr = (*head)->next;

                            system("pause");
                    }
                    else if((*mae)->kodebook[0]=='R'){
                            if(*pala != NULL){
                                *ini = *pala;
                                do{
                                   if((*mae)->nokamar == (*curr)->no){
                                        if((*mae)->date < (*curr)->dateo && (*mae)->date > (*curr)->date){
                                            if((*mae)->month == (*curr)->montho){
                                                if((*mae)->year == (*curr)->yearo){
                                                    sama = 1;
                                                    *choice = 0;
                                                }
                                            }
                                        }
                                   }
                                   *ini =(*ini)->next;
                                }while(*ini != *pala);
                            }
                            if(sama != 1)
                            {
                                FILE *fp = fopen("Database Reguler.txt", "a");          // file processingnya
                                fprintf(fp, "%s#%d#%d#%d-%d-%d-Rp.%d-%s\n", (*mae)->nama, (*mae)->nokamar, (*mae)->durasi, (*mae)->date, (*mae)->month, (*mae)->year, (*mae)->price, (*mae)->kodebook);
                                fclose(fp);
                                *titik = (struct bookr*)malloc(sizeof(struct bookr));                   //memory alloc bookr
                                strcpy((*titik)->nama, (*mae)->nama);
                                (*titik)->no = (*mae)->nokamar;
                                (*titik)->durasi = (*mae)->durasi;
                                (*titik)->date = (*mae)->date;
                                (*titik)->month = (*mae)->month;
                                (*titik)->year = (*mae)->year;
                                (*titik)->prev = NULL;
                                (*titik)->next = NULL;
                                (*titik)->dateo = (*mae)->dateo;
                                (*titik)->montho = (*mae)->montho;
                                (*titik)->yearo = (*mae)->yearo;
                                (*titik) -> price = (*mae)->price * (*mae)->durasi;
                                strcpy((*titik)->kodebook, (*mae)->kodebook);

                                if(*pala == NULL)
                                {
                                    *pala = *titik;                 //jika pala masih kosong, isi pala dan ekor dengan titik.
                                    *ekor = *titik;
                                }
                                else
                                {
                                    (*ekor)->next = *titik;             //Data dilanjutkan secara Doubly linked list, dengan membuat ekor->next = titik dan titik->prev = ekor
                                    (*titik)->prev = *ekor;
                                    *ekor = *titik;
                                }
                                printf("Please wait . . . connecting to server\n");
                                Sleep(1000);
                                printf("\nData peminjaman ruangan telah berhasil diinput dengan status Approved\n");    //Jika berhasil diinput, print ini.
                                printf("Harga kamar : Rp. %d (%d hari)\n", (*titik)->price, (*titik)->durasi);
                                printf("Mohon jangan lupa dengan Kode Boking anda, kode booking anda adalah: %s\n\n", (*titik)->kodebook);
                                dequeue(queue);     // Dequeue setelah ditulis ke file
                                *mae = *queue;
                                int j = 1;
                                printf("\nHasil dequeueh: \n\n");
                                if(*queue != NULL){
                                    while(*mae != NULL){
                                        printf("Queue %d\n", j);
                                        printf("%s\n", (*mae)->nama);
                                        printf("%s\n", (*mae)->stat);
                                        printf("%d\n", (*mae)->nokamar);
                                        printf("%d hari\n", (*mae)->durasi);
                                        printf("%d-%d-%d\n", (*mae)->date, (*mae)->month, (*mae)->year);
                                        printf("Rp.%d\n", (*mae)->price);
                                        printf("%s\n", (*mae)->kodebook);
                                        printf("\n");
                                        (*mae) = (*mae)->next;
                                        j++;
                                    }
                                } else{
                                    printf("Queue kosong\n");
                                    system("pause");
                                    break;
                                }
                                (*ekor)->next = *pala;
                                (*pala)->prev = *ekor;
                            }
                            else
                            {
                                printf("Kamar sudah di reservasi oleh orang lain\n");             //Jika sama == 1/ ada yang bertabrakan tanggal bookingnya.
                            }

                            *ini = (*pala)->next;
                            *mae = *queue;
                            system("pause");
                    }
                }
                else if(decision==2){
                    dequeue(queue);
                } else if(decision == 3){
                    break;
                }
                (*mae) = (*mae)->next;
            }while(*mae != NULL);
        }
    }
    else if (pilihan == 3)
    {
        return;
    }
}

void swapr(struct bookr **a,struct bookr **b)                                   // Fungsi untuk swap struct bookr (kamar reguler)
{
    int bil, bil1, bil2, bil3, bil4 ,bil5;
    char sementara[30];
    strcpy(sementara,(*a)->nama);
    strcpy((*a)->nama,(*b)->nama);
    strcpy((*b)->nama,sementara);
    strcpy(sementara,(*a)->code);
    strcpy((*a)->code,(*b)->code);
    strcpy((*b)->code,sementara);
    bil = (*a)->no;
    (*a)->no=(*b)->no;
    (*b)->no=bil;
    bil1 = (*a)->date;
    (*a)->date=(*b)->date;
    (*b)->date=bil1;
    bil2 = (*a)->month;
    (*a)->month=(*b)->month;
    (*b)->month=bil2;
    bil3 = (*a)->year;
    (*a)->year=(*b)->year;
    (*b)->year=bil3;
    bil4 = (*a)->durasi;
    (*a)->durasi=(*b)->durasi;
    (*b)->durasi=bil4;
    bil5 = (*a)->price;
    (*a)->price = (*b) -> price;
    (*b)->price = bil5;
}

void swapv(struct bookv **a,struct bookv **b)                                   // Fungsi untuk swap struct bookrv (kamar vip)
{
    int bil, bil1, bil2, bil3, bil4, bil5;
    char sementara[30];
    strcpy(sementara,(*a)->nama);
    strcpy((*a)->nama,(*b)->nama);
    strcpy((*b)->nama,sementara);
    strcpy(sementara,(*a)->code);
    strcpy((*a)->code,(*b)->code);
    strcpy((*b)->code,sementara);

    bil = (*a)->no;
    (*a)->no=(*b)->no;
    (*b)->no=bil;

    bil1 = (*a)->date;
    (*a)->date=(*b)->date;
    (*b)->date=bil1;

    bil2 = (*a)->month;
    (*a)->month=(*b)->month;
    (*b)->month=bil2;

    bil3 = (*a)->year;
    (*a)->year=(*b)->year;
    (*b)->year=bil3;

    bil4 = (*a)->durasi;
    (*a)->durasi=(*b)->durasi;
    (*b)->durasi=bil4;

    bil5 = (*a)->price;
    (*a)->price = (*b) -> price;
    (*b)->price = bil5;

}

int cancel(struct bookr **pala, struct bookr **ini, struct bookr **ekor, struct bookv **head, struct bookv **curr, struct bookv **tail, int *sizer, int *sizev)            //Fungsi untuk cancel ruangan
{
    int pilihan;
    int pilihan2;
    char pilihan3;
    char password[10];
    //struct bookr *sementara;
    //struct bookv *temp;
    //struct bookr *titik;
    //struct bookv *node;
    int i, found;

    FILE *fp;
    fflush(stdin);
    system("cls");
    printf("Tipe kamar: \n");
    printf("1. Reguler\n");
    printf("2. VIP\n");
    printf("Pilihan: ");
    scanf("%d", &pilihan); //membedakan pemakaian jenis struct
    found = 0; //flag found
    if(pilihan==1) //tipe kamar reguler
    {
        system("cls");
        *ini = *pala; //agar proses looping dimulai dari data paling awal namun penanda data awal(head) tidak tergeser sama sekali
        while(1) //looping untuk menampilkan bookingan kamar hotel tipe reguler
        {
            system("cls");
            printf("Nama\t\t\t: %s \n", (*ini)->nama);
            printf("No. Kamar\t\t: %d\n", (*ini)->no);
            printf("Lama Menginap\t\t: %d\n", (*ini)->durasi);
            printf("Tanggal Check In\t: %d-%d-%d\n", (*ini)->date, (*ini)->month, (*ini)->year);
            printf("Status\t\t\t: Approved\n");
            printf("Price\t\t\t: %d\n", (*ini)->price);
            printf("1. Next\n");
            printf("2. Prev\n");
            printf("3. Cancel\n");
            printf("4. Cari Kamar\n");
            printf("5. Back\n");
            printf("Pilihan: ");
            scanf("%d", &pilihan2);
            fflush(stdin);
            if(pilihan2==1)
            {
                *ini = (*ini)->next; //menggeser ini ke linked list setelahnya
            }else if(pilihan2==2)
            {
                *ini = (*ini)->prev; //menggeser ini ke linked list sebelumnya
            }else if(pilihan2==3)
            {
                printf("Anda yakin ingin menghapus bookingan kamar hotel tipe reguler untuk kamar &d ?(y/n)\n", (*ini)->no);
                printf("Pilihan: ");
                scanf("%c", &pilihan3);
                fflush(stdin);
                if(pilihan3=='Y' || pilihan3=='y')
                {
                    printf("Masukkan kode booking anda sebagai sistem pengaman: ");
                    printf("\ncheat code: %s\n", (*ini)->kodebook);
                    scanf("%s", &password);
                    //ini = pala;
                    if(strcmp((*ini)->kodebook, password)== 0) //Pengecekan kode booking untuk membatalkan booking agar yang bisa membatalkan hanya yang memesan
                    {

                        fp = fopen("Database Reguler.txt", "w");
                        struct bookr *temp = (*ini);
                        (*ini) = (*ini)->next;

                        while((*ini) != temp){
                            if(strcmp(temp->nama, (*ini)->nama) == 0){
                                (*ini) = (*ini);
                            } else{
                                fprintf(fp, "%s#%d#%d#%d-%d-%d-Rp.%d-%s\n", (*ini)->nama, (*ini)->no, (*ini)->durasi, (*ini)->date, (*ini)->month, (*ini)->year, (*ini)->price, (*ini)->kodebook);
                            }
                            (*ini) = (*ini)->next;
                        }

                        fclose(fp);
                        printf("Kamar berhasil dihapus!\n");
                        //*sizer--;
                        system("pause");
                        break;
                    }else{
                        printf("Kode booking yang anda masukkan salah\n");
                        system("pause");
                        break;
                    }
                }else{
                    break;
                }
            }else if(pilihan2==4){
                (*ini) = (*pala);
                printf("\nMasukkan kode booking kamar yang ingin anda cari: "); scanf("%s", &password);
                for(i = 0; i < *sizer; i++){
                    if(strcmp((*ini)->kodebook, password)== 0){ //Pengecekan kode booking untuk membatalkan booking agar yang bisa membatalkan hanya yang memesan
                        found = 1;
                        break;
                    }else{
                        (*ini) = (*ini)->next;
                    }
                }
                if (found == 1){
                    system("cls");
                    printf("Nama\t\t\t: %s \n", (*ini)->nama);
                    printf("No. Kamar\t\t: %d\n", (*ini)->no);
                    printf("Lama Menginap\t\t: %d\n", (*ini)->durasi);
                    printf("Tanggal Check In\t: %d-%d-%d\n", (*ini)->date, (*ini)->month, (*ini)->year);
                    printf("Status\t\t\t: Approved\n");
                    printf("Price\t\t\t: %d\n", (*ini)->price);
                    printf("Anda yakin ingin menghapus bookingan kamar hotel tipe reguler untuk kamar %d ?(y/n)\n", (*ini)->no);
                    printf("Pilihan: "); fflush(stdin);
                    scanf("%c", &pilihan3);
                    fflush(stdin);
                    if(pilihan3=='Y' || pilihan3=='y'){
                        fp = fopen("Database Reguler.txt", "w");
                        struct bookr *temp = (*ini);
                        (*ini) = (*ini)->next;

                        while((*ini) != temp){
                            if(strcmp(temp->nama, (*ini)->nama) == 0){
                                (*ini) = (*ini);
                            } else{
                                fprintf(fp, "%s#%d#%d#%d-%d-%d-Rp.%d-%s\n", (*ini)->nama, (*ini)->no, (*ini)->durasi, (*ini)->date, (*ini)->month, (*ini)->year, (*ini)->price, (*ini)->kodebook);
                            }
                            (*ini) = (*ini)->next;
                        }
                        fclose(fp);
                        printf("Kamar berhasil dihapus!\n");
                        //*sizer--;
                        system("pause");
                        break;

                    }else{
                        break;
                    }
                } else if (found == 0){
                    printf("Kamar dengan kode booking tersebut tidak ditemukan\n");
                    printf("Silahkan coba lagi atau hubungi costumer service kami\n");
                    system("pause");
                    break;
                }
            } else if(pilihan2 == 5){
                break;
            }
            //system("pause");
        }
    }else{ //tipe kamar VIP
        system("cls");
        *curr = *head;
        while(1) //looping untuk menampilkan bookingan kamar hotel tipe VIP
        {
            system("cls");
            printf("Nama\t: %s \n", (*curr)->nama);
            printf("No. Kamar\t: %d\n", (*curr)->no);
            printf("Lama Menginap\t: %d\n", (*curr)->durasi);
            printf("Tanggal Check In\t: %d-%d-%d\n", (*curr)->date, (*curr)->month, (*curr)->year);
            printf("Status\t: Approved\n");
            printf("Price: %d\n", (*curr)->price);
            printf("1. Next\n");
            printf("2. Prev\n");
            printf("3. Cancel\n");
            printf("4. Cari Kamar\n");
            printf("5. Back\n");
            printf("Pilihan: ");
            scanf("%d", &pilihan2);
            if(pilihan2==1)
            {
                *curr = (*curr)->next;      //menggeser curr ke linked list setelahnya
            }else if(pilihan2==2)
            {
                *curr = (*curr)->prev;      //menggeser curr ke linked list sebelumnya
            }else if(pilihan2==3)
            {
                printf("Anda yakin ingin menghapus bookingan kamar hotel tipe VIP untuk kamar %d ?(y/n)\n", (*curr)->no);
                fflush(stdin);
                printf("Pilihan: ");
                scanf("%c", &pilihan3);
                if(pilihan3=='Y' || pilihan3=='y')
                {
                    printf("Masukkan kode booking anda sebagai sistem pengaman: ");
                    //printf("\ncheat code: %s\n", (*curr)->kodebook);
                    scanf("%s", &password);fflush(stdin);
                    if(strcmp((*curr)->kodebook, password)== 0)    //Pengecekan kode booking untuk membatalkan booking agar yang bisa membatalkan hanya yang memesan
                    {
                        //FILE *fp;
                        fp = fopen ("Database VIP.txt", "w");
                        struct bookv *temp = (*curr);
                        for(i = 0; i < *sizev; i++){
                            if(strcmp(temp->nama,(*curr)->nama) == 0){
                                (*curr) = (*curr);
                            } else{
                                fprintf(fp, "%s#%d#%d#%d-%d-%d-Rp.%d-%s\n", (*curr)->nama, (*curr)->no, (*curr)->durasi, (*curr)->date, (*curr)->month, (*curr)->year, (*curr)->price, (*curr)->kodebook);
                            }
                            (*curr) = (*curr)->next;
                        }
                        fclose(fp);
                        printf("Kamar berhasil dihapus!\n");
                        //*sizev--;
                        system("pause");
                        break;

                    }else{
                        printf("Kode booking yang anda masukkan salah\n");
                        system("pause");
                        break;
                    }
                }else{
                    break;
                }
            }else if(pilihan2==4){
                (*curr) = (*head);
                printf("\nMasukkan kode booking kamar yang ingin anda cari: "); scanf("%s", &password);
                for(i = 0; i < *sizer; i++){
                    if(strcmp((*curr)->kodebook, password)== 0){ //Pengecekan kode booking untuk membatalkan booking agar yang bisa membatalkan hanya yang memesan
                        found = 1;
                        break;
                    }else{
                        (*curr) = (*curr)->next;
                    }
                }
                if(found == 1){


                    system("cls");
                    printf("Nama\t\t\t: %s \n", (*curr)->nama);
                    printf("No. Kamar\t\t: %d\n", (*curr)->no);
                    printf("Lama Menginap\t\t: %d\n", (*curr)->durasi);
                    printf("Tanggal Check In\t: %d-%d-%d\n", (*curr)->date, (*curr)->month, (*curr)->year);
                    printf("Status\t\t\t: Approved\n");
                    printf("Price\t\t\t: %d\n", (*curr)->price);
                    printf("Anda yakin ingin menghapus bookingan kamar hotel tipe reguler untuk kamar %d ?(y/n)\n", (*curr)->no);
                    printf("Pilihan: "); fflush(stdin);
                    scanf("%c", &pilihan3);
                    fflush(stdin);
                    if(pilihan3=='Y' || pilihan3=='y'){
                        fp = fopen("Database VIP.txt", "w");
                        struct bookv *temp = (*curr);
                        (*curr) = (*curr)->next;

                        while((*curr) != temp){
                            if(strcmp(temp->nama, (*curr)->nama) == 0){
                                (*curr) = (*curr);
                            } else{
                                fprintf(fp, "%s#%d#%d#%d-%d-%d-Rp.%d-%s\n", (*curr)->nama, (*curr)->no, (*curr)->durasi, (*curr)->date, (*curr)->month, (*curr)->year, (*curr)->price, (*curr)->kodebook);
                            }
                            (*curr) = (*curr)->next;
                        }
                        fclose(fp);
                        printf("Kamar berhasil dihapus!\n");
                        //*sizev--;
                        system("pause");
                        break;
                    }else{
                        break;
                    }
                } else if (found == 0){
                    printf("Kamar dengan kode booking tersebut tidak ditemukan\n");
                    printf("Silahkan coba lagi atau hubungi costumer service kami\n");
                    system("pause");
                    break;
                }
            } else if( pilihan2 == 5){
                break;
            }
        }
    }
    return 0;
}

void insertToChain(char nama[],int nokamar,int durasi,int date,int month, int year, int price, char kodebook[], struct bookr **hash)
{
    struct bookr *ptr = (*hash);
    struct bookr *hashing = (struct bookr*)malloc(sizeof(struct bookr));

    strcpy(hashing->nama, nama);
    hashing->no = nokamar;
    hashing->durasi = durasi;
    hashing->date = date;
    hashing->month = month;
    hashing->year = year;
    hashing->price = price;
    strcpy(hashing->kodebook, kodebook);
    hashing -> next = NULL;

    if ((*hash)==NULL){
        *hash=hashing;
    }
    else
    {
        while(ptr -> next != NULL){
            ptr = ptr -> next;
        }
        ptr -> next = hashing;
    }
}


void SetColorAndBackground(int ForgC, int BackC)
{
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
    return;
}
//------------------------insert tree----------------------------------
int insert(struct tree **root, struct tree **current, struct tree *kodebook, int temp)
{
    struct tree *newnode = (struct tree*)malloc(sizeof(struct tree));
    strcpy(newnode->kode, kodebook);
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->middle = NULL;
    if(temp==1000000)
    {
        if((*current)->left == NULL)
        {
            (*current)->left = newnode;
            return 0;
        }else
        {
            (*current)=(*current)->left;
            insert(root,current,kodebook,temp);
        }
    }else if(temp==1200000)
    {
        if((*current)->middle == NULL)
        {
            (*current)->middle = newnode;
            return 0;
        }else
        {
            (*current)=(*current)->middle;
            insert(root,current,kodebook,temp);
        }
    }else if(temp==1400000)
    {
        if((*current)->right == NULL)
        {
            (*current)->right = newnode;
            return 0;
        }else
        {
            (*current)=(*current)->right;
            insert(root,current,kodebook,temp);
        }
    }
}

void preorder(struct tree *pnode)
{
    if(pnode==NULL) return;
    printf("\t%s",pnode->kode);
    preorder(pnode->left);
    preorder(pnode->middle);
    preorder(pnode->right);
}

int main(){

    struct bookv *head, *node, *curr, *tail;            //Deklarasi variabel kedua struct
    struct bookr *pala, *titik, *ini, *ekor, *hash;
    struct Queue *mae;                                  //Deklarasi variable queue
    struct Queue *queue = NULL;                         //Deklarasi variable queue sebagai NULL tiap kali program dibuka untuk pertama kali
    struct bookr *HashT[3];
    struct tree *root, *current;

    char nama[30];
    char kodebook[10];
    int no;
    int durasi;
    int date;
    int month;
    int year;
    char tipe[5];
    int code;
    char status[30];
    int choice;
    int exit = 1;
    int i, j, k;
    int pilihan;
    int cek = 0;
    int flag;
    int price;
    int sizer = 0;
    int sizev = 0;
    int nr = 0;
    int nv = 0;
    char keynama[50];
    int found, keyno;


    head = curr = NULL;         //head dan curr dimulai sebagai NULL, sebagai indikator adanya looping diawal atau tidak
    pala = ini = NULL;
    node = NULL;
    titik = NULL;

    while(exit = 1){

        while(sizer != 0){
            struct bookr *temp = pala;                  //semua mula-mula dibikin NULL, agar data selalu terupdate tiap ada perubahan
            pala = pala->next;
            pala->prev = ekor;
            ekor->next = pala;
            free(temp);
            if(sizer == 1){
                pala = NULL;
                ekor = NULL;
            }
            sizer--;
        }

        while(sizev != 0){
            struct bookv *temp = head;                  //semua mula-mula dibikin NULL, agar data selalu terupdate tiap ada perubahan
            head = head->next;
            head->prev = tail;
            tail->next = head;
            free(temp);
            if(sizev == 1){
                head = NULL;
                tail = NULL;
            }
            sizev--;
        }

//----------------------File processing reading dari file.txt, untuk database Reguler------------------------
        FILE *fp;
        fp = fopen("Database Reguler.txt", "r");

        if(fp != NULL){
            while(fscanf(fp, " %[^#]#%d#%d#%d-%d-%d-Rp.%d-%[^\n]", &nama, &no, &durasi, &date, &month, &year, &price, kodebook) !=  EOF){
                fflush(stdin);
                titik = (struct bookr*)malloc(sizeof(struct bookr));
                strcpy(titik->nama, nama);
                titik->no = no;
                titik->durasi = durasi;
                titik->date = date;
                titik->month = month;
                titik->year = year;
                titik->price=price;
                strcpy(titik->kodebook, kodebook);
                titik->next=NULL;
                titik->prev=NULL;
                if(pala == NULL)
                {
                    pala=titik;
                    ekor=titik;
                }
                else
                {
                    ekor->next = titik;             //Data dilanjutkan secara Doubly linked list, dengan membuat ekor->next = titik dan titik->prev = ekor
                    titik->prev = ekor;
                    ekor = titik;
                    ekor->next = pala;
                    pala->prev = ekor;
                }
                sizer++;
            }
        }
        else{
            printf("Error, no file to read\n");
        }
        fclose(fp);
        printf("sizer = %d", sizer);

        //-----------------Hashing Kamar Reguler-----------------

        for(i = 0; i < 3; i++){
            HashT[i] = NULL;               //Hash table dibuat NULL, agar terupdate tiap data berubah
        }

        ini = pala;
        for(i = 0; i < sizer; i++){
            char tempName[100];
            int tempNo;
            int tempDurasi;
            int tempDate;
            int tempMonth;
            int tempYear;
            int tempPrice;
            char tempKodebook[50];
            strcpy(tempName, ini->nama);
            tempNo = ini->no;
            tempDurasi = ini->durasi;
            tempDate = ini->date;
            tempMonth = ini->month;
            tempYear = ini->year;
            tempPrice = ini->price;
            strcpy(tempKodebook, ini->kodebook);
            if(ini->price / durasi == 300000){
                insertToChain(tempName, tempNo, tempDurasi, tempDate, tempMonth, tempYear, tempPrice, tempKodebook, &HashT[0]);
            } else if (ini->price / durasi == 500000){
                insertToChain(tempName, tempNo, tempDurasi, tempDate, tempMonth, tempYear, tempPrice, tempKodebook, &HashT[1]);
            } else if (ini->price / durasi == 800000){
                insertToChain(tempName, tempNo, tempDurasi, tempDate, tempMonth, tempYear, tempPrice, tempKodebook, &HashT[2]);
            }
            ini = ini -> next;
            //system("pause");
        }
        /*
        i=0;
        struct bookr *ptr = HashT[0];
        printf("================================================\n");
        printf("    Kamar Reguler tipe 1 (Rp. 300.000/malam)   \n");
        printf("================================================\n");
        if(ptr != NULL){
            while(ptr != NULL){
            printf("Kamar Reguler #%d\n", i + 1);
            printf("Nama : %s\n", ptr ->nama);
            printf("No : %d\n", ptr ->no);
            printf("\n");
            ptr = ptr -> next;
            i++;
            printf("\n");
            }
        }
        i=0;
        struct bookr *ptr2 = HashT[1];
        printf("================================================\n");
        printf("    Kamar Reguler tipe 1 (Rp. 500.000/malam)   \n");
        printf("================================================\n");
        if(ptr2 != NULL){
            while(ptr2 != NULL){
            printf("Kamar Reguler #%d\n", i + 1);
            printf("Nama : %s\n", ptr2 ->nama);
            printf("No : %d\n", ptr2 ->no);
            printf("\n");
            ptr2 = ptr2 -> next;
            i++;
            printf("\n");
            }
        }

        i=0;
        struct bookr *ptr3 = HashT[2];
        printf("================================================\n");
        printf("    Kamar Reguler tipe 3 (Rp. 800.000/malam)   \n");
        printf("================================================\n");
        if(ptr3 != NULL){
            while(ptr3 != NULL){
            printf("Kamar Reguler #%d\n", i + 1);
            printf("Nama : %s\n", ptr3 ->nama);
            printf("No : %d\n", ptr3 ->no);
            printf("\n");
            ptr3 = ptr3 -> next;
            i++;
            printf("\n");
            }
        }
        system("pause");
        */

//----------------------File processing reading dari file.txt, untuk database VIP------------------------
        struct tree *current = (struct tree*)malloc(sizeof(struct tree));
        strcpy(current->kode, "headroot");
        current->left = NULL;
        current->middle = NULL;
        current->right = NULL;
        root=current;

        fp = fopen("Database VIP.txt", "r");

        if(fp != NULL){
            while(fscanf(fp, " %[^#]#%d#%d#%d-%d-%d-Rp.%d-%[^\n]", &nama, &no, &durasi, &date, &month, &year, &price, kodebook) !=  EOF){
                fflush(stdin);
                node = (struct bookv*)malloc(sizeof(struct bookv));
                strcpy(node->nama, nama);
                node->no = no;
                node->durasi = durasi;
                node->date = date;
                node->month = month;
                node->year = year;
                node->price=price;
                strcpy(node->kodebook, kodebook);
                node->next=NULL;
                node->prev=NULL;
                if(head == NULL)
                {
                    head=node;
                    tail=node;
                }
                else
                {
                    tail->next = node;             //Data dilanjutkan secara Doubly linked list, dengan membuat ekor->next = titik dan titik->prev = ekor
                    node->prev = tail;
                    tail = node;
                    tail->next = head;
                    head->prev = tail;
                }
                sizev++;
                int temp = price/durasi;
                printf("\n%d\n", temp);
                current=root;
                insert(&root, &current, kodebook, temp);

            }
        }
        else{
            printf("Error, no file to read\n");
        }
        preorder(root);
        fclose(fp);


        //--------------Cover--------------

        printf("\n\n");
        printf("Harga kamar VIP: Rp. 600.000 / hari\n");
        printf("Harga kamar Reguler: Rp. 300.000 / hari\n\n\n");

        ini = pala;
        if(sizer != 0){
            printf("Kamar Reguler: \n");
            for(i = 0; i < sizer; i++)
            {
                printf("No. Kamar\t\t: %d sudah dipesan\n", ini->no);
                ini = ini->next;
            }
        }else{
            printf("All Reguler Room avaiable\n");
        }

        curr = head;
        if(sizev != 0){
            printf("Kamar VIP: \n");
            for(i = 0; i < sizev; i++){
                printf("No. Kamar\t\t: %d sudah dipesan\n", curr->no);
                curr = curr->next;
            }
        }else{
            printf("All VIP Room Avaiable\n");
        }

        //--------------Menu--------------

        printf("\nMenu\n");
        printf("1. Input and Approval\n");
        printf("2. Check\n");
        printf("3. Cancel\n");
        printf("4. Search\n");
        printf("5. Exit\n");
        printf("Pilihan: ");scanf("%d", &choice);fflush(stdin);

        switch(choice){       //Switch case pilihan menu
            case 1: userinput(&pala, &ini, &ekor, &head, &curr, &tail, &titik, &node, &code, &mae, &queue);
                break;
            case 2:
                printf("nama ini: %s\n", ini->nama);
                printf("Tipe Kamar:\n");                //Case 2 untuk sort, kami letak langsung di int main, agar tidak kebanyakan passing parameternya, dan memudahkan passing pointernya.
                printf("1. Reguler\n");
                printf("2. VIP\n");
                printf("Pilihan:");
                scanf("%d",&pilihan);
                fflush(stdin);
                ini=pala; //sebagai batas awal loopingan untuk sorting kamar reguler (pilihan==1)
                curr=head; //sebagai batas awal loopingan untuk sorting kamar VIP (pilihan ==2)
                if(pilihan==1)      //untuk kamar reguler
                {
                    do
                    {
                        cek = 0;
                        printf("banana");
                        titik = pala; //sebagai awal pengecekan dalam sorting
                        while(titik->next != ini)      // jadi selama titik -> next tidak sama dengan pala, artinya looping terus berlanjut.
                        {
                            if(titik->no > titik->next->no) //untuk sorting urut nomor kamar.
                            {
                                swapr(&titik,&titik->next);
                                cek = 1;
                            }
                            titik=titik->next;
                        }
                        ini=titik;
                    }while(cek);

                    ini = pala;
                    FILE *fp = fopen("Database Reguler.txt", "w");                                      //Update file to a sorted file
                    for(i = 0; i < sizer; i++){
                        fprintf(fp, "%s#%d#%d#%d-%d-%d-Rp.%d-%s\n", ini->nama, ini->no, ini->durasi, ini->date, ini->month, ini->year, ini->price, ini->kodebook);
                        ini = ini -> next;
                    }
                    fclose(fp);

                    ini = pala;
                    do
                    {
                        system("cls");
                        printf("Kamar Reguler\n");                                                  //print data yang sudah di sort.
                        printf("Nomor: %d\n",ini->no);
                        printf("Nama: %s\n",ini->nama);
                        printf("Tanggal Peminjaman: %d,%d,%d\n",ini->date,ini->month,ini->year);
                        printf("Durasi: %d hari\n",ini->durasi);
                        printf("Price : Rp. %d\n", ini->price);
                        printf("kode book: %s\n", ini->kodebook);
                        printf("Menu:\n");
                        printf("1. Next\n");
                        printf("2. Previous\n");
                        printf("3. Show All\n");
                        printf("4. Exit\n");
                        printf("Pilihan:");scanf("%d",&flag);fflush(stdin);

                        if(flag==1)
                        {
                            ini=ini->next;                  // ke data selanjutnya
                        }
                        else if (flag==2)
                        {
                            ini=ini->prev;                  // ke data sebelumnya
                        }
                        else if (flag==3){                  //tampilkan semua data
                            ini = pala;
                            system("cls");
                            printf("=================================================================================================================\n");
                            printf("                                        Daftar Semua Kamar Reguler                                               \n");
                            printf("=================================================================================================================\n");
                            printf("-----------------------------------------------------------------------------------------------------------------\n");
                            printf("| No  |\t\t\tNama\t\t| Tanggal Peminjaman |\tDurasi\t|   Harga   |\n");
                            printf("-----------------------------------------------------------------------------------------------------------------\n");
                            for(i = 0; i<sizer; i++){
                            printf("| %03d | %-30s  |     %d-%d-%d     |  %d hari  | Rp.%d |\n", ini->no, ini->nama, ini->date,ini->month,ini->year, ini->durasi, ini->price);
                            ini = ini->next;
                            }
                            printf("-----------------------------------------------------------------------------------------------------------------\n");
                            system("pause");
                        } else if (flag == 4){
                            break;
                        }
                    }while(1);
                    system("cls");
                }
                else if (pilihan==2)                //untuk kamar vip
                {
                    do
                    {
                        cek = 0;
                        node = head; //sebagai awal pengecekan dari sorting
                        while(node->next != curr)      // jadi selama titik -> next tidak sama dengan pala, artinya looping terus berlanjut.
                        {
                            if(node->no > node->next->no) //untuk sorting urut nomor kamar.
                            {
                                swapv(&node,&node->next);
                                cek = 1;
                            }
                            node=node->next;
                        }
                        curr=node;
                    }while(cek);

                    curr = head;
                    FILE *fp = fopen("Database VIP.txt", "w");                                      //Update file to a sorted file
                    for(i = 0; i < sizev; i++){
                        fprintf(fp, "%s#%d#%d#%d-%d-%d-Rp.%d-%s\n", curr->nama, curr->no, curr->durasi, curr->date, curr->month, curr->year, curr->price, curr->kodebook);
                        curr = curr -> next;
                    }
                    fclose(fp);

                    curr = head;
                    int check;
                    do
                    {
                        system("cls");
                        printf("Kamar VIP\n");                                                  //print data yang sudah di sort.
                        printf("Nomor: %d\n",curr->no);
                        printf("Nama: %s\n",curr->nama);
                        printf("Tanggal Peminjaman: %d,%d,%d\n",curr->date,curr->month,curr->year);
                        printf("Durasi: %d hari\n",curr->durasi);
                        printf("Price : Rp. %d\n", curr->price);
                        printf("Fitur Kamar: ");
                        current = root;
                        check = 0;
                        while(current->left!=NULL)
                        {
                            if(strcmp(curr->kodebook, current->left->kode)==0)
                            {
                                printf("\tBathup + Twin Bed + TV + Breakfast(Superior) = 1000000");
                                check = 1;
                                break;
                            }else
                            {
                                current=current->left;
                            }
                        }
                        if(check==0)
                        {
                            current = root;
                            while(current->middle!=NULL)
                            {
                                if(strcmp(curr->kodebook, current->middle->kode)==0)
                                {
                                    printf("\tBathup + Queen Bed + TV + Breakfast + Dinner (Superior) = 1200000");
                                    check=1;
                                    break;
                                }else
                                {
                                    current=current->middle;
                                }
                            }
                        }
                        if(check==0)
                        {
                            current = root;
                            while(current->right!=NULL)
                            {
                                if(strcmp(curr->kodebook, current->right->kode)==0)
                                {
                                    printf("\tBathup + King Bed + TV + Breakfast + Lunch + Dinner(Deluxe) = 1400000");
                                    check=1;
                                    break;
                                }else
                                {
                                    current=current->right;
                                }
                            }
                        }
                        printf("\nMenu:\n");
                        printf("1. Next\n");
                        printf("2. Previous\n");
                        printf("3. Show All\n");
                        printf("4. Exit\n");
                        printf("Pilihan:");scanf("%d",&flag);fflush(stdin);

                        if(flag==1)
                        {
                            curr=curr->next;                  // ke data selanjutnya
                        }
                        else if (flag==2)
                        {
                            curr=curr->prev;                  // ke data sebelumnya
                        }
                        else if (flag==3){
                            system("cls");
                            current=root;
                            printf("=================================================================================================================\n");
                            printf("                                            Daftar Semua Kamar VIP                                               \n");
                            printf("=================================================================================================================\n");
                            printf("-----------------------------------------------------------------------------------------------------------------\n");
                            printf("| No  |\t\t\tNama\t\t| Tanggal Peminjaman |\tDurasi\t|   Harga   |\n");
                            printf("-----------------------------------------------------------------------------------------------------------------\n");
                            for(i = 0; i<sizer; i++){
                            printf("| %03d | %-30s  |     %d-%d-%d     |  %d hari  | Rp.%d |\n", curr->no, curr->nama, curr->date,curr->month,curr->year, curr->durasi, curr->price);
                            curr=curr->next;
                            }
                            printf("-----------------------------------------------------------------------------------------------------------------\n");
                            system("pause");
                        } else if ( flag == 4){
                            break;
                        }
                    }while(1);
                    system("cls");
                }
                break;
            case 3:
//-------------------------------Delete-----------------------------
                cancel(&pala, &ini, &ekor, &head, &curr, &tail, &sizer, &sizev);
                break;
            case 4:
                found=0;
                while(1){
                    int srcchoice;
                    char srcpilihan;
                    system("cls");
                    printf("Menu Cari kamar\n");                              //Searching berdasarkan nama dan nomor kamar
                    printf("1. Cari berdasarkan nama\n");
                    printf("2. Cari berdasarkan nomor\n");
                    printf("3. Exit\n");
                    printf("Pilihan: "); scanf("%d", &srcchoice);
                    if(srcchoice == 1){
                        printf("Masukkan nama yang ingin dicari: "); fflush(stdin); scanf("%[^\n]", keynama);
                        ini = pala;
                        for(i = 0; i < sizer ; i++){
                            if(strcmp(ini->nama, keynama)==0){
                                printf("Kamar Reguler\n");                                                  //print data yang sudah disearch.
                                printf("Nomor: %d\n",ini->no);
                                printf("Nama: %s\n",ini->nama);
                                printf("Tanggal Peminjaman: %d-%d-%d\n",ini->date,ini->month,ini->year);
                                printf("Durasi: %d hari\n",ini->durasi);
                                printf("Price : Rp. %d\n", ini->price);
                            }
                            ini = ini->next;
                        }
                        printf("\n");
                        curr = head;
                        for(i = 0; i < sizev; i++){
                            if(strcmp(curr->nama, keynama)==0){
                                printf("Kamar Reguler\n");
                                printf("Nomor: %d\n",curr->no);
                                printf("Nama: %s\n",curr->nama);
                                printf("Tanggal Peminjaman: %d-%d-%d\n",curr->date,curr->month,curr->year);
                                printf("Durasi: %d hari\n",curr->durasi);
                                printf("Price : Rp. %d\n", curr->price);
                            }
                            curr = curr->next;
                        }
                    } else if (srcchoice == 2){
                        printf("Masukkan nomor kamar yang ingin dicari: "); fflush(stdin); scanf("%d", &keyno);
                        ini = pala;
                        for(i = 0; i < sizer ; i++){
                            if(ini->no == keyno){
                                printf("Kamar Reguler\n");                                                  //print data yang sudah disearch.
                                printf("Nomor: %d\n",ini->no);
                                printf("Nama: %s\n",ini->nama);
                                printf("Tanggal Peminjaman: %d-%d-%d\n",ini->date,ini->month,ini->year);
                                printf("Durasi: %d hari\n",ini->durasi);
                                printf("Price : Rp. %d\n", ini->price);
                            }
                            ini = ini->next;
                        }
                        printf("\n");
                        curr = head;
                        for(i = 0; i < sizev; i++){
                            if(curr->no == keyno){
                                printf("Kamar VIP\n");
                                printf("Nomor: %d\n",curr->no);
                                printf("Nama: %s\n",curr->nama);
                                printf("Tanggal Peminjaman: %d-%d-%d\n",curr->date,curr->month,curr->year);
                                printf("Durasi: %d hari\n",curr->durasi);
                                printf("Price : Rp. %d\n", curr->price);
                            }
                            curr = curr->next;
                        }
                    } else if(srcchoice == 3){
                        break;
                    }
                    fflush(stdin);
                    if(found == 0){
                        printf("Kamar tidak ditemukan!\n");
                        system("pause");
                        break;
                    }
                    printf("\nIngin pergi ke menu cancel? (y/n)\n");
                    scanf("%c", &srcpilihan);
                    if(srcpilihan=='Y' || srcpilihan=='y'){
                        cancel(&pala, &ini, &ekor, &head, &curr, &tail, &sizer, &sizev);
                    } else{
                        break;
                    }
                    system("pause");
                }
            case 5: exit = 0; break;

        }
    }

    return 0;
}
