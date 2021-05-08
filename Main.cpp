#include "RMS.h"

/* Curren Taber & Joan Karstrom
 * Professor Hansen
 * CPSC 380-01
 * Project 4: Rate Monotonic Scheduler
 */

// Main
int main(int argc, char* argv[]) {
  RMS* rms = new RMS();
  rms->Run();
  return 0;
}
