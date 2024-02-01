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



template <typename Relation>
class SortedSparseList : public Graph<Relation> {
    std::vector<std::size_t> starting_position{0};
    std::vector<Vertex> relations{};

    auto get_begin_iter(Vertex vertex) const {
        return relations.begin() + starting_position[vertex]; 
    }
    auto get_end_iter(Vertex vertex) const {
        return relations.begin() + starting_position[vertex+1]; 
    }
    auto get_relation_iter(Vertex v1, Vertex v2) {
        auto begin = get_begin_iter(v1);
        auto end = get_end_iter(v1);
        auto found = std::upper_bound( begin, end, v2 );

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
        for (auto relation : list) {
            insert_relation(relation);
        }
    }

    void set_max_vertex(std::size_t vertex) {
        starting_position.resize(vertex + 1);
    }

    void insert_relation(const Relation& relation) {
        // check if node that is larger than current max node
        auto v1 = relation.v1;
        auto v2 = relation.v2;
        auto max = std::max(v1, v2);
        auto max_node = starting_position.size() - 1;
        // if it is larger, resize to new max
        // and fill the new values with last value of old map
        if (max > max_node) {
            starting_position.resize(max+2, starting_position.back());
        }

        auto found_position = get_relation_iter(relation);
        relations.insert(found_position, relation.v2);
        update_boundaries(relation.v1, 1);
    }

    void remove_relation(Relation relation) {
        auto iter = get_relation_iter(relation);
        relations.erase(iter);
        update_boundaries(relation.v1, -1);
    }

    virtual void remove_vertex(Vertex vertex) {
        // remove entire range of values
        auto begin = get_begin_iter(vertex);
        auto end = get_end_iter(vertex);
        relations.erase( begin, end );
        update_boundaries(vertex, begin - end);

        for (Vertex i=0; i<get_vertex_count(); i++) {
            auto begin = get_begin_iter(i);
            auto end = get_end_iter(i);
            auto found = std::upper_bound( begin, end, vertex );
            if (found != end) {
                relations.erase(found);
                update_boundaries(i, -1);
            }
        }
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
        for (auto i = 0; i < starting_position.size()-1; ++i) {
            if (get_neighbour_count(i) > 0)
                unique_vertexes.insert(i);
        }

        for (auto v : relations)
                unique_vertexes.insert(v);

        return unique_vertexes;
    }

    std::size_t get_vertex_count() const {
        return starting_position.size()-1;
    }


    std::size_t get_neighbour_count(Vertex vertex) const {
        return get_end_iter(vertex) - get_begin_iter(vertex);
    }

    std::vector<Vertex> get_neighbours(Vertex vertex) const {
        auto begin = get_begin_iter(vertex);
        auto end = get_end_iter(vertex);
        std::vector<Vertex> neighbours( begin, end );

        return neighbours;
    }
};


#endif // !SORTEDSPARSELIST
