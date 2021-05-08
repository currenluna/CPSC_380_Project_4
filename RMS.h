#include <iostream>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

/* Curren Taber & Joan Karstrom
 * Professor Hansen
 * CPSC 380-01
 * Project 4: Rate Monotonic Scheduler
 */

// Number of runs
#define ITERATION_COUNT 10

// Semaphore name for Fred
#define SEM_FRED_NAME "fred"

// Semaphore name for Wilma
#define SEM_WILMA_NAME "wilma"

class RMS {
  public:
    RMS(); // Constructor
    void Run(); // Runs the program
  private:
    static void* DoWork(void* arg); // A horribly inefficient function
};
