# variant-graph

## Project Overview
This program attempts to solve the issue of mapping COVID-19 RNA genome-mutations by representing RNA variants as unique, numerical sets and then creating a Minimum Superset Graph. This graph will output an adjacency list between variants and will serve as a sort of "family-tree" for the COVID-19 genome.

## Usage (Mac OS)
Clone this repository and navigate inside. Run the command `make` to build the executable. To execute the program, run the command `./variant_graph path/to/input.txt path/to/output.txt`. Your second and third arguments correspond to input and output file paths. Input files are text files with lines of comma-separated values, corresponding to a list of sets. An output .txt file representing the MSG adjacency list is generated at the output file path. After output generation, the user is prompted to check if the output is a valid MSG. This option is recommended not to be used for large data-sets as the algorithm used for checking the MSG is more complex than the one constructing it. 

## Minimum Superset Graph
A Minimum Superset Graph (MSG) is the data structure that will house the variant-data. This data structure is defined as a directed graph where nodes correspond to sets in the sample space and for every edge `(a,b)`, `b` is a minimum superset of `a`. To qualify as a minimum superset, `b` must be a superset of `a` (that is, `a` is a subset of `b`) and there exists no set `c` in the sample space such that `b` is a superset of `c` and `c` is a superset of `a` (hence the "minimum" descriptive). 

## MSG Insert Algorithm
* Input: list of sets, `L`
* Output: adjacency list corresponding to the MSG
```
sort L by increasing set-size
create an empty set of nodes
define the "root node", R, as the node representing the empty set, {}
for each set S in L:
    create a new node N for set S
    create a list of parent-nodes, consisting of one parent, R
    while a parent has children that are subsets of S:
        for each parent, P:
            for each adjacent node of P, C:
                if S is superset of C:
                    remove P from parents
                    add C to parents
    for each node in parents, P:
        add N to P's adjacency list
    add N to the set of nodes
```
