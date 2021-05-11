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

double matrix[10][10];

// Constructor
RMS::RMS() {

}

// A horribly inefficient function
void RMS::DoWork(void* arg) {
  // Initializing the matrix to 1's
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      matrix[i][j] = 1.0;
    }
  }

  // Multiplying operation
  int count = *((int*)arg);
  cout << count << endl;
  for (int x = 0; x < count; x++) {
    double curr = 1.0;
    for (int j = 0; j < 5; j++) {
      for (int i = 0; i < 10; i++) {
        curr *= matrix[i][j];
      }
      for (int i = 0; i < 10; i++) {
        curr *= matrix[i][j+5];
      }
    }
  }

  if (count == workCount_1) {
    cout << "1" << endl;
  } else if (count == workCount_2) {
    cout << "2" << endl;
  } else if (count == workCount_3) {
    cout << "3" << endl;
  } else {
    cout << "4" << endl;
  }
  // sem_post(semFred);
  pthread_exit(0);
}

// Runs the program
void RMS::Run() {

  int policy;
  pthread_attr_t attr;
  cpu_set_t cpuset;
  struct sched_param param;

  pthread_attr_init(&attr);

  if (pthread_attr_setschedpolicy(&attr, SCHED_FIFO) != 0) {
    cout << "Unable to set policy" << endl;
  }

  // Setting Processor Affinity to Core 0
  CPU_ZERO(&cpuset);
  CPU_SET(0, &cpuset);
  sched_setaffinity(0, sizeof(cpuset), &cpuset);
  //cout << CPU_COUNT(&cpuset) << endl;

  // if (pthread_attr_getschedpolicy(&attr, &policy) != 0) {
  //   cout << "unable to get policy" << endl;
  // } else {
  //   if (policy == SCHED_OTHER) {
  //     cout << "other" << endl;
  //   } else if (policy == SCHED_RR) {
  //     cout << "rr" << endl;
  //   } else if (policy == SCHED_FIFO) {
  //     cout << "FIFO" << endl;
  //   }
  // }

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

  // pthread_setschedparam(tid_1, policy, &param);
  // pthread_setschedparam(tid_2, policy, &param);
  // pthread_setschedparam(tid_3, policy, &param);
  // pthread_setschedparam(tid_4, policy, &param);


  pthread_create(&tid_1, &attr, &DoWork, (void*)&workCount_1); // Execute 100 times
  pthread_create(&tid_2, &attr, &DoWork, (void*)&workCount_2); // Execute 200 times
  pthread_create(&tid_3, &attr, &DoWork, (void*)&workCount_3); // Execute 400 times
  pthread_create(&tid_4, &attr, &DoWork, (void*)&workCount_4); // Execute 1600 times

  cout << sched_get_priority_max(policy) << endl;
  cout << sched_get_priority_min(policy) << endl;

  int rc = pthread_getschedparam(tid_1, &policy, &param);
  cout << rc << endl;
  rc = pthread_getschedparam(tid_2, &policy, &param);
  cout << rc << endl;
  rc = pthread_getschedparam(tid_3, &policy, &param);
  cout << rc << endl;
  rc = pthread_getschedparam(tid_4, &policy, &param);
  cout << rc << endl;

  // Joining the child threads with this thread
  pthread_join(tid_1, NULL);
  pthread_join(tid_2, NULL);
  pthread_join(tid_3, NULL);
  pthread_join(tid_4, NULL);

  sem_close(semFred);
  sem_close(semWilma);
}
