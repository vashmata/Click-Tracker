# Click-Tracker
Program that tracks mouse clicks in Windows.

---------------
How it works:
---------------

The program opens a basic console window, asking you how long you'd like it to run for. It then goes into a loop, checking whether or not a mouse button was clicked. If a button was clicked, the program stores the time it was clicked as well as whether it was the left or right mouse button.

Once the time limit is over, the program asks the uses for a filename and creates a csv file with the mouse click data inside. It then asks the user if they want to start over again. The program has some checks to make sure the user doesn't enter incorrect values, but the checks aren't exhaustive.

The reason this program is Windows-only is that I implemented it using Windows functions that return the state of the mouse.

Since the program functions as a loop, I need to have special checking functions that make sure that once the program registers a mouse click, it stops saving values until the button is released and then depressed a second time.

--------------------------------------------
Current status and potential improvements:
--------------------------------------------

New issue: two friends tried to use the program on their computers and it didn't work. Will try to find out more when I get the chance.

Issue resolved. It's an issue with MinGW. Method 1: find libgcc_s_dw2-1.dll and libstdc++-6.dll and drop them in the same folder as the .exe file. Method 2: add "-static-libgcc -static-libstdc++" or just "-static" to the linker compiler flags before compiling.

The program does everything I intended it to do, however there's much that can be done to make it more efficient and user-friendly.

The major weakness of this program is the fact that it isn't based on interrupts, so it's constantly running and using one of the CPU cores. I don't know enough about Windows yet to be able to rewrite it to activate only when a mouse button is clicked, so until then it's very resource heavy.

I'm not yet sure how to make this program work for any OS. I assume I would have to force the program to check the OS it's running on and then define new functions based on how the OS checks the mouse state.

I wrote this program when I was nearing the end of my self-teaching of C and when I had started teaching myself C++. I could rewrite the program to use C++ Strings, which might make the code more manageable/readable.

The program tells the user when it started and how long it will take, but it would be nice to also calculate and display the ETA. Or perhaps it would be nice to input an end time instead of the length of time it should run for.

The program has some error checking, but it would be nice to code it to check for all situations. I mentioned some key error checks that I should add in the code's comments.

Often, especially with very short time intervals, the program will simply end instead of tracking the mouse clicks. When I enter 5 seconds, for example, it sometimes jumps straight to asking if I want to save a file. I don't know why it does this.

It would be nice to have a key or key combination that I could type in to stop the program from running, but I'm not sure how I'd implement this so it doesn't interfere with other Windows functions. I'd also want to make sure that you could save the data that's been stored until now, but that shouldn't be an issue.

At the moment, the program accumulates clicks and stores them into a huge vector. This shouldn't really be a problem considering how small the data I'm saving is, but if someone tried to save it for a REALLY long time it could cause a memory leak. Another option would be to create a csv file right away and update it each time a mouse is clicked.

