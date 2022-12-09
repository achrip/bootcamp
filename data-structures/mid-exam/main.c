#include <sys/utsname.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

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
typedef struct 

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

void addDish() {}
void removeDish() {}
void addCust() {}
void searchCust() {} 
void view() {}
void order() {} 
void payment() {} 
void bye() {
    exit(0);
}
