#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "users.txt"

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

int main()
{
     menu();
     return 0;
}

void add_user()
{
     FILE *fp = fopen(FILENAME, "a");
     if (fp == NULL)
     {
          printf("Error opening file.\n");
          return;
     }
     user u;
     printf("Enter ID: ");
     scanf("%d", &u.id);
     printf("Enter Name: ");
     scanf("%s", u.name);
     printf("Enter Age: ");
     scanf("%d", &u.age);
     fprintf(fp, "%d %s %d\n", u.id, u.name, u.age);
     fclose(fp);
     printf("User added successfully\n");
}

void display_users()
{
     FILE *fp = fopen(FILENAME, "r");
     if (fp == NULL)
     {
          printf("Error opening file.\n");
          return;
     }
     user u;
     printf("ID\tName\tAge\n");
     while (fscanf(fp, "%d %s %d", &u.id, u.name, &u.age) == 3)
          printf("%d\t%s\t%d\n", u.id, u.name, u.age);
     fclose(fp);
}

void update_user()
{
     FILE *fp = fopen(FILENAME, "r");
     FILE *temp = fopen("temp.txt", "w");
     if (!fp || !temp)
     {
          printf("Error opening file.\n");
          return;
     }
     user u;
     int id, found = 0;
     printf("Enter ID to update: ");
     scanf("%d", &id);
     while (fscanf(fp, "%d %s %d", &u.id, u.name, &u.age) == 3)
     {
          if (u.id == id)
          {
               printf("Enter new Name: ");
               scanf("%s", u.name);
               printf("Enter new Age: ");
               scanf("%d", &u.age);
               found = 1;
          }
          fprintf(temp, "%d %s %d\n", u.id, u.name, u.age);
     }
     fclose(fp);
     fclose(temp);
     remove(FILENAME);
     rename("temp.txt", FILENAME);
     if (found)
          printf("User updated successfully.\n");
     else
          printf("User not found.\n");
}

void delete_user()
{
     FILE *fp = fopen(FILENAME, "r");
     FILE *temp = fopen("temp.txt", "w");
     if (!fp || !temp)
     {
          printf("Error opening file.\n");
          return;
     }
     user u;
     int id, found = 0;
     printf("Enter ID to delete: ");
     scanf("%d", &id);
     while (fscanf(fp, "%d %s %d", &u.id, u.name, &u.age) == 3)
     {
          if (u.id == id)
               found = 1;
          else
               fprintf(temp, "%d %s %d\n", u.id, u.name, u.age);
     }
     fclose(fp);
     fclose(temp);
     remove(FILENAME);
     rename("temp.txt", FILENAME);
     if (found)
          printf("User deleted successfully.\n");
     else
          printf("User not found.\n");
}

void menu(){
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