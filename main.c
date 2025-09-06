#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perpustakaan.h"

int main() {
    User loggedUser;

    printf("============= SiPerpus ===============\n");
    printf("=== Library Management System ===\n");

    initUser();
    initBuku();

    if (!login(&loggedUser)) {
        printf("\nLogin failed!\n");
        int choice;
        printf("Do you want to register a new account? (1=Yes, 0=No): ");
        scanf("%d", &choice);
        if (choice == 1) {
            registerUser();
            printf("\nPlease run the program again to login with your new account.\n");
        }
        return 0;
    }

    printf("\nSuccessfully logged in as %s (%s)\n", loggedUser.username, loggedUser.role);

    int menuChoice;
    do {
        if (strcmp(loggedUser.role, "admin") == 0) {
            printf("\n=== Admin Menu ===\n");
            printf("1. Add Book\n");
            printf("2. Show Books\n");
            printf("3. Search Book\n");
            printf("4. Remove Book\n");
            printf("5. Edit Book\n");
            printf("6. Report\n");
            printf("0. Exit\n");
            printf("Choice: "); 
            scanf("%d", &menuChoice);

            switch (menuChoice) {
                case 1: tambahBuku(); break;
                case 2: tampilBuku(); break;
                case 3: cariBuku(); break;
                case 4: hapusBuku(); break;
                case 5: editBuku(); break;
                case 6: laporan(); break;
                case 0: printf("Exiting...\n"); break;
                default: printf("Invalid choice!\n");
            }
        } else {
            printf("\n=== User Menu ===\n");
            printf("1. Show Books\n");
            printf("2. Search Book\n");
            printf("3. Borrow Book\n");
            printf("4. Return Book\n");
            printf("0. Exit\n");
            printf("Choice: "); 
            scanf("%d", &menuChoice);

            switch (menuChoice) {
                case 1: tampilBuku(); break;
                case 2: cariBuku(); break;
                case 3: pinjamBuku(loggedUser.username); break;
                case 4: kembalikanBuku(loggedUser.username); break;
                case 0: printf("Exiting...\n"); break;
                default: printf("Invalid choice!\n");
            }
        }
    } while (menuChoice != 0);

    return 0;
}
