/* loadFile.c */
// Program untuk melakukan load sebuah file ke system image

// KETERANGAN
// Pembuatan loadFile.c dipisahkan dari implementasi kernel.c

#include <stdio.h>

void main(int argc, char* argv[]) {
    int i;
    int n_sector = 0;     // Counter jumlah sector
    int secIdx;           // Indeks section

    FILE* loadFile;
    FILE* systemImage;

    char map[512];
    char files[1024];
    char sectors[512];
    char c;

    if (argc < 2) {
      printf("Nama file tidak ditemukan\n");
      return;
    }

    // Buka source file
    loadFile = fopen(argv[1], "r");

    if (loadFile == 0) {
      printf("File tidak ditemukan\n");
      return;
    }

    // Buka image
    systemImage = fopen("system.img", "r+");
    if (systemImage == 0) {
      printf("system.img tidak ditemukan\n");
      return;
    }

    // Load disk map yang ada
    fseek(systemImage, 512 * 0x100, SEEK_SET);

    for (i = 0; i < 512; i++) {
      map[i] = fgetc(systemImage);
    }

    // Load daftar files
    fseek(systemImage, 512 * 0x101, SEEK_SET);

    for (i = 0; i < 1024; i++) {
      files[i] = fgetc(systemImage);
    }
    
    // Load daftar sector
    fseek(systemImage, 512 * 0x103, SEEK_SET);
    
    for (i = 0; i < 512; i++) {
      sectors[i] = fgetc(systemImage);
    }

    // Cari entri kosong pada file
    for (i = 0; i < 1024; i = i + 16){
      if (files[i+2] == 0){
        break;
      }
    }

    if (i == 1024) {
      printf("Tidak cukup ruang pada file\n");
      return;
    }

    int filesIdx = i;

    // Isi field nama dengan 0x00
    for (i = 0; i < 14; i++) {
      files[filesIdx + i + 2] = 0x00;
    }

    // Copy nama
    for (i = 0; i < 14; i++) {
      if (argv[2][i] == 0){
        break;
      }
      files[filesIdx + i + 2] = argv[2][i];
    }

    // Cari entri kosong pada sektor
    for (i = 0; i < 32; i = i + 1) {
      if (sectors[i<<4] == 0) {
        break;
      }
    }
    if (i == 32) {
      printf("Tidak cukup ruang pada sectors\n");
      return;
    }

    secIdx = i * 16;

    files[filesIdx + 1] = i;
    files[filesIdx] = 0xFF;

    // Cari sektor kosong dan tambahkan ke file
    while (!feof(loadFile)) {
      if (n_sector == 20) {
        // Sektor file penuh
        printf("Tidak cukup ruang pada direktori untuk file\n");
        return;
      }

      // Cari entri map kosong
      for (i = 0; i < 256; i++){
        if (map[i] == 0) {
          break;
        }
      }
        
      if (i == 256) {
        // Sektor penuh lagi
        printf("Tidak cukup ruang untuk file\n");
        return;
      }

      // Mark entri map
      map[i] = 0xFF;

      // Mark sector di direktori entri
      sectors[secIdx] = i;
      secIdx++;
      n_sector++;
      
      printf("File %s berhasil di load ke sektor %d\n", argv[2], i);  // Berhasil load sektor

      // Akses sektor dan tulis isi sektor
      fseek(systemImage, i * 512, SEEK_SET);

      for (i = 0; i < 512; i++) {
        if (feof(loadFile)) {
          fputc(0x0, systemImage);
          break;
        } else {
          c = fgetc(loadFile);
          fputc(c, systemImage);
        }
      }
    }

    // Tulis map, files, dan sectors ke image
    // Sektor map ada di      : 0x100
    // Sektor files ada di    : 0x101 dan 0x102
    // Sektor systemImage ada di   : 0x103

    fseek(systemImage, 512 * 0x100, SEEK_SET);
    
    for (i = 0; i < 512; i++){
      fputc(map[i], systemImage);
    }

    fseek(systemImage, 512 * 0x101, SEEK_SET);
    
    for (i = 0; i < 1024; i++){
      fputc(files[i], systemImage);
    }

    fseek(systemImage, 512 * 0x103, SEEK_SET);
    
    for (i = 0; i < 512; i++){
      fputc(sectors[i], systemImage);
    }

    // Jangan lupa tutup file yang sudah di read
    fclose(loadFile);
    fclose(systemImage);
}
