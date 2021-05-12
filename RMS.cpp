#include "RMS.h"

/* Curren Taber, Joan Karstrom, and Krishna Narayan
 * Professor Hansen
 * CPSC 380-01
 * Project 4: Rate Monotonic Scheduler
 */

int i;
int j;
bool working = true;

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

// Parameters for the Threads
struct sched_param paramsSched;
struct sched_param params1;
struct sched_param params2;
struct sched_param params3;
struct sched_param params4;

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
}

static void handler(int sig, siginfo_t *si, void *uc) {
           /* Note: calling printf() from a signal handler is not safe
              (and should not be done in production programs), since
              printf() is not async-signal-safe; see signal-safety(7).
              Nevertheless, we use printf() here as a simple way of
              showing that the handler was called. */

  printf("Caught signal %d\n", sig);
  signal(sig, SIG_IGN);
}

void* RMS::Scheduler(void* arg) {

  timer_t timerid;
  struct sigevent sev;
  struct itimerspec its;
  long long freq_nanosecs;
  sigset_t mask;
  struct sigaction sa;

  /* Establish handler for timer signal */

   printf("Establishing handler for signal %d\n", SIG);
   sa.sa_flags = SA_SIGINFO;
   sa.sa_sigaction = handler;
   sigemptyset(&sa.sa_mask);
   if (sigaction(SIG, &sa, NULL) == -1)
       cout << "here" << endl; //errExit("sigaction");

   /* Block timer signal temporarily */

   printf("Blocking signal %d\n", SIG);
   sigemptyset(&mask);
   sigaddset(&mask, SIG);
   if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1)
       cout << "here" << endl;//errExit("sigprocmask");

   /* Create the timer */

   sev.sigev_notify = SIGEV_SIGNAL;
   sev.sigev_signo = SIG;
   sev.sigev_value.sival_ptr = &timerid;
   if (timer_create(CLOCKID, &sev, &timerid) == -1)
       cout << "here" << endl;//errExit("timer_create");

   printf("timer ID is 0x%lx\n", (long) timerid);

   /* Start the timer */

   freq_nanosecs = 1;//atoll(argv[2]);
   its.it_value.tv_sec = freq_nanosecs / 1000000000;
   its.it_value.tv_nsec = freq_nanosecs % 1000000000;
   its.it_interval.tv_sec = its.it_value.tv_sec;
   its.it_interval.tv_nsec = its.it_value.tv_nsec;

   if (timer_settime(timerid, 0, &its, NULL) == -1)
        cout << "here" << endl;//errExit("timer_settime");


   /* Unlock the timer signal, so that timer notification
      can be delivered */

   printf("Unblocking signal %d\n", SIG);
   if (sigprocmask(SIG_UNBLOCK, &mask, NULL) == -1)
       cout << "here" << endl;//errExit("sigprocmask");







  int rc; // For checking values of semaphores
  for (i = 0; i < PERIOD_COUNT; i++) {
    for (j = 0; j < UNIT_COUNT; j++) {
      // cout << "time: " << i*UNIT_COUNT+j << endl;
      // Schedule T1 Every Time Unit
      runCounter_1++;
      sem_wait(sem1B);
      sem_post(sem1A);

      // Schedule T2 Every 2 Time Units
      if (j % 2 == 0) {
        sem_getvalue(sem2B, &rc);
        if (rc) {
          // sem_wait(sem2B);
          // sem_post(sem2A);
          runCounter_2++;
        } else {
          missCounter_2++;
        }
        sem_wait(sem2B);
        sem_post(sem2A);
      }

      // Schedule T3 Every 4 Time Units
      if (j % 4 == 0) {
        sem_getvalue(sem3B, &rc);
        //cout << "RC 3 IS HERE " << rc << endl;
        if (rc) {
          // sem_wait(sem3B);
          // sem_post(sem3A);
          runCounter_3++;
        } else {
          missCounter_3++;
        }
        sem_wait(sem3B);
        sem_post(sem3A);
      }

      // Schedule T4 Every 16 Time Units
      if (j % 16 == 0) {
        sem_getvalue(sem4B, &rc);
        if (rc) {
          // sem_wait(sem4B);
          // sem_post(sem4A);
          runCounter_4++;
        } else {
          missCounter_4++;
        }
        sem_wait(sem4B);
        sem_post(sem4A);
      }
      usleep(1000); // 1 millisecond
    }
  }
  working = false;
  cout << "-----------" << endl;
  cout << "Thread 1 ran " << runCounter_1 << " times." << endl;
  cout << "Thread 2 ran " << runCounter_2 << " times." << endl;
  cout << "Thread 3 ran " << runCounter_3 << " times." << endl;
  cout << "Thread 4 ran " << runCounter_4 << " times." << endl;

  cout << "-----------" << endl;
  cout << "Thread 1 missed " << missCounter_1 << " times." << endl;
  cout << "Thread 2 missed " << missCounter_2 << " times." << endl;
  cout << "Thread 3 missed " << missCounter_3 << " times." << endl;
  cout << "Thread 4 missed " << missCounter_4 << " times." << endl;


  sem_post(sem1A);
  sem_post(sem2A);
  sem_post(sem3A);
  sem_post(sem4A);

  pthread_exit(0);
}

