#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for product node
struct node {
    int ID;
    char proName[100];
    double prePrice;
    int quantity;
    struct node* next;
};

struct node* head = NULL;

// Function prototypes
void addProduct();
void displayProducts();
void modifyProduct();
void deleteProduct();
void buyProduct();
void returnProduct();
int searchProduct(int);

// Main function
int main() {
    int choice;
    while (1) {
        printf("\n================ SuperMarket Management System ================\n");
        printf("1. Shopkeeper Portal\n");
        printf("2. Customer Portal\n");
        printf("0. Exit\n");
        printf("===============================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                while (1) {
                    printf("\n================ Shopkeeper Menu ================\n");
                    printf("1. Add a new product\n");
                    printf("2. Display all products\n");
                    printf("3. Modify a product\n");
                    printf("4. Delete a product\n");
                    printf("0. Back\n");
                    printf("===============================================\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1: addProduct(); break;
                        case 2: displayProducts(); break;
                        case 3: modifyProduct(); break;
                        case 4: deleteProduct(); break;
                        case 0: goto mainMenu;
                        default: printf("Invalid choice! Try again.\n");
                    }
                }
            case 2:
                while (1) {
                    printf("\n================ Customer Menu ================\n");
                    printf("1. Buy a product\n");
                    printf("2. Return a product\n");
                    printf("0. Back\n");
                    printf("==============================================\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
                    

                    switch (choice) {
                        case 1: buyProduct(); break;
                        case 2: returnProduct(); break;
                        case 0: goto mainMenu;
                        default: printf("Invalid choice! Try again.\n");
                    }
                }
            case 0:
                printf("Thank you for using SuperMarket Management System!\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
        mainMenu:;
    }
}

// Function to add a product
void addProduct() {
    struct node* t = (struct node*)malloc(sizeof(struct node));
    if (t == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Product ID: ");
    scanf("%d", &t->ID);
    printf("Enter Product Name: ");
    scanf("%s", t->proName);
    printf("Enter Product Price: ");
    scanf("%lf", &t->prePrice);
    printf("Enter Product Quantity: ");
    scanf("%d", &t->quantity);

    t->next = head;
    head = t;


    printf("\nProduct successfully added to the inventory!\n");
}

// Function to display all products
void displayProducts() {
    if (head == NULL) {
        printf("\nNo products available!\n");
        return;
    }

    struct node* p = head;
    printf("\n================ Product List ================\n");
    printf("ID\tName\t\tPrice\t\tQuantity\n");
    printf("==============================================\n");

    while (p != NULL) {
        printf("%d\t%s\t\t%.2lf\t\t%d\n", p->ID, p->proName, p->prePrice, p->quantity);
        p = p->next;
    }
}

// Function to modify a product
void modifyProduct() {
    if (head == NULL) {
        printf("\nNo products available to modify!\n");
        return;
    }

    int id;
    printf("Enter Product ID to modify: ");
    scanf("%d", &id);

    struct node* cur = head;
    while (cur != NULL) {
        if (cur->ID == id) {
            printf("\nOld Name: %s", cur->proName);
            printf("\nOld Price: %.2lf\n", cur->prePrice);

            printf("Enter new Product Name: ");
            scanf("%s", cur->proName);
            printf("Enter new Product Price: ");
            scanf("%lf", &cur->prePrice);
            
            printf("\nProduct modified successfully!\n");
            return;
        }
        cur = cur->next;
    }
    printf("\nProduct not found!\n");
}

// Function to delete a product
void deleteProduct() {
    if (head == NULL) {
        printf("\nNo products available to delete!\n");
        return;
    }

    int id;
    printf("Enter Product ID to delete: ");
    scanf("%d", &id);

    struct node *cur = head, *prev = NULL;
    while (cur != NULL && cur->ID != id) {
        prev = cur;
        cur = cur->next;
    }

    if (cur == NULL) {
        printf("\nProduct not found!\n");
        return;
    }

    if (prev == NULL) 
        head = cur->next;
    else
        prev->next = cur->next;

    free(cur);

    printf("\nProduct deleted successfully!\n");
}

// Function to buy a product
void buyProduct() {
    if (head == NULL) {
        printf("\nNo products available to buy!\n");
        return;
    }

    int id, quant;
    printf("Enter Product ID to buy: ");
    scanf("%d", &id);

    struct node* cur = head;
    while (cur != NULL) {
        if (cur->ID == id) {
            printf("Enter quantity: ");
            scanf("%d", &quant);
            if (cur->quantity >= quant) {
                double total = cur->prePrice * quant;
                cur->quantity -= quant;
            
                printf("\nYou bought %d x %s for Rs. %.2lf\n", quant, cur->proName, total);
                return;
            } else {
                printf("\nNot enough stock available!\n");
                return;
            }
        }
        cur = cur->next;
    }
    printf("\nProduct not found!\n");
}

// Function to return a product
void returnProduct() {
    if (head == NULL) {
        printf("\nNo products available to return!\n");
        return;
    }

    int id, quant;
    printf("Enter Product ID to return: ");
    scanf("%d", &id);

    struct node* cur = head;
    while (cur != NULL) {
        if (cur->ID == id) {
            printf("Enter quantity to return: ");
            scanf("%d", &quant);
            cur->quantity += quant;
            printf("\nYou returned %d x %s. Refund processed!\n", quant, cur->proName);
            return;
        }
        cur = cur->next;
    }
    printf("\nProduct not found!\n");
}
