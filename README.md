# soal-shift-sisop-modul-2-itb02-202

## Laporan Pengerjaan Modul 2 Praktikum Sistem Operasi

### Nama Anggota Kelompok

1. Rachmita Annisa Aulia 5027201032
2. Alvian Ghifari 5027201035
3. Satrio Kamil Widhiwoso 5027201051

# Soal 1

Mas Refadi adalah seorang wibu gemink.  Dan jelas game favoritnya adalah bengshin impek. Terlebih pada game tersebut ada sistem gacha item yang membuat orang-orang selalu ketagihan untuk terus melakukan nya. Tidak terkecuali dengan mas Refadi sendiri. Karena rasa penasaran bagaimana sistem gacha bekerja, maka dia ingin membuat sebuah program untuk men-simulasi sistem history gacha item pada game tersebut. Tetapi karena dia lebih suka nge-wibu dibanding ngoding, maka dia meminta bantuanmu untuk membuatkan program nya. Sebagai seorang programmer handal, bantulah mas Refadi untuk memenuhi keinginan nya itu. 


A. Saat program pertama kali berjalan. Program akan mendownload file characters dan file weapons dari link yang ada dibawah, lalu program akan mengekstrak kedua file tersebut. File tersebut akan digunakan sebagai database untuk melakukan gacha item characters dan weapons. Kemudian akan dibuat sebuah folder dengan nama “**gacha_gacha**” sebagai working directory. Seluruh hasil gacha akan berada di dalam folder tersebut. **Penjelasan sistem gacha ada di poin (d).**

B. Mas Refadi ingin agar setiap kali gacha, item characters dan item weapon akan selalu bergantian diambil datanya dari database. Maka untuk setiap kali jumlah-gacha nya bernilai genap akan dilakukan gacha item weapons, jika bernilai ganjil maka item characters. Lalu untuk setiap kali jumlah-gacha nya mod 10, maka akan dibuat sebuah file baru (.txt) dan output hasil gacha selanjutnya akan berada di dalam file baru tersebut. Dan setiap kali jumlah-gacha nya mod 90, maka akan dibuat sebuah folder baru dan file (.txt) selanjutnya akan berada didalam folder baru tersebut.  **Sehingga untuk setiap folder, akan terdapat 9 file (.txt) yang didalamnya berisi 10 hasil gacha**. Dan karena ini simulasi gacha, maka hasil gacha di dalam file .txt adalah **ACAK/RANDOM** dan setiap file (.txt) isi nya akan **BERBEDA**

C. Format penamaan setiap file (.txt) nya adalah {Hh:Mm:Ss}_gacha_{jumlah-gacha}, misal 04:44:12_gacha_120.txt, dan format penamaan untuk setiap folder nya adalah total_gacha_{jumlah-gacha}, misal total_gacha_270. Dan untuk setiap file (.txt) akan memiliki perbedaan penamaan waktu output sebesar 1 second.

D. Pada game tersebut, untuk melakukan gacha item kita harus menggunakan alat tukar yang dinamakan primogems. Satu kali gacha item akan menghabiskan primogems sebanyak 160 primogems. Karena mas Refadi ingin agar hasil simulasi gacha nya terlihat banyak, maka pada program, primogems di awal di-define sebanyak 79000 primogems. Setiap kali gacha, ada 2 properties yang akan diambil dari database, yaitu name dan rarity. Lalu Outpukan hasil gacha nya ke dalam file (.txt) dengan format hasil gacha **{jumlah-gacha}_[tipe-item]_{rarity}_{name}_{sisa-primogems}**. Program akan selalu melakukan gacha hingga primogems habis.
Contoh : 

E. Proses untuk melakukan gacha item akan dimulai bertepatan dengan anniversary pertama kali mas Refadi bermain bengshin impek, yaitu pada 30 Maret jam 04:44.  Kemudian agar hasil gacha nya tidak dilihat oleh teman kos nya, maka 3 jam setelah anniversary tersebut semua isi di folder gacha_gacha akan di zip dengan nama not_safe_for_wibu dengan dipassword "satuduatiga", lalu semua folder akan di delete sehingga hanya menyisakan file (.zip)

## Penjelasan Code Soal 1
Dalam soal ini kita diminta untuk membuat sebuah simulasi gacha. Kita diberikan 2 buah link untuk di download dan akan digunakan sebagai database item yang akan digacha yaitu weapons dan character. File database yang diberikan adalah dalam format json. Dalam simulasi ini diberikan sebuah primogems yang dapat digunakan untuk melakukan gacha, yaitu 79000 dan setiap gacha yang dilakukan akan mengurangi sebanyak 160 primogems.

