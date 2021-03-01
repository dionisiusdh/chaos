# Tugas Milestone 1 - Operating System
Sistem operasi ini akan berjalan pada sistem 16-bit yang nanti akan disimulasikan dengan _emulator bochs_.

## Kelompok 6 - nojamesno

| Nama Anggota | NIM |
| --- | --- |
| Dionisius Darryl Hermansyah | 13519058 |
| Joel Triwira | 13519073 |
| James Chandra | 13519078 |

## General info
_Interrupt_ merupakan sebuah metode yang digunakan oleh _operating system_ (OS) atau sistem operasi yang digunakan untuk me-_request_ satu atau beberapa aksi dari _Basic Input/Output System_ (BIOS). Jika _interrupt_ dijalankan, maka sistem komputer akan menghentikan pekerjaan yang sedang dilakukan dan mengeksekusi apa yang diminta oleh penginterupsi.

_Kernel_ merupakan sebuah program utama yang dimiliki oleh sebuah OS. Hal ini karena kernel memiliki kontrol atas segala hal yang berada dalam sistem komputer. Kernel ini pula yang akan dieksekusi pertama kali setelah _bootloader_ dijalankan. _Kernel_ memiliki beberapa tugas penting seperti mengatur manajemen _disk_, memori, tugas, dan daya. Proses dapat memanggil sebuah _kernel_. Proses pemanggilan inilah yang disebut juga sebagai _System Call_ atau pemanggilan sistem.

Sistem operasi yang kami buat pun memiliki sebuah _kernel_ sederhana. Berikut merupakan penjelasan singkat mengenai _interrupt_ secara lebih lanjut dan cara kerja _kernel.asm_ (_assembly_) yang digunakan:

Ada 4 fungsi utama yang diimplementasikan pada _kernel.asm_

    void putInMemory (int segment, int address, char character)
Fungsi _putInMemory_ akan menerima 3 parameter input, yaitu: segmen yang bertipe integer, address yang bertipe integer, dan character yang bertipe char. Parameter-parameter ini secara terurut merupakan, segment memory yang ingin diakses (contohnya: 0xB000 merupakan _segment video memory_), offset memori, serta karakter atau warna yang ingin dieksekusi. Fungsi ini bertujuan untuk menulis sebuah karakter pada _segment_ memori dengan offset tertentu. p

    int interrupt (int number, int AX, int BX, int CX, int DX)
Fungsi _interrupt_ akan menjalankan metode _interrupt_ terhadap sistem dengan _number_ tertentu dan mengirim informasi berupa parameter AX, BX, CX, DX (16-bit) ke interrupt terkait. Pada kernel.asm, pertama-tama sistem akan mengambil nomor dari AL pada _interrupt_, dengan tujuan untuk menggunakannya dalam pemanggilan _interrupt_ yang sesuai. 

    void makeInterrupt21()
Fungsi makeInterrupt21 ini bertujuan mempersiapkan tabel _interrupt_ _vector_ untuk memanggil kode Anda jika _interrupt_ 0x21 terpanggil. Jika fungsi ini terpanggil, pertama-tama dia akan mendapatkan alamat dari service routine. Lalu, menaruh interrupts di lowest memory. Kemudian melakukan _interrupt_ 0x21 vector.

    void handleInterrupt21 (int AX, int BX, int CX, int DX)
_handleInterrupt21_ merupakan sebuah fungsi yang akan dijalankan saat terjadi _interrupt_ pada nomor 0x21. Fungsi ini bertujuan untuk menangani pemanggilan _interrupt_ yang dilakukan. Dalam implementasinya fungsi _handleInterrupt21_ akan dipanggil oleh _interrupt21ServiceRoutine_. Cara kerja _handleInterrupt21_ adalah dengan mengecek nilai parameter AX yang diberikan. Jika AX bernilai 0x0 maka akan dipanggil fungsi _printString_, jika 0x1 maka akan dipanggil fungsi _readString_. Parameter lainnya akan menghasilkan _invalid interrupt_.


## Terima kasih
