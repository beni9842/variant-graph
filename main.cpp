#include "graph.h"

#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>

std::vector<Set> readFile(std::string &filename) {
    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        exit(1);
    }

    std::vector<Set> sets;
    std::string line;
    while(getline(input_file, line)) {
        Set set;
        std::stringstream ss(line);
        std::string number;
        while (getline(ss, number, ',')) {
            int x = stoi(number);
            set.insert(x);
        }
        sets.push_back(set);
    }

    input_file.close();
    return sets;
}

void writeFile(std::string &filename, AdjList &output_list) {
    std::ofstream output_file(filename);

    for (auto &adj_pair : output_list) {
        Set set = adj_pair.first;
        std::vector<Set> adj_sets = adj_pair.second;
        std::string set_str = Graph::toString(set);
        for (const Set &adj_set : adj_sets) {
            std::string adj_set_str = Graph::toString(adj_set);
            output_file << set_str << " -> " << adj_set_str << std::endl;
        }
    }

    output_file.close();
}

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Usage: ./main /input/file/path.txt /output/file/path.txt" << std::endl;
        exit(1);
    }
    std::string input_filename = argv[1];
    std::string output_filename = argv[2];
    std::cout << "Attempting to read from file " << input_filename << "..." << std::endl;
    std::vector<Set> sets = readFile(input_filename);
    std::cout << "Assembling graph..." << std::endl;
    Graph basic_graph, tree_graph;
    //basic_graph.SortedInsert(sets);
    tree_graph.TreeInsert(sets);
    std::cout << "Retrieving adjacency lists..." << std::endl;
    AdjList basic_output_list = basic_graph.getAdjList();
    AdjList tree_output_list = tree_graph.getAdjList();
    std::cout << "Writing to output files..." << std::endl;
    std::stringstream basic_ss, tree_ss;
    basic_ss << output_filename << ".basic";
    std::string basic_filename = basic_ss.str();
    tree_ss << output_filename << ".tree";
    std::string tree_filename = tree_ss.str();
    writeFile(basic_filename, basic_output_list);
    writeFile(tree_filename, tree_output_list);
    std::cout << basic_graph.checkGraph() << tree_graph.checkGraph() << std::endl;
    // variant_graph.printGraph();
    return 0;
}