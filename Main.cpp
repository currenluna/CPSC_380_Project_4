#include "RMS.h"

/* Curren Taber, Joan Karstrom, and Krishna Narayan
 * Professor Hansen
 * CPSC 380-01
 * Project 4: Rate Monotonic Scheduler
 */

// Main
int main(int argc, char* argv[]) {
  cout << "here" << endl;
  RMS* rms = new RMS();
  rms->Run();
  return 0;
}
