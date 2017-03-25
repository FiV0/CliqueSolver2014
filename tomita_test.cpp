#include "tomita.h"

#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

/* This is the main file for the tomita algorithm alone.
 * Input: # nodes #edges on the first line
 * 				then all the edges on the next # edges of lines
 *
 * Attention!  Nodes need to numbered 0 to # nodes -1 
 * 		
 */

using namespace std;

ofstream out;

int main(int argc, char * argv[]){

  if(argc != 2 && argc != 3){
    cerr<<"Usage: > ./tomita_test input_file output_file"<<std::endl;
    exit(EXIT_FAILURE);
  }

  ifstream in( argv[1]);
  out.open(argv[2],ofstream::out);

  if(!in.is_open()){
    cerr<<"Failed to open file: "<<argv[1]<<endl;
    exit(EXIT_FAILURE);
  }

  /*if(!out.is_open()){
    cerr<<"Failed to open file: "<<argv[2]<<endl;
    exit(EXIT_FAILURE);
  }*/

  string line;

  getline(in,line);
  stringstream ss (line);

  int n,m,ma=0;
  ss>> n >> m;

  vector< vector <int> > graph (n, vector<int> ());

  for(int i=0;i<m;++i){
    getline(in, line);
    ss.clear();
    ss.str(line);

    int j,k;
    ss>> j >> k;

    graph[j].push_back(k);
    graph[k].push_back(j);
  }

  for(int i=0; i<n; ++i){
    ma = max(ma,(int)graph[i].size());
  }

  tomita(graph, ma+1);

  return 0;
}
