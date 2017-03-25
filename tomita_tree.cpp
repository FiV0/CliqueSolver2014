#include "tomita_tree.h"

#include <iostream>
#include <vector>
#include <algorithm>

int * sets2;
int * reverse2;
int * clique2;
int cliSize2;
bool * inter2;

void tomita_helper2(int &l, int &r, int &m , std::vector< std::vector<int> > & adj,
                        std::vector< std::vector<int> > & res);

inline void swap3(int i, int j){

	int temp;

	reverse2[sets2[i]] = j;
	reverse2[sets2[j]] = i;

	temp = sets2[i];
	sets2[i] = sets2[j];
	sets2[j] = temp;

}

std::vector< std::vector<int> > tomita2(std::vector< std::vector<int> > & adj,int ma){

  int n = adj.size();
  std::vector< std::vector<int> > res;
	// initialization
	// add error checking

  sets2      = new int[n];
	reverse2   = new int[n];
	clique2    = new int[ma];
	cliSize2   = 0;
  inter2     = new bool[n];

	for(int i=0;i<n;++i){
		sets2[i] = i;
		reverse2[i] = i;
	}

	int l=0,r=n,m=0;

	//count = 0;


  tomita_helper2(l,r,m,adj,res);

  //std::cout<<std::endl<<std::endl<< count <<std::endl;
  //std::cout<< maxi <<std::endl;

	delete [] sets2;
	delete [] reverse2;
	delete [] clique2;
  delete [] inter2;

  return res;
}


void tomita_helper2(int &l, int &r, int &m , std::vector< std::vector<int> > & adj,
                        std::vector< std::vector<int> > & res){



		//max-clique2 found
		if (l >= r){
		  res.push_back( std::vector<int> (cliSize2));
      for(int i=0;i<cliSize2;++i){
        res[res.size()-1][i] = clique2[i];
      }
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
      if(neigh_sizes[sets2[i]] > maxx){
        piv = i;
        maxx = neigh_sizes[sets2[i]];
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
					if((int)adj[sets2[i]].size() > maxx){
            std::vector <int>::iterator it = adj[sets2[i]].begin();
            while(it != adj[sets2[i]].end() && m <= reverse2[*it] && reverse2[*it] < r){
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
      inter2[sets2[i]] = 1;
		}

		it = adj[sets2[piv]].begin();
		for(int i=0;i<maxx;++i){
		  inter2[*it] = 0;
			++it;
		}

    for(int i=m; i<r; ++i){
      if(inter2[sets2[i]]){
        move_back[size_mb++] = sets2[i];
      }
    }
    //std::cout<< size_mb << std::endl;

    //main part
		++cliSize2;
		int templ,tempr;
		templ = l;
		tempr = r;

    std::vector<int>::iterator mit;
		for(mit = move_back.begin(); mit != move_back.end(); ++mit){

        int cur = *mit;
				clique2[cliSize2-1] = cur;

        //move vertices to middle
				int x=0,p=0;

#ifndef _MATX_
        for(it = adj[cur].begin(); it != adj[cur].end(); ++it){
				//for(it = adj[sets2[r]].begin(); it != adj[sets2[r]].end(); ++it){
					if( l <= reverse2[*it] && reverse2[*it] < r ){
						if( reverse2[*it] < m ){
							swap3( reverse2[*it], m-1-x);
							++x;
						}else{
							swap3( reverse2[*it], m + p);
							++p;
						}
					}
				}
#endif

				l = m - x;
				r = m + p;

				//update neighbours
				for(int j=l;j<r;++j){
					it = adj[sets2[j]].begin();
					it2 = it;
					//int s = 0;
					while(it != adj[sets2[j]].end() && templ <= reverse2[*it] && reverse2[*it] < tempr ){
						if( m <= reverse2[*it] && reverse2[*it] < r ){
							std::iter_swap(it,it2);
							++it2;
              //++s;
						}
						++it;
					}
					//neigh_sizes[sets2[j]] = s;
				}

        //++level;

        /*try {
            tomita_helper(l,r,m,adj);
        }
        catch (std::exception& e)
        {
          std::cerr << "Exception catched : " << e.what() << std::endl;
        }*/

				tomita_helper2(l,r,m,adj,res);
        //--level;

				l=templ;
				r=tempr;

				/*if(tempm != m){
				  std::cout<< "At level :"<< level << std::endl;
          std::cout<<"Error with m" <<std::endl;
				}*/

				//move v to X and keep track
				swap3(m,reverse2[cur]);
        ++m;

				/*if(size_mb >= (int)move_back.size()){
          std::cout<<move_back.size()<<" vs. "<<size_mb<<std::endl;
          std::cerr<< "Error move_back allocation at level:" <<level<< std:: endl;
         // exit(EXIT_FAILURE);
				}*/
		}
		--cliSize2;

		// move back vertices from X to P
		for(it = move_back.begin(); it != move_back.end(); ++it){
		  --m;
			swap3(reverse2[*it],m);
		}
}
