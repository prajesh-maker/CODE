#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define PASSWORD "C.PROJECT-1" // Change this to a more secure password

typedef struct {
    char tasks[MAX_TASKS][256];
    int task_count;
} ToDoList;

void display_tasks(ToDoList *list) {
    printf("\nYour To-Do List:\n");
    for (int i = 0; i < list->task_count; i++) {
        printf("%d. %s\n", i + 1, list->tasks[i]);
    }
    printf("\n");
}

void add_task(ToDoList *list, const char *task) {
    if (list->task_count < MAX_TASKS) {
        strcpy(list->tasks[list->task_count], task);
        list->task_count++;
        printf("Task added: %s\n", task);
    } else {
        printf("Task limit reached. Cannot add more tasks.\n");
    }
}

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
        printf("4. Exit\n");
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
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}