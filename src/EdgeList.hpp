#ifndef EDGELIST
#define EDGELIST 


#include "Graph.hpp"
#include <algorithm>
#include <vector> 
#include <tuple>  
#include <string>   

// Forward declaration of File, Vertex, and Strategy types
using File = std::string;
//TODO: make Strategy an actual pointer signature!
using Strategy = bool(*)(int, int); 


template <typename Relation>
class EdgeList : public Graph<Relation> {
    std::vector<Relation> relations{};

public:
    EdgeList() = default;
    EdgeList(std::initializer_list<Relation> list) {
        for (auto relation : list) {
            insert_relation(relation);
        }
    }

    void insert_relation(const Relation& relation) {
        relations.push_back(relation);
    }

    void remove_relation(Relation relation) {
        auto iter = std::find(relations.begin(), relations.end(), relation);
        relations.erase(iter);
    }


    void remove_vertex(Vertex vertex) {
        relations.erase(
                std::remove_if(relations.begin(), relations.end(),
                    [vertex](Relation relation) {
                        return (relation.v1 == vertex || relation.v2 == vertex);
                    }
                ), relations.end());
    }


    std::set<Relation> get_edges() const {
        std::set<Relation> result(relations.begin(), relations.end());
        return result;
    }

    
    std::set<Vertex> get_vertexes() const {
        std::set<Vertex> unique_vertexes{};
        for (auto relation : relations) {
            auto v1 = relation.v1;
            auto v2 = relation.v2;
            unique_vertexes.insert(v1);
            unique_vertexes.insert(v2);
        }

        return unique_vertexes;
    }

    std::vector<Vertex> get_neighbours(Vertex vertex) const {
        std::vector<Vertex> result{};
        for (auto relation : relations){
            auto v1 = relation.v1;
            auto v2 = relation.v2;
            if (vertex == v1)
                result.push_back(v2);
            if (vertex == v2)
                result.push_back(v1);
        }
        return result;
    }
};


#endif // !EDGELIST
