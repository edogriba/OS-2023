#include <atomic>
#include <iostream>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

std::atomic_int signal_terminate(0);
std::atomic_int counter(0);
std::atomic_int sleep_value(1);

// Signal handler function for SIGINT
void handleSIGINT(int signal)
{
    std::cout << "SIGINT received" << std::endl;
    std::cout << "Number of forks: " << counter << std::endl;
    signal_terminate = 1;
}

// Signal handler function for SIGUSR1
void handleSIGUSR1(int signal)
{
    std::cout << "SIGUSR1 received" << std::endl;
    std::cout << "Number of forks: " << counter << std::endl;
    sleep_value += 1;
    std::cout << "Sleep value has been increased of 1. Now its value is " << sleep_value << std::endl;

}

// Signal handler function for SIGALRM
void handleSIGALRM(int signal)
{
    std::cout << "SIGALRM received" << std::endl;
    sleep_value -= 1;
    std::cout << "Sleep value has been decreased of 1. Now its value is " << sleep_value << std::endl;
}

int main()
{
    auto pid = getpid();

    // Register signal handlers
    signal(SIGINT, handleSIGINT);
    signal(SIGUSR1, handleSIGUSR1);
    signal(SIGALRM, handleSIGALRM);

    // Main program logic
    std::cout << "(Processs ID: " << pid << "). Running the program. Press Ctrl+C to send SIGINT." << std::endl;

    // Simulating a long-running process

    while (signal_terminate.load() != 1)
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            std::cerr << "Failed to fork a child process." << std::endl;
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // Child process
            std::cout << "Child process  " << getpid() << " is running." << std::endl;
            int X = sleep_value;
            sleep(X);
            exit(0);
           
        }
        else
        {
            // Parent process
            int status;
            waitpid(pid, &status, 0);
            std::cout << "Child process " << pid << " has exited with status: " << WEXITSTATUS(status) << std::endl;
        }
        counter++;
    }
    return 0;
}

