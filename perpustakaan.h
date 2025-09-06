#ifndef PERPUSTAKAAN_H
#define PERPUSTAKAAN_H

#define FILE_USER "user.txt"
#define FILE_BUKU "buku.txt"

typedef struct {
    char username[50];
    char password[50];
    char role[10]; 
} User;

typedef struct {
    char kode[10];
    char judul[100];
    char penulis[100];
    int tahun;
    int status; 
} Buku;

// User
int login(User *u);
void registerUser();
void initUser();

// Buku
void initBuku();
void tambahBuku();
void tampilBuku();
void cariBuku();
void hapusBuku();
void editBuku();
void pinjamBuku(const char *username);
void kembalikanBuku(const char *username);
void laporan();

#endif
