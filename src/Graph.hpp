#ifndef GRAPH_H
#define GRAPH_H


#include <cstddef>
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

    // Definition of counter iterator
    template <typename VertexType>
    struct Iter {
        std::size_t counter = 0;

        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = VertexType;
        using reference = value_type;
        using pointer = value_type;

        Iter() = default;
        Iter(std::size_t value = 0) : counter(value) {}
        Iter(const Iter &other) : counter(other.counter) {};
        Iter& operator=(const Iter& other) { counter = other.counter; };

        Iter& operator++() {
            ++counter;
            return *this;
        }

        Iter operator++(int) {
            Iter temp = *this;
            ++(*this);
            return temp;
        }

        Iter& operator--() {
            --counter;
            return *this;
        }

        Iter operator--(int) {
            Iter temp = *this;
            --(*this);
            return temp;
        }

        Iter& operator+=(int n) {
            counter += n;
            return *this;
        }

        Iter& operator-=(int n) {
            counter -= n;
            return *this;
        }

        int operator-(const Iter& other) const {
            return counter - other.counter;
        }

        int operator+(const Iter& other) const {
            return counter + other.counter;
        }

        bool operator==(const Iter& other) const {
            return counter == other.counter;
        }

        bool operator!=(const Iter& other) const {
            return !(*this == other);
        }

        std::size_t& operator*() {
            return counter;
        }

        const std::size_t& operator*() const {
            return counter;
        }
    };

    using iterator = Iter<Vertex>;
    using const_iterator = Iter<const Vertex>;

    Graph() = default;
    Graph(int);
    Graph(std::initializer_list<Relation>);
    Graph &operator=(Graph &&) = default;
    Graph &operator=(const Graph &) = default;
    ~Graph() = default;

    void import_from(File);
    void save_to(File);

    iterator begin() { return iterator{0}; }
    iterator end() { return iterator { this->get_vertex_count() }; }
    const_iterator begin() const { return const_iterator{0}; }
    const_iterator end() const { return const_iterator{ this->get_vertex_count() }; }

    void remove_vertex(iterator);
    void remove_vertex(Vertex);

    void insert_relation(Relation);
    void remove_relation(Relation);

    virtual std::size_t get_vertex_count() const;
    virtual std::size_t get_edge_count() const = 0;

    std::size_t get_neighbour_count(const_iterator) const;
    std::size_t get_neighbour_count(Vertex);

    std::vector<Relation> get_neighbours(const_iterator) const;
    std::vector<Relation> get_neighbours(Vertex);

    bool is_in_relation(iterator, iterator);
    bool is_in_relation(Vertex, Vertex);

    std::vector<Relation> single_source_shortest_path(const_iterator, const_iterator, Strategy) const;
    std::vector<Relation> single_source_shortest_path(Vertex, Vertex, Strategy);

    Graph<Relation> color_graph();
    std::size_t get_max_flow(iterator, iterator);
    std::size_t get_max_flow(Vertex, Vertex);

    std::tuple<int, std::vector<Relation>> get_max_flow_path(const_iterator, const_iterator) const;
    std::tuple<int, std::vector<Relation>> get_max_flow_path(Vertex, Vertex);

    std::vector<Vertex> find_eulerian_path();
    std::vector<Vertex> find_eulerian_circuit();

    std::vector<Relation> find_bridges();
    std::vector<Vertex> find_articulation_points();

    Graph<Relation> calculate_cartesian_product();
    Graph<Relation> calculate_tensor_product();
};


struct UndirectedRelation {
    int v1;
    int v2;

    // Overloading operator<< for UndirectedRelation
    friend std::ostream& operator<<(std::ostream& stream, const UndirectedRelation& relation) {
        stream << "{" << relation.v1 << ", " << relation.v2 << "}";
        return stream;
    }
};


class EdgeList : public Graph<UndirectedRelation> {
    std::vector<UndirectedRelation> relations{};
    using iterator = Graph<UndirectedRelation>::Iter<Vertex>;
    using const_iterator = Graph<UndirectedRelation>::Iter<Vertex>;

public:
    EdgeList() = default;
    EdgeList(std::initializer_list<UndirectedRelation> list) {
        for (auto relation : list) {
            relations.push_back(relation);
        }
    }

    std::size_t get_edge_count() const {
        return relations.size();
    }

    std::size_t get_vertex_count() const {
        std::set<Vertex> unique_vertexes{};
        for (auto relation : relations) {
            auto v1 = relation.v1;
            auto v2 = relation.v2;
            unique_vertexes.insert(v1);
            unique_vertexes.insert(v2);
        }

        return unique_vertexes.size();
    }

    std::vector<UndirectedRelation> get_neighbours(Vertex vertex) const {
        std::vector<UndirectedRelation> result{};
        for (auto relation : relations){
            auto v1 = relation.v1;
            auto v2 = relation.v2;
            if (vertex == v1 || vertex == v2) {
                result.push_back(relation);
            }
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& stream, const EdgeList& obj) {
        stream << "Number of Vertexes: " << obj.get_vertex_count() << '\n';
        for (auto vertex: obj) {
            stream << "Relation of Vertex: " << vertex << " are:\n";
            for (auto relation : obj.get_neighbours(vertex)) {
                stream << "\t" << relation << "\n";
            }
        }

        return stream;
    }
};


#endif // !GRAPH_H
