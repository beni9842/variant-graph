#include "graph.h"

#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

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

    // graph construction
    auto start = std::chrono::high_resolution_clock::now();
    Graph g;
    g.MSGInsert(sets);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Graph constructed in " << duration.count() << "ms." << std::endl;

    std::cout << "Retrieving adjacency lists..." << std::endl;
    AdjList output_list = g.getAdjList();
    std::cout << "Writing to output file..." << std::endl;
    writeFile(output_filename, output_list);

    std::cout << "Would you like to confirm that the output graph is an MSG? (y/n) ";
    std::string input;
    std::cin >> input;
    if (input[0] == 'y' || input[0] == 'Y') {
        bool isMSG =  g.checkGraph();
        if (isMSG) {
            std::cout << "Correctly outputted a MSG." << std::endl;
        } else {
            std::cout << "Output is not a valid MSG." << std::endl;
        }
    }
    // variant_graph.printGraph();
    return 0;
}