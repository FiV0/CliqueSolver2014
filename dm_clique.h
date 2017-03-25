#ifndef _dm_clique_h_
#define _dm_clique_h_

/* This module finds the diffrent cliques from the prime graphs nodes
 * which are themselves trees*/

#include "prime_graph_io.h"
#include <list>
#include <vector>


std::vector< std::list<int> > tree_cliques_rec(node * tree,
                std::vector< std::vector< std::vector<int> > > & prime_edges);

std::vector< std::list<int> > tree_cliques_ite(node * tree,
                std::vector< std::vector< std::vector<int> > > & prime_edges);

#endif
