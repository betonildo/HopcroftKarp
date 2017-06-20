#include "common.hpp"
#include "graph.hpp"
#include "read_dimacs.hpp"

int main() {

    Graph g;

    read_dimacs(stdin, g);

    uint matching = g.maximumMatching();
    std::cout << matching << std::endl;

    return 0;
}
