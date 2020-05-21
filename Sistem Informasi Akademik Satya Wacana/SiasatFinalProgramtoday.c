#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
#include<time.h>
#include<ctype.h>
#include<dos.h>
#include <unistd.h>
#include <windows.h>

//fungsi program
void gotoxy(int x,int y);
void rectangle(int x,int y,int l,int b);
void delay(unsigned int mseconds);
int waktu(void);
void login();
void returnfunc();
void rocket();
void countdown();
void ulang();
void tutup();
int waktu();
char cari_mhs;

//fungsi admin
void admin();
void tambah_mhs();
void hapus_mhs();
void edit_mhs();
void view_mhs();
void pencari_mhs();
char us[40] = {"y"};
char pw[40] = {"x"};

FILE *fp, *ft;

struct mahasiswa
{
    int nim;
    char fakultas[10];
    char namaD[25];
    char namaB[25];
    float ips[5];
    float ipk;
};

struct mahasiswa a;
////////////////////////////
void menu()
{
    system("cls");
    int a;

    gotoxy(20,4);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 BERANDA ");
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(20,6);
    printf("\xDB\xDB\xDB 1. Tambah Mahasiswa");
    gotoxy(20,8);
    printf("\xDB\xDB\xDB 2. Hapus Mahasiswa");
    gotoxy(20,10);
    printf("\xDB\xDB\xDB 3. Perbarui Mahasiswa");
    gotoxy(20,12);
    printf("\xDB\xDB\xDB 4. List Mahasiswa");
    gotoxy(20,14);
    printf("\xDB\xDB\xDB 5. Pencarian Mahasiswa");
    gotoxy(20,16);
    printf("\xDB\xDB\xDB 6. Keluar");
    gotoxy(20,18);
    printf("------------------------------------------");
    gotoxy(20,19);
    waktu();

    switch(getch())
    {
    case '1':
        tambah_mhs();
        break;
    case '2':
        hapus_mhs();
        break;
    case '3':
        edit_mhs();
        break;
    case '4':
        view_mhs();
        break;
    case '5':
        pencari_mhs();
        break;
    case '6':
        system("cls");
        tutup();
        system("cls");
        countdown();
        system("cls");
        rocket();
        system("cls");
        exit(0);
    }
}

void tambah_mhs()
{
    int i,j,n,ceknim;
    float gpa;

    system("cls");

    gotoxy(20,4);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Tambah Mahasiswa");
    printf(" \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(20,6);
    printf("Jumlah mahasiswa yang akan diinput: ");
    gotoxy(57,6);
    scanf("%d", &n);

    struct mahasiswa a[n];

    fp = fopen("datamhs.txt", "a+");

    for(i=0;i<n;i++)
    {
        system("cls");

        gotoxy(20,3);
        printf("Input ke-%d",i+1);

        rectangle(20,4,76,10);
        gotoxy(21,5);
        printf("NIM:");
        gotoxy(27,5);
        scanf("%d", &ceknim);

        if(checknim(ceknim)==0)
        {
            gotoxy(20,13);
            printf("\aNIM sudah ada!");
            getch();
            menu();
        }
        a[i].nim = ceknim;
        gotoxy(21,6);
        printf("Fakultas:");
        gotoxy(32,6);
        scanf("%s", a[i].fakultas);
        gotoxy(21,7);
        printf("Nama Depan:");
        gotoxy(34,7);
        scanf("%s", a[i].namaD);
        gotoxy(21,8);
        printf("Nama Belakang:");
        gotoxy(37,8);
        scanf("%s", a[i].namaB);
        gotoxy(21,9);
        printf("IP (5 Semester):");

        for(j=0,gpa=0;j<5;j++)
        {
            gotoxy(38+(j*5),9);
            scanf("%f",&a[i].ips[j]);
            gpa+=a[i].ips[j];
        }

            gpa/=5.0;
            a[i].ipk=gpa;
    }
    fwrite(a, sizeof(a), 1, fp);
    fclose(fp);

    gotoxy(20,11);
    printf("Data berhasil diisi!");

    gotoxy(20,12);
    returnfunc();
}

void hapus_mhs()
{
    system("cls");
    int d;
    char lagi='y';
    while(lagi=='y')
    {
        system("cls");
        gotoxy(10,5);
        printf("Masukkan NIM mahasiswa yang akan dihapus: ");
        scanf("%d",&d);
        fp=fopen("datamhs.txt","r+");
        rewind(fp);
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(a.nim==d)
            {
                gotoxy(10,7);
                printf("Data Mahasiswa ditemukan!");
                rectangle(10,10,76,14);
                gotoxy(11,11);
                printf("Nama: %s %s",a.namaD, a.namaB);
                gotoxy(11,12);
                printf("NIM: %d",a.nim);
                gotoxy(11,13);
                printf("Fakultas: %s",a.fakultas);
                cari_mhs='t';
            }
        }
            if(cari_mhs!='t')
            {
                gotoxy(10,10);
                printf("Data tidak ditemukan!");
                if(getch())
                menu();
            }
            if(cari_mhs='t')
            {
                gotoxy(10,9);
                printf("Apakah anda ingin menghapus? (y/n) ");
                if(getch()=='y')
                {
                    ft=fopen("t.txt","w+");
                    rewind(fp);
                    while(fread(&a,sizeof(a),1,fp)==1)
                    {
                        if(a.nim!=d)
                        {
                            fseek(ft,0,SEEK_CUR);
                            fwrite(&a,sizeof(a),1,ft);
                        }
                    }
                    fclose(ft);
                    fclose(fp);
                    remove("datamhs.txt");
                    rename("t.txt","datamhs.txt");
                    fp=fopen("datamhs.dat","rb+");
                    if(cari_mhs='t')
                    {
                        gotoxy(10,16);
                        printf("berhasil dihapus!");
                        gotoxy(10,17);
                        printf("hapus lagi?(Y/N)");
                    }
                }
                else
                    menu();
                    fflush(stdin);
                    lagi=getch();
            }
    }
    gotoxy(10,15);
    menu();
}

