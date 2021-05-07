# Assignment 2: See-Saw Simulator

## 1. IDENTIFYING INFO
- Curren Taber & Joan Karstrom
- Professor Hansen
- CPSC 380-01: Operating Systems
- April 19, 2021

## 2. SOURCE FILES
- README.md
- Main.cpp
- SeeSaw.h
- SeeSaw.cpp

## 3. DESCRIPTION

When Main.cpp runs, it creates a SeeSaw pointer and calls RunSimulation() on the new SeeSaw object. Upon creation, the SeeSaw object initializes two binary semaphores (semFred and semWilma), a boolean (fredsTurn), two doubles for height (fredsHeight and wilmasHeight), and an integer for tracking the current round (i). The RunSimulation() method starts by unlinking and creating the two semaphores, with semFred set to 0 and semWilma set to 1 (this allows Fred to run first since he calls sem_wait() on semWilma). Then, RunSimulation creates two child threads named tid_fred and tid_wilma, which run the functions FredSee() and WilmaSaw(), respectively. Both FredSee() and WilmaSaw() call sem_wait() on the opposite person’s semaphore, execute the critical section, then call sem_post() on their own semaphore. In the critical section, each thread checks if fredsHeight is 1 and wilmasHeight is 7, or vice versa. If this condition occurs, then the fredsTurn changes its value and indicates the current person pushing the see-saw (fredsTurn = true means Fred pushes the see-saw). Fred pushes with an upward velocity of 1 ft/s, whereas Wilma pushes with an upward velocity of 1.5 ft/s. FredSee() and WilmaSaw update the heights of Fred and Wilma, printing their current height every second. Once the simulation finishes ITERATION_COUNT rounds, then tid_fred and tid_wilma join with their parent thread, and the program finishes.

## 3. REFERENCES
- [Semaphore Tutorial](https://youtu.be/ukM_zzrIeXs)
- [Semaphore Documentation](https://pubs.opengroup.org/onlinepubs/7908799/xsh/semaphore.h.html)
- [Semaphore Threads with POSIX Semaphores](http://www.csc.villanova.edu/~mdamian/threads/posixsem.html)
- [Using Semaphores on Mac](https://stackoverflow.com/questions/4136181/program-using-semaphores-runs-fine-on-linux-unexpected-results-on-mac-osx)
- [Error Checking with Semaphores](https://stackoverflow.com/questions/36755003/initialise-semaphores-using-sem-open)
- [Adding a Timed Delay with C++](https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program)
