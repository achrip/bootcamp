#include <sys/utsname.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Main Fucntionals
void menu();
void addDish();
void removeDish();
void addCust();
void searchCust();
void view();
void order();
void payment();
void bye();

// Structs
typedef struct dish{
    char name[255];
    int price;
    int quantity;
    struct dish* next;
} Dish;

Dish* head = NULL;
Dish* tail = NULL;

// Other Functionals
void showInfo();
Dish* dish_add(const char *name, int price, int qty);
Dish* dish_insert(const char *name, int price, int qty);
void dish_print();
int dish_is_empty();



int main()
{
    menu();

    return 0;
}

void showInfo() {
    struct utsname info;
    time_t currentTime;
    struct tm *localTime;

    uname(&info);
    time(&currentTime);

    localTime = localtime(&currentTime);

    char dateTimeString[100];
    strftime(dateTimeString, 100, "%A %B %d %I:%M:%S %Y", localTime);
    printf("System: %s\n", info.sysname);
    printf("The current date and time is: %s\n", dateTimeString);
}

Dish* dish_add(const char *name, int price, int qty) {
    Dish* new = (Dish*) malloc(sizeof(Dish));
    strcpy(new->name, name);
    new->price = price;
    new->quantity = qty;
    new->next = NULL;
}

Dish* dish_insert(const char *name, int price, int qty) {
    Dish* new = dish_add(name, price, qty);

    if (!head) head = tail = new;
    else if (head->price < price) {
        new->next = head->next;
        head = new;
    }
    else if (tail->price > price) {
        tail->next = new;
        tail = new;
    }
    else {
        Dish* curr = head;
        while (curr->next && curr->next->price > price) curr = curr->next;
        new->next = curr->next;
        curr->next = new;
    }
}

int dish_is_empty() {
    return head == NULL; 
}

void dish_print() {
    if (dish_is_empty()) {
        printf("Error: There's no dish available!\n");
        return;
    }

    Dish* d = head;
    int count = 1;
    while (d) {
        printf("%-5d %-15s %-10d Rp%-10d\n", count, d->name,
                d->quantity, d->quantity);
        ++count;
        d = d->next;
    }

}
void menu() {
    int choose;
    showInfo();
    printf("1. Add Dish\n2. Remove Dish\n3. Add Customer\n4. Search Customer\n");
    printf("5. View Warteg\n6. Order\n7. Payment\n8. Exit Warteg\n>> ");
    scanf("%d", &choose);
    getchar();

    switch (choose) {
        case 1:
            addDish();
            break;
        case 2:
            removeDish();
            break;
        case 3:
            addCust();
            break;
        case 4:
            searchCust();
            break;
        case 5:
            view();
            break;
        case 6:
            order();
            break;
        case 7:
            payment();
            break;
        case 8:
            bye();
            break;
        default:
            break;
    }
}

void addDish() {
    char name[255];
    int price, qty, flag;

    do {
        printf("Insert the name of the dish [Lowercase letters]: ");
        scanf("%s", name);
        getchar();
        
        flag = 0; 
        for (int i = 0; i < strlen(name); i++) {
            if (isupper(name[i])) {
                flag = 1;
                break;
            }
        }
    } while (flag);

    do {
        printf("Insert the price of the dish [1000..50000]: ");
        scanf("%d", &price);
        getchar();

        flag = 0;
        if (price < 1000 || price > 50000) flag = 1;
    } while (flag);

    do {
        printf("Insert the quantity of the dish [1..999]: ");
        scanf("%d", &qty);
        getchar(); 

        flag = 0;
        if (qty < 1 || qty > 999) flag = 1;
    } while (flag);

    /*add the new dish to the linked list*/
    dish_insert(name, price, qty);

    // done
    printf("The dish has been added!\n");
    printf("Press enter to continue...\n");
    getchar();
}

void removeDish() {
    printf("\tBude's Menu\n=====================================\n");
    printf("%-5s %-15s %-10s %-10s\n", "No.", "Name", "Quantity", "Price");
    dish_print();
    printf("=====================================\n",
            "Insert dish's name to be deleted: ");
    char name[255]; 
    scanf("%s", name);
    getchar();

    // search and delete said food

    printf("The dish has been removed!\n");
    printf("Press enter to continue..."); 
    getchar();   
}
void addCust() {}
void searchCust() {}
void view() {}
void order() {}
void payment() {}
void bye() {
    exit(0);
}
