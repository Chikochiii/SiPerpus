#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perpustakaan.h"

// ================= USER =================
void initUser() {
    FILE *fp = fopen(FILE_USER, "r");
    if (fp) { fclose(fp); return; }

    fp = fopen(FILE_USER, "w");
    if (!fp) return;

    fclose(fp);
}

int login(User *u) {
    FILE *fp = fopen(FILE_USER, "r");
    if (!fp) return 0;

    char uname[50], pass[50];
    printf("Username: "); scanf("%s", uname);
    printf("Password: "); scanf("%s", pass);

    char line[200];
    while (fgets(line, sizeof(line), fp)) {
        char *username = strtok(line, "|");
        char *password = strtok(NULL, "|");
        char *role = strtok(NULL, "|\n");

        if (username && password && role &&
            strcmp(username, uname) == 0 &&
            strcmp(password, pass) == 0) {
            strcpy(u->username, username);
            strcpy(u->password, password);
            strcpy(u->role, role);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void registerUser() {
    FILE *fp = fopen(FILE_USER, "a");
    if (!fp) return;

    User u;
    printf("\n=== Register New Account ===\n");
    printf("Username: "); scanf("%s", u.username);
    printf("Password: "); scanf("%s", u.password);

    int roleChoice;
    printf("Choose Role (1=User, 2=Admin): ");
    scanf("%d", &roleChoice);
    if (roleChoice == 2) strcpy(u.role, "admin");
    else strcpy(u.role, "user");

    fprintf(fp, "%s|%s|%s\n", u.username, u.password, u.role);
    fclose(fp);

    printf("Account successfully created!\n");
}

// ================= BOOK =================
void initBuku() {
    FILE *fp = fopen(FILE_BUKU, "r");
    if (fp) { fclose(fp); return; }

    fp = fopen(FILE_BUKU, "w");
    if (!fp) return;

    fprintf(fp, "B001|Atomic Habits|James Clear|2018|0\n");
    fprintf(fp, "B002|Rich Dad Poor Dad|Robert Kiyosaki|1997|0\n");
    fprintf(fp, "B003|The Subtle Art of Not Giving a F*ck|Mark Manson|2016|0\n");
    fprintf(fp, "B004|Ikigai|Héctor García & Francesc Miralles|2017|0\n");
    fprintf(fp, "B005|Thinking, Fast and Slow|Daniel Kahneman|2011|0\n");
    fprintf(fp, "B006|Sapiens|Yuval Noah Harari|2011|0\n");
    fprintf(fp, "B007|The Psychology of Money|Morgan Housel|2020|0\n");
    fprintf(fp, "B008|Start With Why|Simon Sinek|2009|0\n");
    fprintf(fp, "B009|Educated|Tara Westover|2018|0\n");
    fprintf(fp, "B010|The Power of Habit|Charles Duhigg|2012|0\n");

    fclose(fp);
}

void tampilBuku() {
    FILE *fp = fopen(FILE_BUKU, "r");
    if (!fp) { printf("No book data available!\n"); return; }

    char line[256];
    printf("\n=== Book List ===\n");
    while (fgets(line, sizeof(line), fp)) {
        Buku b;
        sscanf(line, "%[^|]|%[^|]|%[^|]|%d|%d",
               b.kode, b.judul, b.penulis, &b.tahun, &b.status);
        printf("Code: %s | Title: %s | Author: %s | Year: %d | Status: %s\n",
               b.kode, b.judul, b.penulis, b.tahun,
               b.status == 0 ? "Available" : "Borrowed");
    }
    fclose(fp);
}

void tambahBuku() {
    FILE *fp = fopen(FILE_BUKU, "a");
    if (!fp) return;

    Buku b;
    printf("\n=== Add New Book ===\n");
    printf("Book Code: "); scanf("%s", b.kode);
    getchar();
    printf("Book Title: "); fgets(b.judul, sizeof(b.judul), stdin);
    b.judul[strcspn(b.judul, "\n")] = 0;
    printf("Author: "); fgets(b.penulis, sizeof(b.penulis), stdin);
    b.penulis[strcspn(b.penulis, "\n")] = 0;
    printf("Publication Year: "); scanf("%d", &b.tahun);
    b.status = 0;

    fprintf(fp, "%s|%s|%s|%d|%d\n",
            b.kode, b.judul, b.penulis, b.tahun, b.status);
    fclose(fp);

    printf("Book added successfully!\n");
}

void cariBuku() {
    FILE *fp = fopen(FILE_BUKU, "r");
    if (!fp) return;

    char keyword[100];
    printf("\nEnter title/code: ");
    scanf(" %[^\n]", keyword);

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), fp)) {
        Buku b;
        sscanf(line, "%[^|]|%[^|]|%[^|]|%d|%d",
               b.kode, b.judul, b.penulis, &b.tahun, &b.status);

        if (strstr(b.judul, keyword) || strstr(b.kode, keyword)) {
            printf("Found: %s - %s (%s)\n", b.kode, b.judul, b.penulis);
            found = 1;
        }
    }
    if (!found) printf("Book not found!\n");
    fclose(fp);
}

