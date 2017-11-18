#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

// Program initialization
BOOL restart = TRUE; // will loop program until false
char *timeUnit; // string containing the units
SHORT conversion; // assigned based on timeUnit
SHORT maxTime; // quantity of timeUnit
SHORT entryLimit = 15; // max chars you can enter as an answer

void setUnits(); // assigns units
void setTime(); // assigns time
void checkLoop(); // checks if you want to restart

#endif // MENU_H_INCLUDED
