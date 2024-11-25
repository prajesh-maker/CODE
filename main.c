#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define TASK_LENGTH 256

// Structure to hold a task
typedef struct {
    char description[TASK_LENGTH];
} Task;

// Function declarations
void addTask(Task tasks[], int *taskCount);
void viewTasks(Task tasks[], int taskCount);
void deleteTask(Task tasks[], int *taskCount);

int main() {
    Task tasks[MAX_TASKS];
    int taskCount = 0;
    int choice;

    while (1) {
        printf("\nTo-Do List Menu:\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Delete Task\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        switch (choice) {
            case 1:
                addTask(tasks, &taskCount);
                break;
            case 2:
                viewTasks(tasks, taskCount);
                break;
            case 3:
                deleteTask(tasks, &taskCount);
                break;
            case 4:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function to add a task
void addTask(Task tasks[], int *taskCount) {
    if (*taskCount >= MAX_TASKS) {
        printf("Task list is full! Cannot add more tasks.\n");
        return;
    }
    printf("Enter the task description: ");
    fgets(tasks[*taskCount].description, TASK_LENGTH, stdin);
    tasks[*taskCount].description[strcspn(tasks[*taskCount].description, "\n")] = '\0'; // Remove newline
    (*taskCount)++;
    printf("Task added successfully!\n");
}

// Function to view all tasks
void viewTasks(Task tasks[], int taskCount) {
    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }
    printf("\nTo-Do List:\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d. %s\n", i + 1, tasks[i].description);
    }
}

// Function to delete a task
void deleteTask(Task tasks[], int *taskCount) {
    if (*taskCount == 0) {
        printf("No tasks available to delete.\n");
        return;
    }
    int taskNumber;
    printf("Enter the task number to delete: ");
    scanf("%d", &taskNumber);
    getchar(); // Consume the newline character

    if (taskNumber < 1 || taskNumber > *taskCount) {
        printf("Invalid task number!\n");
        return;
    }

    // Shift tasks down to fill the gap
    for (int i = taskNumber - 1; i < *taskCount - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
    (*taskCount)--;
    printf("Task deleted successfully!\n");
}