## A
Disini kita diminta untuk melakukan download file characters dan file weapons dan dimminta untuk mengekstrak kedua file itu. Kita juga diminta untuk membuat sebuah folder yang bernama "gacha_gacha" yang akan digunakan untuk menyimpan semua hasil gacha.

#### **buat dua child proses untuk download dan bikin folder**
```c
pid_t childfrom1, childfrom1_2;
(childfrom1 = fork()) && (childfrom1_2 = fork());
```
#### **child 1 untuk  download**
```c
if (childfrom1 == 0)
{
    char *argv[][6] = {
        {"wget", "-q", "https://drive.google.com/u/0/uc?id=1xYYmsslb-9s8-4BDvosym7R4EmPi6BHp&export=download", "-O", "characters.zip", NULL},
        {"wget", "-q", "https://drive.google.com/u/0/uc?id=1XSkAqqjkNmzZ0AdIZQt_eWGOZ0eJyNlT&export=download", "-O", "weapons.zip", NULL}};
    printf("Sedang download database..");
    for (int x = 0; x < 2; x++)
    {
        if (fork() == 0)
            continue;
        sleep(10);
        execv("/bin/wget", argv[x]);
    }
}
```
child proses pertama diatas digunakan untuk mendownload file menggunakan wget, disitu akan dilakukan perulangan sebanyak jumlah file yang ingin di download, yaitu sebanyak 2. Menggunakan execv untuk memanggil fungsi system(wget), dan diberi sleep(10) untuk memberi jeda setiap file yang di download agar selesai.

#### **child 2 untuk membuat folder**
```c
else if (childfrom1_2 == 0)
{
    char *argv[] = {"mkdir", "gacha_gacha", NULL};
    execv("/bin/mkdir", argv);
}
```
Child ini digunakan untuk membuat folder "gacha_gacha".

selanjutnya setelah kedua child tersebut telah selesai, maka akan masuk ke parent dari kedua proses tersebut, disini digunakan fungsi wait untuk menunggu kedua proses tersebut berjalan. 

pada parent ini akan dilakukan unzip dan menghapus file zip yang telah didownload di awal tadi. di parent ini akan dibuat child lagi untuk melakukan remove setelah unzip selesai.

#### **parent yang membuat child untuk unzip dan remove zip**
```c
else
{
    while ((wait(&status)) > 0)
        ;
    pid_t inichild3;
    inichild3 = fork();
    if (inichild3 == 0)
    {
        char *argv[][5] = {
            {"unzip", "-q", "characters.zip", NULL},
            {"unzip", "-q", "weapons.zip", NULL}};
        printf("\nSedang unzip..\n");
        for (int x = 0; x < 2; x++)
        {
            if (fork() == 0)
                continue;
            sleep(10);
            execv("/bin/unzip", argv[x]);
        }
    }
    else
    {
        while ((wait(&status)) > 0)
            ;
        char *argv[][6] = {
            {"rm", "characters.zip", NULL},
            {"rm", "weapons.zip", NULL}};
        for (int x = 0; x < 2; x++)
        {
            if (fork() == 0)
                continue;
            execv("/bin/rm", argv[x]);
        }
    }
}
```

## B
Disini kita diberitahu bahwa setiap gacha bernilai genap akan melakukan gacha weapons, dan setiap gacha bernilai ganjil akan melakukan gacha character. Lalu untuk setiap kali gacha mod 10 akan membuat file baru (txt) untuk memasukkan semua hasil gacha setelahnya dan untuk setiap kali mod 90 akan membuat folder yang isinya adalah kumpulan 9 file setelahnya. Sehingga untuk setiap folder, akan terdapat 9 file (.txt) yang didalamnya berisi 10 hasil gacha.

#### **bentuk while loop untuk melakukan gacha sampai primogems habis**
```c
while (primogems > 0)
{
    if (i % 2 == 0) // genap
    {
        if (i % 90 == 0) 
        {

            if (i % 10 == 0)
            {
                // buat folder dan file txt
            }
        }
        else if (i % 10 == 0)
        {
            //buat file txt
        }
    //gacha untuk weapons
    }
    else if (i % 2 == 1) // ganjil
    {
       //gacha untuk character
    }
    i++;
    primogems = primogems - 160;
    sleep(1);
}
```

