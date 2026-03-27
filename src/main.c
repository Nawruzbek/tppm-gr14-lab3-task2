/* main.c */
/* Author: Ibragimov Nawruzbek */
/* lab3_zadacha2 */

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include "students.h"

#define TRUE 1
#define FALSE 0

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("students.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    while(TRUE) {
        printf("\nMenu to manage the database (students.db):\n");
        printf("1. SELECT records\n");
        printf("2. INSERT records\n");
        printf("3. DELETE records\n");
        printf("4. Exit\n");
        printf("Choose: ");

        int choice;
        scanf("%d", &choice);

        if (choice == 4) break;

        switch(choice) {
            case 1: selectRecords(db); break;
            case 2: insertNewRecord(db); break;
            case 3: deleteRecord(db); break;
            default: printf("No such option\n");
        }
    }

    sqlite3_close(db);
    return 0;
}
