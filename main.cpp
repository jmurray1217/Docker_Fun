#include <fstream>
#include "tools.hpp"

int main() {
    print_hello();
    std::ofstream out("/app/data/tasks.txt");
    out << "Buy milk\n";
    return 0;
}