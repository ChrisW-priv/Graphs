#ifndef GRAPH_H
#define GRAPH_H


#include <cstddef>
#include <map>
#include <set>
#include <vector> 
#include <tuple>  
#include <string>   
#include <iostream>


// Forward declaration of File, VertexType, and Strategy types
using File = std::string;
//TODO: make Strategy an actual pointer signature!
using Strategy = bool(*)(int, int); 


template<typename PayloadType=void, typename VertexType=std::size_t>
struct Graph {
    template <typename NodePayloadType, typename NodeVertexType>
    struct Node {
        NodeVertexType v1;
        NodeVertexType v2;
        NodePayloadType payload;
        auto operator<=>(const Node<NodePayloadType, NodeVertexType>& relation) const = default;
        friend std::ostream& operator<<(std::ostream& stream, const Node<NodePayloadType, NodeVertexType>& relation) {
            stream << "{" << relation.v1 << ", " << relation.v2 << "}";
            return stream;
        }
    };
    // Specialization for when T is void
    template <typename NodeVertexType>
    struct Node<void, NodeVertexType> {
        NodeVertexType v1;
        NodeVertexType v2;
        auto operator<=>(const Node<void, NodeVertexType>& relation) const = default;
        friend std::ostream& operator<<(std::ostream& stream, const Node<void, NodeVertexType>& relation) {
            stream << "{" << relation.v1 << ", " << relation.v2 << "}";
            return stream;
        }
    };
    using Relation = Node<PayloadType, VertexType>;

    Graph() = default;
    Graph(int);
    Graph(std::initializer_list<Relation>);
    Graph &operator=(Graph &&) = default;
    Graph &operator=(const Graph &) = default;
    ~Graph() = default;

    void import_from(File);
    void save_to(File);

    virtual void remove_vertex(VertexType) = 0;

    virtual void insert_relation(const Relation&) = 0;
    virtual void remove_relation(Relation) = 0;

    virtual std::set<VertexType> get_vertexes() const = 0;
    virtual std::set<Relation> get_edges() const = 0;
    
    std::size_t get_vertex_count() const {
        return get_vertexes().size();
    }

    std::size_t get_edge_count() const {
        return get_edges().size();
    }

    virtual std::vector<VertexType> get_neighbours(VertexType vertex) const = 0;
    std::size_t get_neighbour_count(VertexType vertex) const {
        return get_neighbours(vertex).size();
    }

    std::vector<Relation> single_source_shortest_path(VertexType, VertexType, Strategy);

    Graph<Relation> color_graph();

    std::size_t get_max_flow(VertexType, VertexType);
    std::tuple<int, std::vector<Relation>> get_max_flow_path(VertexType, VertexType);

    std::vector<VertexType> find_eulerian_path();
    std::vector<VertexType> find_eulerian_circuit();

    std::vector<Relation> find_bridges();
    std::vector<VertexType> find_articulation_points();

    Graph<Relation> calculate_cartesian_product();
    Graph<Relation> calculate_tensor_product();
    
    friend std::ostream& operator<<(std::ostream& stream, const Graph<PayloadType, VertexType>& obj) {
        auto vertexes = obj.get_vertexes();

        stream << "Number of Vertexes: " << obj.get_vertex_count() << '\n';
        for (auto vertex: vertexes) {
            stream << "Relations of VertexType: " << vertex << " are:\n";
            for (auto relation : obj.get_neighbours(vertex)) {
                stream << "\t" << relation << "\n";
            }
        }

        return stream;
    }
};


#endif // !GRAPH_H
