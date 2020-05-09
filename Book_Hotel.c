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



void userinput(struct bookr **pala, struct bookr **ini, struct bookr **ekor, struct bookv **head, struct bookv **curr, struct bookv **tail, struct bookr **titik, struct bookv **node, int *choice)
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
    int sama;
    char codbook;
    int pricer = 300000;
    int pricev = 600000;
    char kodebook[10];
    int i;
    srand((unsigned int)(time(NULL)));
    char pass[6];
    char password[10];

    system("cls");
    printf("Pilih Tipe Kamar : \n");                    //Kami memisahkan menu ruang reguler dan VIP, agar memisahkan insert data ke booking VIP dan booking Reguler.
    printf("1. Reguler\n");
    printf("2. VIP\n");
    printf("Pilihan : ");
    scanf("%d", &(*choice));
    fflush(stdin);

    if(*choice==1)
    {
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

        FILE *fp = fopen("Database Reguler.txt", "a");                                      //ini File Processingnya
        fprintf(fp, "#%s#%d#%d#%d-%d-%d-Rp.%d-%s\n", nama, nokamar, durasi, date, month, year, pricer, kodebook);
        fclose(fp);

        if(*pala != NULL)       //selama pala masi ada isi, programnya lanjut
        {
            *ini = *pala;       //sebaga variabel untuk membuat ini sebagai head, dan head tetap diam sebagai data pertama
            do{
                if(nokamar == (*ini)->no){                                          //Fungsi untuk check apakaha ada booking di ruang yang sama dan tanggal yang sama atau tidak.
                    if(date < (*ini)->dateo && date > (*ini)->date){               //Agar tidak ada tanggal booking yang bertabrakan
                        if(month == (*ini)->montho){
                            if(year == (*ini)->yearo){
                                sama = 1;
                                *choice =0;
                            }
                        }
                    }
                }
               *ini = (*ini)->next;             //ini = ini -> next agar lanjut ke data selanjutnya
            }while(*ini != *pala);
        }
        if(sama != 1)
        {
            *titik = (struct bookr*)malloc(sizeof(struct bookr));                   //memory alloc bookr
            strcpy((*titik)->nama, nama);
            (*titik)->no = nokamar;
            (*titik)->durasi = durasi;
            (*titik)->date = date;
            (*titik)->month = month;
            (*titik)->year = year;
            (*titik)->prev = NULL;
            (*titik)->next = NULL;
            (*titik)->dateo = dateo;
            (*titik)->montho = montho;
            (*titik)->yearo = yearo;
            (*titik) -> price = pricer * durasi;
            strcpy((*titik)->kodebook, kodebook);

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
            (*ekor)->next = *pala;
            (*pala)->prev = *ekor;
        }
        else
        {
            printf("Kamar sudah di reservasi oleh orang lain\n");             //Jika sama == 1/ ada yang bertabrakan tanggal bookingnya.
           // choice = 0;
        }

        *ini = (*pala)->next;


        system("pause");

    }
    else if(*choice==2)                                                     //Menu untuk ruang booking VIP
    {
        fflush(stdin);
        printf("\nNama\t:");
        scanf("%[^s\n]", &nama);
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

        FILE *fp = fopen("Database VIP.txt", "a");          // file processingnya
        fprintf(fp, "#%s#%d#%d#%d-%d-%d-Rp.%d-%s\n", nama, nokamar, durasi, date, month, year, pricev, kodebook);
        fclose(fp);

        if(*head != NULL)
        {
            *curr = *head;
            do{
                if(nokamar == (*curr)->no){                                         // cek ada tanggal booking yang bertabrakan atau tidak
                    if(date < (*curr)->dateo && date > (*curr)->date){
                        if(month == (*curr)->montho){
                            if(year == (*curr)->yearo){
                                sama = 1;
                                *choice=0;
                            }
                        }

                    }
                }
               *curr = (*curr)->next;
            }while(*curr != *head);
        }
        if(sama != 1)
        {
            *node = (struct bookv*)malloc(sizeof(struct bookv));                            //Memory alloc struct bookv.
            strcpy((*node)->nama, nama);
            (*node)->no = nokamar;
            (*node)->durasi = durasi;
            (*node)->date = date;
            (*node)->month = month;
            (*node)->year = year;
            (*node)->prev = NULL;
            (*node)->next = NULL;
            (*node)->dateo = dateo;
            (*node)->montho = montho;
            (*node)->yearo = yearo;
            (*node) -> price = pricev * durasi;
            strcpy((*node)->kodebook , kodebook);

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
            Sleep(1000);
            printf("\nData peminjaman ruangan telah berhasil diinput dengan status Approved\n");
            printf("Harga kamar : Rp. %d\n\n", (*node)->price);
            printf("Mohon jangan lupa dengan Kode Boking anda, kode booking anda adalah: %s\n\n", (*node)->kodebook);
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


void cancel(struct bookr **pala, struct bookr **ini, struct bookr **ekor, struct bookv **head, struct bookv **curr, struct bookv **tail, int *nr, int *nv)            //Fungsi untuk cancel ruangan
{
    int pilihan;
    int pilihan2;
    char pilihan3;
    char password[10];
    struct bookr *sementara;
    struct bookv *temp;
    struct bookr *titik;
    struct bookv *node;
    fflush(stdin);
    system("cls");
    printf("Tipe kamar: \n");
    printf("1. Reguler\n");
    printf("2. VIP\n");
    printf("Pilihan: ");
    scanf("%d", &pilihan); //membedakan pemakaian jenis struct
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
            printf("4. Back\n");
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
                    //printf("\ncheat code: %s\n", (*ini)->kodebook);
                    scanf("%s", &password);
                    if(*nr==1)
                    {
                        free(pala);
                        free(ini);
                        free(ekor);
                        system("cls");
                        printf("Data Bookingan Kosong\n");
                        system("pause");
                        *nr = *nr-1;
                        return 0;
                    }
                    if(strcmp((*ini)->kodebook, password)== 0) //Pengecekan kode booking untuk membatalkan booking agar yang bisa membatalkan hanya yang memesan
                    {
                            sementara = *ini;
                            titik = (*ini)->prev;
                            *ini = (*ini)->next;
                            free(sementara); //Membatalkan bookingan kamar hotel dengan membebaskan 1 kotak linked list
                            (*ini)->prev = titik;
                            titik->next = *ini;
                            *nr = *nr - 1;
                    }else{
                        printf("Kode booking yang anda masukkan salah");
                        break;
                    }
                }else{
                    break;
                }
            }else if(pilihan2==4)
            {
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
            printf("4. Back\n");
            printf("Pilihan: ");
            scanf("%d", &pilihan2);
            if(pilihan2==1)
            {
                *curr = (*curr)->next;      //menggeser ini ke linked list setelahnya
            }else if(pilihan2==2)
            {
                *curr = (*curr)->prev;      //menggeser ini ke linked list sebelumnya
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
                    scanf("%s", &password);
                    if(*nv==1)
                    {
                        free(head);
                        free(curr);
                        free(tail);
                        system("cls");
                        printf("Data Bookingan Kosong\n");
                        system("pause");
                        *nv = *nv-1;
                        return 0;
                    }
                    if(strcmp((*curr)->kodebook, password)== 0)    //Pengecekan kode booking untuk membatalkan booking agar yang bisa membatalkan hanya yang memesan
                    {
                        temp = *curr;
                        node = (*curr)->prev;
                        *curr = (*curr)->next;
                        free(temp);         //Membatalkan bookingan kamar hotel dengan membebaskan 1 kotak linked list
                        (*curr)->prev = node;
                        node->next = *curr;
                        *nv = *nv - 1;
                    }else{
                        printf("Kode booking yang anda masukkan salah");
                        system("pause");
                        break;
                    }
                }else{
                    break;
                }
            }else if(pilihan2==4)
            {
                break;
            }

        }
    }
}

