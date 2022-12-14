#include <sys/utsname.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define max_size 999

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
    struct dish* prev;
} Dish;

typedef struct customer{ 
    char name[255]; 

    // linked list customer
    struct customer* next; 
    struct customer* prev; 

    // customer has order and it can be expanded into a linked list
    struct dish* orderList; 
} Cust; 

Cust* table[max_size];
Dish* head = NULL;
Dish* tail = NULL; 

// Other Functionals
void showInfo();
Cust* customer_add(const char* name); 
void customer_insert(const char* name);
int customer_search(const char* name);
void customer_print();
Dish* dish_add(const char *name, int price, int qty);
void dish_insert(const char *name, int price, int qty);
void dish_print();
int dish_is_empty();
unsigned int hash_function(const char* s); 

int main()
{
    while(1) menu();

    return 0;
}

/*                  Initialization of Other Functionals                     */
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
    printf("%s\n", dateTimeString);
}

Dish* dish_add(const char *name, int price, int qty) {
    Dish* new = (Dish*) malloc(sizeof(Dish));
    strcpy(new->name, name);
    new->price = price;
    new->quantity = qty;
    new->next = NULL;
    new->prev = NULL;
}

void dish_insert(const char *name, int price, int qty) {
    Dish* new = dish_add(name, price, qty);

    if (!head) head = tail = new;
    else if (head->quantity <= qty) {
        new->next = head;
        head->prev = new; 
        head = new;
    }
    else if (tail->quantity >= qty) {
        tail->next = new;
        new->prev = tail;
        tail = new;
    }
    else {
        Dish* curr = head;
        while (curr->next->quantity >= qty) curr = curr->next;
        new->next = curr->next;
        new->prev = curr; 
        curr->next->prev = new; 
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
                d->quantity, d->price);
        ++count;
        d = d->next;
    }

}

int dish_remove(const char* name) {
    if (strcmp(head->name, name) == 0) {
        Dish* toRemove = head; 
        head = head->next;
        head->prev = NULL;  
        toRemove->next = NULL; 
        free(toRemove);
        return 0; 
    }
    else if (strcmp(tail->name, name) == 0) {
        Dish* toRemove = tail; 
        tail = tail->prev; 
        tail->next = NULL; 
        toRemove->prev = NULL; 
        free(toRemove);
        return 0; 
    }
    else {
        Dish* current = head; 

        while (strcmp(current->name, name) != 0) {
            if (current == tail) return 1; 
            current = current->next;
        } 
        current->next->prev = current->prev; 
        current->prev->next = current->next; 
        current->next = NULL; 
        current->prev = NULL; 
        free(current); 
        return 0; 
    }
}

unsigned int hash_function(const char* s) {
    unsigned int hash = 5381; 
    int c;

    // TODO: use XOR version if permitted
    while (c = *s++) hash = ((hash << 5) + hash) + c;  

    return hash % max_size;    
}

Cust* customer_add(const char* name) {
    Cust* new = (Cust*) malloc(sizeof(Cust)); 

    strcpy(new->name, name); 
    new->next = NULL;
    new->prev = NULL;  
    new->orderList = NULL; 

    return new; 
}

void customer_insert(const char* name) {
    Cust* new = customer_add(name); 

    unsigned int index = hash_function(name); 
    if (!table[index]) table[index] = new;
    else {
        Cust* p = table[index]; 
        
        while(p->next) p = p->next; 
        new->next = p->next; 
        p->next = new; 
        new->prev = p; 
    }
}

int customer_search(const char* name) {
    unsigned int index = hash_function(name); 

    if (!table[index]) return -1; 
    else { 
        Cust* p = table[index]; 

        while (p->next) {
            if (strcmp(p->name, name) == 0) return 0; 
            p = p->next; 
        }
    } 
    return -1; 
}

void customer_print() {
    for (int i = 0; i < max_size; i++) {
        if (!table[i]) continue; 

        printf("%d.", i); 
        for(Cust* p = table[i]; p != NULL; p = p->next){
            printf("%s", p->name); 
            if (p->next) printf("-->"); 
        }
        printf("\n"); 
    }
}

void customer_order(const char *name, int qty, const char* customer) {
    Dish* order = dish_add(name, NULL, qty); 
    
    unsigned int index = hash_function(customer); 

    Cust* c = table[index]; 
    if(!c->orderList) c->orderList = order; 
    else { 
        Dish* p = c->orderList; 
        while (p->next) p = p->next; 
        p->next = order; 
        order->prev = p; 
    } 
}


/*                      Initialization of Main Functionals                      */
void menu() {
    int choose;
    system("clear"); 
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
        scanf("%[^\n]", name);
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
    puts("The dish has been added!");
    printf("Press enter to continue...");
    getchar();
}

void removeDish() {
    puts("\t\tBude's Menu\n==========================================");
    printf("%-5s %-15s %-10s %-10s\n", "No.", "Name", "Quantity", "Price");
    dish_print();
    puts("==========================================\n");
    printf("Insert dish's name to be deleted: ");
    char name[255]; 
    scanf("%s", name);
    getchar();

    // search and delete said food
    if (dish_remove(name) == 0) puts("The dish has been removed!");
    else printf("There's no dish named %s!\n", name); 
    printf("Press enter to continue..."); 
    getchar();   
}

void addCust() {
    char name[255]; 
    int flag; 

    do {
        printf("Insert the customer's name [Without space]: ");
        scanf("%s", name); 
        getchar(); 

        flag = 0; 
        for (int i = 0; i < strlen(name); i++) {
            if(name[i] == ' ') {
                flag = 1; 
                break; 
            }
        }
    } while (flag); 

    // 
    customer_insert(name);  
    puts("Customer has been added"); 
    printf("Press enter to continue..."); 
    getchar(); 
}

void searchCust() {
    char name[255]; 
    printf("Insert the customer's name to be searched: ");
    scanf("%s", name); 
    getchar(); 
    
    if (customer_search(name) == 0) printf("%s is present.\n", name);
    else printf("%s is not present.\n", name); 
    printf("Press enter to continue..."); 
    getchar(); 
}

void view() {
    puts("Customer's List"); 
    customer_print(); 
    printf("Press enter to continue..."); 
    getchar(); 
}
void order() {
    char cust[255], name[255];  
    int dishes, qty; 

    printf("Insert the customer's name: "); 
    scanf("%s", cust); 
    getchar(); 

    printf("Insert the amount of dish: "); 
    scanf("%d", &dishes); 
    getchar(); 

    for (int i = 0; i < dishes; i++) {
        printf("[%d] Insert the dish's name and quantity: "); 
        scanf("%[^x]s %d", name, &qty);
        getchar();  

        customer_order(name, qty, cust); 
    }
    puts("Order success!"); 
    printf("Press enter to continue..."); 
    getchar(); 
}
void payment() {}
void bye() {
    puts("Please expand your terminal to full screen!"); 
    printf("Press enter to continue..."); 
    getchar(); 
    system("clear"); 

    FILE *splash = fopen("./splash-screen.txt", "r"); 
    char c;
    while (!feof(splash)) {
        c = getc(splash); 
        printf("%c", c); 
    }; 
    fclose(splash); 
    exit(0);
}
