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
