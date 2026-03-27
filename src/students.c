/* students.c */
/* Author: Ibragimov Nawruzbek */
/* lab3_zadacha2 */

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void printResult(sqlite3_stmt *res, int columns) {
    while (sqlite3_step(res) == SQLITE_ROW) {
        for (int i = 0; i < columns; i++) {
            printf("%-15s ", sqlite3_column_text(res, i));
        }
        printf("\n");
    }
}

void selectRecords(sqlite3 *db) {
    sqlite3_stmt *res;
    int choice, option;
    char sql[200];

    printf("\n1. Select values from the students table\n");
    printf("2. Select values from the subjects table\n");
    printf("3. Select values from the teachers table\n");
    printf("Choose: ");
    scanf("%d", &choice);

    if (choice == 1) {
        strcpy(sql, "SELECT * FROM students");
        printf("1. Select all table\n");
        printf("2. Select by id\n");
        printf("3. Select by last name\n");
        printf("Choose: ");
        scanf("%d", &option);

        if (option == 2) {
            int id;
            printf("Enter Student id: ");
            scanf("%d", &id);
            sprintf(sql, "SELECT * FROM students WHERE Student_id = %d", id);
        } else if (option == 3) {
            char lname[50];
            printf("Enter Last Name: ");
            scanf("%s", lname);
            sprintf(sql, "SELECT * FROM students WHERE LastName LIKE '%s'", lname);
        }

        sqlite3_prepare_v2(db, sql, -1, &res, 0);
        printResult(res, 7);
        sqlite3_finalize(res);
    }
    else if (choice == 2) {
        strcpy(sql, "SELECT * FROM subjects");
        sqlite3_prepare_v2(db, sql, -1, &res, 0);
        printResult(res, 2);
        sqlite3_finalize(res);
    }
    else if (choice == 3) {
        strcpy(sql, "SELECT * FROM teachers");
        sqlite3_prepare_v2(db, sql, -1, &res, 0);
        printResult(res, 3);
        sqlite3_finalize(res);
    }
}

void insertNewRecord(sqlite3 *db) {
    char *err_msg = 0;
    char sql[500];
    int choice;

    printf("\n1. Insert into students table\n");
    printf("2. Insert into subjects table\n");
    printf("Choose: ");
    scanf("%d", &choice);

    if (choice == 1) {
        char fname[50], lname[50];
        int group_id, height, weight, age;
        printf("Enter FirstName: ");
        scanf("%s", fname);
        printf("Enter LastName: ");
        scanf("%s", lname);
        printf("Enter Group_id: ");
        scanf("%d", &group_id);
        printf("Enter height: ");
        scanf("%d", &height);
        printf("Enter weight: ");
        scanf("%d", &weight);
        printf("Enter age: ");
        scanf("%d", &age);

        sprintf(sql, "INSERT INTO students (FirstName, LastName, Group_id, height, weight, age) VALUES ('%s', '%s', %d, %d, %d, %d)",
                fname, lname, group_id, height, weight, age);
    }
    else if (choice == 2) {
        int subj_id;
        char title[100];
        printf("Enter Subject_id: ");
        scanf("%d", &subj_id);
        printf("Enter Title: ");
        scanf("%s", title);
        sprintf(sql, "INSERT INTO subjects (Subject_id, Title) VALUES (%d, '%s')", subj_id, title);
    }

    sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (err_msg) {
        printf("Error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Record inserted successfully\n");
    }
}

void deleteRecord(sqlite3 *db) {
    char *err_msg = 0;
    char sql[200];
    int choice;

    printf("\n1. Delete from students\n");
    printf("2. Delete from marks\n");
    printf("Choose: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int id;
        printf("Enter Student id to delete: ");
        scanf("%d", &id);
        sprintf(sql, "DELETE FROM students WHERE Student_id = %d", id);
    }
    else if (choice == 2) {
        int id;
        printf("Enter MarkId to delete: ");
        scanf("%d", &id);
        sprintf(sql, "DELETE FROM marks WHERE MarkId = %d", id);
    }

    sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (err_msg) {
        printf("Error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Record deleted successfully\n");
    }
}
