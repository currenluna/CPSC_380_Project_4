# Assignment 4: Rate Monotonic Scheduler

## 1. IDENTIFYING INFO
- Curren Taber, Joan Karstrom, and Krishna Narayan
- Professor Hansen
- CPSC 380-01: Operating Systems
- May 11, 2021

## 2. SOURCE FILES
- README.md
- Main.cpp
- RMS.h
- RMS.cpp

## 3. DESCRIPTION

We designed our scheduler so that the scheduler is the main thread, and within the scheduler we dispatch which threads are supposed to be running through the period. We can release/unlock them at the desired frequency by using the modulo function. Synchronization/dispatch of threads through the scheduler happens through semaphores, in a similar fashion to how Fred and Wilma threads were synchronized in project 3. 8 semaphores were used -- half locked, and half unlocked. Initially, thread 1 would be unlocked -- as it finished its task, it would signal the scheduler to then unlock, which would unlock thread 2, which would then finish its task, and signal the scheduler to unlock, which would unlock thread 3, etc. until all four threads had their opportunity (given that they were performing at their desired frequency) to run. At this point, the process is looped and begins again.

## 3. REFERENCES
- [Passing Arguments to Threads](https://courses.engr.illinois.edu/cs241/fa2010/ppt/10-pthread-examples.pdf)
- [Operating System Concepts Textbook](http://www.nastooh.com/teaching/Silberschatz_Operating_System_Concepts_10e_2018.pdf)
- [Setting Pthread Affinity](https://man7.org/linux/man-pages/man3/pthread_setaffinity_np.3.html)
- [Using sched_setaffinity()](https://stackoverflow.com/questions/10490756/how-to-use-sched-getaffinity-and-sched-setaffinity-in-linux-from-c)
- [Thread Priority](http://www.yonch.com/tech/82-linux-thread-priority)
