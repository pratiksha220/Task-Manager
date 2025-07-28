#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Task {
    int id;
    char description[100];
    struct Task* next;
};

struct Task* createTask(int id) {
    struct Task* newTask = (struct Task*)malloc(sizeof(struct Task));
    newTask->id = id;
    printf("Enter task description: ");
    scanf(" %[^\n]s", newTask->description);  // Fix for reading full line
    newTask->next = NULL;
    return newTask;
}

void addTask(struct Task** head, int id) {
    struct Task* newTask = createTask(id);
    if (*head == NULL) {
        *head = newTask;
    } else {
        struct Task* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newTask;
    }
    printf("Task added successfully!\n");
}

void displayTasks(struct Task* head) {
    int count = 1;
    if (head == NULL) {
        printf("No tasks to display.\n");
        return;
    }
    printf("\n-- Task List --\n");
    while (head != NULL) {
        printf("Task %d: [ID: %d] %s\n", count++, head->id, head->description);
        head = head->next;
    }
}

void searchTask(struct Task* head, int id) {
    while (head != NULL) {
        if (head->id == id) {
            printf("Task Found: [ID: %d] %s\n", head->id, head->description);
            return;
        }
        head = head->next;
    }
    printf("Task with ID %d not found.\n", id);
}

void deleteTask(struct Task** head, int id) {
    struct Task* temp = *head, *prev = NULL;
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Task not found.\n");
        return;
    }
    if (prev == NULL)
        *head = temp->next;
    else
        prev->next = temp->next;
    free(temp);
    printf("Task deleted successfully.\n");
}

int main() {
    struct Task* head = NULL;
    int choice, id;

    do {
        printf("\n==== Task Manager ====\n");
        printf("1. Add Task\n2. Display Tasks\n3. Search Task\n4. Delete Task\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Task ID: ");
                scanf("%d", &id);
                addTask(&head, id);
                break;
            case 2:
                displayTasks(head);
                break;
            case 3:
                printf("Enter Task ID to search: ");
                scanf("%d", &id);
                searchTask(head, id);
                break;
            case 4:
                printf("Enter Task ID to delete: ");
                scanf("%d", &id);
                deleteTask(&head, id);
                break;
            case 5:
                printf("Exiting Task Manager.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
