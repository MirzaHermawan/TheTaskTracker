//HEADER FILE

//Mirza Ananta Hermawan 2206822212
//Darrel Khayru Risyad 2206820781
//Group 6
//Project 1 (REVISED)
//01-03-2024

#ifndef THETASKTRACKER_H
#define THETASKTRACKER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAKS_TUGAS 100

typedef struct {
    char nama_tugas[100];
    char batas_waktu[20];
    char deskripsi[200];
} Tugas;

typedef struct {
    char nama[100];
    Tugas tugas[MAKS_TUGAS];
    int jumlah_tugas;
} Kelas;

void tambah_kelas(Kelas **kelas, int *jumlah_kelas) {
    *kelas = realloc(*kelas, (*jumlah_kelas + 1) * sizeof(Kelas));
    if (*kelas == NULL) {
        printf("memory allocation failed\n");
        return;
    }

    printf("enter class name: ");
    scanf(" %[^\n]", (*kelas)[*jumlah_kelas].nama);
    (*kelas)[*jumlah_kelas].jumlah_tugas = 0;

    (*jumlah_kelas)++;
}

void tambah_tugas(Kelas *kelas, int jumlah_kelas) {
    if (jumlah_kelas == 0) {
        printf("no classes available please add a class first.\n");
        return;
    }

    printf("select the class number to add an assignment:\n");
    int i;
    for (i = 0; i < jumlah_kelas; i++) {
        printf("%d. %s\n", i + 1, kelas[i].nama);
    }
    int pilihan_kelas;
    scanf("%d", &pilihan_kelas);
    getchar();  

    if (pilihan_kelas < 1 || pilihan_kelas > jumlah_kelas) {
        printf("invalid class number.\n");
        return;
    }

    Kelas *kelas_terpilih = &kelas[pilihan_kelas - 1];

    printf("enter assignment name: ");
    scanf(" %[^\n]", kelas_terpilih->tugas[kelas_terpilih->jumlah_tugas].nama_tugas);

    printf("enter deadline (dd-mm-yyyy): ");
    scanf(" %[^\n]", kelas_terpilih->tugas[kelas_terpilih->jumlah_tugas].batas_waktu);

    printf("enter description: ");
    scanf(" %[^\n]", kelas_terpilih->tugas[kelas_terpilih->jumlah_tugas].deskripsi);

    kelas_terpilih->jumlah_tugas++;
}

void lihat_tugas(Kelas *kelas, int jumlah_kelas) {
    int i, j;
    for (i = 0; i < jumlah_kelas; i++) {
        printf("\n===============================\n");
        printf("%s\n", kelas[i].nama);
        printf("===============================\n");

        qsort(kelas[i].tugas, kelas[i].jumlah_tugas, sizeof(Tugas), bandingkan_batas_waktu);

        for (j = 0; j < kelas[i].jumlah_tugas; j++) {
            printf("%d. %s\n", j + 1, kelas[i].tugas[j].nama_tugas);
            printf("description: %s\n", kelas[i].tugas[j].deskripsi);
            printf("deadline: %s\n\n", kelas[i].tugas[j].batas_waktu);
        }
    }
}

void cari_tugas(Kelas *kelas, int jumlah_kelas) {
    printf("enter keyword to search assignments: ");
    char kata_kunci[100];
    scanf(" %[^\n]", kata_kunci);

    printf("\nSearch Results:\n");
    int i, j, ditemukan = 0;
    for (i = 0; i < jumlah_kelas; i++) {
        printf("\n===============================\n");
        printf("%s\n", kelas[i].nama);
        printf("===============================\n");

        for (j = 0; j < kelas[i].jumlah_tugas; j++) {
            char* nama_tugas_lower = strdup(kelas[i].tugas[j].nama_tugas);
            char* deskripsi_lower = strdup(kelas[i].tugas[j].deskripsi);
            for (int k = 0; nama_tugas_lower[k]; k++)
                nama_tugas_lower[k] = tolower(nama_tugas_lower[k]);
            for (int k = 0; deskripsi_lower[k]; k++)
                deskripsi_lower[k] = tolower(deskripsi_lower[k]);

            if (strstr(nama_tugas_lower, kata_kunci) != NULL ||
                strstr(deskripsi_lower, kata_kunci) != NULL) {
                printf("%d. %s\n", j + 1, kelas[i].tugas[j].nama_tugas);
                printf("description: %s\n", kelas[i].tugas[j].deskripsi);
                printf("deadline: %s\n\n", kelas[i].tugas[j].batas_waktu);
                ditemukan = 1;
            }
            free(nama_tugas_lower);
            free(deskripsi_lower);
        }
    }

    if (!ditemukan) {
        printf("no assignments found matching the keyword.\n");
    }
}

void hapus_tugas(Kelas *kelas, int jumlah_kelas) {
    printf("select the class number to delete an assignment:\n");
    int i;
    for (i = 0; i < jumlah_kelas; i++) {
        printf("%d. %s\n", i + 1, kelas[i].nama);
    }
    int pilihan_kelas;
    scanf("%d", &pilihan_kelas);

    if (pilihan_kelas < 1 || pilihan_kelas > jumlah_kelas) {
        printf("invalid class number.\n");
        return;
    }

    Kelas *kelas_terpilih = &kelas[pilihan_kelas - 1];

    printf("select the assignment number to delete:\n");
    for (i = 0; i < kelas_terpilih->jumlah_tugas; i++) {
        printf("%d. %s\n", i + 1, kelas_terpilih->tugas[i].nama_tugas);
    }
    int pilihan_tugas;
    scanf("%d", &pilihan_tugas);

    if (pilihan_tugas < 1 || pilihan_tugas > kelas_terpilih->jumlah_tugas) {
        printf("invalid assignment number.\n");
        return;
    }

    for (i = pilihan_tugas - 1; i < kelas_terpilih->jumlah_tugas - 1; i++) {
        kelas_terpilih->tugas[i] = kelas_terpilih->tugas[i + 1];
    }

    kelas_terpilih->jumlah_tugas--;
}

void tampilkan_bantuan() {
    printf("\nHelp menu:\n");
    printf("1. Add class: add a new class\n");
    printf("2. Add assignment: add a new assignment to a class\n");
    printf("3. View assignments: display all assignments, sorted by deadline\n");
    printf("4. Search assignments by keyword: find assignments for a specific keyword\n");
    printf("5. Delete assignment: remove an assignment from a class\n");
    printf("6. Help: display this help menu\n");
    printf("7. Exit: close the program\n");
}

int bandingkan_batas_waktu(const void *a, const void *b) {
    const Tugas *tugasA = (const Tugas *)a;
    const Tugas *tugasB = (const Tugas *)b;
    int tanggalA = parse_tanggal(tugasA->batas_waktu);
    int tanggalB = parse_tanggal(tugasB->batas_waktu);
    return tanggalA - tanggalB;
}

int parse_tanggal(const char *tanggal) {
    int hari, bulan, tahun;
    sscanf(tanggal, "%d-%d-%d", &hari, &bulan, &tahun);
    return tahun * 10000 + bulan * 100 + hari;
}

#endif
