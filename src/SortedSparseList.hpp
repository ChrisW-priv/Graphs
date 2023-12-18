#ifndef SORTEDSPARSELIST
#define SORTEDSPARSELIST 


#include "Graph.hpp"
#include <algorithm>
#include <cstddef>
#include <vector> 
#include <tuple>  
#include <string>   


// Forward declaration of File, Vertex, and Strategy types
using File = std::string;
using Vertex = std::size_t;
//TODO: make Strategy an actual pointer signature!
using Strategy = bool(*)(int, int); 


class SortedSparseList : public Graph<Relation> {
    std::vector<Vertex> starting_position;
    std::vector<std::size_t> relations;

    std::size_t get_begin_range(Vertex vertex) {
        return starting_position[vertex]; 
    }
    std::size_t get_end_range(Vertex vertex) {
        return starting_position[vertex+1]; 
    }
    auto get_relation_iter(Relation relation) {
        auto from = relation.v1;
        auto begin = get_begin_range(from);
        auto to = relation.v2;
        auto end = get_end_range(to);
        auto found_position = std::lower_bound(
                relations.begin()+begin,
                relations.end()+end,
                to);
        return found_position;
    }

public:
    SortedSparseList() = default;
    SortedSparseList(std::initializer_list<Relation> list) {
        for (auto relation : list) {
            insert_relation(relation);
        }
    }

    void insert_relation(Relation relation) {
        auto found_position = get_relation_iter(relation);
        relations.insert(found_position, relation.v2);
    }

    void insert_relation_undirected(Relation relation) {
        insert_relation(relation);
        insert_relation({relation.v2, relation.v1});
    }

    void remove_relation(Relation relation) {
        auto iter = get_relation_iter(relation);
        relations.erase(iter);
    }


    virtual void remove_vertex(Vertex vertex) {
        relations.erase(
                relations.begin() + get_begin_range(vertex), 
                relations.end() + get_end_range(vertex));
        starting_position.erase(starting_position.begin() + vertex);
        for (auto it=starting_position.begin(); it < starting_position.end(); ++ it) {

        }



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

    std::vector<Relation> get_neighbours(Vertex vertex) const {
        std::vector<Relation> result{};
        for (auto relation : relations){
            auto v1 = relation.v1;
            auto v2 = relation.v2;
            if (vertex == v1 || vertex == v2) {
                result.push_back(relation);
            }
        }
        return result;
    }
};


#endif // !SORTEDSPARSELIST