Diatas adalah gambaran loop yang dilakukan untuk melakukan gacha sampai primogems habis. Untuk genap gacha dilakukan setelah pengecekan apakah iterasi mod 90 dan mod 10, jika iya akan membuat file dan folder sesuai iterasinya, jika tidak maka akan tetap melakukan gacha dan disimpan ke file yang telah ada. juga dapat dilihat primogems juga akan berkurang sebanyak 160 setiap kali perulangan.

#### **jika mod 2 dan mod 90**
```c
if (i % 90 == 0)
{

    f = f + 90;
    createFolder(f);
    if (i % 10 == 0)
    {
        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        sprintf(waktu, "%d:%d:%d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
        jam = waktu;
        persepuluh = persepuluh + 10;
    }
}
```
#### **Fungsi Create Folder**
```c
void createFolder(int f)
{
    int status = 0;
    if (fork() == 0)
    {
        char buffer[256];
        snprintf(buffer, sizeof buffer, "./gacha_gacha/total_gacha_%d", f + 90);
        char *argv[] = {"mkdir", buffer, NULL};
        execv("/bin/mkdir", argv);
    }
    while (wait(&status) > 0);
}
```

#### **jika hanya mod 10**
```c
else if (i % 10 == 0)
{
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    sprintf(waktu, "%d:%d:%d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    jam = waktu;
    persepuluh = persepuluh + 10;
}
```
Ini untuk menyimpan variabel2 yang nanti digunakan untuk penamaan file. file akan dibuat pada saat gacha genap dilakukan.


karena ini simulasi gacha, pengambilan akan dilakukan secara random dari database yang telah diberikan. Cara yang dapat digunakan untuk melakukan random adalah mengumpulkan semua file yang ada di suatu database character atau weapons kedalam sebuah array. Setelah memasukkan ke dalam array maka akan dilakukan randomisasi menggunakan fungsi rand()

#### **Randomisasi/gacha namafile yang akan diambil**
```c
const char *getweapons()
{
    DIR *d = opendir("/home/alvin/Sistem_Operasi/Modul2/rundisini/weapons");
    int i = 0;
    char *arrayWeapon[131];
    struct dirent *dir;
    dir = readdir(d);

    while (dir != NULL)
    {
        if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))
        {
        }
        else
        {
            arrayWeapon[i] = (char *)malloc(strlen(dir->d_name) + 1);
            strcpy(arrayWeapon[i], dir->d_name);
            i++;
        }
        dir = readdir(d);
    }

    closedir(d);

    srand(time(0));
    int lower = 0, upper = (130 - 1);
    int random = rand() % (upper - lower + 1) + lower;

    return arrayWeapon[random];
}
```
Dapat dilihat diatas adalah sebuah fungsi yang akan mereturn sebuah namafile secara acak/random. Hal yang sama dilakukan dengan database character.
## C
untuk menamai file dan folder, akan menggunakan sprintf untuk menggabungkan template nama dan direktori yang ada.

### **nama folder**
```c
snprintf(buffer, sizeof buffer, "./gacha_gacha/total_gacha_%d", f + 90);
char *argv[] = {"mkdir", buffer, NULL};
execv("/bin/mkdir", argv);
```
### **nama file**
```c
snprintf(filePath, sizeof filePath, "./gacha_gacha/total_gacha_%d/%s_gacha_%d.txt", f + 90, jam, persepuluh - 10);
```
snprintf juga bisa digunakan untuk membuat file jika file tersebut tidak ada.

## D
Disini dijelaskan untuk melakukan gacha akan memerlukan 160 primogems, dan diawal akan di define sebanyak 79000. Setiap kali melakukan gacha akan ada 2 properties yang akan diambil dari database, yaitu **name** dan **rarity**. untuk melakukan parsing dari json ke c diawal akan mendefine beberapa variabel.

#### **define struct dan buffer untuk parsing data json**
```c
FILE *fp;
char buffer[4096];
struct json_object *parsed_json;
struct json_object *rarity;
struct json_object *name;
```

setelah membuat struct dan buffer, untuk mengambil data dari json yang diinginkan adalah sebagai berikut
#### **contoh parsing genap(weapons)**
```c
const char *weapon = getweapons();
char namafile[256];
snprintf(namafile, sizeof namafile, "./weapons/%s", weapon);
fp = fopen(namafile, "r");
fread(buffer, 4096, 1, fp);
fclose(fp);
parsed_json = json_tokener_parse(buffer);
json_object_object_get_ex(parsed_json, "name", &name);
json_object_object_get_ex(parsed_json, "rarity", &rarity);

FILE *d = NULL;
char filePath[500];
snprintf(filePath, sizeof filePath, "./gacha_gacha/total_gacha_%d/%s_gacha_%d.txt", f + 90, jam, persepuluh - 10);
d = fopen(filePath, "a");
fprintf(d, "%d_weapons_%d_%s_%d\n", i, json_object_get_int(rarity), json_object_get_string(name), primogems);
fclose(d);
```
Dapat dilihat diatas, setelah melakukan parsing sebuah json dari file yang telah dirandom, maka akan melakukan append pada file yang sebelumnya telah dibuat dengan menggunakan fprintf sesuai format yang ada. dan jika file yang ingin dibuat tidak ada, maka akan otomatis membuat file tersebut dengan sesuai variabel yang telah diambil pada mod 10.

