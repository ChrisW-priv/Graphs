#include "./src/Graph.hpp"
#include "./src/EdgeList.hpp"
#include "./src/SortedSparseList.hpp"
#include <iostream>


int main() {
    
    EdgeList<> g{{
        {0,2},
        {2,4},
        {4,6},
        {6,8},
        {8,10},
        {10,12}
    }};
    
    std::cout << g << "\n";
    
    g.remove_vertex(6);
    std::cout << g << "\n";
    g.remove_vertex(2);
    std::cout << g << "\n";
}
