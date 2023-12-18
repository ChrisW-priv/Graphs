#ifndef GRAPH_H
#define GRAPH_H


#include <cstddef>
#include <map>
#include <set>
#include <vector> 
#include <tuple>  
#include <string>   
#include <iostream>


// Forward declaration of File, Vertex, and Strategy types
using File = std::string;
using Vertex = std::size_t;
//TODO: make Strategy an actual pointer signature!
using Strategy = bool(*)(int, int); 


template<typename Relation>
struct Graph {

    Graph() = default;
    Graph(int);
    Graph(std::initializer_list<Relation>);
    Graph &operator=(Graph &&) = default;
    Graph &operator=(const Graph &) = default;
    ~Graph() = default;

    void import_from(File);
    void save_to(File);

    virtual void remove_vertex(Vertex) = 0;

    virtual void insert_relation(Relation) = 0;
    virtual void remove_relation(Relation) = 0;

    virtual std::set<Vertex> get_vertexes() const = 0;
    virtual std::set<Relation> get_edges() const = 0;
    
    std::size_t get_vertex_count() const {
        return get_vertexes().size();
    }

    std::size_t get_edge_count() const {
        return get_edges().size();
    }

    virtual std::vector<Relation> get_neighbours(Vertex) const = 0;
    std::size_t get_neighbour_count(Vertex vertex) {
        return get_neighbours(vertex).size();
    }

    std::vector<Relation> single_source_shortest_path(Vertex, Vertex, Strategy);

    Graph<Relation> color_graph();

    std::size_t get_max_flow(Vertex, Vertex);
    std::tuple<int, std::vector<Relation>> get_max_flow_path(Vertex, Vertex);

    std::vector<Vertex> find_eulerian_path();
    std::vector<Vertex> find_eulerian_circuit();

    std::vector<Relation> find_bridges();
    std::vector<Vertex> find_articulation_points();

    Graph<Relation> calculate_cartesian_product();
    Graph<Relation> calculate_tensor_product();
    
    friend std::ostream& operator<<(std::ostream& stream, const Graph<Relation>& obj) {
        auto vertexes = obj.get_vertexes();

        stream << "Number of Vertexes: " << obj.get_vertex_count() << '\n';
        for (auto vertex: vertexes) {
            stream << "Relation of Vertex: " << vertex << " are:\n";
            for (auto relation : obj.get_neighbours(vertex)) {
                stream << "\t" << relation << "\n";
            }
        }

        return stream;
    }
};


struct Relation {
    Vertex v1;
    Vertex v2;

    auto operator<=>(const Relation& relation) const = default;

    friend std::ostream& operator<<(std::ostream& stream, const Relation& relation) {
        stream << "{" << relation.v1 << ", " << relation.v2 << "}";
        return stream;
    }
};



struct WeightedRelation : public Relation {
    std::size_t weight;

    friend std::ostream& operator<<(std::ostream& stream, const WeightedRelation& relation) {
        stream << "{" << relation.v1 << ", " << relation.v2 << ", " << relation.weight << "}";
        return stream;
    }
};


#endif // !GRAPH_H