void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

int main(){

    struct bookv *head, *node, *curr, *tail;            //Deklarasi variabel kedua struct
    struct bookr *pala, *titik, *ini, *ekor;

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
    int nr = 0;
    int nv = 0;
    int i;
    int pilihan;
    int cek;
    int flag;
    int price;
    int size;
    head = curr = NULL;         //head dan curr dimulai sebagai NULL, sebagai indikator adanya looping diawal atau tidak
    pala = ini = NULL;

    FILE *fp;
    fp = fopen("Database Reguler.txt", "r");
    size=0;

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
            size++;
        }
    }
    else{
        printf("Error, no file to read\n");
    }
    fclose(fp);

    fp = fopen("Database VIP.txt", "r");
    size=0;

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
            strcpy(titik->kodebook, kodebook);
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
            size++;
        }
    }
    else{
        printf("Error, no file to read\n");
    }
    fclose(fp);

    /*ini = pala;
    do
    {
        printf("Nama\t: %-30s \n", ini->nama);
        printf("No. Kamar\t: %d\n", ini->no);
        printf("Lama Menginap\t: %d\n", ini->durasi);
        printf("Tanggal Check In\t: %d-%d-%d\n", ini->date, ini->month, ini->year);
        printf("Status\t: Approved pisang\n");
        printf("Price: %d\n", ini->price);
        printf("Kode booking: %s\n\n", ini->kodebook);
        ini = ini->next;
    }while(ini->next != pala);

    curr = head;
    do
    {
        printf("Nama\t: %-30s \n", curr->nama);
        printf("No. Kamar\t: %d\n", curr->no);
        printf("Lama Menginap\t: %d\n", curr->durasi);
        printf("Tanggal Check In\t: %d-%d-%d\n", curr->date, curr->month, curr->year);
        printf("Status\t: Approved pisang\n");
        printf("Price: %d\n", curr->price);
        printf("Kode booking: %s\n\n", curr->kodebook);
        curr = curr->next;
    }while(curr->next != head);
    system("pause");*/


    while(exit = 1){



        //system("cls");
        SetColorAndBackground(255,0);                                             //color value range 0 up-to 256
        printf("================================================\n");             //Menu booking hotel
        printf("               Hotel Del Luna\n ");
        printf("================================================\n");
        SetColorAndBackground(190,0);
        printf("                                    ,-,-.\n");
        printf("                                   /.( +.\\\n");
        printf("                                   \\ {. */\n");
        printf("                                    `-`-'\n");
        SetColorAndBackground(255,0);
        printf("                 _ _.-'`-._ _\n");
        printf("                ;.'________'.;\n");
        printf("     _________n.[____________].n_________\n");
        printf("    |'''''''''''||==||==||==||''''''''''']\n");
        printf("    |'''''''''' ||..||..||..||'''''''''''|\n");
        printf("    |LI LI LI LI||LI||LI||LI||LI LI LI LI|\n");
        printf("    |.. .. .. ..||..||..||..||.. .. .. ..|\n");
        printf("    |LI LI LI LI||LI||LI||LI||LI LI LI LI|\n");
        printf(" ,,;;,;;;,;;;,;;;,;;;,;;;,;;;,;;,;;;,;;;,;;,,\n\n");
        SetColorAndBackground(151,0);

        fflush(stdin);
        if(nr==0)
        {
            printf("Regular Room: All Available\n");
        }else{
            printf("Regular Room: ");
            ini=pala;
            for(i = 0; i < nr; i++){
                for(i=0;i<nr;i++)
                {
                    printf("\nKamar %d sudah dipesan", ini->no);
                    ini = ini->next;
                }
            }

        }

        if(nv==0)
        {
            printf("\n\nVIP Room : All Available\n");
        }else{
            printf("\nVIP Room: ");
            curr=head;
            for(i=0;i<nv;i++)
            {
                printf("\nKamar %d sudah dipesan", curr->no);
                curr = curr->next;
            }
        }

        printf("\n\n");
        printf("Harga kamar VIP: Rp. 600.000 / hari\n");
        printf("Harga kamar Reguler: Rp. 300.000 / hari\n\n\n");

        printf("Menu\n");
        printf("1. Input\n");
        printf("2. check\n");
        printf("3. cancel\n");
        printf("4. Exit\n");
        printf("Pilihan: ");scanf("%d", &choice);

        switch(choice){
            case 1: userinput(&pala, &ini, &ekor, &head, &curr, &tail, &titik, &node, &code);       //Switch case pilihan menu
                if(code==1)
                {
                    nr++;
                }else if(code==2)
                {
                    nv++;
                }
                break;

            case 2:
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
                    do
                    {
                        system("cls");
                        printf("Kamar Reguler\n");                                                  //print data yang sudah di sort.
                        printf("Nomor: %d\n",ini->no);
                        printf("Nama: %s\n",ini->nama);
                        printf("Tanggal Peminjaman: %d,%d,%d\n",ini->date,ini->month,ini->year);
                        printf("Durasi: %d hari\n",ini->durasi);
                        printf("Price : Rp. %d\n", ini->price);
                        printf("Menu:\n");
                        printf("1. Next\n");
                        printf("2. Previous\n");
                        printf("3. Exit\n");
                        printf("Pilihan:");scanf("%d",&flag);fflush(stdin);

                        if(flag==1)
                        {
                            ini=ini->next;                  // ke data selanjutnya
                        }
                        else if (flag==2)
                        {
                            ini=ini->prev;                  // ke data sebelumnya
                        }
                        else if (flag==3)
                        {
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
                    do
                    {
                        system("cls");
                        printf("Kamar Reguler\n");                                                  //print data yang sudah di sort.
                        printf("Nomor: %d\n",curr->no);
                        printf("Nama: %s\n",curr->nama);
                        printf("Tanggal Peminjaman: %d,%d,%d\n",curr->date,curr->month,curr->year);
                        printf("Durasi: %d hari\n",curr->durasi);
                        printf("Price : Rp. %d\n", curr->price);
                        printf("Menu:\n");
                        printf("1. Next\n");
                        printf("2. Previous\n");
                        printf("3. Exit\n");
                        printf("Pilihan:");scanf("%d",&flag);fflush(stdin);

                        if(flag==1)
                        {
                            curr=curr->next;                  // ke data selanjutnya
                        }
                        else if (flag==2)
                        {
                            curr=curr->prev;                  // ke data sebelumnya
                        }
                        else if (flag==3)
                        {
                            break;
                        }
                    }while(1);
                    system("cls");
                }
                break;


            case 3: cancel(&pala, &ini, &ekor, &head, &curr, &tail, &nr, &nv);
                break;
            case 4: exit = 0; break;

        }
    }

    return 0;
}
