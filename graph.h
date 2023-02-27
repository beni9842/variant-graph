#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <set>
#include <unordered_set>

using Set = std::set<int>;

struct Node {
    Set set;
    std::vector<Node*> adj;

    Node(Set data):set(data),adj({}){};
    bool operator==(const Node &n);
};

using AdjList = std::vector<std::pair<Set, std::vector<Set>>>;

class Graph {
    std::vector<Node*> nodes;
    public:
        Graph() { nodes = {}; };
        // void BasicInsert(std::vector<Set> sets);
        // void SortedInsert(std::vector<Set> sets);
        void MSGInsert(std::vector<Set> sets);
        // void recursiveInsert(Node *parent, Node *new_node);
        static bool isSuperset(Set a, Set b);
        bool isMinimumSuperset(const Set &a, const Set &b);
        // static bool hasChildSuperset(Node *parent, Set set);
        AdjList getAdjList() const;
        void printGraph();
        // bool operator==(const Graph &g);
        static std::string toString(Set s);
        bool checkGraph();
};

#endif