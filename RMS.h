#include <iostream>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

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
#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN

// Semaphore name for Fred
#define SEM_SCHED_A "semSchedA"
#define SEM_SCHED_B "semSchedB"
#define SEM_1_A "sem1A"
#define SEM_1_B "sem1B"
#define SEM_2_A "sem2A"
#define SEM_2_B "sem2B"
#define SEM_3_A "sem3A"
#define SEM_3_B "sem3B"
#define SEM_4_A "sem4A"
#define SEM_4_B "sem4B"

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
