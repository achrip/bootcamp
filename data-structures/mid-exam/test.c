#include <stdio.h>
#include <time.h>

int main() {
  time_t currentTime;
  struct tm *localTime;

  // Get the current time
  time(&currentTime);

  // Convert the current time to the local time
  localTime = localtime(&currentTime);

  // Print the date and time in the specified format
  char dateTimeString[100];
  strftime(dateTimeString, 100, "%A %B %d %I:%M:%S %Y", localTime);
  printf("The current date and time is: %s\n", dateTimeString);

  return 0;
}