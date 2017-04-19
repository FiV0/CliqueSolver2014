
### Maximal Clique Enumeration

This software implements maximal clique enumeration on graphs.
The algorithms are based on the following two papers:

[The worst-case time complexity for generating all maximal cliques and computational experiments, Tomita et al.](http://www.sciencedirect.com/science/article/pii/S0304397506003586)

[Listing All Maximal Cliques in Sparse Graphs in Near-optimal Time, Eppstein et al.](https://arxiv.org/abs/1006.5440)

The `tomita_t` program takes a graph in edge list format as input and outputs every
maximal clique (one per line).

The format for `tomita_t` is as follows: The first line contains the number of nodes and then follow the edges one per line, indicated by two 0-indexed vertices.
Example (the triangle):
```
3
0 1
0 2
1 2
```

The `mode_solver` program takes a prime graph as input and outputs every maximal clique (one per line).
Modules in the prime graph help to eliminate some computations of the general case.

The format for `mode_solver` as follows: The first part contains the prime vertices which are either simple vertices (the vertex number of the original graph) or prime (Premier), series (Serie) or parallel (Parallel) nodes. The second part contains the edges of the prime graph 0-indexed.

Example:
```
12
11
Serie( 8 9 )
10
7
Premier( 6 5 3 4 : [1 2 2 4 3 4 ] )
Serie( 2 1 )
0
1 3
1 4
2 3
2 4
3 5
4 5
5 6
6 7
7 8
```

The first 8 lines contain the prime graph vertices. The remaining 9 lines contain the prime graph edges. Serie or Parallel nodes contain their corresponding
nodes from the original graph. Premier nodes contain on top of the corresponding nodes (6 5 3 4 in the example) of the original graph and edge list ([1 2 2 4 2 4])
describing the connections in the module. The edge list [1 2 2 4 3 4] describes the edges (6 5), (5 4) and (3 4) inside the module.

To switch between mode_solver and tomita_t, follow the comments in the makefile
and uncomment/comment the respecive compilations directives in tomita.h

#### Author:
Finn Völkel