void edit_mhs()
{
    system("cls");
    int c=0;
    int d,e;
    rectangle(0,0,71,23);
    gotoxy(20,4);
    printf("**************************EDIT MAHASISWA**************************");
    char another='y';
    while(another=='y')
    {
        system("cls");
        gotoxy(15,6);
        printf("Masukkan NIM Mahasiswa yang akan diedit: ");
        scanf("%d",&d);
        fp=fopen("datamhs.txt","r+");
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(checknim(d)==0)
            {
                gotoxy(20,8);
                printf("NIM: %d",a.nim);
                gotoxy(20,9);
                printf("Nama Depan:");scanf("%s",a.namaD);
                gotoxy(20,10);
                printf("Nama Belakang:");scanf("%s",a.namaB);
                gotoxy(20,11);
                printf("Fakultas:");scanf("%s",a.fakultas);
                printf("Data telah diubah!\a\a");
                fseek(fp,ftell(fp)-sizeof(a),0);
                fwrite(&a,sizeof(a),1,fp);
                fclose(fp);
                c=1;
            }
            if(c==0)
            {
                gotoxy(20,9);
                printf("Data tidak ditemukan!");
            }
        }
        gotoxy(20,16);
        printf("Lagi? (Y/N)");
        fflush(stdin);
        another=getch() ;
    }
        returnfunc();
}

void pencari_mhs()
{
    system("cls");
    int c=0;
    int d;
    rectangle(0,0,71,16);
    gotoxy(1,1);
    printf("**************************PENCAHARIAN MAHASISWA**********************");

    gotoxy(15,4);
    printf("MASUKAN NIM :");
    scanf("%d",&d);
    gotoxy(25,5);
    fp=fopen("datamhs.txt","r+");
    while(fread(&a,sizeof(a),1,fp)==1)
    {


               if(checknim(d)==0)
    {
        gotoxy(15,8);
        printf("NIM          : %d",a.nim);
        gotoxy(15,9);
        printf("Nama Depan   : %s",a.namaD);
        gotoxy(15,10);
        printf("Nama Belakang: %s",a.namaB);
        gotoxy(15,11);
        printf("Fakultas     : %s",a.fakultas);
        gotoxy(15,12);
        printf("\n\n");
        fseek(fp,ftell(fp)-sizeof(a),0);
        fwrite(&a,sizeof(a),1,fp);
        fclose(fp);
        c=1;
    }


            if(c==0)
            {
                gotoxy(15,9);
                printf("Data tidak ditemukan!");
            }


    }

    gotoxy(1,29);
    returnfunc();


}

void view_mhs()
{
    int i=0,j,jumlah;
    system("cls");
    rectangle(0,0,71,23);
    gotoxy(1,1);
    printf("*****************************LIST MAHASISWA**************************");
    gotoxy(1,2);
    printf("FAKULTAS           NIM          NAMA LENGKAP                  IPK    ");
    j=4;

    fp = fopen("datamhs.txt", "r");
    while(fread(&a, sizeof(a), 1, fp) == 1)
    {
        gotoxy(4,j);
        printf("%s", a.fakultas);
        gotoxy(20,j);
        printf("%d", a.nim);
        gotoxy(33,j);
        printf("%s %s", a.namaD, a.namaB);
        gotoxy(63,j);
        printf("%.2f", a.ipk);
        printf("\n\n");
        j++;
    }
    jumlah = j - 4;
    gotoxy(1,20);
    printf("Jumlah Mahasiswa: %d", jumlah);
    fclose(fp);
    gotoxy(1,22);
    returnfunc();
}

