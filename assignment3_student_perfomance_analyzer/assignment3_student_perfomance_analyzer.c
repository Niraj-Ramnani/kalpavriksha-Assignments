#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_STUDENT 100
#define NUM_SUBJECTS 3

typedef enum
{
    GRADE_F = 0,
    GRADE_D = 2,
    GRADE_C = 3,
    GRADE_B = 4,
    GRADE_A = 5
} Grade;

typedef struct
{
    int rollNumber;
    char name[50];
    int marks[NUM_SUBJECTS];
} Student;

void inputStudentDetails(Student students[], int *n);
void printStudentData(Student students[], int n);
void sortStudentsByRoll(Student students[], int n);
int calculateTotal(int subjectMarks[], int subjectCount);
float calculateAverage(int totalMarks, int subjectCount);
Grade assignGrade(float averageMarks);
void printPerformanceStar(Grade grade);
void printRollNumber(Student students[], int it, int n);
bool isValidMark(int subjectMarks[], int subjectCount);
bool isValidRollNumber(Student students[], int count, int rollNumber);
char gradeEnumToChar(Grade g);

int main()
{
    int N;
    Student students[MAX_STUDENT];

    inputStudentDetails(students, &N);
    sortStudentsByRoll(students, N);
    printStudentData(students, N);

    printf("\nList of Roll Numbers : ");
    printRollNumber(students, 0, N);
    printf("\n");

    return 0;
}

void inputStudentDetails(Student students[], int *n)
{
    scanf("%d", n);
    bool validRoll = false;
    bool validMarks = false;

    for (int i = 0; i < *n; i++)
    {
        do
        {

            scanf("%d %s %d %d %d", &students[i].rollNumber, students[i].name,
                  &students[i].marks[0], &students[i].marks[1], &students[i].marks[2]);
            validRoll = isValidRollNumber(students, i, students[i].rollNumber);
            if (!validRoll)
            {
                printf("\n Error: Duplicate roll number! \n");
            }
            validMarks = isValidMark(students[i].marks, NUM_SUBJECTS);
            if (!validMarks)
            {
                printf("\n Error: Marks must be between 0 and 100.\n");
            }
        } while (!validMarks || !validRoll);
    }
}

void printStudentData(Student students[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int totalMarks = calculateTotal(students[i].marks, NUM_SUBJECTS);
        float averageMarks = calculateAverage(totalMarks, NUM_SUBJECTS);
        Grade grade = assignGrade(averageMarks);

        printf("\nRoll: %d\n", students[i].rollNumber);
        printf("Name: %s\n", students[i].name);
        printf("Total: %d\n", totalMarks);
        printf("Average: %.2f\n", averageMarks);
        printf("Grade: %c\n", gradeEnumToChar(grade));

        if (grade == GRADE_F)
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

int calculateTotal(int subjectMarks[], int subjectCount)
{
    int total = 0;
    for (int i = 0; i < subjectCount; i++)
    {
        total += subjectMarks[i];
    }
    return total;
}

float calculateAverage(int totalMarks, int subjectCount)
{
    if (subjectCount == 0)
        return 0.0;
    return (float)totalMarks / subjectCount;
}

Grade assignGrade(float averageMarks)
{
    if (averageMarks >= 85)
        return GRADE_A;
    if (averageMarks >= 70)
        return GRADE_B;
    if (averageMarks >= 50)
        return GRADE_C;
    if (averageMarks >= 35)
        return GRADE_D;
    return GRADE_F;
}

void printPerformanceStar(Grade grade)
{
    printf("Performance: ");
    for (int i = 0; i < grade; i++)
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

bool isValidMark(int subjectMarks[], int subjectCount)
{
    for (int i = 0; i < subjectCount; i++)
    {
        if (subjectMarks[i] < 0 || subjectMarks[i] > 100)
        {
            return false;
        }
    }
    return true;
}

bool isValidRollNumber(Student students[], int count, int rollNumber)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].rollNumber == rollNumber)
        {
            return false;
        }
    }
    return true;
}

char gradeEnumToChar(Grade g)
{
    switch (g)
    {
    case GRADE_A:
        return 'A';
    case GRADE_B:
        return 'B';
    case GRADE_C:
        return 'C';
    case GRADE_D:
        return 'D';
    case GRADE_F:
        return 'F';
    }
    return ' ';
}