#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_PHONE_LEN 15

// Structure for phonebook node
typedef struct PhonebookNode {
    int cno;
    char name[MAX_NAME_LEN];
    char phone[MAX_PHONE_LEN];
    int search_count;
    struct PhonebookNode* next;
} PhonebookNode;

// Structure for favorites list node
typedef struct FavoriteNode {
    char name[MAX_NAME_LEN];
    struct FavoriteNode* next;
} FavoriteNode;

// Create a new phonebook node
PhonebookNode* create_phonebook_node(int cno, const char* name, const char* phone) {
    PhonebookNode* new_node = (PhonebookNode*)malloc(sizeof(PhonebookNode));
    new_node->cno = cno;
    strcpy(new_node->name, name);
    strcpy(new_node->phone, phone);
    new_node->search_count = 0;
    new_node->next = NULL;
    return new_node;
}

// Insert a node in the phonebook
void insert_phonebook(PhonebookNode** head, int cno, const char* name, const char* phone) {
    PhonebookNode* new_node = create_phonebook_node(cno, name, phone);
    new_node->next = *head;
    *head = new_node;
}

// Display the phonebook
void display_phonebook(PhonebookNode* head) {
    while (head) {
        printf("CNo: %d, Name: %s, Phone: %s, Searched: %d times\n", head->cno, head->name, head->phone, head->search_count);
        head = head->next;
    }
}

// Search for a customer by CNo and increment search count
PhonebookNode* search_phonebook(PhonebookNode* head, int cno) {
    while (head) {
        if (head->cno == cno) {
            head->search_count++;
            printf("Customer Found: %s, Phone: %s\n", head->name, head->phone);
            return head;
        }
        head = head->next;
    }
    printf("Customer not found.\n");
    return NULL;
}

// Add customer to the favorites list if searched more than once
void add_to_favorites(PhonebookNode* customer, FavoriteNode** fav_head) {
    if (customer->search_count > 1) {
        FavoriteNode* fav = (FavoriteNode*)malloc(sizeof(FavoriteNode));
        strcpy(fav->name, customer->name);
        fav->next = *fav_head;
        *fav_head = fav;
        printf("Added to Favorites: %s\n", customer->name);
    }
}

// Display the favorites list
void display_favorites(FavoriteNode* head) {
    printf("\nFavorites:\n");
    while (head) {
        printf("Customer Name: %s\n", head->name);
        head = head->next;
    }
}

int main() {
    PhonebookNode* phonebook = NULL;
    FavoriteNode* favorites = NULL;

    // Insert customers
    insert_phonebook(&phonebook, 1, "Alice", "1234567890");
    insert_phonebook(&phonebook, 2, "Bob", "2345678901");
    insert_phonebook(&phonebook, 3, "Charlie", "3456789012");

    // Display phonebook
    printf("Phonebook:\n");
    display_phonebook(phonebook);

    // Search and add to favorites
    PhonebookNode* customer = search_phonebook(phonebook, 1);
    if (customer) add_to_favorites(customer, &favorites);
    
    customer = search_phonebook(phonebook, 1); // Searching Alice again
    if (customer) add_to_favorites(customer, &favorites); // Alice added to favorites

    // Display updated phonebook and favorites list
    printf("\nUpdated Phonebook:\n");
    display_phonebook(phonebook);
    display_favorites(favorites);

    return 0;
}