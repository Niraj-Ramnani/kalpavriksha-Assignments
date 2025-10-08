#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILENAME "users.txt"
#define TEMP_FILENAME "temp.txt"

typedef struct
{
    int id;
    char name[50];
    int age;
} User;

void addUser();
void displayUsers();
void updateUser();
void deleteUser();
void menu();
void inputUserDetails(User *u);

int main()
{
    menu();
    return 0;
}

void addUser()
{
    FILE *filePointer = fopen(FILENAME, "a");
    if (filePointer == NULL) {
        printf("Error opening file.\n");
        return;
    }
    User u;
    int maxId = 0;
    FILE *filePointerRead = fopen(FILENAME, "r");
    User temp;
    while (filePointerRead && fscanf(filePointerRead, "%d %s %d", &temp.id, temp.name, &temp.age) == 3) {
        if (temp.id > maxId) {
            maxId = temp.id;
        }
    }
    if (filePointerRead) {
        fclose(filePointerRead);
    }
    u.id = maxId + 1;
    printf("Assigned ID: %d\n", u.id);

    inputUserDetails(&u);

    fprintf(filePointer, "%d %s %d\n", u.id, u.name, u.age);
    fclose(filePointer);
    printf("User added successfully\n");
}

void displayUsers()
{
    FILE *filePointer = fopen(FILENAME, "r");
    if (filePointer == NULL) {
        printf("Error opening file.\n");
        return;
    }
    User u;
    printf("ID\tName\tAge\n");
    while (fscanf(filePointer, "%d %s %d", &u.id, u.name, &u.age) == 3) {
        printf("%d\t%s\t%d\n", u.id, u.name, u.age);
    }
    fclose(filePointer);
}

void updateUser()
{
    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);

    FILE *filePointer = fopen(FILENAME, "r");
    bool found = false;
    User tempUser;
    while (filePointer && fscanf(filePointer, "%d %s %d", &tempUser.id, tempUser.name, &tempUser.age) == 3) {
        if (tempUser.id == id) {
            found = true;
            break;
        }
    }
    if (filePointer) {
        fclose(filePointer);
    }

    if (!found) {
        printf("User not found.\n");
        return;
    }

    filePointer = fopen(FILENAME, "r");
    FILE *temp = fopen(TEMP_FILENAME, "w");
    User u;
    while (fscanf(filePointer, "%d %s %d", &u.id, u.name, &u.age) == 3) {
        if (u.id == id) {
            inputUserDetails(&u);
        }
        fprintf(temp, "%d %s %d\n", u.id, u.name, u.age);
    }
    fclose(filePointer);
    fclose(temp);
    remove(FILENAME);
    rename(TEMP_FILENAME, FILENAME);
    printf("User updated successfully.\n");
}

void deleteUser()
{
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    FILE *filePointer = fopen(FILENAME, "r");
    bool found = false;
    User tempUser;
    while (filePointer && fscanf(filePointer, "%d %s %d", &tempUser.id, tempUser.name, &tempUser.age) == 3) {
        if (tempUser.id == id) {
            found = true;
            break;
        }
    }
    if (filePointer) {
        fclose(filePointer);
    }

    if (!found) {
        printf("User not found.\n");
        return;
    }

    filePointer = fopen(FILENAME, "r");
    FILE *temp = fopen(TEMP_FILENAME, "w");
    User u;
    while (fscanf(filePointer, "%d %s %d", &u.id, u.name, &u.age) == 3) {
        if (u.id != id) {
            fprintf(temp, "%d %s %d\n", u.id, u.name, u.age);
        }
    }
    fclose(filePointer);
    fclose(temp);
    remove(FILENAME);
    rename(TEMP_FILENAME, FILENAME);
    printf("User deleted successfully.\n");
}

void inputUserDetails(User *u)
{
    printf("Enter Name: ");
    scanf("%s", u->name);
    printf("Enter Age: ");
    scanf("%d", &u->age);
}

void menu()
{
    int choice;
    do {
        printf("\n1. Add User\n2. Display Users\n3. Update User\n4. Delete User\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addUser();
                break;
            case 2:
                displayUsers();
                break;
            case 3:
                updateUser();
                break;
            case 4:
                deleteUser();
                break;
            case 5:
                printf("Exiting \n");
                break;
            default:
                printf("Invalid choice \n");
        }
    } while (choice != 5);
}
