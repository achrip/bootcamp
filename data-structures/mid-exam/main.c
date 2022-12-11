#include <sys/utsname.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
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

// Other Functionals
void showInfo(); 

// Structs
typedef struct { 
    char name[255]; 
    int price; 
    int quantity; 

} Dish; 

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
    int price, qty;

    int flag = 0;
    do {
        printf("Insert the name of the dish [Lowercase letters]: "); 
        scanf("%s", name);

        for (int i = 0; i < strlen(name); i++) {
            if (isupper(name[i])) {
                flag = 1; 
                break; 
            }
        }
    } while (flag);

    int flag = 0;  
    do {
        printf("Insert the price of the dish [1000..50000]: "); 
        scanf("%d", &price); 

        if (price < 1000 || price > 50000) flag = 1; 
    } while (flag);

    int flag = 0;  
    do {
        printf("Insert the quantity of the dish [1..999]: "); 
        scanf("%d", &qty); 

        if (qty < 1 || qty > 999) flag = 1; 
    } while (flag); 

    /*add the new dish to the linked list*/
    printf("The dish has been added!\n\n");
    printf("Press enter to continue...\n");
    getchar(); 
}

void removeDish() {
    
}
void addCust() {}
void searchCust() {} 
void view() {}
void order() {} 
void payment() {} 
void bye() {
    exit(0);
}
