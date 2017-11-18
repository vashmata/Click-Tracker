#ifndef CLICKS_H_INCLUDED
#define CLICKS_H_INCLUDED

char *LEFT = "L";
char *RIGHT = "R";
SHORT BMASK = (SHORT)1 << ((sizeof(SHORT)*CHAR_BIT) - 1);

// Clicking loop
SHORT Lstate; // was the button pressed?
SHORT Rstate;
BOOL Lcheck = FALSE; // these flip to TRUE when button is pressed
BOOL Rcheck = FALSE; // and flip to FALSE when button is released
vector <char *> clicks; // sequence of <button> <time> <button> ...

void writeClick(char *button); // registers which click and when into an array
void checkClick(char *button); // checks if right or left button was clicked

#endif // CLICKS_H_INCLUDED
