# variant-graph

## Project Overview
This program attempts to solve the issue of mapping COVID-19 RNA genome-mutations by representing RNA variants as unique, numerical sets and then creating a Minimum Superset Graph. This graph will output an adjacency list between variants and will serve as a sort of "family-tree" for the COVID-19 genome.

## Usage (Mac OS)
Clone this repository and navigate inside. Run the command `make` to build the executable. To execute the program, run the command `./variant_graph path/to/input.txt path/to/output.txt`. Your second and third arguments correspond to input and output file paths. Input files are text files with lines of comma-separated values, corresponding to a list of sets. An output .txt file representing the MSG adjacency list is generated at the output file path. After output generation, the user is prompted to check if the output is a valid MSG. This option is recommended not to be used for large data-sets as the algorithm used for checking the MSG is more complex than the one constructing it. 

## Minimum Superset Graph
A Minimum Superset Graph (MSG) is the data structure that will house the variant-data. This data structure is defined as a directed graph where nodes correspond to sets in the sample space and for every edge $(a,b)$, $b$ is a minimum superset of $a$. To qualify as a minimum superset, $b$ must be a superset of $a$ (that is, $a$ is a subset of $b$) and there exists no set $c$ in the sample space such that $b$ is a superset of $c$ and $c$ is a superset of $a$ (hence the "minimum" descriptive). 

## Tree Insert Algorithm
* Input: list of sets, L
* Output: adjacency list corresponding to the MSG

1. Create an empty list of nodes (each node will correspond to an adjacency pair).
2. Sort L by increasing set-size.
3. Define a root node as a node for the empty set.
4. For set S in L:
    1. create a node N for set S
    2. use the Recursive Insert algorithm with the root node and N
    3. add N to the list of nodes

## Recursive Insert Algorithm
* Input: nodes P and N

1. For adjacent node C of P:
    1. if C is superset of N:
        1. recursiveInsert(C, N)
        2. quit
2. add N to the adjacency list for P
    
