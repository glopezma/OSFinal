#include "boxes.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <pthread.h>
#include <stdlib.h>
#include <cmath>
using namespace std;

//This function inputs the pbm image into a matrix
void input_data(std::vector<std::vector<int> >& matrix, int col, int row, int *barray){
	for(int i=0; i<col; ++i){
		for(int j=0; j<row; ++j){
			matrix[i][j] = *((int *)barray+i * row+j);
		}
	}
	delete [] barray;
}

//sets max_x, max_y, min_x, min_y
void setBox(box& myBox){
	for(int i=0; i<myBox.cord.size(); ++i){
		// cout<<"x:"<<myBox.cord[i].x<<" y:"<<myBox.cord[i].y<<endl;
		if(myBox.cord[i].x > myBox.max_x){
			myBox.max_x = myBox.cord[i].x;
		}
		else if(myBox.cord[i].y > myBox.max_y){
			myBox.max_y = myBox.cord[i].y;
		}
		else if(myBox.cord[i].x < myBox.min_x){
			myBox.min_x = myBox.cord[i].x;
		}
		else if(myBox.cord[i].y < myBox.min_y){
			myBox.min_y = myBox.cord[i].y;
		}
	}
}

//The equation to check x or y coordinates are range is
//Equation: |x1 - x| <= 3 && |y1 - y| <= 3
bool inRange(int max_var, int min_var){
	if(abs(max_var - min_var) <= 3){
		return true;
	}
	return false;
}

//checks if coordinates belong in a box
bool inRangeCord(int x, int y, box myBox){
	for(int i=0; i<myBox.cord.size(); ++i){
		if(inRange(myBox.cord[i].x, x) && inRange(myBox.cord[i].y, y)){
			coordinates newCord;
			myBox.cord.push_back(newCord);	//access last element in list
			myBox.cord[myBox.cord.size()-1].x = x; 
			myBox.cord[myBox.cord.size()-1].y = y;
			return true;
		}
	}
	return false;
}

//check if two boxes are in range of each other by calling inRange()
bool boxInRange(box& box1, box& box2){
	if((inRangeCord(box1.max_x, box2.min_x, box1) || inRangeCord(box1.min_x, box2.max_x, box1)) && (inRangeCord(box1.min_y, box2.max_y, box1) || inRangeCord(box1.max_y, box2.min_y, box1))){ //have to check 4 different things depending if above, below, left or right of each other.  
		copyBoxes(box1, box2);
		return true;
	}
	return false;
}

//puts all the coordinates of box2 into box1
void copyBoxes(box& box1, box& box2){
	while(!box2.cord.empty()){
		box1.cord.push_back(box2.cord.back());
		box2.cord.pop_back();
	}
}

//creates line of 1's between max/min y/x coordinates: aka creating the box
bool draw_box(box myBox, vector<vector<int> >& matrix){
	int yDistance = abs(myBox.max_y - myBox.min_y);
	int xDistance = abs(myBox.max_x - myBox.min_x);

	cout<<"yDistance: "<<yDistance<<" xDistance: "<<xDistance<<endl;

	for(int i=0; i<=yDistance; ++i){
		matrix[myBox.min_y+i][myBox.min_x]=1;
		matrix[myBox.min_y+i][myBox.max_x]=1;
	}
	for(int i=0; i<=xDistance; ++i){
		matrix[myBox.min_y][myBox.min_x+i]=1;
		matrix[myBox.min_y][myBox.max_x+i]=1;	
	}
}

// char binToHex(string value){
// 	switch(value){
// 		case "0000": return '0';
//         case "0001": return '1';
//         case "0010": return '2';
//         case "0011": return '3';
//         case "0100": return '4';
//         case "0101": return '5';
//         case "0110": return '6';
//         case "0111": return '7';
//         case "1000": return '8';
//         case "1001": return '9';
//         case "1010": return 'A';
//         case "1011": return 'B';
//         case "1100": return 'C';
//         case "1101": return 'D';
//         case "1110": return 'E';
//         case "1111": return 'F';
//     }
// }

// string hexToBin(char value){
// 	switch(toupper(value)){
// 		case '0': return "0000";
//         case '1': return "0001";
//         case '2': return "0010";
//         case '3': return "0011";
//         case '4': return "0100";
//         case '5': return "0101";
//         case '6': return "0110";
//         case '7': return "0111";
//         case '8': return "1000";
//         case '9': return "1001";
//         case 'A': return "1010";
//         case 'B': return "1011";
//         case 'C': return "1100";
//         case 'D': return "1101";
//         case 'E': return "1110";
//         case 'F': return "1111";
// 	}
// }

// hex::hex(){
// 	one = 0;
// 	two = 0;
// 	four = 0;
// 	eight = 0;
// }

//changes hex string into binary string
// hex::hex(char value, int col, int row){
// 	string hexString = hexToBin(value);
// 	for(int i = 0; i<4; ++i){
// 		switch(i){
// 			case 0: 
// 				one = hexString.c_str()[i];
// 				break;
// 			case 1: 
// 				two = hexString.c_str()[i];
// 				break;
// 			case 2: 
// 				four = hexString.c_str()[i];
// 				break;
// 			case 3: 
// 				eight = hexString.c_str()[i];
// 				break;
// 		}
// 	}
// }

//output the new file that is has the boxes in it
// void output_data(vector<vector<int> >& matrix, ofstream& fout, int col, int row){

// }

//this function just opens the file
// void open_file(ifstream& fin, string file){
//   fin.open(file.c_str());
//   if(fin.fail()){
//       cout<<"problem with file open"<<endl;
//     }
// }

// coordinates::coordinates(){
// 	x=0;
// 	y=0;
// }

// box::box(){
// 	max_x = 0;			
// 	max_y = 0; 			
// 	min_x = 0;			
// 	min_y = 0; 			
// }