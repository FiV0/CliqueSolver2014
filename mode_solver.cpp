#include "dm_clique.h"
#include "prime_graph_io.h"
#include "tomita.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

/* main file for mode_solver input file in prime graph format */

using namespace std;

vector< list<int> > * tree_cliques;

ofstream out;

int main(int argc, char * argv[]){

  if(argc != 3){
    cerr<< "Usage: > ./mode_solver input_file output_file" << endl;
    exit(EXIT_FAILURE);
  }

  ifstream in (argv[1]);
  out.open(argv[2],ofstream::out);

  if(in.is_open() && out.is_open()){

    char c;
    int n,m,i = 0;
    string line;
    stringstream ss;

    getline(in,line);
    ss.str(line);
    ss >> c >> n;
    //cout<<n<<endl;

    //trees
    vector< vector< vector<int> > >prime_edges;
    //node ** trees = new node*[n];
    node * tree;
    tree_cliques = new vector< list<int> >[n];

    //graph
    vector< vector<int> > p_graph(n, vector<int> ());

    while(i < n){
      getline(in, line);

      //cout<<line<<endl;
      //cout<<i<<endl;

      tree = tree_construction(line, prime_edges);
      tree_cliques[i] = tree_cliques_rec(tree,prime_edges);
      tree_destruction(tree);

      ++i;
    }

    getline(in,line);
    //cout<<line<<endl;
    ss.clear();
    ss.str(line);
    ss >> c >> m;
    //cout<<m<<endl;

    i=0;

    while(i < m){
      getline(in,line);
      ss.clear();
      ss.str(line);

      //cout<<line<<endl;

      int j,k;
      ss >> j >> k;

      p_graph[j-1].push_back(k-1);
      p_graph[k-1].push_back(j-1);

      ++i;
    }

    //test
    /*for(int i=0;i<n;++i){
      for(vector<int>::iterator it = p_graph[i].begin(); it != p_graph[i].end();++it){
      if(i == *it) cout << " big error"<< endl;
      }
      }*/

    int ma = -1;
    for(int i=0;i<n;++i){
      ma = max(ma,(int)p_graph[i].size());
    }

    tomita(p_graph,ma+1);

    /*for(int i=0;i<n;++i){
      tree_destruction(tree[i]);
      }*/

    //delete [] trees;
    delete [] tree_cliques;

    in.close();
    out.close();

  }else{
    if(!in.is_open()){
      cerr<< "Could not open input_file" << endl;
    }else{
      cerr<< "Could not open output_file" << endl;
    }
    exit(EXIT_FAILURE);
  }

  return 0;
}
