#include <stdio.h>
#include <stdlib.h>

typedef struct Date {
    int year;
    int month;
    int day;
} Date;

typedef struct TreeNode {
    Date date;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to create a new Date
Date createDate(int year, int month, int day) {
    Date newDate;
    newDate.year = year;
    newDate.month = month;
    newDate.day = day;
    return newDate;
}

// Function to add days to a Date
void addDays(Date* date, int days) {
    // Simplistic way to add days; does not handle month/year overflow correctly.
    date->day += days;
    // Here, a full implementation should handle the overflow of days correctly
}

// Function to create a new TreeNode
TreeNode* createTreeNode(Date date) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->date = date;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a Date into the BinaryTree
TreeNode* insert(TreeNode* root, Date date) {
    if (root == NULL) {
        return createTreeNode(date);
    }
    if (date.year < root->date.year || 
        (date.year == root->date.year && date.month < root->date.month) || 
        (date.year == root->date.year && date.month == root->date.month && date.day < root->date.day)) {
        root->left = insert(root->left, date);
    } else {
        root->right = insert(root->right, date);
    }
    return root;
}

// Function to update all dates in the tree by adding a certain number of days
void updateDates(TreeNode* root, int days) {
    if (root != NULL) {
        addDays(&root->date, days);
        updateDates(root->left, days);
        updateDates(root->right, days);
    }
}

// Function for preorder traversal of the tree
void preorderTraversal(TreeNode* root) {
    if (root != NULL) {
        printf("%04d-%02d-%02d\n", root->date.year, root->date.month, root->date.day);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Main function to test the implementation
int main() {
    TreeNode* root = NULL;
    
    // Create date objects
    Date date1 = createDate(2023, 1, 10);
    Date date2 = createDate(2023, 5, 15);
    Date date3 = createDate(2023, 3, 22);
    Date date4 = createDate(2023, 7, 30);
    Date date5 = createDate(2023, 2, 18);
    
    // Insert dates into the binary tree
    root = insert(root, date1);
    root = insert(root, date2);
    root = insert(root, date3);
    root = insert(root, date4);
    root = insert(root, date5);
    
    // Update each date by adding 3 days
    updateDates(root, 3);
    
    // Display the updated dates using preorder traversal
    printf("Updated dates (Preorder Traversal):\n");
    preorderTraversal(root);
    
    return 0;
}
