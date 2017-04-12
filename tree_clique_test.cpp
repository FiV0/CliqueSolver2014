#include "prime_graph_io.h"
#include "dm_clique.h"

#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <cstdlib>

/* test file for prime_graph_io and dm_clique */

using namespace std;

void print_tree(node * tree,int l){

  for(int i=0;i<l;++i){
    cout<<"-";
  }

  if(tree->type == LEAF){
    cout<<tree->num<<endl;
  }else{
    switch (tree->type){
      case SERIE:
        cout<<"S";
        break;
      case PARALLEL:
        cout<<"L";
        break;
      default:
        cout<<"P";
    }
    cout<<endl;
    child * c = tree->children;
    while(c){
      print_tree(c->no, l + 1);
      c = c->next;
    }
  }
}

int main (int argc, char * argv[]){

  if(argc != 2){
    cerr<<"Usage:> ./tree_clique_test input.txt"<<endl;
    exit(EXIT_FAILURE);
  }

  ifstream in( argv[1] );

  if(in.is_open()){

    string line;
    if(getline(in,line)){
      vector< vector < vector<int> > > prime_edges;
      node * tree = tree_construction(line, prime_edges);
      print_tree(tree,0);

      vector< list<int> > res = tree_cliques_rec(tree,prime_edges);

      vector< list<int> >::iterator vit;
      list<int>::iterator lit;
      for(vit = res.begin(); vit != res.end(); ++vit){
        for(lit = vit->begin(); lit != vit->end(); ++lit)
          cout<< *lit << " ";
        cout<<endl;
      }

      tree_destruction(tree);
    }

  }else{
    cerr<<"ERROR opening file"<<endl;
    exit(EXIT_FAILURE);
  }

  return 0;
}
