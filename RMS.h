#include <iostream>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

/* Curren Taber, Joan Karstrom, and Krishna Narayan
 * Professor Hansen
 * CPSC 380-01
 * Project 4: Rate Monotonic Scheduler
 */

// Number of runs
#define PERIOD_COUNT 10
#define WORK_COUNT_1 100
#define WORK_COUNT_2 200
#define WORK_COUNT_3 400
#define WORK_COUNT_4 1600

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
