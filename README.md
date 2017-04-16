
### Maximal Clique Enumeration

This software implements maximal clique enumeration on graphs.
The algorithms are based on the following two papers:

[The worst-case time complexity for generating all maximal cliques and computational experiments, Tomita et al.](http://www.sciencedirect.com/science/article/pii/S0304397506003586)

[Listing All Maximal Cliques in Sparse Graphs in Near-optimal Time, Eppstein et al.](https://arxiv.org/abs/1006.5440)

The `tomita_t` program takes a graph in edge list format as input and outputs every
maximal clique (one per line).

The `mode_solver` program takes a prime graph as input and outputs every maximal clique (one per line).
Modules in the prime graph help to eliminate some computations of the general case.

To switch between mode_solver and tomita_t, follow the comments in the makefile
and uncomment/comment the respecive compilations directives in tomita.h

#### Author:
Finn Völkel
