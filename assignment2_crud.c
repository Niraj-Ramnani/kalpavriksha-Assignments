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
} user;

void add_user();
void display_users();
void update_user();
void delete_user();
void menu();
void input_user_details(user *u);

int main()
{
    menu();
    return 0;
}

void add_user()
{
    FILE *file_pointer = fopen(FILENAME, "a");
    if (file_pointer == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    user u;
    int max_id = 0;
    FILE *filepointer_read = fopen(FILENAME, "r");
    user temp;
    while (filepointer_read && fscanf(filepointer_read, "%d %s %d", &temp.id, temp.name, &temp.age) == 3)
    {
        if (temp.id > max_id)
            max_id = temp.id;
    }
    if (filepointer_read)
        fclose(filepointer_read);
    u.id = max_id + 1;
    printf("Assigned ID: %d\n", u.id);

    input_user_details(&u);

    fprintf(file_pointer, "%d %s %d\n", u.id, u.name, u.age);
    fclose(file_pointer);
    printf("User added successfully\n");
}

void display_users()
{
    FILE *file_pointer = fopen(FILENAME, "r");
    if (file_pointer == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    user u;
    printf("ID\tName\tAge\n");
    while (fscanf(file_pointer, "%d %s %d", &u.id, u.name, &u.age) == 3)
        printf("%d\t%s\t%d\n", u.id, u.name, u.age);
    fclose(file_pointer);
}

void update_user()
{
    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);

    FILE *file_pointer = fopen(FILENAME, "r");
    bool found = false;
    user temp_user;
    while (file_pointer && fscanf(file_pointer, "%d %s %d", &temp_user.id, temp_user.name, &temp_user.age) == 3)
    {
        if (temp_user.id == id)
        {
            found = true;
            break;
        }
    }
    if (file_pointer)
        fclose(file_pointer);

    if (!found)
    {
        printf("User not found.\n");
        return;
    }

    file_pointer = fopen(FILENAME, "r");
    FILE *temp = fopen(TEMP_FILENAME, "w");
    user u;
    while (fscanf(file_pointer, "%d %s %d", &u.id, u.name, &u.age) == 3)
    {
        if (u.id == id)
        {
            input_user_details(&u);
        }
        fprintf(temp, "%d %s %d\n", u.id, u.name, u.age);
    }
    fclose(file_pointer);
    fclose(temp);
    remove(FILENAME);
    rename(TEMP_FILENAME, FILENAME);
    printf("User updated successfully.\n");
}

void delete_user()
{
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    FILE *file_pointer = fopen(FILENAME, "r");
    bool found = false;
    user temp_user;
    while (file_pointer && fscanf(file_pointer, "%d %s %d", &temp_user.id, temp_user.name, &temp_user.age) == 3)
    {
        if (temp_user.id == id)
        {
            found = true;
            break;
        }
    }
    if (file_pointer)
        fclose(file_pointer);

    if (!found)
    {
        printf("User not found.\n");
        return;
    }

    file_pointer = fopen(FILENAME, "r");
    FILE *temp = fopen(TEMP_FILENAME, "w");
    user u;
    while (fscanf(file_pointer, "%d %s %d", &u.id, u.name, &u.age) == 3)
    {
        if (u.id != id)
        {
            fprintf(temp, "%d %s %d\n", u.id, u.name, u.age);
        }
    }
    fclose(file_pointer);
    fclose(temp);
    remove(FILENAME);
    rename(TEMP_FILENAME, FILENAME);
    printf("User deleted successfully.\n");
}

void input_user_details(user *u)
{
    printf("Enter Name: ");
    scanf("%s", u->name);
    printf("Enter Age: ");
    scanf("%d", &u->age);
}

void menu()
{
    int choice;
    do
    {
        printf("\n1. Add User\n2. Display Users\n3. Update User\n4. Delete User\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            add_user();
            break;
        case 2:
            display_users();
            break;
        case 3:
            update_user();
            break;
        case 4:
            delete_user();
            break;
        case 5:
            printf("Exiting \n");
            break;
        default:
            printf("Invalid choice \n");
        }
    } while (choice != 5);
}
