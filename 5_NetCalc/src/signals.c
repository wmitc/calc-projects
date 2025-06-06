#define _XOPEN_SOURCE 700 // Macro required for POSIX functionality

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "signals.h"

#define SIG1 1
#define SIG2 2

volatile sig_atomic_t signal_flag_g = 0;

/**
 * @brief Implementation of the signal_handler function
 */
void signal_handler(int signal)
{
    // Set signal_flag_g to default value
    signal_flag_g = 0;

    // Modify signal_flag_g for SIGUSR1 or SIGINT signals
    if (signal == SIGUSR1)
    {
        signal_flag_g = SIG1;
    }
    else if (signal == SIGINT)
    {
        signal_flag_g = SIG2;
    }
}

/**
 * Implementation of the signal_action_setup function
 */
int signal_action_setup(void)
{

    // Instantiation a signal action and set fields
    struct sigaction action;
    sigemptyset(&action.sa_mask);
    action.sa_flags   = SA_RESTART;
    action.sa_handler = signal_handler;

    // Check for SIGUSR1 or SIGINT errors
    if (sigaction(SIGUSR1, &action, NULL) < 0)
    {
        fprintf(stderr, "[-] sigaction SIGUSR1 error");
        return EXIT_FAILURE;
    }
    else if (sigaction(SIGINT, &action, NULL) < 0)
    {
        fprintf(stderr, "[-] sigaction SIGINT error");
        return EXIT_FAILURE;
    }

    return SUCCESS;
}

/*** end of file ***/
