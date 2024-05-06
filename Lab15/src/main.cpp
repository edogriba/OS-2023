#include <iostream>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>
#include <boost/program_options.hpp>

// Thread local storage for the number
thread_local int number = 2;
thread_local int prime = 2;

bool isPrime(int number) {
    if(number < 2) return false;
    for(int i = 2; i * i <= number; i++){
        if(number % i == 0){
            return false;
        }
    }
    return true;
}

void work(int id) {
    // first create and start timer
    std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now(); 
    std::chrono::duration<double> elapsed;
    //computing prime numbers
    while (true) {
        if (isPrime(number)) {
            prime = number;
        }
        number++;
        // trying to context switch
        std::this_thread::yield();
        std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
        // calcultating elapsed time
        elapsed = end_time - start_time;
        if ((float) elapsed.count() >= 30.0) {
            break; // if too much time has passed break
        }
    }   

    std::stringstream os;
    os << "Thread " << id << " ended. "
       << "Total run time: " << elapsed.count()
       << " seconds. Largest prime calculated: " << prime;
    std::cout << std::flush << os.str() << std::endl;
}



int main(int argc, char *argv[]) {
    try {
        boost::program_options::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("threads", boost::program_options::value<int>(), "set the number of threads")
        ;

        boost::program_options::variables_map vm;
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
        boost::program_options::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 1;
        }

        
        int num_threads = 0;
        if (vm.count("threads")) {
            num_threads = vm["threads"].as<int>();
        }
        else {
            std::cout << desc << "\n";
            return 1;
        }
        // create a vector of threads
        std::vector<std::thread> t_vec;
        for (int i=0; i<num_threads; i++) {
            t_vec.push_back(std::thread (work, i));
        }
        for (std::thread& t : t_vec) {
            t.join(); // join thread with the main one
        }
    }
    catch(std::system_error& e) {
        std::cerr << "System error: " << e.what() << "\n";
        return 1;
    }
    catch(boost::program_options::invalid_option_value& e) {
        std::cerr << "Invalid option value: " << e.what() << "\n";
        return 1;
    }
    catch(boost::program_options::unknown_option& e) {
        std::cerr << "Unknown option: " << e.what() << "\n";
        return 1;
    }
    catch(boost::program_options::multiple_occurrences& e) {
        std::cerr << "Multiple occurrences of the same option: " << e.what() << "\n";
        return 1;
    }
    catch(std::exception& e) {
        std::cerr << "Standard exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}

