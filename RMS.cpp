#include "RMS.h"

/* Curren Taber, Joan Karstrom, and Krishna Narayan
 * Professor Hansen
 * CPSC 380-01
 * Project 4: Rate Monotonic Scheduler
 */

sem_t* semFred;
sem_t* semWilma;

int i = PERIOD_COUNT;
int workCount_1 = WORK_COUNT_1;
int workCount_2 = WORK_COUNT_2;
int workCount_3 = WORK_COUNT_3;
int workCount_4 = WORK_COUNT_4;

int runCounter_1 = 0;
int runCounter_2 = 0;
int runCounter_3 = 0;
int runCounter_4 = 0;

int missCounter_1 = 0;
int missCounter_2 = 0;
int missCounter_3 = 0;
int missCounter_4 = 0;

int matrix[10][10];

// Constructor
RMS::RMS() {

}

// A horribly inefficient function
void* RMS::DoWork(void* arg) {
  // sem_wait(semWilma);

  // Initializing the matrix to 1's
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      matrix[i][j] = 1;
    }
  }

  // Multiplying operation
  int count = *((int*)arg);
  for (int x = 0; x < count; x++) {
    int curr = 1;
    for (int j = 0; j < 5; j++) {
      for (int i = 0; i < 10; i++) {
        matrix[i][j] *= curr;
      }
      for (int i = 0; i < 10; i++) {
        matrix[i][j+5] *= curr;
      }
    }
    if (count == workCount_1) {
      runCounter_1++;
      cout << runCounter_1 << " ";
    }
  }

  // sem_post(semFred);
  pthread_exit(0);
}

// Runs the program
void RMS::Run() {

  sem_unlink(SEM_FRED_NAME);
  semFred = sem_open(SEM_FRED_NAME, O_CREAT, 0777, 0);
  if (semFred == SEM_FAILED) {
    cout << "Failed to open semaphore for Fred" << endl;
    exit(-1);
  }

  sem_unlink(SEM_WILMA_NAME);
  semWilma = sem_open(SEM_WILMA_NAME, O_CREAT, 0777, 1);
  if (semWilma == SEM_FAILED) {
    cout << "Failed to open semaphore for Wilma" << endl;
    exit(-1);
  }

  // Creating child threads
  pthread_t tid_1;
  pthread_t tid_2;
  pthread_t tid_3;
  pthread_t tid_4;

    cout << "here" << endl;
  pthread_create(&tid_1, NULL, &DoWork, (void*)&workCount_1); // Execute 100 times
  // pthread_create(&tid_2, NULL, &DoWork, (void*)&workCount_2); // Execute 200 times
  // pthread_create(&tid_3, NULL, &DoWork, (void*)&workCount_3); // Execute 400 times
  // pthread_create(&tid_4, NULL, &DoWork, (void*)&workCount_4); // Execute 1600 times

  // Joining the child threads with this thread
  pthread_join(tid_1, NULL);
  // pthread_join(tid_2, NULL);
  // pthread_join(tid_3, NULL);
  // pthread_join(tid_4, NULL);

  sem_close(semFred);
  sem_close(semWilma);
}