void hapusBuku() {
    FILE *fp = fopen(FILE_BUKU, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) return;

    char kode[10];
    printf("Code of book to remove: ");
    scanf("%s", kode);

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), fp)) {
        Buku b;
        sscanf(line, "%[^|]|%[^|]|%[^|]|%d|%d",
               b.kode, b.judul, b.penulis, &b.tahun, &b.status);
        if (strcmp(b.kode, kode) != 0) {
            fprintf(temp, "%s", line);
        } else found = 1;
    }
    fclose(fp); fclose(temp);
    remove(FILE_BUKU);
    rename("temp.txt", FILE_BUKU);
    if (found) printf("Book removed.\n");
    else printf("Book not found.\n");
}

void editBuku() {
    FILE *fp = fopen(FILE_BUKU, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) return;

    char kode[10];
    printf("Code of book to edit: ");
    scanf("%s", kode);

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), fp)) {
        Buku b;
        sscanf(line, "%[^|]|%[^|]|%[^|]|%d|%d",
               b.kode, b.judul, b.penulis, &b.tahun, &b.status);
        if (strcmp(b.kode, kode) == 0) {
            printf("New Title: "); getchar(); fgets(b.judul, sizeof(b.judul), stdin);
            b.judul[strcspn(b.judul, "\n")] = 0;
            printf("New Author: "); fgets(b.penulis, sizeof(b.penulis), stdin);
            b.penulis[strcspn(b.penulis, "\n")] = 0;
            printf("New Year: "); scanf("%d", &b.tahun);
            fprintf(temp, "%s|%s|%s|%d|%d\n", b.kode, b.judul, b.penulis, b.tahun, b.status);
            found = 1;
        } else fprintf(temp, "%s", line);
    }
    fclose(fp); fclose(temp);
    remove(FILE_BUKU);
    rename("temp.txt", FILE_BUKU);
    if (found) printf("Book updated successfully.\n");
    else printf("Book not found.\n");
}

void pinjamBuku(const char *username) {
    FILE *fp = fopen(FILE_BUKU, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) return;

    char kode[10];
    printf("Code of book to borrow: ");
    scanf("%s", kode);

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), fp)) {
        Buku b;
        sscanf(line, "%[^|]|%[^|]|%[^|]|%d|%d",
               b.kode, b.judul, b.penulis, &b.tahun, &b.status);
        if (strcmp(b.kode, kode) == 0 && b.status == 0) {
            b.status = 1;
            printf("Book %s successfully borrowed!\n", b.judul);
            found = 1;
        }
        fprintf(temp, "%s|%s|%s|%d|%d\n", b.kode, b.judul, b.penulis, b.tahun, b.status);
    }
    fclose(fp); fclose(temp);
    remove(FILE_BUKU);
    rename("temp.txt", FILE_BUKU);
    if (!found) printf("Book is not available.\n");
}

void kembalikanBuku(const char *username) {
    FILE *fp = fopen(FILE_BUKU, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) return;

    char kode[10];
    printf("Code of book to return: ");
    scanf("%s", kode);

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), fp)) {
        Buku b;
        sscanf(line, "%[^|]|%[^|]|%[^|]|%d|%d",
               b.kode, b.judul, b.penulis, &b.tahun, &b.status);
        if (strcmp(b.kode, kode) == 0 && b.status == 1) {
            b.status = 0;
            printf("Book %s successfully returned!\n", b.judul);
            found = 1;
        }
        fprintf(temp, "%s|%s|%s|%d|%d\n", b.kode, b.judul, b.penulis, b.tahun, b.status);
    }
    fclose(fp); fclose(temp);
    remove(FILE_BUKU);
    rename("temp.txt", FILE_BUKU);
    if (!found) printf("Book cannot be returned.\n");
}

void laporan() {
    FILE *fp = fopen(FILE_BUKU, "r");
    if (!fp) return;

    char line[256];
    int total=0, borrowed=0, available=0;
    while (fgets(line, sizeof(line), fp)) {
        Buku b;
        sscanf(line, "%[^|]|%[^|]|%[^|]|%d|%d",
               b.kode, b.judul, b.penulis, &b.tahun, &b.status);
        total++;
        if (b.status == 0) available++;
        else borrowed++;
    }
    fclose(fp);

    printf("\n=== Book Report ===\n");
    printf("Total Books   : %d\n", total);
    printf("Available     : %d\n", available);
    printf("Borrowed      : %d\n", borrowed);
}
