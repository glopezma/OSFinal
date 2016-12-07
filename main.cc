#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <pthread.h>
#include <stdlib.h>
#include "boxes.h"
#include "pbmb_io.hpp"
using namespace std;

//Program is called: bounding_box
//This program will make boxes arround letter regions.  
//letter regions are determined with the formula |x1 - x| <= 3 || |y1 - y| <= 3
//aka if sepearted by at most 2 white pixels, then they are in the same region.  
//output the number of regions to the standard error stream for testing purposes
//will take 2 argumants from command line: name of the PBM file && number of x -> pthreads and devisions that should be made in parallel
//program should when finished ouput the new PBM file  with the bounding boxes with same name but with prefix .new 
//number of boxes will be outputted with the cerr (standard error) output
//abcdef.pbm.new

int main(int argc, char const *argv[]){
	//If there aren't enough arguments, then the program shuts down
	if(argc != 3){
		exit(1);
	}
	int col = 0;
	int row = 0;
	bool found = true;
	string fileName = argv[1];
	//int pthreadNum = atoi(argv[2]);			
	vector<box> boxes;				//contains the struct that holds the coordinates of the letters I need to box
	vector<int> deleteBoxes; 		//structure for error correction to hold which boxes need to be deleted during merging of boxes

	int *b;
	bool error;
	
	error = pbmb_read ( fileName, row, col, &b );
	if ( error ){
		cout << "\n";
		cout << "  PBMB_READ failed!\n";
	}

	vector<vector<int> > matrix(col, std::vector<int>(row)); //create the cc*rr matrix

	input_data(matrix, col, row, b); 	//fills matrix with the data from the .pbm file
 
	//This is the initial creation of boxes that will need another function at the end to make sure there were no errors.  It groups coordinates together. 
	for(int i=0; i<col; ++i){
		for(int j=0; j<row; ++j){
			if(matrix[i][j] == 1){
				if(boxes.empty()){	//If it's empty, then we need to create the first box which is done as such.  
					box newBox;
					coordinates newCord;
					boxes.push_back(newBox);
					boxes[0].cord.push_back(newCord);
					boxes[0].cord[0].x = j;
					boxes[0].cord[0].y = i;
					// cout<<"boxes:"<<0<<
				}
				else{
					for(int k=0; k<boxes.size(); ++k){		//checking the coordinates to see if there are in range of any known boxes
						if(inRangeCord(i, j, boxes[k])){	//Send the box and then check all the coordinate points in that box 
							found = false;					//If we found something then we don't want to create a new element
						}
					}//if the coordinate didn't fit in any of the known boxes so far, then we create a new box with the coordniate in it.  
					if(!found){
						box newBox;
						coordinates newCord;
						boxes.push_back(newBox);
						boxes[boxes.size()-1].cord.push_back(newCord);
						boxes[boxes.size()-1].cord[0].x = j;
						boxes[boxes.size()-1].cord[0].y = i;
						found=true;
					}
				}
			}
		}
	}
// //-------------------------------- Before box --------------------------------
// 	cout<<endl<<"Matrix Before:"<<endl;
// 	for(int i=0; i<col; ++i){
// 	 	// cout<<endl<<col<<"/"<<matrix.size()<<" "<<row<<"/"<<matrix[i].size()<<endl;
// 		// cout<<i<<".) ";
// 		for(int j=0; j<row; ++j){
// 			cout<<matrix[i][j];
// 			// cout<<"i:"<<i<<" j:"<<j<<endl;
// 		}
// 		cout<<endl;
// 	}
// 	cout<<"Before boxes"<<endl;

// //-------------------------------- Before box --------------------------------

	//set min and max for all boxes
	for(int i=0; i<boxes.size(); ++i){
		// cout<<"myBox: "<<i<<endl;
		setBox(boxes[i]); 
		// cout<<endl;
	}

	//merge boxes if they are close enough together
	for(int i=0; i<boxes.size(); ++i){
		for(int j=i; j<boxes.size(); ++j){
			if(j != i){
				if(boxInRange(boxes[i], boxes[j])){
					deleteBoxes.push_back(j);
				}
			}
			while(!deleteBoxes.empty()){
				boxes.erase(boxes.begin()+deleteBoxes.back());
				deleteBoxes.pop_back();
			}
		}
	}
		cout<<"error"<<endl;


	//set min and max for all boxes again if they merged
	for(int i=0; i<boxes.size(); ++i){
		setBox(boxes[i]); 
		draw_box(boxes[i], matrix);
	}

//-------------------------------- After Box --------------------------------
	for(int i=0; i<col; ++i){
		for(int j=0; j<row; ++j){
			cout<<matrix[i][j];
		}
	}
//-------------------------------- After Box --------------------------------

	// b = new int[col*row];
	//put all matrix data into array
	// pbmb_write(outputFile, col, row, b);

	cerr<<boxes.size();

	return 0;
}
