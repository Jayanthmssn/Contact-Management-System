
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a contact node
struct Node {
    int id;
    char name[50];
    char phone[15];

    struct Node *left;
    struct Node *right;
};

// Create a new contact
struct Node* createNode(int id, char name[], char phone[]) {

    struct Node *newNode =
        (struct Node*)malloc(sizeof(struct Node));

    newNode->id = id;

    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Insert a contact into BST
struct Node* insert(struct Node *root,
                    int id, char name[], char phone[]) {

    if (root == NULL) {
        return createNode(id, name, phone);
    }

    if (id < root->id) {
        root->left = insert(root->left, id, name, phone);
    }
    else if (id > root->id) {
        root->right = insert(root->right, id, name, phone);
    }
    else {
        printf("Contact ID already exists!\n");
    }

    return root;
}

// Search for a contact
struct Node* search(struct Node *root, int id) {

    if (root == NULL || root->id == id) {
        return root;
    }

    if (id < root->id) {
        return search(root->left, id);
    }
    else {
        return search(root->right, id);
    }
}

// Find minimum node
struct Node* findMin(struct Node *root) {

    while (root != NULL && root->left != NULL) {
        root = root->left;
    }

    return root;
}

// Delete a contact
struct Node* deleteNode(struct Node *root, int id) {

    if (root == NULL) {
        return NULL;
    }

    if (id < root->id) {
        root->left = deleteNode(root->left, id);
    }
    else if (id > root->id) {
        root->right = deleteNode(root->right, id);
    }
    else {

        // Node has no left child
        if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }

        // Node has no right child
        else if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        // Node has two children
        struct Node *temp = findMin(root->right);

        root->id = temp->id;
        strcpy(root->name, temp->name);
        strcpy(root->phone, temp->phone);

        root->right = deleteNode(root->right, temp->id);
    }

    return root;
}

// Display contacts using inorder traversal
void display(struct Node *root) {

    if (root != NULL) {

        display(root->left);

        printf("%-10d %-20s %-15s\n",
               root->id, root->name, root->phone);

        display(root->right);
    }
}

// Main function
int main() {

    struct Node *root = NULL;

    int choice, id;
    char name[50], phone[15];

    while (1) {

        printf("\n===== CONTACT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Delete Contact\n");
        printf("4. Display All Contacts\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:

                printf("Enter Contact ID: ");
                scanf("%d", &id);

                if (search(root, id) != NULL) {
                    printf("Contact ID already exists!\n");
                    break;
                }

                printf("Enter Name: ");
                scanf(" %49[^\n]", name);

                printf("Enter Phone Number: ");
                scanf("%14s", phone);

                root = insert(root, id, name, phone);

                printf("Contact added successfully!\n");
                break;

            case 2:

                printf("Enter Contact ID to search: ");
                scanf("%d", &id);

                struct Node *found;
                found = search(root, id);

                if (found != NULL) {

                    printf("\nContact Found!\n");
                    printf("ID: %d\n", found->id);
                    printf("Name: %s\n", found->name);
                    printf("Phone: %s\n", found->phone);

                }
                else {
                    printf("Contact not found!\n");
                }

                break;

            case 3:

                printf("Enter Contact ID to delete: ");
                scanf("%d", &id);

                if (search(root, id) != NULL) {

                    root = deleteNode(root, id);
                    printf("Contact deleted successfully!\n");

                }
                else {
                    printf("Contact not found!\n");
                }

                break;

            case 4:

                if (root == NULL) {
                    printf("No contacts available!\n");
                }
                else {

                    printf("\nID        Name                 Phone\n");
                    printf("-----------------------------------------------\n");

                    display(root);
                }

                break;

            case 5:

                printf("Exiting Contact Management System.\n");
                return 0;

            default:

                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