**Proses diatas juga dilakukan pada iterasi ganjil dengan perbedaan database yang diambil**

## E
Di poin E ini kita diminta untuk membuat daemon proses dimana semua script diatas akan dijalankan pada 30 Maret jam 04:44. dan setelah tiga jam semua isi di folder gacha_gacha akan di zip dengan nama not_safe_for_wibu dengan dipassword "satuduatiga", lalu semua folder akan di delete sehingga hanya menyisakan file (.zip).

untuk membuat daemon kita menggunakan template daemon yang sudah disediakan di github, dan untuk mengatur kode dijalankan sesuai jam yang diinginkan, kita menggunakan epochtime dari tanggal yang telah diberikan dan mengatur agar kode tersebut akan berjalan jika local time machine sudah melewati batas waktu tersebut. dan jika melebihi 3 jam dari waktu anniv, maka kode yang selanjutnya akan berjalan.

#### **Template daemon**
```c
int main()
{
    pid_t pid, sid; // Variabel untuk menyimpan PID
    int status;
    pid = fork(); // Menyimpan PID dari Child Process

    /* Keluar saat fork gagal
     * (nilai variabel pid < 0) */
    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }

    /* Keluar saat fork berhasil
     * (nilai variabel pid adalah PID dari child process) */
    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/home/alvin/Sistem_Operasi/Modul2/rundisini")) < 0)
    {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    time_t currenttime = time(NULL);
    int limit = 1;
    while (1)
    {
        currenttime = time(NULL);
        if (currenttime >= 1648590284 && limit == 1)
        {
            //kode saat jam anniv
        }
        else if (currenttime >= 1648601084)
        {
            //kode setelah 3 jam
        }
    }
    return 0;
}
```
Script total yang sebelumnya dibuat akan ditaruh pada if pertama `if (currenttime >= 1648590284 && limit == 1)`

dan script untuk zip dan remove akan ditaruh pada else if kedua `else if (currenttime >= 1648601084)`

#### **Script setelah 3 jam anniv**
```c
// kode setelah jam d-day
else if (currenttime >= 1648601084)
{
    // kode setelah jam d-day
    pid_t childsetelahjam;
    childsetelahjam = fork();
    if (childsetelahjam == 0)
    {
        char *zipAkhir[] = {"zip", "-r", "-P", "satuduatiga", "not_safe_for_wibu.zip", "gacha_gacha", NULL};
        execv("/bin/zip", zipAkhir);
    }
    else
    {
        while ((wait(&status)) > 0)
            ;
        char *hapus[] = {"rm", "-v", "!(*.zip)", NULL};
        execv("/bin/rm", hapus);
        exit(1);
    }

    sleep(30);
}
```
## Kendala yang dihadapi
Kendala yang dihadapi adalah tidak dapat merandom 10 file dalam waktu 1 detik, sehingga yang awalnya diminta file random akan berjarak 1 detik, hasilnya file random berjarak 10 detik karena srand tidak dapat megenerate seed untuk random baru dibawah 1 detik 

## Screenshot hasil soal 1

