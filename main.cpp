#include "./src/Graph.hpp"
#include "./src/EdgeList.hpp"
#include "./src/SortedSparseList.hpp"
#include <iostream>


int main() {

    Relation r1{0,2};
    Relation r2{2,4};
    Relation r3{4,6};
    Relation r4{6,8};
    Relation r5{8,10};
    Relation r6{10,12};
    
    SortedSparseList g{ {r1, r2, r3, r4, r5, r6 } };
    
    std::cout << g << "\n";
    
    g.remove_vertex(6);
    std::cout << g << "\n";
    g.remove_vertex(2);
    std::cout << g << "\n";
}
