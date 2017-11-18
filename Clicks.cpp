#include <windows.h>
#include <ctime>
#include <iostream>
#include <limits.h>
#include <vector>
#include <fstream>

using namespace std;

#define LEFT "L"
#define RIGHT "R"
#define BMASK (SHORT)1 << (sizeof(SHORT)*CHAR_BIT) - 1

// Clicking loop
SHORT Lstate; // was the button pressed?
SHORT Rstate;
BOOL Lcheck = FALSE; // these flip to TRUE when button is pressed
BOOL Rcheck = FALSE; // and flip to FALSE when button is released
vector <char *> clicks; // sequence of <button> <time> <button> ...

void writeClick(char *button) { // save data to array
    clicks.push_back(button);
    time_t seconds = time(NULL); char *currTime = ctime(&seconds);
    char time1[7]; strncpy( time1, currTime+4, 6 ); time1[6]='\0'; // date string
    clicks.push_back(strdup(time1)); // this can cause memory leaks
    char time2[9]; strncpy( time2, currTime+11, 8 ); time2[8]='\0'; // time string
    clicks.push_back(strdup(time2)); // this can cause memory leaks
}

void checkClick(char *button) { // must come before writeClick()
    // checks which button is pressed and calls writeClick()
    // this function assumes Windows OS
    if (button == LEFT) { // check for left clicks
        Lstate = GetAsyncKeyState(VK_LBUTTON); // MSB is 1 when the key is down
        // cout << bitset<16>( (SHORT)1 << (sizeof(SHORT)*CHAR_BIT) - 1 ) << endl; // debugging
        if (Lstate & BMASK){ // if MSB is 1 with implementation-defined size
            if (Lcheck == FALSE){ // mouse pressed down and program doesn't know yet
                Lcheck = TRUE; // program knows mouse was clicked and is still pressed down
                //cout <<button<<" button pressed!"<< endl; //testing
                writeClick(LEFT);
            }
        }
        else {
            if (Lcheck == TRUE){ // button has been released and check hasn't flipped yet
                Lcheck = FALSE; // it needs to be reset for the next mouse click
                //cout <<button<<" button released!"<< endl; //testing
            }
        }
    }
    if (button == RIGHT) { // check for right clicks
        Rstate = GetAsyncKeyState(VK_RBUTTON); // MSB is 1 when the key is down
        // cout << bitset<16>( (SHORT)1 << (sizeof(SHORT)*CHAR_BIT) - 1 ) << endl; // debugging
        if (Rstate & BMASK){ // if MSB is 1 with implementation-defined size
            if (Rcheck == FALSE){ // mouse pressed down and program doesn't know yet
                Rcheck = TRUE; // program knows mouse was clicked and is still pressed down
                //cout <<button<<" button pressed!"<< endl; //testing
                writeClick(RIGHT);
            }
        }
        else {
            if (Rcheck == TRUE){ // button has been released and check hasn't flipped yet
                Rcheck = FALSE; // it needs to be reset for the next mouse click
                //cout <<button<<" button released!"<< endl; //testing
            }
        }
    }
}



