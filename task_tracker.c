//REVISION .C FILE

//Mirza Ananta Hermawan 2206822212
//Darrel Khayru Risyad 2206820781
//Group 6
//Project 1 (REVISED)
//01-03-2024

/* this code is The Task Tracker*
this code aims to help student organize their tasks of academia based on
the class/course taken according to the class/course itself or its deadline*/

//revision made
//1. change the searching function to use strstr for keyword searching
//2. split the program into .c and .h header file
//3. polished the code

//Bismillah


#include <stdio.h>
#include "task_tracker.h"

int main() {
    Kelas *kelas = NULL;
    int jumlah_kelas = 0;

    while (1) {
        printf("\n========= TheTaskTracker =========\n");
        printf("1. Add class\n");
        printf("2. Add assignment\n");
        printf("3. View assignments\n");
        printf("4. Search assignments by keyword\n");
        printf("5. Delete assignment\n");
        printf("6. Help\n");
        printf("7. Exit\n");
        printf("==================================\n");
        printf("Enter your choice: ");
        int pilihan;
        scanf("%d", &pilihan);
        getchar(); 

        switch (pilihan) {
            case 1:
                tambah_kelas(&kelas, &jumlah_kelas);
                break;
            case 2:
                tambah_tugas(kelas, jumlah_kelas);
                break;
            case 3:
                lihat_tugas(kelas, jumlah_kelas);
                break;
            case 4:
                cari_tugas(kelas, jumlah_kelas);
                break;
            case 5:
                hapus_tugas(kelas, jumlah_kelas);
                break;
            case 6:
                tampilkan_bantuan();
                break;
            case 7:
                free(kelas);  
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}
