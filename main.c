#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TASKS 100
#define MAX_BIRTHDAYS 100
#define PASSWORD "C.PROJECT-1" // Change this to a more secure password

typedef struct {
    char tasks[MAX_TASKS][256];
    int task_count;
} ToDoList;

typedef struct {
    char name[256];
    int day, month;
} Birthday;

// Declare global arrays for birthdays and their count
Birthday birthdays[MAX_BIRTHDAYS];
int birthday_count = 0;

// Function to display tasks
void display_tasks(ToDoList *list) {
    printf("\nYour To-Do List:\n");
    for (int i = 0; i < list->task_count; i++) {
        printf("%d. %s\n", i + 1, list->tasks[i]);
    }
    printf("\n");
}

// Function to add a task
void add_task(ToDoList *list, const char *task) {
    if (list->task_count < MAX_TASKS) {
        strcpy(list->tasks[list->task_count], task);
        list->task_count++;
        printf("Task added: %s\n", task);
    } else {
        printf("Task limit reached. Cannot add more tasks.\n");
    }
}

// Function to delete a task
void delete_task(ToDoList *list, int index) {
    if (index >= 0 && index < list->task_count) {
        for (int i = index; i < list->task_count - 1; i++) {
            strcpy(list->tasks[i], list->tasks[i + 1]);
        }
        list->task_count--;
        printf("Task deleted.\n");
    } else {
        printf("Invalid task number.\n");
    }
}

// Function to add a birthday
void add_birthday() {
    if (birthday_count < MAX_BIRTHDAYS) {
        printf("Enter name: ");
        fgets(birthdays[birthday_count].name, sizeof(birthdays[birthday_count].name), stdin);
        birthdays[birthday_count].name[strcspn(birthdays[birthday_count].name, "\n")] = 0; // Remove newline character

        printf("Enter day and month of birth (DD MM): ");
        scanf("%d %d", &birthdays[birthday_count].day, &birthdays[birthday_count].month);
        getchar(); // Consume the newline character

        birthday_count++;
        printf("Birthday added.\n");
    } else {
        printf("Birthday list is full.\n");
    }
}

// Function to display all birthdays
void display_birthdays() {
    if (birthday_count == 0) {
        printf("No birthdays to display.\n");
        return;
    }

    printf("\nUpcoming Birthdays:\n");
    for (int i = 0; i < birthday_count; i++) {
        printf("%d. %s - %02d/%02d\n", i + 1, birthdays[i].name, birthdays[i].day, birthdays[i].month);
    }
    printf("\n");
}

// Function to check if a birthday is today
void check_today_birthday() {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    int today_day = tm_info->tm_mday;
    int today_month = tm_info->tm_mon + 1; // tm_mon is 0-based (0 = January)

    for (int i = 0; i < birthday_count; i++) {
        if (birthdays[i].day == today_day && birthdays[i].month == today_month) {
            printf("Today is %s's birthday!\n", birthdays[i].name);
            return;
        }
    }
    printf("No birthdays today.\n");
}

int main() {
    ToDoList todo_list = { .task_count = 0 };
    char input[256];
    char password[256];

    // Password Authentication
    printf("Enter password to access the To-Do List: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    if (strcmp(password, PASSWORD) != 0) {
        printf("Incorrect password. Access denied.\n");
        return 1;
    }

    int choice;
    do {
        printf("\n1. Add Task\n");
        printf("2. Delete Task\n");
        printf("3. Display Tasks\n");
        printf("4. Add Birthday\n");
        printf("5. Display Birthdays\n");
        printf("6. Check Today's Birthday\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        switch (choice) {
            case 1:
                printf("Enter task: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0; // Remove newline character
                add_task(&todo_list, input);
                break;
            case 2:
                printf("Enter task number to delete: ");
                int task_num;
                scanf("%d", &task_num);
                delete_task(&todo_list, task_num - 1); // Convert to zero-based index
                break;
            case 3:
                display_tasks(&todo_list);
                break;
            case 4:
                add_birthday();
                break;
            case 5:
                display_birthdays();
                break;
            case 6:
                check_today_birthday();
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}
