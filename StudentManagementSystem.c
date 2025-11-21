#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Students {
    char name[30];
    int age;
    int marks;
    char gender;
};

// ---------------- Helper Functions ----------------

int get_age(int i) {
    int age;
    printf("Enter the age of student %d: ", i + 1);
    scanf("%d", &age);
    getchar();

    while (age <= 0 || age >= 60) {
        printf("Invalid age, please try again: ");
        scanf("%d", &age);
        getchar();
    }
    return age;
}

int get_marks(int i) {
    int marks;
    printf("Enter the marks of student %d: ", i + 1);
    scanf("%d", &marks);
    getchar();

    while (marks < 0 || marks >= 500) {
        if (marks < 0)
            printf("Marks cannot be negative.\n");
        else
            printf("Marks cannot exceed 500.\n");

        printf("Please try again: ");
        scanf("%d", &marks);
        getchar();
    }
    return marks;
}

char get_gender(int i) {
    char gender;
    printf("Enter the gender of student %d [M/F]: ", i + 1);
    scanf(" %c", &gender);

    while (gender != 'm' && gender != 'M' && gender != 'f' && gender != 'F') {
        printf("Invalid input. Please enter [M/F]: ");
        scanf(" %c", &gender);
    }
    return gender;
}

void get_name(int i, char *name) {
    printf("Enter the name of student %d: ", i + 1);
    scanf(" %[^\n]", name);
}

// ---------------- Core Functions ----------------

void add_records(int *size, struct Students **s) {
    int i, n;

    printf("Enter how many extra students you would like to add: ");
    scanf("%d", &n);
    getchar();

    *s = (struct Students *)realloc(*s, (*size + n) * sizeof(struct Students));
    if (*s == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    for (i = *size; i < *size + n; i++) {
        get_name(i, (*s)[i].name);
        (*s)[i].age = get_age(i);
        (*s)[i].marks = get_marks(i);
        (*s)[i].gender = get_gender(i);
    }

    *size += n;
}

void display_records(int size, struct Students *ptr) {
    for (int i = 0; i < size; i++) {
        printf("\nDetails of student %d:\n", i + 1);
        printf("Name   : %s\n", ptr[i].name);
        printf("Age    : %d\n", ptr[i].age);
        printf("Gender : %c\n", ptr[i].gender);
        printf("Marks  : %d\n", ptr[i].marks);
    }
}

void save_records(int size, struct Students *s) {
    FILE *ptr = fopen("records.dat", "wb");
    if (ptr == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fwrite(s, sizeof(struct Students), size, ptr);
    fclose(ptr);
    printf("Records saved successfully.\n");
}

void load_records(int *size, struct Students **s) {
    FILE *p = fopen("records.dat", "rb");
    if (p == NULL) {
        printf("No records found.\n");
        return;
    }

    fseek(p, 0, SEEK_END);
    long file_size = ftell(p);
    rewind(p);

    *size = file_size / sizeof(struct Students);
    *s = (struct Students *)realloc(*s, *size * sizeof(struct Students));

    if (*s == NULL) {
        printf("Memory allocation failed while loading.\n");
        fclose(p);
        return;
    }

    fread(*s, sizeof(struct Students), *size, p);
    fclose(p);

    printf("Records loaded successfully (%d records).\n", *size);
}

void delete_record(int *size, struct Students **s) {
    char n[30];
    int i, j, f = 0;

    printf("Enter the name of the student to delete: ");
    scanf(" %[^\n]", n);

    for (i = 0; i < *size; i++) {
        if (strcmp((*s)[i].name, n) == 0) {
            printf("Match Found! Deleting student %d...\n", i + 1);
            f = 1;

            for (j = i; j < *size - 1; j++)
                (*s)[j] = (*s)[j + 1];

            (*size)--;
            struct Students *temp = realloc(*s, *size * sizeof(struct Students));
            if (temp != NULL)
                *s = temp;
            else
                printf("Warning: Memory shrink failed, but deletion succeeded.\n");

            break;
        }
    }

    if (!f)
        printf("No match found.\n");
}

void modify_record(int size, struct Students *s) {
    char name[30];
    int f = 0;

    printf("Enter the name of the student to modify: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < size; i++) {
        if (strcmp(s[i].name, name) == 0) {
            printf("Match Found! Modifying record of student %d...\n", i + 1);
            f = 1;

            get_name(i, s[i].name);
            s[i].age = get_age(i);
            s[i].marks = get_marks(i);
            s[i].gender = get_gender(i);
            break;
        }
    }

    if (!f)
        printf("Student not found.\n");
}

// ---------------- Menu and Main ----------------

void menu() {
    printf("\nChoose an option:\n");
    printf("1. Add records\n");
    printf("2. Display records\n");
    printf("3. Save records\n");
    printf("4. Load records\n");
    printf("5. Delete a record\n");
    printf("6. Modify a record\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int n, i, response;

    printf("Enter how many students you want to create initially: ");
    scanf("%d", &n);
    getchar();

    struct Students *s = (struct Students *)malloc(n * sizeof(struct Students));

    for (i = 0; i < n; i++) {
        get_name(i, s[i].name);
        s[i].age = get_age(i);
        s[i].marks = get_marks(i);
        s[i].gender = get_gender(i);
    }

    do {
        menu();
        scanf("%d", &response);
        getchar();

        switch (response) {
            case 1:
                add_records(&n, &s);
                break;
            case 2:
                display_records(n, s);
                break;
            case 3:
                save_records(n, s);
                break;
            case 4:
                load_records(&n, &s);
                break;
            case 5:
                delete_record(&n, &s);
                break;
            case 6:
                modify_record(n, s);
                break;
            case 0:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (response != 0);

    free(s);
    return 0;
}