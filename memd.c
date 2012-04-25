/**
* A primitive tool to debug memory problem of another program
* memd.c sets up a SIGSEGV handler so that it will print out
* process id and thread id then go into infinite loop to be attached
* by gdb.
* author: tuan t. pham <tuan at vt dot edu>
* compile:
* $ gcc -fPIC -g -c -o memd.o memd.c
* $ gcc -shared -o memd.so memd.o -lpthread
*/

#include <signal.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

void memd_sigsegv_handler(int signo, siginfo_t *info, void* context);

void __attribute__ ((constructor))
memd_init(void)
{
  sigset_t          block_mask;
  struct sigaction  event_sig;

  fprintf(stderr, "Installing SIGSEGV handler...\n");

  sigfillset(&block_mask);
  event_sig.sa_sigaction = memd_sigsegv_handler;
  event_sig.sa_mask = block_mask;
  event_sig.sa_flags = SA_RESTART;
  sigaction(SIGSEGV, &event_sig, NULL);
}

void
memd_sigsegv_handler(int signo, siginfo_t *info, void* context)
{
  volatile long mdebug = 0;
  fprintf(stderr, "Segmentation fault occurred at address %#x\n", (long) (void*) info->si_addr);
  fprintf(stderr, "Process id %d thread id %#x\n", getpid(), pthread_self());

  while (0 == mdebug)
  {
    usleep(5000);
  }
}
