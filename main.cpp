#include "src/Graph.hpp"
#include <iostream>


int main() {
    UndirectedRelation r1{0,2};
    UndirectedRelation r2{2,4};
    UndirectedRelation r3{4,6};
    UndirectedRelation r4{6,8};
    UndirectedRelation r5{8,10};
    UndirectedRelation r6{10,12};

    EdgeList g{ {r1, r2, r3, r4, r5, r6 } };

    std::cout << g << "\n";
}
