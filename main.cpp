#include "./src/Graph.hpp"
/* #include "./src/EdgeList.hpp" */
#include "./src/SortedSparseList.hpp"
#include <iostream>


int main() {
    Node<void> r1{0,2};
    Node<void> r2{2,4};
    Node<void> r3{4,6};
    Node<void> r4{6,8};
    Node<void> r5{8,10};
    Node<void> r6{10,12};
    
    SortedSparseList<Node<void>> g{ {r1, r2, r3, r4, r5, r6 } };
    
    std::cout << g << "\n";
    
    g.remove_vertex(6);
    std::cout << g << "\n";
    g.remove_vertex(2);
    std::cout << g << "\n";
}
