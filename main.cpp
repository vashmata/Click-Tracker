#include <windows.h>
#include <ctime>
#include <iostream>
#include <limits.h>
#include <vector>
#include <fstream>
//#include <string> // not used in main
//#include <bitset> // debugging

using namespace std;
// the following headers use std namespace
#include "clicks.h"
#include "menu.h"

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
        for (unsigned int i=0;i<clicks.size();i+=3) {
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
