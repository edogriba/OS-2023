#include <process.hpp>

#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <boost/spirit/include/qi.hpp>

void parsePath(std::string env_str, std::vector<std::string>& pathComponents)
{
  boost::spirit::qi::rule<std::string::iterator, std::string()> component = +(boost::spirit::qi::char_ - ':');
  boost::spirit::qi::rule<std::string::iterator, std::vector<std::string>()> pathGrammar = component % ':';

    // Parse the path
    auto it = env_str.begin();
    auto end = env_str.end();
    bool success = boost::spirit::qi::parse(it, end, pathGrammar, pathComponents);

    // Check if parsing was successful
    if (success && it == end) {
        // Print the path components
        for (const std::string& component : pathComponents) {
            std::cout << component << std::endl;
        }
    } else {
        std::cerr << "Failed to parse the path." << std::endl;
    }
}

std::string getFullCommandPath(const std::string& command) {
    std::string commandPath;
    std::vector<std::string> paths;

    parsePath(getenv("PATH"), paths);

    for (const auto& path : paths) {
        std::filesystem::path filePath(path + '/' + command);
	bool file_exists = std::filesystem::exists(filePath);
	bool file_is_regular_file = std::filesystem::is_regular_file(filePath);
	bool file_is_exec = false;
	if ( ( std::filesystem::status(filePath).permissions() &
		std::filesystem::perms::owner_exec) !=
		std::filesystem::perms::none )
	{
		file_is_exec = true;
	}

        if (file_exists &&
	    file_is_regular_file &&
	    file_is_exec)
        {
            commandPath = filePath.string();
            break;
        }
    }

    return commandPath;
}

int main (int argc, char** argv)
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <command> [args...]" << std::endl;
        return 1;
    }

    // Get the full path of the command
    std::string commandPath = getFullCommandPath(argv[1]);
    if (commandPath.empty()) {
        std::cerr << "Command not found." << std::endl;
        return 1;
    }

    // Set up the command and arguments for execvp()
    std::vector<std::string> commandArgs;
    for (int i = 1; i < argc; ++i) {
        commandArgs.push_back(argv[i]);
    }

    cse4733::process process(commandPath, commandArgs);

    if (process.execute()) {
        process.wait();
        std::cout << "Child process terminated." << std::endl;
    } else {
        // Error occurred
        return 1;
    }

    return 0;
}
