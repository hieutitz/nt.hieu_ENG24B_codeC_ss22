#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
} Student;

Student students[100];
int studentCount = 0;
int maxStudents = 100;
char fileName[] = "students.dat";

void loadStudents();
void saveStudents();
void printStudents();
void addStudent();
void editStudent();
void deleteStudent();
void searchStudent();
void sortStudents();

int main() {
    int choice;

    loadStudents();

    do {
        printf("\n=== MENU ===\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printStudents();
                break;
            case 2:
                addStudent();
                break;
            case 3:
                editStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                searchStudent();
                break;
            case 6:
                sortStudents();
                break;
            case 7:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 7);

    return 0;
}

void loadStudents() {
    FILE *file = fopen(fileName, "rb");
    if (file) {
        fread(&studentCount, sizeof(int), 1, file);
        fread(students, sizeof(Student), studentCount, file);
        fclose(file);
    } else {
        studentCount = 0;
    }
}

void saveStudents() {
    FILE *file = fopen(fileName, "wb");
    if (file) {
        fwrite(&studentCount, sizeof(int), 1, file);
        fwrite(students, sizeof(Student), studentCount, file);
        fclose(file);
    }
}

void printStudents() {
    if (studentCount == 0) {
        printf("Danh sach sinh vien trong.\n");
    } else {
        for (int i = 0; i < studentCount; i++) {
            printf("ID: %d, Ten: %s, Tuoi: %d\n", students[i].id, students[i].name, students[i].age);
        }
    }
}

void addStudent() {
    if (studentCount >= maxStudents) return;

    Student newStudent;
    printf("Nhap ID: ");
    scanf("%d", &newStudent.id);
    getchar();
    printf("Nhap ten: ");
    fgets(newStudent.name, 50, stdin);
    for (int i = 0; newStudent.name[i] != '\0'; i++) {
        if (newStudent.name[i] == '\n') {
            newStudent.name[i] = '\0';
            break;
        }
    }
    printf("Nhap tuoi: ");
    scanf("%d", &newStudent.age);

    students[studentCount++] = newStudent;
    saveStudents();
}

void editStudent() {
    int id, found = 0;
    printf("Nhap ID sinh vien can sua: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = 1;
            printf("Nhap ten moi: ");
            fgets(students[i].name, 50, stdin);
            for (int j = 0; students[i].name[j] != '\0'; j++) {
                if (students[i].name[j] == '\n') {
                    students[i].name[j] = '\0';
                    break;
                }
            }
            printf("Nhap tuoi moi: ");
            scanf("%d", &students[i].age);
            saveStudents();
            break;
        }
    }
    if (!found) printf("Khong tim thay sinh vien voi ID nay.\n");
}

void deleteStudent() {
    int id, found = 0;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = 1;
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            saveStudents();
            break;
        }
    }
    if (!found) printf("Khong tim thay sinh vien voi ID nay.\n");
}

void searchStudent() {
    int id, found = 0;
    printf("Nhap ID sinh vien can tim: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = 1;
            printf("ID: %d, Ten: %s, Tuoi: %d\n", students[i].id, students[i].name, students[i].age);
            break;
        }
    }
    if (!found) printf("Khong tim thay sinh vien voi ID nay.\n");
}

void sortStudents() {
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            if (students[i].id > students[j].id) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    saveStudents();
}

