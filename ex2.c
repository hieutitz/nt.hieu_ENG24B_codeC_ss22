#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char username[50];
    char password[50];
} Account;

Account accounts[100];
int accountCount = 0;
char fileName[] = "accounts.dat";

void loadAccounts();
void saveAccounts();
void registerAccount();
void login();

int main() {
    int choice;

    loadAccounts();

    do {
        printf("\n=== MENU ===\n");
        printf("1. Dang nhap\n");
        printf("2. Dang ky\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                registerAccount();
                break;
            case 3:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 3);

    return 0;
}

void loadAccounts() {
    FILE *file = fopen(fileName, "rb");
    if (file) {
        fread(&accountCount, sizeof(int), 1, file);
        fread(accounts, sizeof(Account), accountCount, file);
        fclose(file);
    } else {
        accountCount = 0;
    }
}

void saveAccounts() {
    FILE *file = fopen(fileName, "wb");
    if (file) {
        fwrite(&accountCount, sizeof(int), 1, file);
        fwrite(accounts, sizeof(Account), accountCount, file);
        fclose(file);
    }
}

void registerAccount() {
    if (accountCount >= 100) {
        printf("Khong the dang ky them tai khoan moi.\n");
        return;
    }

    Account newAccount;
    char confirmPassword[50];
    int isDuplicate;

    do {
        isDuplicate = 0;
        printf("Nhap ten tai khoan: ");
        fgets(newAccount.username, 50, stdin);
        newAccount.username[strcspn(newAccount.username, "\n")] = '\0';

        for (int i = 0; i < accountCount; i++) {
            if (strcmp(accounts[i].username, newAccount.username) == 0) {
                printf("Tai khoan da ton tai. Vui long nhap lai.\n");
                isDuplicate = 1;
                break;
            }
        }
    } while (isDuplicate);

    do {
        printf("Nhap mat khau: ");
        fgets(newAccount.password, 50, stdin);
        newAccount.password[strcspn(newAccount.password, "\n")] = '\0';

        printf("Xac nhan mat khau: ");
        fgets(confirmPassword, 50, stdin);
        confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

        if (strcmp(newAccount.password, confirmPassword) != 0) {
            printf("Mat khau xac nhan khong trung khop. Vui long nhap lai.\n");
        }
    } while (strcmp(newAccount.password, confirmPassword) != 0);

    accounts[accountCount++] = newAccount;
    saveAccounts();

    printf("Dang ky thanh cong!\n");
}

void login() {
    char username[50];
    char password[50];
    int isAuthenticated = 0;

    printf("Nhap ten tai khoan: ");
    fgets(username, 50, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Nhap mat khau: ");
    fgets(password, 50, stdin);
    password[strcspn(password, "\n")] = '\0';

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0 &&
            strcmp(accounts[i].password, password) == 0) {
            isAuthenticated = 1;
            break;
        }
    }

    if (isAuthenticated) {
        printf("Dang nhap thanh cong!\n");
    } else {
        printf("Dang nhap that bai. Vui long kiem tra lai thong tin.\n");
    }
}

