#include <stdio.h>
#include <string.h>
#define MAX_STUDENT 100

typedef struct
{
     int rollNumber;
     char name[50];
     int marks[3];
} Student;

void getStudentData(Student students[], int *n);
void printStudentData(Student students[], int n);
void sortStudentsByRoll(Student students[], int n);
int calculateTotal(int subjectMarks[]);
float calculateAverage(int totalMarks);
char assignGrade(float averageMarks);
void printPerformanceStar(char grade);
void printRollNumber(Student students[], int it, int n);

int main()
{
     int N;
     Student students[MAX_STUDENT];

     getStudentData(students, &N);
     sortStudentsByRoll(students, N);
     printStudentData(students, N);

     printf("\nList of Roll Numbers : ");
     printRollNumber(students, 0, N);
     printf("\n");

     return 0;
}

void getStudentData(Student students[], int *n)
{
     printf("Enter number of students (1-100): ");
     scanf("%d", n);
     if (*n < 1 || *n > MAX_STUDENT)
     {
          printf("Invalid number of students.\n");
          *n = 0;
          return;
     }
     for (int i = 0; i < *n; i++)
     {
          scanf("%d %s %d %d %d", &students[i].rollNumber, students[i].name,
                &students[i].marks[0], &students[i].marks[1], &students[i].marks[2]);
     }
}

void printStudentData(Student students[], int n)
{
     for (int i = 0; i < n; i++)
     {
          int totalMarks = calculateTotal(students[i].marks);
          float averageMarks = calculateAverage(totalMarks);
          char grade = assignGrade(averageMarks);

          printf("\nRoll: %d\n", students[i].rollNumber);
          printf("Name: %s\n", students[i].name);
          printf("Total: %d\n", totalMarks);
          printf("Average: %.2f\n", averageMarks);
          printf("Grade: %c\n", grade);

          if (grade == 'F')
          {
               continue;
          }
          printPerformanceStar(grade);
     }
}

void sortStudentsByRoll(Student students[], int n)
{
     for (int i = 0; i < n - 1; i++)
     {
          for (int j = i + 1; j < n; j++)
          {
               if (students[i].rollNumber > students[j].rollNumber)
               {
                    Student temp = students[i];
                    students[i] = students[j];
                    students[j] = temp;
               }
          }
     }
}

int calculateTotal(int subjectMarks[])
{
     return subjectMarks[0] + subjectMarks[1] + subjectMarks[2];
}

float calculateAverage(int totalMarks)
{
     return totalMarks / 3.0;
}

char assignGrade(float averageMarks)
{
     if (averageMarks >= 85)
          return 'A';
     if (averageMarks >= 70)
          return 'B';
     if (averageMarks >= 50)
          return 'C';
     if (averageMarks >= 35)
          return 'D';
     return 'F';
}

void printPerformanceStar(char grade)
{
     printf("Performance: ");
     int starCount = 0;
     switch (grade)
     {
     case 'A':
          starCount = 5;
          break;
     case 'B':
          starCount = 4;
          break;
     case 'C':
          starCount = 3;
          break;
     case 'D':
          starCount = 2;
          break;
     }
     for (int i = 0; i < starCount; i++)
     {
          printf("*");
     }
     printf("\n");
}

void printRollNumber(Student students[], int it, int n)
{
     if (it >= n)
     {
          return;
     }
     printf("%d ", students[it].rollNumber);
     printRollNumber(students, it + 1, n);
}
