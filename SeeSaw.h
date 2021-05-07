#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

/* Curren Taber & Joan Karstrom
 * Professor Hansen
 * CPSC 380-01
 * Project 3: See-Saw Simulator
 */

// Number of runs
#define ITERATION_COUNT 10

// Semaphore name for Fred
#define SEM_FRED_NAME "fred"

// Semaphore name for Wilma
#define SEM_WILMA_NAME "wilma"

class SeeSaw {
  public:
    SeeSaw(); // Constructor
    void RunSimulation(); // Runs the See-Saw Simulation
  private:
    static void* FredSee(void* arg); // Updates and prints Fred's height
    static void* WilmaSaw(void* arg); // Updates and prints Wilma's height
};
