# soal-shift-sisop-modul-2-itb02-202

## Laporan Pengerjaan Modul 2 Praktikum Sistem Operasi

### Nama Anggota Kelompok

1. Rachmita Annisa Aulia 5027201032
2. Alvian Ghifari 5027201035
3. Satrio Kamil Widhiwoso 5027201051


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

