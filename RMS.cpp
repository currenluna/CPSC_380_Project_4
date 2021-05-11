#include "RMS.h"

/* Curren Taber, Joan Karstrom, and Krishna Narayan
 * Professor Hansen
 * CPSC 380-01
 * Project 4: Rate Monotonic Scheduler
 */

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

// Semaphores for the Threads
sem_t* sem1A;
sem_t* sem1B;
sem_t* sem2A;
sem_t* sem2B;
sem_t* sem3A;
sem_t* sem3B;
sem_t* sem4A;
sem_t* sem4B;

// Constructor
RMS::RMS() {}

// A horribly inefficient function
void RMS::DoWork() {
  // Initializing the matrix to 1's
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      matrix[i][j] = 1.0;
    }
  }
  // Multiplying operation
  double curr = 1.0;
  for (int j = 0; j < 5; j++) {
    for (int i = 0; i < 10; i++) {
      curr *= matrix[i][j];
    }
    for (int i = 0; i < 10; i++) {
      curr *= matrix[i][j+5];
    }
  }
  pthread_exit(0);
}

void* RMS::Scheduler(void* arg) {
  for (int i = 0; i < PERIOD_COUNT; i++) {
    for (int j = 0; j < UNIT_COUNT; j++) {
      // Schedule T1 Every Time Unit


      // Schedule T2 Every 2 Time Units
      if (j % 2 == 0) {

      }

      // Schedule T3 Every 4 Time Units
      if (j % 4 == 0) {

      }

      // Schedule T4 Every 16 Time Units
      if (j % 16 == 0) {

      }
      usleep(10000); // 10 milliseconds
    }
  }
}

void* RMS::Thread1(void* arg) {
  while (true) {
    sem_wait(sem1A);
    for (int i = 0; i < WORK_COUNT_1; i++){
      DoWork();
    }
    runCounter_1++;
    sem_post(sem1B);
  }
}

void* RMS::Thread2(void* arg) {
  while (true) {
    for (int i = 0; i < WORK_COUNT_2; i++){
      DoWork();
    }
    runCounter_2++;
  }
}

void* RMS::Thread3(void* arg) {
  while (true) {
    for (int i = 0; i < WORK_COUNT_3; i++){
      DoWork();
      runCounter_3++;
    }
  }
}

void* RMS::Thread4(void* arg) {
  while (true) {
    for (int i = 0; i < WORK_COUNT_4; i++){
      runCounter_4++;
      DoWork();
    }
  }
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

  // Setting Semaphore 1A
  sem_unlink(SEM_1_A);
  sem1A = sem_open(SEM_1_A, O_CREAT, 0777, 0);
  if (sem1A == SEM_FAILED) {
    cout << "Failed to open Semaphore 1A" << endl;
    exit(-1);
  }

  // Setting Semaphore 1B
  sem_unlink(SEM_1_B);
  sem1B = sem_open(SEM_1_B, O_CREAT, 0777, 0);
  if (sem1B == SEM_FAILED) {
    cout << "Failed to open Semaphore 1B" << endl;
    exit(-1);
  }

  // Setting Semaphore 2A
  sem_unlink(SEM_2_A);
  sem2A = sem_open(SEM_2_A, O_CREAT, 0777, 0);
  if (sem2A == SEM_FAILED) {
    cout << "Failed to open Semaphore 2A" << endl;
    exit(-1);
  }

  // Setting Semaphore 2B
  sem_unlink(SEM_2_B);
  sem2B = sem_open(SEM_2_B, O_CREAT, 0777, 0);
  if (sem2B == SEM_FAILED) {
    cout << "Failed to open Semaphore 2B" << endl;
    exit(-1);
  }

  // Setting Semaphore 3A
  sem_unlink(SEM_3_A);
  sem3A = sem_open(SEM_3_A, O_CREAT, 0777, 0);
  if (sem3A == SEM_FAILED) {
    cout << "Failed to open Semaphore 3A" << endl;
    exit(-1);
  }

  // Setting Semaphore 3B
  sem_unlink(SEM_3_B);
  sem3B = sem_open(SEM_3_B, O_CREAT, 0777, 0);
  if (sem3B == SEM_FAILED) {
    cout << "Failed to open Semaphore 3B" << endl;
    exit(-1);
  }

  // Setting Semaphore 4A
  sem_unlink(SEM_4_A);
  sem4A = sem_open(SEM_4_A, O_CREAT, 0777, 0);
  if (sem4A == SEM_FAILED) {
    cout << "Failed to open Semaphore 4A" << endl;
    exit(-1);
  }

  // Setting Semaphore 4B
  sem_unlink(SEM_4_B);
  sem4B = sem_open(SEM_4_B, O_CREAT, 0777, 0);
  if (sem4B == SEM_FAILED) {
    cout << "Failed to open Semaphore 4B" << endl;
    exit(-1);
  }

  pthread_t tid_S;
  pthread_t tid_1;
  pthread_t tid_2;
  pthread_t tid_3;
  pthread_t tid_4;

  pthread_create(&tid_S, &attr, &Scheduler, NULL); // Scheduler Thread
  pthread_create(&tid_1, &attr, &Thread1, NULL); // Execute 100 times
  pthread_create(&tid_2, &attr, &Thread2, NULL); // Execute 200 times
  pthread_create(&tid_3, &attr, &Thread3, NULL); // Execute 400 times
  pthread_create(&tid_4, &attr, &Thread4, NULL); // Execute 1600 times

  // cout << sched_get_priority_max(policy) << endl;
  // cout << sched_get_priority_min(policy) << endl;
  //
  // int rc = pthread_getschedparam(tid_1, &policy, &param);
  // cout << rc << endl;
  // rc = pthread_getschedparam(tid_2, &policy, &param);
  // cout << rc << endl;
  // rc = pthread_getschedparam(tid_3, &policy, &param);
  // cout << rc << endl;
  // rc = pthread_getschedparam(tid_4, &policy, &param);
  // cout << rc << endl;

  // Joining the child threads with this thread
  pthread_join(tid_S, NULL);
  pthread_join(tid_1, NULL);
  pthread_join(tid_2, NULL);
  pthread_join(tid_3, NULL);
  pthread_join(tid_4, NULL);

  sem_close(sem1A);
  sem_close(sem1B);
  sem_close(sem2A);
  sem_close(sem2B);
  sem_close(sem3A);
  sem_close(sem3B);
  sem_close(sem4A);
  sem_close(sem4B);
}
