#ifndef _prime_graph_io_
#define _prime_graph_io_

/* This module does the input ouput for graphs in prime graph format 
 * as I used it with Sofiane
 */

#include <string>
#include <vector>
#include <utility>

#define LEAF 0
#define SERIE 1
#define PARALLEL 2
#define PRIME 3

struct node;

struct child{
	node * no;
	child * next;
};

struct node{
	int type;
	child * children;
	int num;
};

node * tree_construction(std::string line,
			std::vector< std::vector< std::vector<int> > > & prime_edges);
void tree_destruction(node * n);


#endif

