#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

typedef struct Cards{
    int state;
    char value;
    struct Cards *next;
}Card;

Card* create_node(char value){
    Card* p = (Card*)malloc(sizeof(Card));
    p->value = value;
    p->state = 0;
    p->next = NULL;
    return p;
}

void insert_node(Card** head, char value){
    Card* p = create_node(value);
    p->next = *head;
    *head = p;

}

void search_node(Card** head, int num1, int num2, int *count){
    Card *p = *head;
    int i = 1, n = (num1 > num2)?(num1):(num2);
    Card *c1, *c2;
    while(p && (i <= n)){
        if(i == num1){
            c1 = p;
            printf("loc(%d)-%c\tAND\t", i, p->value);
        }
        if(i == num2){
            c2 = p;
            printf("loc(%d)-%c   ", i, p->value);
        }
        i++;
    }
    p = p->next;
    if(c1->value == c2->value){
        c1->state = c2->state = 1;
        (*count)++;
        printf("Matched...\nTry Matching the rest...\n");
    }
    else{
        printf("Opps! No match! Try again...\n");
    }
}

void print_nodes(Card* head){
    printf("ALL THE CARDS ARE : \n");
    Card *p = head;
    while(p){
        printf("%c\t", p->value);
        p = p->next;
    }
    printf("\n");
}

int main(){
    int a, b, count=0;
    Card *head = NULL;
    insert_node(&head, '2');
    insert_node(&head, '5');
    insert_node(&head, 'A');
    insert_node(&head, 'K');
    
    insert_node(&head, '5');
    insert_node(&head, 'K');
    insert_node(&head, 'A');
    insert_node(&head, '2');

    print_nodes(head);

    while(1){
        printf("\nEnter two locations (1 to 8) : ");
        scanf("%d%d",&a, &b);
        search_node(&head, a, b, &count);
        if(count == 4){
            printf("\nCongratulation. All cards are matched...");
            print_nodes(head);
            break;
        }
    }
    return 0;
}