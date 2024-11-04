#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100

// Structure to represent a menu item
typedef struct {
    char name[50];
    float price;
} MenuItem;

// Structure to represent an order item
typedef struct {
    MenuItem item;
    int quantity;
} OrderItem;

// Function prototypes
void displayMenu(MenuItem menu[], int size);
void addOrder(OrderItem order[], int *orderCount, MenuItem menu[], int menuSize);
void printBill(OrderItem order[], int orderCount);

int main() {
    MenuItem menu[] = {
        {"Burger", 115},
        {"Pizza", 100},
        {"Pasta", 169},
        {"Salad", 205},
        {"Soda", 73}
    };
    int menuSize = sizeof(menu) / sizeof(menu[0]);

    OrderItem order[MAX_ITEMS];
    int orderCount = 0;
    int choice;

    do {
        printf("\nRestaurant Billing Software\n");
        printf("1. Display Menu\n");
        printf("2. Add Order\n");
        printf("3. Print Bill\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayMenu(menu, menuSize);
                break;
            case 2:
                addOrder(order, &orderCount, menu, menuSize);
                break;
            case 3:
                printBill(order, orderCount);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

// Function to display the menu
void displayMenu(MenuItem menu[], int size) {
    printf("\nMenu:\n");
    for (int i = 0; i < size; i++) {
        printf("%d. %s - ₹%.2f\n", i + 1, menu[i].name, menu[i].price);
    }
}

// Function to add an order
void addOrder(OrderItem order[], int *orderCount, MenuItem menu[], int menuSize) {
    int itemNumber, quantity;

    displayMenu(menu, menuSize);
    printf("Enter item number to order: ");
    scanf("%d", &itemNumber);

    if (itemNumber < 1 || itemNumber > menuSize) {
        printf("Invalid item number!\n");
        return;
    }

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    order[*orderCount].item = menu[itemNumber - 1];
    order[*orderCount].quantity = quantity;
    (*orderCount)++;
    printf("Item added to order!\n");
}

// Function to print the bill
void printBill(OrderItem order[], int orderCount) {
    float total = 0.0;
    printf("\nBill:\n");
    for (int i = 0; i < orderCount; i++) {
        float itemTotal = order[i].item.price * order[i].quantity;
        printf("%s x %d = ₹%.2f\n", order[i].item.name, order[i].quantity, itemTotal);
        total += itemTotal;
    }
    printf("Total: $%.2f\n", total);
}