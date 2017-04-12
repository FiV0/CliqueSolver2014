#ifndef _tomita_h_
#define _tomita_h_

/* This is the module that implements the tomita algorithm  used in tomita_test and mode_solver*/

#include <vector>
#include <list>
#include <fstream>

//#define _MATX_

// uncomment/comment the defines for _DEBUG_TOMITA_ and _MODE_SOLVER_ to switch between the mode_solver and tomita respectively

//#define _DEBUG_TOMITA_

#define _MODE_SOLVER_

extern std::ofstream out;

extern std::vector< std::list<int > >* tree_cliques;

void tomita(std::vector< std::vector <int> > & adj, int ma);

#endif
