#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Node structure for the polynomial linked list
typedef struct PolyNode {
    int coeff; // Coefficient
    int exp;   // Exponent
    struct PolyNode* next;
} PolyNode;

// Function to create a new node
PolyNode* create_node(int coeff, int exp) {
    PolyNode* new_node = (PolyNode*)malloc(sizeof(PolyNode));
    new_node->coeff = coeff;
    new_node->exp = exp;
    new_node->next = NULL;
    return new_node;
}

// Function to insert a node in descending order of exponents
void insert_node(PolyNode** head, int coeff, int exp) {
    PolyNode* new_node = create_node(coeff, exp);
    if (*head == NULL || (*head)->exp < exp) {
        new_node->next = *head;
        *head = new_node;
    } else {
        PolyNode* temp = *head;
        while (temp->next != NULL && temp->next->exp > exp) {
            temp = temp->next;
        }
        new_node->next = temp->next;
        temp->next = new_node;
    }
}

// Function to print the polynomial
void print_polynomial(PolyNode* head) {
    PolyNode* temp = head;
    while (temp != NULL) {
        if (temp->coeff > 0 && temp != head) {
            printf(" + ");
        }
        if (temp->exp == 0) {
            printf("%d", temp->coeff);
        } else {
            printf("%dx^%d", temp->coeff, temp->exp);
        }
        temp = temp->next;
    }
    printf("\n");
}

// Function to add two polynomials
PolyNode* add_polynomials(PolyNode* p1, PolyNode* p2) {
    PolyNode* result = NULL;
    while (p1 != NULL && p2 != NULL) {
        if (p1->exp == p2->exp) {
            int sum_coeff = p1->coeff + p2->coeff;
            if (sum_coeff != 0) {
                insert_node(&result, sum_coeff, p1->exp);
            }
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1->exp > p2->exp) {
            insert_node(&result, p1->coeff, p1->exp);
            p1 = p1->next;
        } else {
            insert_node(&result, p2->coeff, p2->exp);
            p2 = p2->next;
        }
    }

    // Insert remaining terms from p1
    while (p1 != NULL) {
        insert_node(&result, p1->coeff, p1->exp);
        p1 = p1->next;
    }

    // Insert remaining terms from p2
    while (p2 != NULL) {
        insert_node(&result, p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

// Function to evaluate the polynomial for a given value of x
int evaluate_polynomial(PolyNode* poly, int x) {
    int result = 0;
    while (poly != NULL) {
        result += poly->coeff * (int)pow(x, poly->exp);
        poly = poly->next;
    }
    return result;
}

int main() {
    PolyNode* P = NULL;
    PolyNode* Q = NULL;

    // P(x) = 4x^3 + 3x^2 - 2x + 7
    insert_node(&P, 4, 3);
    insert_node(&P, 3, 2);
    insert_node(&P, -2, 1);
    insert_node(&P, 7, 0);

    // Q(x) = -13x^3 + 9x^2 + 2x + 1
    insert_node(&Q, -13, 3);
    insert_node(&Q, 9, 2);
    insert_node(&Q, 2, 1);
    insert_node(&Q, 1, 0);

    printf("Polynomial P(x): ");
    print_polynomial(P);
    
    printf("Polynomial Q(x): ");
    print_polynomial(Q);

    // Add the two polynomials
    PolyNode* sum = add_polynomials(P, Q);
    printf("\nSum of P(x) and Q(x): ");
    print_polynomial(sum);

    // Evaluate the polynomial for a given x
    int x = 2;
    int eval = evaluate_polynomial(sum, x);
    printf("\nP(x) + Q(x) evaluated at x = %d is: %d\n", x, eval);

    return 0;
}