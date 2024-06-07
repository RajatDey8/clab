#include <stdio.h>
#include <stdlib.h>

// Date structure definition
typedef struct {
    int day;
    int month;
    int year;
} Date;

// Function to check the number of days in a month
int days_in_month(int month, int year) {
    static const int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        return 29; // February in a leap year
    }
    return days_in_month[month - 1];
}

// Function to add days to a date
void add_days(Date *date, int days) {
    date->day += days;
    while (date->day > days_in_month(date->month, date->year)) {
        date->day -= days_in_month(date->month, date->year);
        date->month++;
        if (date->month > 12) {
            date->month = 1;
            date->year++;
        }
    }
}

// Function to print a date
void print_date(Date date) {
    printf("%04d-%02d-%02d\n", date.year, date.month, date.day);
}

// Queue node structure
typedef struct QueueNode {
    Date date;
    struct QueueNode *next;
} QueueNode;

// Queue structure
typedef struct {
    QueueNode *front;
    QueueNode *rear;
} Queue;

// Function to create a queue
Queue* create_queue() {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Function to add a date to the queue
void enqueue(Queue *queue, Date date) {
    QueueNode *new_node = (QueueNode*)malloc(sizeof(QueueNode));
    new_node->date = date;
    new_node->next = NULL;
    if (queue->rear == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

// Function to remove a date from the queue
Date dequeue(Queue *queue) {
    if (queue->front == NULL) {
        printf("Queue is empty\n");
        exit(1);
    }
    QueueNode *temp = queue->front;
    Date date = temp->date;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return date;
}

// Function to check if the queue is empty
int is_empty(Queue *queue) {
    return queue->front == NULL;
}

// Function to update each date in the queue by adding 3 days
void update_dates(Queue *queue) {
    QueueNode *current = queue->front;
    while (current != NULL) {
        add_days(&current->date, 3);
        current = current->next;
    }
}

// Function to find and display the most recent date in the queue
Date find_most_recent_date(Queue *queue) {
    if (is_empty(queue)) {
        printf("Queue is empty\n");
        exit(1);
    }

    Date most_recent_date = queue->front->date;
    QueueNode *current = queue->front->next;

    while (current != NULL) {
        if (current->date.year > most_recent_date.year ||
           (current->date.year == most_recent_date.year && current->date.month > most_recent_date.month) ||
           (current->date.year == most_recent_date.year && current->date.month == most_recent_date.month && current->date.day > most_recent_date.day)) {
            most_recent_date = current->date;
        }
        current = current->next;
    }

    return most_recent_date;
}

// Main function to demonstrate the Date ADT and queue operations
int main() {
    Queue *queue = create_queue();
    
    // Example dates
    Date date1 = {1, 6, 2023};
    Date date2 = {5, 6, 2023};
    Date date3 = {30, 5, 2023};
    Date date4 = {3, 6, 2023};
    
    // Enqueue dates
    enqueue(queue, date1);
    enqueue(queue, date2);
    enqueue(queue, date3);
    enqueue(queue, date4);
    
    printf("Original Dates:\n");
    QueueNode *current = queue->front;
    while (current != NULL) {
        print_date(current->date);
        current = current->next;
    }
    
    // Update dates by adding 3 days
    update_dates(queue);
    
    printf("\nUpdated Dates:\n");
    current = queue->front;
    while (current != NULL) {
        print_date(current->date);
        current = current->next;
    }
    
    // Find and print the most recent date
    Date most_recent_date = find_most_recent_date(queue);
    printf("\nMost Recent Date:\n");
    print_date(most_recent_date);
    
    return 0;
}