void tutup()
{
    int i;
    system("cls");
    rectangle(0,0,80,23);
    gotoxy(29,4); printf("TUGAS RANCANG ASD D");
    gotoxy(25,5); for(i=0;i<27;i++) printf("%c",196);
    gotoxy(25,8); printf("Dibuat oleh:");
    gotoxy(25,9);for(i=0;i<27;i++) printf("%c",196);
    gotoxy(25,11); printf("Axl D. B. Hallatu/672017077");
    gotoxy(25,13); printf("Aldyth M. V. Nahak/672017081");
    gotoxy(25,15); printf("Stefanus Y. M. Nange/672017091");
    gotoxy(25,17); printf("Immanuel W. Irsal/672017207");
    gotoxy(16,21);

    printf("Terima kasih telah menggunakan program kami. . .");

    getch();
}

void login(void)
{
    system("cls");
    char a[100] = "SISTEM INFORMASI AKADEMIK SATYA WACANA";
    char w[100] = "L0calh34rtz@gmail.com";
    char ch, user[20], pass[20];
    int i = 0, j;

    gotoxy(10,4);
    for(j = 0; j < 20; j++)
    {
        delay(50);
        printf("*");
    }

    for(j = 0; j < 38; j++)
    {
        delay(50);
        printf("%c", a[j]);
    }

    for(j = 0; j < 20; j++)
    {
        delay(50);
        printf("*");
    }

    gotoxy(37,5);
    for(j = 0; j < 24; j++)
    {
        delay(50);
        printf("%c", w[j]);
    }

    gotoxy(44,20);
    waktu();

    gotoxy(15,9);
    printf("Username: ");
    scanf("%s", user);
    gotoxy(15,10);
    printf("Password: ");

    while(ch != 13)
    {
        ch = getch();

        if(ch != 13 && ch != 8)
        {
            putch('*');
            pass[i] = ch;
            i++;
        }
    }
    pass[i] = '\0';

    if(strcmp(user,us)==0 && strcmp(pass,pw)==0)
    {
        system("cls");
        gotoxy(15,12);
        printf("Login Berhasil!");
        gotoxy(15,13);
        printf("Tekan untuk melanjutkan . . . . . ");
        getch();
        menu();
    }
    else{
        gotoxy(15,13);
        printf("\aUsername/Password Salah!");
        getch();
        login();
    }
}
///////////////////////////

int main()
{
    login();
    return;
}

//////////////////////////
COORD coord = {0, 0};
COORD max_res,cursor_size;

void gotoxy (int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void rectangle(int x,int y,int l,int b)
{
    int i,m;
    gotoxy(x,y);
    printf("%c",201);
    for(i=x+1;i<l-1;i++)
    {
        gotoxy(i,y);
        printf("%c",205);
    }
    gotoxy(i,y);
    printf("%c",187);

    for (m=y+1;m<b;m++)
    {
        gotoxy(x,m);
        for(i=x;i<l;i++)
        {
            if(i==x||i==l-1)
            {
                gotoxy(i,m);
                printf("%c",186);
            }

        }

    }

    gotoxy(x,m); printf("%c",200);
    for(i=x+1;i<l-1;i++)
    {
        gotoxy(i,m);
        printf("%c",205);
    }
    gotoxy(i,m); printf("%c",188);
}

int waktu(void)
{
    time_t t;
    time(&t);
    printf("Tanggal dan waktu: %s\n",ctime(&t));

    return 0 ;
}

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void returnfunc()
{
    {
    printf(" Untuk kembali tekan ENTER");
    }
    a:
    if(getch()==13) //allow only use of enter
    menu();
    else
    goto a;
}

void countdown()
{
    int a,i;
    for(a = 3; a >= 0; a--)
        {
            gotoxy(10,7);
            printf("Program akan keluar otomatis dalam %d detik . . . . . ", a);
            delay(1000);
        }
}

int checknim(int t)
{
    rewind(fp);
    while(fread(&a,sizeof(a),1,fp)==1)
    if(a.nim==t)
    return 0;
      return 1;
}

void rocket()
{
    int i;
    const char rocket[] =
"           _\n\
          /^\\\n\
          |-|\n\
          | |\n\
          |N|\n\
          |A|\n\
          |S|\n\
          |A|\n\
         /| |\\\n\
        / | | \\\n\
       |  | |  |\n\
        `-\"\"\"-`\n\
";

    for (i = 0; i < 50; i ++) printf("\n");
    printf("%s", rocket);
    int j = 300000;
    for (i = 0; i < 50; i ++) {
        usleep(j);
        j = (int)(j * 0.9);
        printf("\n");
    }
}
//////////////////////////