#### **HASIL FOLDER GACHA_GACHA**
![1](https://user-images.githubusercontent.com/83297238/159967310-022044e8-4858-492c-b7fd-7d6955746569.png)
#### **FOLDER PERTAMA (total_gacha_90)**
![2](https://user-images.githubusercontent.com/83297238/159967319-fc271739-53a3-4288-aee6-8b7a50c7d878.png)
#### **HASIL FOLDER TERAKHIR(total_gacha_540)**
![3](https://user-images.githubusercontent.com/83297238/159967323-390d3054-136a-46d9-9d9a-7913dd8b1a66.png)
#### **HASIL FILE TXT PERTAMA**
![4](https://user-images.githubusercontent.com/83297238/159967326-421be4fc-261f-4e96-b210-a1d99391bfe1.png)
#### **HASIL FILE TXT TERAKHIR**
![5](https://user-images.githubusercontent.com/83297238/159967328-dd28e2bf-5abf-48ec-ae20-26a2831e838c.png)
**79000/160= 493.75 (ada 493 kali gacha)**
#### **HASIL DAEMON**
![6](https://user-images.githubusercontent.com/83297238/159967331-47b6cf5b-c4df-4a61-8927-e963ef60b5ed.png)


# Soal 3

Conan adalah seorang detektif terkenal. Suatu hari, Conan menerima beberapa laporan tentang hewan di kebun binatang yang tiba-tiba hilang. Karena jenis-jenis hewan yang hilang banyak, maka perlu melakukan klasifikasi hewan apa saja yang hilang.

A. Untuk mempercepat klasifikasi, Conan diminta membuat program untuk membuat 2 directory di **/home/[USER]/modul2/** dengan nama `darat` lalu 3 detik kemudian membuat directory ke 2 dengan nama `air`. 

B. Kemudian program diminta dapat melakukan extract **animal.zip** di **/home/[USER]/modul2/**.

C. Tidak hanya itu, hasil extract dipisah menjadi hewan darat dan hewan air sesuai dengan nama filenya. Untuk hewan darat dimasukkan ke folder **/home/[USER]/modul2/darat** dan untuk hewan air dimasukkan ke folder **/home/[USER]/modul2/air**. Rentang pembuatan antara folder darat dengan folder air adalah 3 detik dimana folder darat dibuat terlebih dahulu. Untuk hewan yang tidak ada keterangan air atau darat harus dihapus.

D. Setelah berhasil memisahkan hewan berdasarkan hewan darat atau hewan air. Dikarenakan jumlah burung yang ada di kebun binatang terlalu banyak, maka pihak kebun binatang harus merelakannya sehingga conan harus menghapus semua burung yang ada di directory **/home/[USER]/modul2/darat**. Hewan burung ditandai dengan adanya `bird` pada nama file.

E. Terakhir, Conan harus membuat file list.txt di folder **/home/[USER]/modul2/air** dan membuat list nama semua hewan yang ada di directory **/home/[USER]/modul2/air** ke `list.txt` dengan format **UID_[UID file permission]_Nama File.[jpg/png]** dimana UID adalah user dari file tersebut file permission adalah permission dari file tersebut.
Contoh : conan_rwx_hewan.png

## Penjelasan Code Soal 3
Dalam soal ini, kita diminta untuk meng-unzip file yang telah diberikan yaitu **animal.zip**. Kemudian, buat dua direktori yang bernama darat dan air pada folder **/home/[USER]/modul2/** . Dari hasil unzip tersebut, bagi file yang mengandung nama darat, maka akan dimasukkan ke direktori darat. Begitu juga dengan file yang mengandung nama air akan masuk ke direktori air. Selanjutnya, kita diminta untuk menghapus file yang mengandung nama `bird` dan file yang tidak memiliki klasifikasi darat maupun air. Terakhir, kita diminta untuk membuat file yang bernama **list.txt** di folder **/home/[USER]/modul2/air** dengan isi nama semua hewan yang berada di direktori **/home/[USER]/modul2/air** dengan format **UID_[UID file permission]_Nama File.[jpg/png]** dimana UID adalah user dari file tersebut file permission adalah permission dari file tersebut.

## A
Kita diminta untuk membuat program untuk membuat 2 directory di **/home/[USER]/modul2/** dengan nama `darat` lalu 3 detik kemudian membuat directory ke 2 dengan nama `air`. 

### Membuat direktori *darat* dan *air*
```c
void listFilesRecursively(char * path);
int main() {
  chdir("/home/[USER]/modul2/");

  int fork0 = fork();
  int status;

  if (fork0 == 0) {
    char * argv[] = {"mkdir", "-p", "darat", NULL };
    execv("/bin/mkdir", argv);
  } 
  else {
    while ((wait( & status)) > 0);
    int fork2 = fork();
    
    if (fork2 == 0) {
      sleep(3);
      char * argv[] = {"mkdir","-p","air",NULL};
      execv("/bin/mkdir", argv);
    }
  }
} 
```
Pertama-tama, kita deklarasikan terlebih dahulu fungsi `void listFilesRecursively(char * path);` untuk merekursi file dalam sebuah direktori yang akan digunakan pada soal selanjutnya dan akan juga saya jelaskan nanti. Sebelum kita membuat direktori, kita perlu mengubah working directory terlebih dahulu karena direktori darat dan air akan dibuat di direktori modul dua. Caranya adalah dengan menggunakan function `chdir("directory")`. Kemudian kita lanjutkan dengan mendeklarasikan status dan fork untuk membuat dua proses yaitu *child* dan *parent*, proses child akan ditandai dengan PID nya sama dengan 0. Selanjutnya, gunakan fungsi `if(fork==0)` untuk melanjutkan proses di child. Kemudian kita deklarasi array argv dengan isi `"mkdir", "-p", "darat", NULL ` yang digunakan untuk membuat direktori bernama darat ("**-p**" digunakan agar tidak error jika direktori bernama darat sudah ada), **NULL** digunakan untuk menandai akhirnya proses. Kemudian kita menggunakan function execv dengan parameter path function mkdir dan array argv yang berisi commandnya. Jika `execv()` berhasil dijalankan, maka program akan berhenti, maka dari itu, kita menggunakan function `else` untuk kembali ke proses *parent*. Pada function else, akan ditulis kode `while ((wait( & status)) > 0);` yang akan menunggu proses childnya selesai terlebih dahulu sebelum melanjutkan ke proses parent. Dilanjutkan dengan deklarasi fork selanjutnya agar program bisa terus berjalan walaupun menggunakan function `execv`. Bisa dibilang penggunaan `fork()` dan `execv()` adalah pengganti function `system()` yang tidak boleh digunakan pada soal ini. Setelah `wait()` selesai dijalankan, digunakan function `sleep(3)` untuk memberikan delay selama tiga detik sesuai dengan permintaan soal. Setelah delay tiga detik, akan dibuat direktori bernama air yang memiliki langkah-lagkah yang sama dengan pembuatan direktori darat. Perbedaannya hanya terletak di nama filenya.

## B
Dalam soal ini bagian ini, kita diminta untuk meng-unzip file yang telah diberikan yaitu **animal.zip**.

```c
else {
      while ((wait( & status)) > 0);
      int fork3 = fork();
      
      if (fork3 == 0) {  
        char * argv[] = {"unzip","animal.zip", NULL};
        execv("/bin/unzip", argv);
      }
} 
```
Sama seperti sebelumnya, kita akan menggunakan function `wait()` untuk menunggu proses sebelumnya selesai, dan `fork()` untuk membentu fork lain agar program dapat lanjut berjalan. Pada kode ini, array argv diisi dengan command `"unzip","animal.zip", NULL` yang digunakan untuk mengextract suatu file zip. Kemudain `execv()` berisi parameter file path nya yaitu **/bin/unzip** dan commandnya yang sebelumnya sudah tercatat di array argv.

## C
Setelah file tersebut di unzip, akan dihasilkan sebuah direktori bernama animal yang berisi nama-nama binatang dan tempat hidupnya(darat/air). Kita diminta untuk memindahkan semua file yang mengandung nama **"darat"** ke direktori **darat** yang sudah kita buat pada soal sebelumnya, dan memindahkan semua file yang mengandung nama **"air"** ke direktori **air** yang sudah kita buat jugaa pada soal sebelumnya. Setelah itu delete hewan yang tidak memilki keterangan air atau darat.

### Memindahkan file yang mengandung nama *darat* dan *air* ke foldernya masing-masing 
```c
else {
    while ((wait( & status)) > 0);
    int fork4 = fork();
    
    if (fork4 == 0) {
        char * argv[] = {"find", "/home/[USER]/modul2/animal/", "-name", "*darat*", "-exec", "mv", "-t", "/home/[USER]/modul2/darat/", "{}", "+", NULL};
        execv("/bin/find", argv);
        } 
        else {
            while ((wait( & status)) > 0);
            int fork5 = fork();
            if (fork5 == 0) {
                char * argv[] = {"find", "/home/[USER]/modul2/animal/", "-name", "*air*", "-exec","mv", "-t", "/home/[USER]/modul2/air/", "{}", "+", NULL};
                execv("/bin/find", argv);
                }
        }
}
```
Sama seperti sebelumnya, kita akan menggunakan function `wait()` untuk menunggu proses sebelumnya selesai, dan `fork()` untuk membentu fork lain agar program dapat lanjut berjalan. Pada kode ini, array argv diisi dengan command `{"find", "/home/[USER]/modul2/animal/", "-name", "*darat*", "-exec", "mv", "-t", "/home/[USER]/modul2/darat/", "{}", "+", NULL};`. Command `find` digunakna untuk mencari file dalam sebuah direktori, `/home/[USER]/modul2/animal/` adalah direktori yang akan digunakan untuk mencari filenya, `"-name", "*darat*"` digunakan untuk mencari file yang mengandung nama darat entah itu di awal, di tengah, maupun di akhir. Command `"-exec", "mv"` adalah lanjutan dari command `find`, yang berfungsi untuk memindahkan file hasil pencarian tersebut ke direktori tertentu, dan `"/home/[USER]/modul2/darat/"` adalah tujuan pindahnya. kemudian akan dijalankan `execv()` dengan parameter file path nya yaitu **/bin/find**, dan command yang akan dieksekusi sesuai dengan array argv. Fungsi `find()` ini juga digunakan untuk memindahkan file yang mengandung nama air pada direktori animal, ke dalam direktori air. Perbedaannya adalah command `"-name", "*darat*"`, diganti dengan `"-name", "*air*"`, dan path direktori `"/home/[USER]/modul2/darat/"` diganti dengan `"/home/[USER]/modul2/air/"`.

### Menghapus hewan yang tidak memilki keterangan *air* atau *darat*.
Selanjutnya, kita diminta untuk menghapus hewan yang tidak memilki keterangan air atau darat.
```c
else {
    while ((wait( & status)) > 0);
    int fork6 = fork();
    if (fork6 == 0) {
        chdir("/home/[USER]/modul2/animal/");
        char * argv[] = {"find", "-type", "f", "-name", "*", "-delete", NULL};
        execv("/bin/find", argv);
        }
}  
```
Untuk wait dan fork nya sama dengan soal-soal sebelumnya. Pertama-tama, kita akan mengganti working directory nya ke direktori animal dengan fungsi `chdir()`. Pada soal ini, kita akan mencatat command `"find", "-type", "f", "-name", "*", "-delete", NULL` pada array argv. Command `find` berguna untuk mencari file dalam sebuah direktori,`"-type", "f"` artinya yang dicari bertipe file, dan `"-name", "*", "-delete"` berarti semua file akan terhapus. Karena file yang terdapat nama *darat* dan *air* sudah dipindahkan ke file nya masing-masing, file yang tersisa di direktori animal hanya binatang yang tidak memiliki keterangan. Kemudian dijalankan fungsi `execv()` dengan parameter path file fungsi find yaitu **/bin/find** dan akan mengeksekusi command yang tersimpan di array argv.

## D
Pada soal ini, kita diminta untuk menghapus semua burung yang ada di directory **/home/[USER]/modul2/darat**. Hewan burung ditandai dengan adanya `bird` pada nama file.
```c
else {
    while ((wait( & status)) > 0);
    int fork7 = fork();
              
    if (fork7 == 0) {
        chdir("/home/[USER]/modul2/darat/");
        char * argv[] = {"find", "-type", "f", "-name", "*bird*", "-delete", NULL};
        execv("/bin/find", argv);
        }
}
```
Untuk wait dan fork nya sama dengan soal-soal sebelumnya. Pertama-tama, kita akan mengganti working directory nya ke direktori animal dengan fungsi `chdir()`. Pada soal ini, kita akan mencatat command `"find", "-type", "f", "-name", "bird", "-delete", NULL` pada array argv. Command `find` berguna untuk mencari file dalam sebuah direktori,`"-type", "f"` artinya yang dicari bertipe file, command `"-name", "*bird*"` artinya adalah file yang ingin dicari mengandung nama "**bird**", dan command `"-delete"` digunakan untuk menghapus file yang sudah dicari fungsi find sebelumnya. Kemudian dijalankan fungsi `execv()` dengan parameter path file fungsi find yaitu **/bin/find** dan akan mengeksekusi command yang tersimpan di array argv.

## E
Pada soal ini, kita diminta untuk membuat file list.txt di folder **/home/[USER]/modul2/air** dan membuat list nama semua hewan yang ada di directory **/home/[USER]/modul2/air** ke `list.txt` dengan format **UID_[UID file permission]_Nama File.[jpg/png]** dimana UID adalah user dari file tersebut file permission adalah permission dari file tersebut.

### Panggil fungsi
```c
else{
    chdir("/home/[USER]/modul2/air/");
    char path[100] = "/home/[USER]/modul2/air";
    listFilesRecursively(path);
    }
```
Pertama-tama, kita akan mengganti working directory nya ke direktori animal dengan fungsi `chdir()`. Kemudian, disini di deklarasi string yang bernama `path` yang berisi address direktori yang akan digunakan untuk rekursif file. Kemudian panggil fungsi `listFilesRecursively()` untuk merekursi file yang berada di direktori `path`.

### Fungsi **listFilesRecursively()**
```c
void listFilesRecursively(char * basePath) {
  char path[100] = "/home/[USER]/modul2/air";
  struct stat fs;
  struct stat info;
  struct dirent * dp;
  int r, x;

  DIR * dir = opendir(basePath);
  FILE * fptr = fopen("list.txt", "w");

  if (!dir)
    return;

  while ((dp = readdir(dir)) != NULL) {
    if (strcmp(dp -> d_name, ".") != 0 && strcmp(dp -> d_name, "..") != 0) {
      if (strcmp((dp -> d_name), "list.txt") == 0)
        continue;
      else
        x = stat(path, & info);
      struct passwd * pw = getpwuid(info.st_uid);
      fprintf(fptr, "%s_", pw -> pw_name);
      r = stat(path, & fs);
      if (fs.st_mode & S_IRUSR)
        fprintf(fptr, "r");
      if (fs.st_mode & S_IWUSR)
        fprintf(fptr, "w");

      fprintf(fptr, "_");
      fprintf(fptr, "%s\n", dp -> d_name);
      strcpy(path, basePath);
      strcat(path, "/");
      strcat(path, dp -> d_name);

      listFilesRecursively(path);
    }
  }

  closedir(dir);
}
```
Pertama, buat fungsi bernama **listFilesRecursively** dengan parameter `char * basePath`. Pointer `basePath` akan digunakan untuk menyimpan address dari direktori yang ingin di rekursi. Kemudian, deklarasi string path berupa address directory nya, struct untuk mencari pemilik user dan permissionnya, dan integer **r** dan **x** untuk menyimpan stat / informasi dari file.
```c
DIR * dir = opendir(basePath);
FILE * fptr = fopen("list.txt", "w");
```
Disini dir digunakan untuk membuka directory sesuai dengan parameter yang diberikan yaitu `basePath` dan fopen digunakan untuk membuat file **list.txt** (w digunakan agar jika sudah ada file bernama list.txt akan di overwrite) .

```c
if(!dir)
return;
while ((dp = readdir(dir)) != NULL) {
    if (strcmp(dp -> d_name, ".") != 0 && strcmp(dp -> d_name, "..") != 0) {
        if (strcmp((dp -> d_name), "list.txt") == 0)
        continue;
        else
        x = stat(path, & info);
        struct passwd * pw = getpwuid(info.st_uid);
        fprintf(fptr, "%s_", pw -> pw_name);
        r = stat(path, & fs);
        if (fs.st_mode & S_IRUSR)
        fprintf(fptr, "r");
        if (fs.st_mode & S_IWUSR)
        fprintf(fptr, "w");
        fprintf(fptr, "_");
        fprintf(fptr, "%s\n", dp -> d_name);
        strcpy(path, basePath);
        strcat(path, "/");
        strcat(path, dp -> d_name);

        listFilesRecursively(path);
        }
    }
```
Pertama, kita cek dahulu apakah direktori tersebut ada, jika tidak maka akan return. Selanjutnya akan digunakan fungsi while dimana selama file nya masih ada yang belum dibaca, maka akan kodenya akan terus berjalan. Kemudian kita gunakan fprintf untuk output nama hewan sesuai dengan formatnya yaitu **UID_[UID file permission]_Nama File.[jpg/png]**. Untuk mendapatkan nama user, kita menggunakan fungsi `getpwuid()`. Untuk mendapatkan permission filenya, kita menggunakan fungsi `IRUSR` dan `IWUSR`. dan untuk mendapatkan nama file, kita menggunakan fungsi `pw -> pw_name`. Setelah selesai, maka akan memanggil fungsi  `listFilesRecursively()` kembali untuk mengulang prosesnya. Karena di dalam folder air terdapat file `list.txt` juga, kita akan menggunakan function if dan strcmp untuk mengcompare nama file dengan `list.txt`. Jika ==0, maka akan continue(file `list.txt` tidak akan dibaca).

## Screenshot file
- Screenshot direktori **modul 2**

![1](https://raw.githubusercontent.com/Satriokml/images/main/Praktikum%202/modul2.png)
- Screenshot direktori **animal**

![2](https://raw.githubusercontent.com/Satriokml/images/main/Praktikum%202/animal.png)
- Screenshot direktori **darat**

![3](https://raw.githubusercontent.com/Satriokml/images/main/Praktikum%202/darat.png)
- Screenshot direktori **air**

![4](https://raw.githubusercontent.com/Satriokml/images/main/Praktikum%202/air.png)
- Screenshot file `list.txt`

![5](https://raw.githubusercontent.com/Satriokml/images/main/Praktikum%202/list.png)

## Kendala yang ditemui
- Sempet bingung karena tidak dapat menggunakan command `rm` dan `mv`

