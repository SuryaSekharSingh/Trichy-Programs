#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

// Structure for inventory node
typedef struct InventoryNode {
    int product_id;
    char product_name[MAX_NAME_LEN];
    float price;
    int bought_count;
    struct InventoryNode* next;
} InventoryNode;

// Create a new inventory node
InventoryNode* create_node(int product_id, const char* product_name, float price) {
    InventoryNode* new_node = (InventoryNode*)malloc(sizeof(InventoryNode));
    new_node->product_id = product_id;
    strcpy(new_node->product_name, product_name);
    new_node->price = price;
    new_node->bought_count = 0;
    new_node->next = NULL;
    return new_node;
}

// Insert node at the end of the inventory
void insert_node(InventoryNode** head, int product_id, const char* product_name, float price) {
    InventoryNode* new_node = create_node(product_id, product_name, price);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    InventoryNode* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

// Delete a node from the inventory based on product ID
void delete_node(InventoryNode** head, int product_id) {
    InventoryNode* temp = *head, *prev = NULL;
    if (temp != NULL && temp->product_id == product_id) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->product_id != product_id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    prev->next = temp->next;
    free(temp);
}

// Search for a node by product ID and increment the bought count
InventoryNode* search_node(InventoryNode* head, int product_id) {
    while (head != NULL) {
        if (head->product_id == product_id) {
            head->bought_count++;
            printf("Product Found: %s, Price: %.2f, Bought %d times\n", head->product_name, head->price, head->bought_count);
            return head;
        }
        head = head->next;
    }
    printf("Product not found.\n");
    return NULL;
}

// Display the inventory
void display_inventory(InventoryNode* head) {
    printf("\nInventory:\n");
    while (head != NULL) {
        printf("Product ID: %d, Name: %s, Price: %.2f, Bought: %d times\n", head->product_id, head->product_name, head->price, head->bought_count);
        head = head->next;
    }
}

// Display the most frequently bought products
void analyze_inventory(InventoryNode* head) {
    printf("\nMost Frequently Bought Products:\n");
    int max_bought = 0;
    InventoryNode* temp = head;
    
    // Find the maximum bought count
    while (temp != NULL) {
        if (temp->bought_count > max_bought) {
            max_bought = temp->bought_count;
        }
        temp = temp->next;
    }
    
    // Display products with the maximum bought count
    temp = head;
    while (temp != NULL) {
        if (temp->bought_count == max_bought && max_bought > 0) {
            printf("Product ID: %d, Name: %s, Bought: %d times\n", temp->product_id, temp->product_name, temp->bought_count);
        }
        temp = temp->next;
    }
}

int main() {
    InventoryNode* inventory = NULL;

    // Insert 10 products into the inventory
    insert_node(&inventory, 1, "Laptop", 799.99);
    insert_node(&inventory, 2, "Phone", 599.99);
    insert_node(&inventory, 3, "Tablet", 299.99);
    insert_node(&inventory, 4, "Headphones", 49.99);
    insert_node(&inventory, 5, "Keyboard", 29.99);
    insert_node(&inventory, 6, "Mouse", 19.99);
    insert_node(&inventory, 7, "Monitor", 199.99);
    insert_node(&inventory, 8, "Printer", 89.99);
    insert_node(&inventory, 9, "Camera", 249.99);
    insert_node(&inventory, 10, "Speakers", 59.99);

    // Display inventory
    display_inventory(inventory);

    // Search products and increment bought count
    search_node(inventory, 1); // Searching Laptop
    search_node(inventory, 2); // Searching Phone
    search_node(inventory, 1); // Searching Laptop again
    search_node(inventory, 5); // Searching Keyboard

    // Analyze and display the most frequently bought products
    analyze_inventory(inventory);

    // Delete a product
    delete_node(&inventory, 3); // Delete Tablet

    // Display inventory after deletion
    display_inventory(inventory);

    return 0;
}