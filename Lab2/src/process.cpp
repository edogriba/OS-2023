#include <process.hpp>

#include <iostream>
#include <sstream>
#include <sys/wait.h>
#include <unistd.h>

namespace cse4733
{
    process::process(const std::string &path, const std::vector<std::string> &args)
        : processId(-1), executablePath(path), arguments(args) {}

    bool process::execute()
    {
        std::vector<char *> argv;
        for (const auto &arg : arguments)
        {
            argv.push_back(const_cast<char *>(arg.c_str()));
        }
        argv.push_back(nullptr);

        int f = fork(); //   Fork the parent process to create a child process.
        if (f < -1)
        {
            std::cerr << "Fork failed" << std::endl; //   If the fork fails, display an error message and exit.
            exit(1);
        }
        else if (f == 0)
        { //  This is the child process
            std::cout << "I am the Child process and this is my ProcessID: " << getpid() << std::endl; // Display its own PID
            std::cout << "I am the Child process and my Parent's ProcessID is: " << getppid() << std::endl; // Display the parent's PID.
            std::cout << "My role is: Child process" << std::endl; //   Display message
            execvp(executablePath.c_str(), argv.data()); //  Call to execvp()
            std::cout << "If execvp runs well this line should not be printed" << std::endl;
            exit(1);
        }
        else
        {  // This is the parent process
            std::cout << "I am the Parent process and this is my ProcessID: " << getpid() << std::endl;         // Display its own PID
            std::cout << "I am the Parent process and this is my Parent's ProcessID: " << getppid() << std::endl; // Display the parent's PID.
            std::cout << "My role is: Parent  " << std::endl; 
            process::wait();   //    Wait for the child process to terminate using the wait() system call.
            std::cout << "The child process terminated" << std::endl;  //    Display a message indicating the termination of the child process
            exit(0);
        }
    }
    void process::wait()
    {
        int status;
        waitpid(processId, &status, 0);
    }

    pid_t process::get_id() const
    {
        return this->processId;
    }

} // namespace cse4733
