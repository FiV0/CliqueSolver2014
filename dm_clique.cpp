#include "dm_clique.h"
#include "tomita_tree.h"

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

vector< list <int> > tree_cliques_ite(node * tree, vector< vector< vector<int> > > & prime_edges){

	return vector< list <int> > () ;
}

vector< list<int> > tree_cliques_rec(node * tree ,
								vector< vector< vector<int> > > & prime_edges){

	switch (tree->type){
		case LEAF:
      {
        vector< list<int> > res (1);
        res[0] = list<int> (1,tree->num);
        return res;
        break;
      }
		case SERIE:
      {
			vector< list <int> > res;
			vector< vector< list<int> > > res_children;
			//get results from children
			for( child * c = tree->children; c != NULL ; c = c->next ){
				res_children.push_back(tree_cliques_rec(c->no,prime_edges));
			}

			// do combinations
			int n = res_children.size();
			int * size = new int[res_children.size()];
			bool finished = false;
			for(int i=0;i<n;i++) size[i] = 0;

			while(!finished){

        if(size[0] >= (int)res_children[0].size()) {
          cerr<<"Error occured during backtracking"<<endl;
          exit(EXIT_FAILURE);
        }
        //cout<<res_children[0].size()<<endl;
        //cout<<res_children[1].size()<<endl;

				list<int> cu = res_children[0][size[0]];
				for(int i=1;i<n;i++){
					cu.insert(cu.end(),res_children[i][size[i]].begin(),res_children[i][size[i]].end());
				}

				res.push_back(cu);
				size[n-1]++;

				//backtrack
				if(size[n-1] == (int)res_children[n-1].size()){
					int i = n-1;
					while( i >= 0 && size[i] >= (int)res_children[i].size()-1){
						size[i] = 0;
						i--;
					}
					if(i >= 0){
						size[i]++;
					}else{
						finished = true;
					}
				}
			}

			delete [] size;
			return res;
			break;
      }
		case PARALLEL:
      {
			vector< list <int> > res = tree_cliques_rec(tree->children->no,prime_edges);
			for( child * c = tree->children->next; c != NULL ; c = c->next ){
				vector< list <int> > cur = tree_cliques_rec(c->no,prime_edges);
				res.insert(res.end(),cur.begin(),cur.end());
			}
			return res;
			break;
      }
		default:
      {

			vector< list <int> > res;
			vector< vector< list<int> > > res_children;
			//get results from children
			for( child * c = tree->children; c != NULL ; c = c->next ){
				res_children.push_back(tree_cliques_rec(c->no,prime_edges));
			}
			int num = tree->num;
			//maybe optimize this for space
      vector< vector<int> > cliques = tomita2(prime_edges[num],prime_edges[num].size());

      vector< vector<int> >::iterator vvit;
      vector<int>::iterator vit;
			//vector< list<int> >::iterator i,j;
			int * sizes = new int[prime_edges[num].size()];

			for(vvit = cliques.begin(); vvit != cliques.end(); ++vvit){
        //int n = vvit->size();

        for(int k = 0; k < (int)vvit->size(); ++k){
          sizes[k] = 0;
        }

        bool finished = false;

        while(!finished){
          int atSize = 0;
          vit = vvit->begin();
          list<int> cu = res_children[*vit][sizes[atSize]];
          ++vit;
          ++atSize;
          for(; vit != vvit->end(); ++vit){
            cu.insert(cu.begin(),res_children[*vit][sizes[atSize]].begin(),
                        res_children[*vit][sizes[atSize]].end());
            ++atSize;
          }
          res.push_back(cu);
          --atSize;
          ++sizes[atSize];
          --vit;

          if(sizes[atSize] == (int)res_children[*vit].size() ){
            --sizes[atSize];
            while(atSize > -1 && sizes[atSize] == (int)res_children[*vit].size()-1){
              sizes[atSize] = 0;
              --atSize;
              --vit;
            }
            if(atSize == -1){
              finished = true;
            }else{
              sizes[atSize]++;
            }
          }
        }
			}

			delete [] sizes;

			return res;
      }
	}
}
