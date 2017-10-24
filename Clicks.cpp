#include <windows.h>
#include <ctime>
#include <iostream>
#include <limits.h>
#include <vector>
#include <fstream>
//#include <bitset> // debugging
//#include <stdlib.h> // not using this anymore

#define LEFT "L"
#define RIGHT "R"
#define BMASK (SHORT)1 << (sizeof(SHORT)*CHAR_BIT) - 1

using namespace std;

// Program initialization
BOOL restart = TRUE; // will loop program until false
char *timeUnit; // string containing the units
SHORT conversion; // assigned based on timeUnit
SHORT maxTime; // quantity of timeUnit
SHORT entryLimit = 15; // max chars you can enter as an answer
void setUnits(); // assigns units
void setTime(); // assigns time
void checkLoop(); // checks if you want to restart

// Clicking loop
SHORT Lstate; // was the button pressed?
SHORT Rstate;
BOOL Lcheck = FALSE; // these flip to TRUE when button is pressed
BOOL Rcheck = FALSE; // and flip to FALSE when button is released
vector <char *> clicks; // sequence of <button> <time> <button> ...
void writeClick(char *button); // registers which click and when into an array
void checkClick(char *button); // checks if right or left button was clicked

int main() {
    // rewrite with C++ strings
    // tell user when the program is expected to end?
    //  allow the user to input an end time/date?
    // error checking, exception handling?
    // rewrite with interrupts? signals
    // for some reason the program ends prematurely sometimes?
    // alternate exit strategy that will still save the data?
    //  for this just use SIGABRT or another interrupt
    //  and turn the file creation and stuff into a function
    // do I save the data as it's registered or wait for the timer?
    //  the way it works now is fine since the size of the stored data is tiny

    // Initialization
    cout <<"Hi! This program tracks your mouse clicks and saves the info into a .csv file."<< endl;
while (restart == TRUE) { // program will loop if you want
    setUnits(); setTime(); // No error checking for strings longer than 15 chars

    // set titles in array
    clicks.push_back("Button");
    clicks.push_back("Date");
    clicks.push_back("Time");

    // loop for button checking
    while ( (clock() / CLOCKS_PER_SEC / conversion) < maxTime ){ // prevent infinite loop
        checkClick(LEFT); checkClick(RIGHT);
    }
    time_t seconds = time(NULL); char *currTime = ctime(&seconds); // register time
    //cout <<"Max limit of "<<maxTime<<" "<<timeUnit<<" has passed. "
    cout <<"It is now "<<currTime;
    cout <<"Program no longer tracking mouse clicks."<< endl;

    // Preparing filename
    cout <<endl<<"What would you like to name this .csv file?"<< endl;
    char fname[entryLimit+4]; // make extra room for extension
    cin >> fname; strcat(fname,".csv");
    cout <<endl<<"Okay, writing data to '"<<fname<<"'..."<< endl;

    //writing to file
    fstream fs;
    fs.open(fname,fstream::out);
    for (int i=0;i<clicks.size();i+=3) {
        fs <<clicks[i]<<','<<clicks[i+1]<<','<<clicks[i+2]<< endl;
    }
    fs.close();
    cout <<"Done!"<< endl;

    // debugging
    /*
    cout <<"Check for this data inside file"<< endl;
    for (int i=0;i<clicks.size();i++){
        cout<<clicks[i]<<endl;
    }
    */

    checkLoop(); // there's no error checking for larger strings
}
    return 0;
}

void setUnits() { // sets units for the timer
    cout <<endl<<"What time scale would you like to use? Type '1' for seconds, "
        "'2' for minutes, \n'3' for hours, '4' for days."<< endl;
    char entry[entryLimit]; // there's no error checking for larger strings
    cin >> entry; int choice = atoi(entry); // convert to number
    switch (choice) {
    case 1:
        conversion = 1;
        timeUnit = "seconds";
        break;
    case 2:
        conversion = 60;
        timeUnit = "minutes";
        break;
    case 3:
        conversion = 3600;
        timeUnit = "hours";
        break;
    case 4:
        conversion = 86400;
        timeUnit = "days";
        break;
    default:
        cout <<"Invalid entry! Try again."<< endl;
        setUnits(); // recursion is nice
    }
}

void setTime() { // sets number of timeUnit for timer
    cout <<"Okay, how many "<<timeUnit<<" should the program run for?"<< endl;
    char num[entryLimit]; // there's no error checking for larger strings
    cin >> num; maxTime = atoi(num); // convert to number

    time_t seconds = time(NULL); char *currTime = ctime(&seconds); // register time
    cout <<endl<<"Program started "<<currTime;
    cout <<"Program will finish in "<<maxTime<<" "<<timeUnit<<endl<<"..."<< endl;
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

void writeClick(char *button) { // save data to array
    clicks.push_back(button);
    time_t seconds = time(NULL); char *currTime = ctime(&seconds);
    char time1[7]; strncpy( time1, currTime+4, 6 ); time1[6]='\0'; // date string
    clicks.push_back(strdup(time1)); // this can cause memory leaks
    char time2[9]; strncpy( time2, currTime+11, 8 ); time2[8]='\0'; // time string
    clicks.push_back(strdup(time2)); // this can cause memory leaks
}

void checkLoop() { // checks if you want to do another batch
    cout <<endl<<"Would you like to try this again? Type '1' for yes, '2' for no."<< endl;
    char ans[entryLimit]; // there's no error checking for larger strings
    cin >> ans; int ans1 = atoi(ans); // convert to number
    switch (ans1) {
    case 1:
        break;
    case 2:
        cout <<"Okay, ending the program."<< endl;
        restart = FALSE;
        break;
    default:
        cout <<"Really? You only had 2 options and you messed it up?"<< endl;
        checkLoop();
    }
}
