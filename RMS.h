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
#define UNIT_COUNT 16
#define WORK_COUNT_1 100
#define WORK_COUNT_2 200
#define WORK_COUNT_3 400
#define WORK_COUNT_4 1600

// Semaphore name for Fred
#define SEM_SCHED "semSched"
#define SEM_2 "sem2"
#define SEM_3 "sem3"
#define SEM_4 "sem4"


class RMS {
  public:
    RMS(); // Constructor
    void Run(); // Runs the program
  private:
    static void DoWork(); // A horribly inefficient function
    static void* Scheduler(void* arg);
    static void* Thread1(void* arg);
    static void* Thread2(void* arg);
    static void* Thread3(void* arg);
    static void* Thread4(void* arg);
};
