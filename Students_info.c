#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 50
#define SUBJECTS 5
#define ID_LENGTH 50

typedef struct {
    char id[ID_LENGTH];
    char name[30];
    float marks[SUBJECTS];
    float fees_paid, total_fees;
} 
Student;

Student students[MAX_STUDENTS];
int count = 0;
char subjects[SUBJECTS][50] = {"Mathematics-1", "Engineering Drawing", "C Programming", "English", "Chemistry"};

int findStudent(char *id) {
    int i;
    for(i = 0; i < count; i++) {
        if(strcmp(students[i].id, id) == 0) return i;
    }
    return -1;
}

void addStudent() {
    Student *s = &students[count];
    int i;
    
    if(count >= MAX_STUDENTS) {
        printf("Maximum limit reached!\n");
        return;
    }
    
    printf("Enter Student ID: ");
    scanf(" %[^\n]", s->id);    // we use arrays insted of structs then use this -> student_ids[student_count]);
    
    if(findStudent(s->id) != -1) {
        printf("Student ID already exists!\n");
        return;
    }
    
    printf("Enter Name: ");
    scanf(" %[^\n]", s->name);
    
    printf("Enter marks for 5 subjects:\n");
    for(i = 0; i < SUBJECTS; i++) {
        printf("%s: ", subjects[i]);
        scanf("%f", &s->marks[i]);
        
        if(s->marks[i] < 0 || s->marks[i] > 100) {
            printf("Invalid marks! Enter 0-100: ");
            scanf("%f", &s->marks[i]);
        }
    }
    
    printf("Enter Total Fees: ");
    scanf("%f", &s->total_fees);
    printf("Enter Fees Paid: ");
    scanf("%f", &s->fees_paid);
    
    if(s->fees_paid > s->total_fees) {
        s->fees_paid = s->total_fees;
        printf("Fees adjusted to total fees amount.\n");
    }
    
    count++;
    printf("Student added successfully!\n");
}

void generateReport() {
    char id[ID_LENGTH];
    int i, index;
    float total = 0, avg;
    char grade, overall_grade;
    
    if(count == 0) {
        printf("No students found!\n");
        return;
    }
    
    printf("Enter Student ID: ");
    scanf(" %[^\n]", id);
    
    index = findStudent(id);
    if(index == -1) {
        printf("Student not found!\n");
        return;
    }
    
    Student *s = &students[index];
    
    printf("\n============ REPORT CARD ============\n");
    printf("Student ID: %s\n", s->id);
    printf("Name: %s\n", s->name);
    printf("=====================================\n");
    printf("Subject          Marks    Grade\n");
    printf("=====================================\n");
    
    for(i = 0; i < SUBJECTS; i++) {
        if(s->marks[i] >= 90) grade = 'A';
        else if(s->marks[i] >= 80) grade = 'B';
        else if(s->marks[i] >= 70) grade = 'C';
        else if(s->marks[i] >= 60) grade = 'D';
        else grade = 'F';
        
        printf("%-15s %6.1f      %c\n", subjects[i], s->marks[i], grade);
        total += s->marks[i];
    }
    
    avg = total / SUBJECTS;
    if(avg >= 90) overall_grade = 'A';
    else if(avg >= 80) overall_grade = 'B';
    else if(avg >= 70) overall_grade = 'C';
    else if(avg >= 60) overall_grade = 'D';
    else overall_grade = 'F';
    
    printf("=====================================\n");
    printf("Total Marks: %.1f/500\n", total);
    printf("Percentage: %.2f%%\n", (total/500)*100);
    printf("Overall Grade: %c\n", overall_grade);
    printf("=====================================\n");
    printf("Fee Details:\n");
    printf("Total Fees: $%.2f\n", s->total_fees);
    printf("Fees Paid: $%.2f\n", s->fees_paid);
    printf("Balance: $%.2f\n", s->total_fees - s->fees_paid);
    printf("Status: %s\n", s->fees_paid >= s->total_fees ? "PAID" : "PENDING");
    printf("=====================================\n");
}

void displayAll() {
    int i, j;
    float total;
    
    if(count == 0) {
        printf("No students registered!\n");
        return;
    }
    
    printf("\n========== ALL STUDENTS ==========\n");
    printf("%-10s %-15s %-8s %-8s %-10s\n", "ID", "Name", "Total", "Percent", "Balance");
    printf("========================================================\n");
    
    for(i = 0; i < count; i++) {
        total = 0;
        for(j = 0; j < SUBJECTS; j++) {
            total += students[i].marks[j];
        }
        
        printf("%-10s %-15s %-8.1f %-8.2f $%-9.2f\n", 
               students[i].id, 
               students[i].name, 
               total,
               (total/500)*100,
               students[i].total_fees - students[i].fees_paid);
    }
    
    printf("========================================================\n");
    printf("Total Students: %d\n", count);
}

int main() {
    int choice;
    
    printf("========================================\n");
    printf("     STUDENT INFORMATION SYSTEM\n");
    printf("========================================\n");
    
    while(1) {
        printf("\n1. Add Student\n");
        printf("2. Generate Report\n");
        printf("3. Display All Students\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: 
                addStudent(); 
                break;
            case 2: 
                generateReport(); 
                break;
            case 3: 
                displayAll(); 
                break;
            case 4: 
                printf("Thank you for using Student Information System!\n");
                return 0;
            default: 
                printf("Invalid choice! Please enter 1-4.\n");
        }
    }
    
    return 0;
}