void* RMS::Thread1(void* arg) {
  while (working) {
    sem_wait(sem1A);
    // cout << WORK_COUNT_1 << endl;
    for (int i = 0; i < WORK_COUNT_1; i++){
      DoWork();
    }
    // runCounter_1++;
    sem_post(sem1B);
  }
  pthread_exit(0);
}

void* RMS::Thread2(void* arg) {
  while (working) {
    sem_wait(sem2A);
    // cout << WORK_COUNT_2 << endl;
    for (int i = 0; i < WORK_COUNT_2; i++){
      DoWork();
    }
    // runCounter_2++;
    sem_post(sem2B);
  }
  pthread_exit(0);
}

void* RMS::Thread3(void* arg) {
  while (working) {
    sem_wait(sem3A);
    // cout << WORK_COUNT_3 << endl;
    for (int i = 0; i < WORK_COUNT_3; i++){
      DoWork();
    }
    // runCounter_3++;
    sem_post(sem3B);
  }
  pthread_exit(0);
}

void* RMS::Thread4(void* arg) {
  while (working) {
    sem_wait(sem4A);
    // cout << WORK_COUNT_4 << endl;
    for (int i = 0; i < WORK_COUNT_4; i++){
      DoWork();
    }
    // runCounter_4++;
    sem_post(sem4B);
  }
  pthread_exit(0);
}

// Runs the program
void RMS::Run() {

  int policy;
  pthread_attr_t attr;
  cpu_set_t cpuset;

  pthread_attr_init(&attr);

  //Setting Schedule Policy to FIFO
  if (pthread_attr_setschedpolicy(&attr, SCHED_FIFO) != 0) {
    cout << "Unable to set policy" << endl;
  }

  // Setting Processor Affinity to Core 0
  CPU_ZERO(&cpuset);
  CPU_SET(0, &cpuset);
  if ((sched_setaffinity(0, sizeof(cpuset), &cpuset) != 0)) {
    cout << "Unable to set policy" << endl;
  }

  // Setting Semaphore 1A
  sem_unlink(SEM_1_A);
  sem1A = sem_open(SEM_1_A, O_CREAT, 0777, 0);
  if (sem1A == SEM_FAILED) {
    cout << "Failed to open Semaphore 1A" << endl;
    exit(-1);
  }

  // Setting Semaphore 1B
  sem_unlink(SEM_1_B);
  sem1B = sem_open(SEM_1_B, O_CREAT, 0777, 1);
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

  // Creating child threads
  // Setting Semaphore 2B
  sem_unlink(SEM_2_B);
  sem2B = sem_open(SEM_2_B, O_CREAT, 0777, 1);
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
  sem3B = sem_open(SEM_3_B, O_CREAT, 0777, 1);
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
  sem4B = sem_open(SEM_4_B, O_CREAT, 0777, 1);
  if (sem4B == SEM_FAILED) {
    cout << "Failed to open Semaphore 4B" << endl;
    exit(-1);
  }

  pthread_t tid_Sched;
  pthread_t tid_1;
  pthread_t tid_2;
  pthread_t tid_3;
  pthread_t tid_4;

  paramsSched.sched_priority = 99;
  params1.sched_priority = 98;
  params2.sched_priority = 97;
  params3.sched_priority = 96;
  params4.sched_priority = 95;

  pthread_setschedparam(tid_Sched, SCHED_FIFO, &paramsSched);
  pthread_setschedparam(tid_1, SCHED_FIFO, &params1);
  pthread_setschedparam(tid_2, SCHED_FIFO, &params2);
  pthread_setschedparam(tid_3, SCHED_FIFO, &params3);
  pthread_setschedparam(tid_4, SCHED_FIFO, &params4);

  pthread_create(&tid_Sched, &attr, &Scheduler, NULL); // Scheduler Thread
  pthread_create(&tid_1, &attr, &Thread1, NULL); // Execute 100 times
  pthread_create(&tid_2, &attr, &Thread2, NULL); // Execute 200 times
  pthread_create(&tid_3, &attr, &Thread3, NULL); // Execute 400 times
  pthread_create(&tid_4, &attr, &Thread4, NULL); // Execute 1600 times

  int a;
  a = pthread_setaffinity_np(tid_Sched, sizeof(cpu_set_t), &cpuset);
  a = pthread_setaffinity_np(tid_1, sizeof(cpu_set_t), &cpuset);
  a = pthread_setaffinity_np(tid_2, sizeof(cpu_set_t), &cpuset);
  a = pthread_setaffinity_np(tid_3, sizeof(cpu_set_t), &cpuset);
  a = pthread_setaffinity_np(tid_4, sizeof(cpu_set_t), &cpuset);

  // Joining the child threads with this thread
  pthread_join(tid_Sched, NULL);
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
