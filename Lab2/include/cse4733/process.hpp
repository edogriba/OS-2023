#include <vector>
#include <string>

namespace cse4733 {

class process {
public:
    process(const std::string& path,
	 const std::vector<std::string>& args);

    bool execute();

    void wait();

    pid_t get_id() const;

private:
    pid_t processId;
    std::string executablePath;
    std::vector<std::string> arguments;
};

} // namespace cse4733
