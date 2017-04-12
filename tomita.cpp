/***************************

  Written by Finn Völkel, 17.7.2014
  finn.volkel@etu.univ-lyon1.fr

  Please cite the following two papers when using this software:

  Tomita, E., Tanaka, A., Takahashi, H.: The worst-case time complexity for generating all
  maximal cliques and computational experiments. Theor. Comput. Sci. 363(1), 28–42 (2006)

  Eppstein, D., Strash, D.: Listing all maximal cliques in large sparse real-world graphs.
  10th Int. Symp. Experimental Algorithms, Crete, 2011

 ****************************/

#include "tomita.h"

#ifdef _MODE_SOLVER_

#include "dm_clique.h"
#include <list>

#endif

#include <iostream>
#include <vector>
#include <algorithm>

//int maxi;
//int level;

int count;

int * sets;
int * reverse;
int * clique;
int cliSize;
bool * inter;

//int * neigh_sizes;

#ifdef _MATX_
bool ** matx;
#endif

#ifdef _MODE_SOLVER_
int *sizes;
#endif


void tomita_helper(int &l, int &r, int &m , std::vector< std::vector<int> > & adj);

inline void swap2(int i, int j){

  int temp;

  reverse[sets[i]] = j;
  reverse[sets[j]] = i;

  temp = sets[i];
  sets[i] = sets[j];
  sets[j] = temp;

}

void tomita(std::vector< std::vector<int> > & adj,int ma){

  int n = adj.size();
  // initialization
  // add error checking

  // for use with small graphs (adj mat fits into memory)
#ifdef _MATX_
  matx      = new bool*[n];
  for(int i=0;i<n;++i){
    matx[i] = new bool[n-i];
    for(int j=0;j<n-i;++j){
      matx[i][j] = 0;
    }
    std::vector<int>::iterator it;
    for(it = adj[i].begin(); it != adj[i].end(); ++it){
      if(*it > i) matx[i][*it-i] = 1;
    }
  }
#endif

  sets      = new int[n];
  reverse   = new int[n];
  clique    = new int[ma];
  cliSize   = 0;
  inter     = new bool[n];

  //neigh_sizes = new int[n];


#ifdef _MODE_SOLVER_

  sizes = new int [ma];

#endif

  for(int i=0;i<n;++i){
    sets[i] = i;
    reverse[i] = i;
    //neigh_sizes[i] = adj[i].size();
  }

  //defines for recursive version or not
  int l=0,r=n,m=0;

  count = 0;
  //maxi = 0;
  //level = 1;



  tomita_helper(l,r,m,adj);

  std::cout<<std::endl<<std::endl<< count <<std::endl;
  //std::cout<< maxi <<std::endl;

  delete [] sets;
  delete [] reverse;
  delete [] clique;
  delete [] inter;

  //delete [] neigh_sizes;

#ifdef _MATX_
  for(int i=0;i<n;++i){
    delete [] matx[i];
  }
  delete [] matx;
#endif

#ifdef _MODE_SOLVER_

  delete [] sizes;

#endif

}

void tomita_helper(int &l, int &r, int &m , std::vector< std::vector<int> > & adj){

  //max-clique found
  if (l >= r){

#ifdef _DEBUG_TOMITA_

    /*for(int i=0;i<cliSize;i++){
      std::cout<< clique[i] << " ";
      }
      std::cout<<std::endl;*/
    std::vector<int> vec(cliSize);
    for(int i=0;i<cliSize;i++){
      vec[i] = clique[i];
    }

    sort(vec.begin(),vec.end());

    for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it){
      out<<*it<< " ";
    }
    out<<std::endl;

    ++count;
    //maxi = std::max(maxi, level);
#endif

#ifdef _MODE_SOLVER_

    for(int i=0;i<cliSize;++i){
      sizes[i] = 0;
    }

    bool finished = false;

    while(!finished){

      /*for(int i = 0;i<cliSize; ++i){
        std::list<int>::iterator it;
        for(it = tree_cliques[clique[i]][sizes[i]].begin();
        it != tree_cliques[clique[i]][sizes[i]].end(); ++it){
        std::cout<<*it<<" ";
        }
        }
        std::cout<<std::endl<<std::endl;*/

      std::vector<int> vec;
      for(int i = 0;i<cliSize; ++i){
        std::list<int>::iterator it;
        for(it = tree_cliques[clique[i]][sizes[i]].begin();
            it != tree_cliques[clique[i]][sizes[i]].end(); ++it){
          vec.push_back(*it);
        }
      }
      sort(vec.begin(),vec.end());

      for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it){
        out<<*it<< " ";
      }
      out<<std::endl;

      ++count;

      sizes[cliSize-1]++;

      //backtrack
      if(sizes[cliSize -1] == (int)tree_cliques[clique[cliSize-1]].size()){
        int i = cliSize-1;
        while( i >= 0 && sizes[i] >= (int)tree_cliques[clique[i]].size()-1 ){
          sizes[i] = 0;
          i--;
        }
        if(i >= 0){
          sizes[i]++;
        }else{
          finished = true;
        }
      }
    }

