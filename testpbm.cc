#include <iostream> 
#include <fstream>
#include <string>
#include "pbma_io.hpp"
#include "pbma_io.cpp"

using namespace std;

// void open_file(ifstream& fin, string file){
//   fin.open(file.c_str(), ios::binary);
//   if(fin.fail()){
//       cout<<"problem with file open"<<endl;
//     }
// }

int main(){
	int *pointer;
	string file_name = "abcdef.pbm"
	int col;
	int row;

	pbmb_read(file_name, col, row, &pointer);

	size = col*row;
	for(int i=0; i<size; ++i){
		cout<<*pointer[i];
	}
	return 0;
}