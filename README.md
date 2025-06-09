# Sisop-5-2025-IT04

## KELOMPOK IT04
| No | Nama                              | NRP         |
|----|-----------------------------------|-------------|
| 1  | Raya Ahmad Syarif                 | 5027241041  |
| 2  | Salsa Bil Ulla         | 5027241052 |
| 3  | Adinda Cahya Pramesti   | 5027241117  |


## Daftar Isi

- [Kelompok](#kelompok-it04)
- [Daftar Isi](#daftar-isi)
- [Soal](#soal)
- [Petunjuk Soal](#petunjuk-soal)
  - [Source](#source)
  - [Headers](#headers)
  - [Makefile](#makefile)
  - [Video Demonstrasi](#video-demonstrasi)
- [Laporan](#laporan)

## Soal

Pada suatu hari, anda merasa sangat lelah dari segala macam praktikum yang sudah ada, sehingga anda berencana untuk tidur yang nyenyak di sebuah jam 3:34AM yang cerah. Tetapi, anda terbangun di dalam dunia berbeda yang bernama "Eorzea". Ada sesuatu yang mengganggu pikiran anda sehingga anda diharuskan membuat sebuah operating system bernama "EorzeOS" untuk mendampingi diri anda dalam dunia ini.

1. Sebagai seorang main character dari dunia ini, ternyata anda memiliki kekuatan yang bernama "The Echo", kekuatan ini memungkinkan anda untuk berbicara pada Operating System ini (mungkin sebenarnya bukan ini kekuatannya, tetapi ini cukup kuat juga), dengan tujuan agar semua hal yang anda katakan, bila bukan merupakan sebuah command yang valid, akan mengulang hal yang anda katakan.

   Ilustrasi:
   ```
   user> Hello!
   Hello!
   user> I have the Echo
   I have the Echo
   ```

2. gurt: yo

   Ilustrasi:
   ```
   user> yo
   gurt
   user> gurt
   yo
   ```

3. Seorang main character memerlukan sebuah nama yang semua orang bisa ingat dengan baik. Buatlah sebuah command yang memungkinkan pengguna untuk mengubah nama user pada shell yang digunakan:
   * `user <username>` = mengubah username menjadi `<username>`
   * `user` = mengubah username menjadi default `user`
   
   Ilustrasi:
   ```
   user> user Tia
   Username changed to Tia
   Tia> user
   Username changed to user
   user>
   ```

4. Tiga negara besar dari Eorzean Alliance butuh bantuan anda untuk ikut serta dalam "Grand Company" mereka sehingga anda bisa mengubah warna terminal ajaib anda sesuai warna utama dari company mereka:
   * `grandcompany maelstrom` = clear terminal, ubah semua teks berikutnya jadi merah
   * `grandcompany twinadder` = clear terminal, ubah semua teks berikutnya jadi kuning
   * `grandcompany immortalflames` = clear terminal, ubah semua teks berikutnya jadi biru
   * `grandcompany <selain atau kosong>` = tunjukkan error message
   * `clear` = clear terminal, ubah semua teks berikutnya kembali jadi awal (para Grand Company sedih kamu netral)

   Selain mengubah seluruh warna terminal, nama anda di dalam terminal akan diberikan tambahan nama judul Grand Company:
   * Maelstrom = `user@Storm`
   * Twin Adder = `user@Serpent`
   * Immortal Flames = `user@Flame`
   * `clear` = menghapus nama grand company

   Ilustrasi:
   ```
   gurt> grandcompany maelstrom
   -- terminal clear menjadi warna merah --
   gurt@Storm> clear
   -- terminal clear menjadi warna putih --
   ```

5. Sebagai pahlawan terkenal di antara ketiga negara besar Eorzean Alliance, salah satu supplier senjata terbesar di seluruh Eorzea bernama "Rowena's House of Splendors" tiba-tiba memerlukan bantuan anda untuk membuat sebuah sistem kalkulator sederhana melalui command karena pemimpin mereka tertidur setelah mengurus semua orang di dalam Eorzea:
   * `add <x> <y>` = x + y
   * `sub <x> <y>` = x - y
   * `mul <x> <y>` = x * y
   * `div <x> <y>` = x / y

   Ilustrasi:
   ```
   user> add 4 2
   6
   user> sub 4 2
   2
   user> mul 3 -2
   -6
   user> div -6 -2
   3
   ```

6. me: yogurt
   
   gurt:
   * `yo`
   * `ts unami gng </3`
   * `sygau`

   pilih secara *random*

   Ilustrasi:
   ```
   user> yogurt
   gurt> yo
   user> yogurt
   gurt> ts unami gng </3
   user> yogurt
   gurt> sygau
   ```

8. Perusahaan mesin "Garlond Ironworks" tiba-tiba lelah mengurus permintaan senjata perang untuk orang ke-148649813234 yang berusaha menghadapi final boss yang sama, sehingga mereka perlu bantuan kamu untuk melengkapi `Makefile` yang diberikan dengan command-command yang sesuai untuk compile seluruh operating system ini.

## Petunjuk Soal

### Source

* [kernel.asm](src/kernel.asm)
  * `_putInMemory`: penjelasan terdapat dalam modul
  * `_interrupt`: fungsi untuk interrupt
    * `number`: interrupt vector number
    * `AX`,`BX`,`CX`,`DX`: register untuk diisi
    * `AX` merupakan kombinasi dari `AH` dan `AL`, pola ini juga berlaku untuk `BX`,`CX`, dan `DX`
    * Untuk menggabungkan jenis register `H` dan `L` menjadi `X` bisa menggunakan salah satu metode berikut:
      ```c
      AX = AH << 8 | AL    // first method
      AX = AH * 256 + AL   // second method
      ```
   * `getBiosTick`: fungsi untuk mendapatkan tick dari BIOS
* [kernel.c](src/kernel.c)
  * Diisi penerapan fungsi `printString`, `readString`, dan `clearScreen` dengan bantuan `kernel.asm`
    * untuk `printString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` dengan parameter `AH = 0x0E` untuk _teletype output_. Karakter yang ditampilkan dapat dimasukkan pada register `AL`. Fungsi ini akan menampilkan string karakter ASCII (_null-terminated_) ke layar.
    * untuk `readString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 16h` dengan parameter `AH = 0x00` untuk _keyboard input_. Fungsi ini akan membaca karakter ASCII (_non-control_) yang dimasukkan oleh pengguna dan menyimpannya pada buffer hingga menekan tombol `Enter`. Handle tombol `Backspace` dibebaskan kepada praktikan.
    * untuk `clearScreen`: Ukuran layar adalah `80x25` karakter. Setelah layar dibersihkan, kursor akan kembali ke posisi awal yaitu `(0, 0)` dan buffer video untuk warna karakter diubah ke warna putih. Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` atau menggunakan fungsi `putInMemory` untuk mengisi memori video.
* [shell.c](src/shell.c)
  * Diisi penerapan shell yang menggunakan fungsi kernel untuk parsing keseluruhan command yang diinput

### Headers

* [std_type.h](include/std_type.h)
  * `byte`: unsigned char data type, untuk angka 0-255 (`0x00`-`0xFF`)
  * `bool`: untuk boolean (true/false), karena boolean tidak built-in
* [std_lib.h](include/std_lib.h)
  * `div`: division
  * `mod`: modulo
  * Pembagian dan modulo tidak ada dalam assembly, sehingga harus dilengkapi dengan operator yang tersedia (`+`,`-`,`*`,`<<`,`>>`)
  * `strcmp`: membandingkan dua string
  * `strcpy`: copy string
  * `clear`: fill memory dengan `0`
  * `atoi`: alphanumeric to integer (string menjadi angka)
  * `itoa`: integer to alphanumeric (angka menjadi string)
* [kernel.h](include/kernel.h)
  * Deklarasi header untuk fungsi-fungsi dalam `kernel.c`
* [shell.h](include/shell.h)
  * Deklarasi header untuk fungsi-fungsi dalam `shell.c`

### Makefile

* [makefile](./makefile)
   * `prepare` : membuat disk image baru `floppy.img` pada direktori `bin/` dengan ukuran 1.44 MB.
   * `bootloader` : mengkompilasi `bootloader.asm` menjadi `bootloader.bin` pada direktori `bin/`.
   * `stdlib` : mengkompilasi `std_lib.c` menjadi `std_lib.o` pada direktori `bin/`.
   * `shell`: mengkompilasi `shell.c` menjadi `shell.o` pada direktori `bin/`.
   * `kernel` : mengkompilasi `kernel.c` menjadi `kernel.o` pada direktori `bin/` dan mengkompilasi `kernel.asm` menjadi `kernel_asm.o` pada direktori `bin/`.
   * `link` : menggabungkan `bootloader.bin`, `kernel.o`, `kernel_asm.o`, dan `std_lib.o` menjadi `floppy.img`.
   * `build` : menjalankan perintah `prepare`, `bootloader`, `stdlib`, `kernel`, dan `link`.

### Video Demonstrasi

[Akses Video dalam Assets](./assets/demo.mp4)

https://github.com/user-attachments/assets/1cfa66b1-b2f5-4e3e-a4b2-ec8b012f6fbb


## Laporan

> Isi sesuai pengerjaan.
### Soal 1: Perintah yo dan gurt
Deskripsi: Perintah yo harus mencetak "gurt\n" dan perintah gurt mencetak "yo\n".
Implementasi:
- Fungsi parseCommand di shell.c mem-parsing input pengguna ke variabel cmd.
- Membandingkan cmd dengan strcmp:
```
if (strcmp(cmd, "yo")) {
    printString("gurt\n");
} else if (strcmp(cmd, "gurt")) {
    printString("yo\n");
}
```

- Fungsi strcmp di std_lib.c membandingkan string karakter demi karakter:
```
bool strcmp(char *s1, char *s2) {
    while (*s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    return (*s1 == *s2);
}
```

### Soal 2: Perintah user
Deskripsi: Mengubah username pada prompt. Tanpa argumen, reset ke "user"; dengan argumen, ubah ke input pengguna (maks. 15 karakter).
Implementasi:
- Variabel global username di shell.c menyimpan nama pengguna (default: "user").
- Dalam parseCommand:
```
if (strcmp(cmd, "user")) {
    if (arg[0][0] == '\0') {
        strcpy(username, "user");
        printString("Username reset to 'user'\n");
    } else {
        strcpy(username, arg[0]);
        printString("Username changed to ");
        printString(username);
        printString("\n");
    }
}
```

- Fungsi strcpy di std_lib.c menyalin argumen ke username.
- Prompt diperbarui oleh updatePrompt:
```
void updatePrompt() {
    printString(username);
    if (company_suffix[0] != '\0') {
        printString("@");
        printString(company_suffix);
    }
}
```

### Soal 3: Perintah grandcompany
Deskripsi: Mengubah tema warna dan suffix prompt berdasarkan Grand Company: maelstrom (merah, "Storm"), twinadder (kuning, "Serpent"), immortalflames (biru, "Flame").
Implementasi:
- Fungsi handleGrandCompany di shell.c:
```
void handleGrandCompany(char *arg) {
    byte new_color;
    char new_suffix[16];
    bool valid_company = true;
    new_color = current_color;
    if (strcmp(arg, "maelstrom")) {
        new_color = 0x04;
        strcpy(new_suffix, "Storm");
    } else if (strcmp(arg, "twinadder")) {
        new_color = 0x0E;
        strcpy(new_suffix, "Serpent");
    } else if (strcmp(arg, "immortalflames")) {
        new_color = 0x01;
        strcpy(new_suffix, "Flame");
    } else {
        printString("Invalid Grand Company. Options: maelstrom, twinadder, immortalflames\n");
        valid_company = false;
    }
    if (valid_company) {
        clearScreen();
        strcpy(company_suffix, new_suffix);
        changeColor(new_color);
    }
}
```

- Fungsi changeColor menggunakan interupsi BIOS 0x10 untuk mengatur warna teks:
```
void changeColor(byte color) {
    current_color = color;
    interrupt(0x10, 0x0E00 + ' ', color, 0, 0);
}
```

### Soal 4: Perintah clear
Deskripsi: Membersihkan layar, mereset suffix Grand Company, dan mengembalikan warna ke default (0x07).
Implementasi:
- Dalam parseCommand:
```
if (strcmp(cmd, "clear")) {
    clearScreen();
    company_suffix[0] = '\0';
    changeColor(0x07);
}
```

- Fungsi clearScreen di kernel.c mengosongkan memori video di 0xB800:
```
void clearScreen() {
    int i;
    for (i = 0; i < 80 * 25 * 2; i += 2) {
        putInMemory(0xB800, i, ' ');
        putInMemory(0xB800, i + 1, 0x07);
    }
    interrupt(0x10, 0x0200, 0, 0, 0);
}
```

### Soal 5: Perintah Kalkulator (add, sub, mul, div)
Deskripsi: Melakukan operasi aritmatika pada dua argumen bilangan, menangani error pembagian dengan nol.
Implementasi:
- Fungsi handleCalculator di shell.c:
```
void handleCalculator(char *cmd, char arg[2][64]) {
    int x, y, result;
    char result_str[16];
    result = 0;
    atoi(arg[0], &x);
    atoi(arg[1], &y);
    if (strcmp(cmd, "add")) {
        result = x + y;
    } else if (strcmp(cmd, "sub")) {
        result = x - y;
    } else if (strcmp(cmd, "mul")) {
        result = x * y;
    } else if (strcmp(cmd, "div")) {
        if (y == 0) {
            printString("Error: Division by zero\n");
            return;
        }
        result = x / y;
    }
    itoa(result, result_str);
    printString(result_str);
    printString("\n");
}
```
- Menggunakan atoi dan itoa dari std_lib.c untuk konversi string-integer.

### Soal 6: Perintah yogurt
Deskripsi: Menampilkan salah satu dari tiga pesan acak: "gurt> yo", "gurt> ts unami gng </3", atau "gurt> sygau".
Implementasi:
- Dalam parseCommand:
```
if (strcmp(cmd, "yogurt")) {
    r = mod(getRandom(), 3);
    if (r == 0) {
        printString("gurt> yo\n");
    } else if (r == 1) {
        printString("gurt> ts unami gng </3\n");
    } else {
        printString("gurt> sygau\n");
    }
}
```

- Fungsi getRandom di std_lib.c menghasilkan angka acak:
```
int getRandom() {
    static unsigned int seed = 42;
    seed = seed * 1103515245 + 12345;
    return mod(div(seed, 65536), 32768);
}
```

### Soal 7: Prompt Dinamis
Deskripsi: Prompt menampilkan username dan suffix Grand Company (jika ada).
Implementasi:
- Fungsi updatePrompt di shell.c:
```
void updatePrompt() {
    printString(username);
    if (company_suffix[0] != '\0') {
        printString("@");
        printString(company_suffix);
    }
}
```
- Dipanggil sebelum menampilkan "> " di fungsi shell.
