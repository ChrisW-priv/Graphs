#ifndef SORTEDSPARSELIST
#define SORTEDSPARSELIST 


#include "Graph.hpp"
#include <algorithm>
#include <cstddef>
#include <set>
#include <vector> 
#include <tuple>  
#include <string>   


// Forward declaration of File, Vertex, and Strategy types
using File = std::string;
using Vertex = std::size_t;
//TODO: make Strategy an actual pointer signature!
using Strategy = bool(*)(int, int); 


class SortedSparseList : public Graph<Relation> {
    std::vector<Vertex> starting_position{0};
    std::vector<std::size_t> relations{};

    std::size_t get_begin_range(Vertex vertex) const {
        return starting_position[vertex]; 
    }
    std::size_t get_end_range(Vertex vertex) const {
        return starting_position[vertex+1]; 
    }
    auto get_relation_iter(Vertex v1, Vertex v2) {
        auto begin = relations.begin() + get_begin_range(v1);
        auto end = relations.end() + get_end_range(v1);
        auto found = std::lower_bound( begin, end, v2);

        return found;
    }
    auto get_relation_iter(Relation relation) {
        auto from = relation.v1;
        auto to = relation.v2;
        return get_relation_iter(from, to);
    }
    void update_boundaries(std::size_t vertex_updated, std::size_t by_how_much){
        for (auto i = vertex_updated+1; i < starting_position.size(); ++i) {
            starting_position[i] += by_how_much;
        }
    }


public:
    SortedSparseList() = default;
    SortedSparseList(std::initializer_list<Relation> list) {
        set_max_vertex(13);
        for (auto relation : list) {
            insert_relation(relation);
        }
    }

    void set_max_vertex(Vertex vertex) {
        starting_position.resize(vertex);
    }

    void insert_relation(Relation relation) {
        // check if node that is larger than current max node
        auto v1 = relation.v1;
        auto v2 = relation.v2;
        auto max = std::max(v1, v2);
        auto max_node = starting_position.size() - 1;
        // if it is larger, resize to new max
        // and fill the new values with last value of old map
        if (max > max_node) {
            starting_position.resize(max, starting_position.back());
        }

        auto found_position = get_relation_iter(relation);
        relations.insert(found_position, relation.v2);
        update_boundaries(relation.v1, 1);
    }

    void remove_relation(Relation relation) {
        auto iter = get_relation_iter(relation);
        relations.erase(iter);
    }

    virtual void remove_vertex(Vertex vertex) {
        // remove entire range of values
        relations.erase(
                relations.begin() + get_begin_range(vertex), 
                relations.end() + get_end_range(vertex));

        for (Vertex i=0; i<get_vertex_count(); i++) {
            auto begin = relations.begin() + get_begin_range(i);
            auto end = relations.end() + get_end_range(i);
            auto found = std::lower_bound( begin, end, vertex);
            if (found != end) 
                relations.erase(found);
        }
        
        // remove reference in map
        starting_position.erase(starting_position.begin() + vertex);
    }

    std::set<Relation> get_edges() const {
        std::set<Relation> result(relations.begin(), relations.end());
        return result;
    }

    std::size_t get_edge_count() const {
        return relations.size();
    }


    std::set<Vertex> get_vertexes() const {
        std::set<Vertex> unique_vertexes{};
        for (auto relation : relations) {
            unique_vertexes.insert(relation);
        }

        return unique_vertexes;
    }

    std::size_t get_vertex_count() const {
        return starting_position.size()-1;
    }

    std::vector<Relation> get_neighbours(Vertex vertex) const {
        std::vector<Vertex> neighbours(
                relations.begin() + get_begin_range(vertex), 
                relations.end() + get_end_range(vertex+1));

        std::vector<Relation> result;

        for (const auto &x : neighbours) {
            result.push_back({vertex, x});
        }
        return result;
    }
};


#endif // !SORTEDSPARSELIST
