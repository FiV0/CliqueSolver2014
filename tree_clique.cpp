#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char * argv []){
	
	if(argc != 2){
		cout<<"Usage: > test_clique filename"<<endl;
		exit(0);
	}

	ifstream in(argv[1]);

	
	return 0;
}
