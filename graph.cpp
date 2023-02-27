#include "graph.h"
#include <sstream>
#include <iostream>


// void Graph::SortedInsert(std::vector<Set> sets) {
//     nodes = {};
//     std::sort(sets.begin(), sets.end(), [](const Set &a, const Set &b) {
//         return a.size() < b.size();
//     });

//     for (const Set &set : sets) {
//         Node *new_node = new Node(set);
//         for (int i = nodes.size()-1; i >= 0; i--) {
//             Node *old_node = nodes[i];
//             if (isMinimumSuperset(old_node->set, new_node->set)) {
//                 old_node->adj.push_back(new_node);
//             }
//         }
//         nodes.push_back(new_node);
//     }
// }

void Graph::MSGInsert(std::vector<Set> sets) {
    nodes = {};
    std::sort(sets.begin(), sets.end(), [](const Set &a, const Set &b) {
        return a.size() < b.size();
    });

    Node *root = new Node({});
    Node *new_node;
    std::vector<Node*> parents, children;
    for (const Set &set : sets) {
        new_node = new Node(set);
        parents = { root };
        bool parentFound = false;
        while(!parentFound) {
            parentFound = true;
            for (auto it = parents.begin(); it != parents.end(); it++) {
                Node *parent = *it;
                for (Node *child : parent->adj) {
                    if (isSuperset(child->set, set)) {
                        parents.erase(it);
                        parents.push_back(child);
                        parentFound = false;
                    }
                }
            }
        }
        for (Node *parent : parents) {
            parent->adj.push_back(new_node);
        }
        nodes.push_back(new_node);
    }
}

bool Graph::isSuperset(Set a, Set b) {
    if (a.size() > b.size()) {
        return false;
    } else {
        return includes(b.begin(), b.end(), a.begin(), a.end());
    }
}


bool Graph::isMinimumSuperset(const Set &a, const Set &b) {

    if (isSuperset(a, b)) {
        for (Node *n : nodes) {
            const auto &c = n->set;
            if (a == c || b == c) {
                continue;
            }
            if (c.size() > a.size() && c.size() < b.size() && includes(c.begin(), c.end(), a.begin(), a.end()) && includes(b.begin(), b.end(), c.begin(), c.end())) {
                return false;
            }
        }

        return true;
    }

    return false;
}

AdjList Graph::getAdjList() const {
    AdjList adj_list;
    for (Node *node : nodes) {
        std::vector<Set> adj_sets;
        for (Node *adj_node : node->adj) {
            adj_sets.push_back(adj_node->set);
        }
        adj_list.push_back({node->set, adj_sets});
    }
    return adj_list;
}

std::string Graph::toString(Set s) {
    std::stringstream ss;
    for (int x : s) {
        ss << x << ",";
    }
    std::string str = ss.str();
    str.pop_back();
    return str;
}

void Graph::printGraph() {
    for (Node *n : nodes) {
        std::string node_str = toString(n->set);
        for (Node *adj : n->adj) {
            std::string adj_string = toString(adj->set);
            std::cout << node_str << " -> " << adj_string << std::endl;
        }
    }
}

bool Graph::checkGraph() {
    for (Node *node : nodes) {
        for (Node *child : node->adj) {
            if (!isMinimumSuperset(node->set, child->set)) {
                return false;
            }
        }
    }
    return true;
}