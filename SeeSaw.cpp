#include "SeeSaw.h"

/* Curren Taber & Joan Karstrom
 * Professor Hansen
 * CPSC 380-01
 * Project 3: See-Saw Simulator
 */

// Constructor
SeeSaw::SeeSaw() {
  sem_t* semFred;
  sem_t* semWilma;
  bool fredsTurn = true;
  double fredsHeight = 0;
  double wilmasHeight = 8;
  int i = ITERATION_COUNT;
}

// Updates and prints Fred's height
void* SeeSaw::FredSee(void* arg) {

  while (i >= 0) {
    // Critical Section
    sem_wait(semWilma);

    if (fredsHeight == 1 && wilmasHeight == 7) {
      fredsTurn = true;
      i -= 1;
      if (i >= 0) {
        cout << endl << "CURRENT ROUND: " << ITERATION_COUNT - i << endl << endl;
      }
    } else if (fredsHeight == 7 && wilmasHeight == 1) {
      fredsTurn = false;
    }

    if (i >= 0 && fredsHeight > 0) {
      cout << "Fred's height: " << fredsHeight << ", ";
    }

    if (fredsTurn && fredsHeight < 7) {
      fredsHeight += 1;
    } else if (!fredsTurn && fredsHeight > 1) {
      fredsHeight -= 1.5;
    }

    sem_post(semFred);
    usleep(1000000); // Added delay
  }
  pthread_exit(0);
}

// Updates and prints Wilma's height
void* SeeSaw::WilmaSaw(void* arg) {

  while (i >= 0) {
    // Critical Section
    sem_wait(semFred);

    if (fredsHeight == 1 && wilmasHeight == 7) {
      fredsTurn = true;
      i -= 1;
      if (i >= 0) {
        cout << endl << "CURRENT ROUND: " << ITERATION_COUNT - i << endl << endl;
      }
    } else if (fredsHeight == 7 && wilmasHeight == 1) {
      fredsTurn = false;
    }

    if (i >= 0 && wilmasHeight < 8) {
      cout << "Wilma's height: " << wilmasHeight << endl;
    }

    if (fredsTurn && wilmasHeight > 1) {
      wilmasHeight -= 1;
    } else if (!fredsTurn && wilmasHeight < 7) {
      wilmasHeight += 1.5;
    }

    sem_post(semWilma);
    usleep(1000000); // Added delay
  }
  pthread_exit(0);
}

// Runs the See-Saw Simulation
void SeeSaw::RunSimulation() {

  cout << "SIMULATION START" << endl;

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

  // Creating child threads for Fred and Wilma
  pthread_t tid_fred;
  pthread_t tid_wilma;

  pthread_create(&tid_fred, NULL, &FredSee, NULL);
  pthread_create(&tid_wilma, NULL, &WilmaSaw, NULL);

  // Joining the child threads with this thread
  pthread_join(tid_fred, NULL);
  pthread_join(tid_wilma, NULL);

  sem_close(semFred);
  sem_close(semWilma);
}