#endif

    //if(count % 10000 == 0)std::cout<<count<<std::endl;

    return;
  }

  // P empty
  if( m >= r){
    //maxi = std::max(maxi,level);
    return;
  }

  // search for pivot
  int piv;
  int maxx = -1;
  /*for(int i=l; i<r ; ++i){
    if(neigh_sizes[sets[i]] > maxx){
    piv = i;
    maxx = neigh_sizes[sets[i]];
    }
    }*/
  /*if(maxx < 0)
    std::cerr<<"Error finding pivot"<<std::endl;*/

  int n = adj.size();
  if( l == 0 && r == n){
    int count = 0;
    std::vector< std::vector<int> >::iterator it;
    for(it = adj.begin(); it != adj.end(); ++it){
      if( maxx < (int)it->size()){
        piv = count;
        maxx = it->size();
      }
      ++count;
    }
  }else{
    for(int i=l; i<r; ++i){
      int cur = 0;
      // check if condition is worth it
      if((int)adj[sets[i]].size() > maxx){
        std::vector <int>::iterator it = adj[sets[i]].begin();
        while(it != adj[sets[i]].end() && m <= reverse[*it] && reverse[*it] < r){
          ++it;
          ++cur;
        }
        if(maxx < cur){
          piv = i;
          maxx = cur;
        }
      }
    }
  }

  // continue if move_back size == 0
  if( r - m - maxx == 0 ){
    //maxi = std::max(maxi, level);
    return;
  }

  std::vector<int>::iterator it, it2, it3;

  // P \ largest
  int size_mb = 0;
  if( r - m - maxx < 0 ){
    std::cerr<<"Error with move_back allocation"<<std::endl;
    std::cout<<r<<" "<<m<<" "<< maxx <<std::endl;
  }

  std::vector<int> move_back(r-m-maxx);

  for(int i=m; i<r; ++i){
    inter[sets[i]] = 1;
  }

  it = adj[sets[piv]].begin();
  for(int i=0;i<maxx;++i){
    inter[*it] = 0;
    ++it;
  }

  for(int i=m; i<r; ++i){
    if(inter[sets[i]]){
      move_back[size_mb++] = sets[i];
    }
  }
  //std::cout<< size_mb << std::endl;

  //main part
  ++cliSize;
  int templ,tempr;
  templ = l;
  tempr = r;

  std::vector<int>::iterator mit;
  for(mit = move_back.begin(); mit != move_back.end(); ++mit){

    int cur = *mit;
    clique[cliSize-1] = cur;

    //move vertices to middle
    int x=0,p=0;

#ifndef _MATX_
    for(it = adj[cur].begin(); it != adj[cur].end(); ++it){
      //for(it = adj[sets[r]].begin(); it != adj[sets[r]].end(); ++it){
      if( l <= reverse[*it] && reverse[*it] < r ){
        if( reverse[*it] < m ){
          swap2( reverse[*it], m-1-x);
          ++x;
        }else{
          swap2( reverse[*it], m + p);
          ++p;
        }
      }
    }
#endif

#ifdef _MATX_
    int ma,mi;
    for(int i=l;i<m-x; ){
      ma = std::max(cur,sets[i]);
      mi = std::min(cur,sets[i]);
      if(matx[mi][ma-mi]){
        swap2(i,m-1-x);
        ++x;
      }else{
        ++i;
      }
    }

    for(int i=r-1;i>=m+p; ){
      ma = std::max(cur,sets[i]);
      mi = std::min(cur,sets[i]);
      if(matx[mi][ma-mi]){
        swap2(i,m+p);
        ++p;
      }else{
        --i;
      }
    }
#endif

    l = m - x;
    r = m + p;

    //update neighbours
    for(int j=l;j<r;++j){
      it = adj[sets[j]].begin();
      it2 = it;
      //int s = 0;
      while(it != adj[sets[j]].end() && templ <= reverse[*it] && reverse[*it] < tempr ){
        if( m <= reverse[*it] && reverse[*it] < r ){
          std::iter_swap(it,it2);
          ++it2;
          //++s;
        }
        ++it;
      }
      //neigh_sizes[sets[j]] = s;
    }

    //++level;

    /*try {
      tomita_helper(l,r,m,adj);
      }
      catch (std::exception& e)
      {
      std::cerr << "Exception catched : " << e.what() << std::endl;
      }*/

    tomita_helper(l,r,m,adj);
    //--level;

    l=templ;
    r=tempr;

    /*if(tempm != m){
      std::cout<< "At level :"<< level << std::endl;
      std::cout<<"Error with m" <<std::endl;
      }*/

    //move v to X and keep track
    swap2(m,reverse[cur]);
    ++m;

    /*if(size_mb >= (int)move_back.size()){
      std::cout<<move_back.size()<<" vs. "<<size_mb<<std::endl;
      std::cerr<< "Error move_back allocation at level:" <<level<< std:: endl;
    // exit(EXIT_FAILURE);
    }*/
    }
    --cliSize;

    // move back vertices from X to P
    for(it = move_back.begin(); it != move_back.end(); ++it){
      --m;
      swap2(reverse[*it],m);
    }
  }
