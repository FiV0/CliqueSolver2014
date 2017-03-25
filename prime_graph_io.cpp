#include "prime_graph_io.h"
#include <iostream>
#include <utility>
#include <vector>
#include <sstream>
#include <cstdlib>

using namespace std;

int find_closing(int s, string line){
	int open=1, closed=0;
	++s;
	while(open != closed){
		if(line[s] == '(') ++open;
		if(line[s] == ')') ++closed;
		++s;
	}
	return s;
}

int find_end(int s, string line){
	while(s < (int)line.length() && line[s] != ' ') ++s;
	return s;
}

int count_nb(int s, string line){
	int res = 0;
	while(line[s+1] != ')') {
		if(line[s] == ' ' && ('0' <= line[s+1] && line[s+1] <= '9')){
			++res;
		}
		++s;
	}
	return res;
}

node * tree_construction(string line,
				vector< vector< vector<int> > > & pr_edges){

	node * res = new node;
	res->children = NULL;
	if('0' <= line[0] && line[0] <= '9'){
		res->type = LEAF;

		stringstream ss (line);
		ss >>	res->num;

		return res;
	}else{
		if(line[0] == 'S' || line[0] == 'L'){
				if(line[0] == 'S'){
					res->type = SERIE;
				}else{
					res->type = PARALLEL;
				}
				int close = find_closing(1,line);
				for(int i=2; i<close-1; ){
					if(line[i] != ' '){
						child * c = new child;
						int close2;
						if('0' <= line[i] && line[i] <= '9'){
							close2 = find_end(i,line);
						}else{
							close2 = find_closing(i+1,line);
						}
						c->next = res->children;
						c->no = tree_construction(line.substr(i,close2-i),pr_edges);
						res->children = c;
						i = close2;
					}else{
						i++;
					}
				}
			}else{
				res->type = PRIME;
				int close = find_closing(1,line);
				int i,nb_ch = 0;
				for(i=2; i<close-1; ){
					//
					if(line[i] == ':'){
						++i;
						break;
					}

					if(line[i] != ' '){
						child * c = new child;
						++nb_ch;
						int close2;
						if('0' <= line[i] && line[i] <= '9'){
							close2 = find_end(i,line);
						}else{
							close2 = find_closing(i+1,line);
						}
						c->next = res->children;
						c->no = tree_construction(line.substr(i,close2-i),pr_edges);
						res->children = c;
						i = close2;
					}else{
						++i;
					}
				}
				int nb = count_nb(i,line);
				if( nb % 2 == 1){
					cerr<<"ERROR while reading input file\n" << endl;
					cerr<< line << endl;
					exit(EXIT_FAILURE);
				}

				res->num = pr_edges.size();

				vector< vector<int> > v(nb_ch , vector<int> ());
				stringstream ss(line.substr(i,line.length()-i));
				for(int i=0; i< (nb/2) ; ++i){
					int j,k;
					ss >> j >> k;
					v[j-1].push_back(k-1);
					v[k-1].push_back(j-1);
				}
				pr_edges.push_back(v);
		}
		return res;
	}
}

void tree_destruction( node * n){
	if(n->type == LEAF){
		delete n;
	}else{
		child * c = n->children;
		child * temp;
		while(c){
			tree_destruction(c->no);
			temp = c->next;
			delete c;
			c = temp;
		}
	}
}

