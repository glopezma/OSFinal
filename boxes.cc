#include "boxes.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <pthread>
#include <stdlib.h>
#include <cmath>
using namespace std;

//this function just opens the file
void open_file(ifstream& fin, string file){
  fin.open(file.c_str());
  if(fin.fail()){
      cout<<"problem with file open"<<endl;
    }
}

hex::hex(){
	one = 0;
	two = 0;
	four = 0;
	eight = 0;
}

box::setBox(){
	for(int i=0; i<cord.size(); ++i){
		if(cord[i].x > max_x){
			max_x = cord[i].x;
		}
		else if(cord[i].y > max_y){
			max_y = cord[i].y;
		}
		else if(cord[i].x < min_x){
			min_x = cord[i].x;
		}
		else if(cord[i].y < min_y){
			min_y = cord[i].y;
		}
	}
}

//changes hex string into binary string
hex::hex(char value, int col, int row){
	string hexString = hexToBin(value);
	for(int i = 0; i<4; ++i){
		switch(i){
			case 0: 
				one = hexString.c_str()[i];
				break;
			case 1: 
				two = hexString.c_str()[i];
				break;
			case 2: 
				four = hexString.c_str()[i];
				break;
			case 3: 
				eight = hexString.c_str()[i];
				break;
		}
	}
}

//This function inputs the pbm image into a matrix
void input_data(vector<vector<int> >& matrix, ifstream& fin, int& col, int& row){
	//this function inputs all the data in the file into the program's matrix
	string p4;
	char temp;

	//removing the "p4" and getting the Height and width
	fin>>p4;
	fin>>temp;
	fin>>col;
	fin>>row;
	fin>>temp;

	//imports the file into a matrix so easier to traverse
	for(int i = 0; i<col; ++i){
		for(int j = 0; j<row; ++j){
			fin>>temp;
			if(temp != '\n'){
				matrix[i][j] = temp;	
			}
		}
	}
}

//The equation to check in range is: |x1 - x| <= 3 && |y1 - y| <= 3

//used in the program to check if the outlines for boxes are close enough that they should merge into one box
//checks the boorder choordinate on each and returns true if they are close enough
bool inRange(int max_var, int min_var, box myBox){
	if(abs(max_var - min_var) <= 3){
		return true;
	}
	return false;
}

//checks if coordinates belong in a box
bool inRangeCord(int x, int y, box myBox){
	for(int i=0; i<myBox.cord.size(); ++i){
		if(abs(myBox.cord[i].x - x) <= 3 && abs(myBox.cord[i].y - y) <= 3){
			myBox.cord.push_back(new coordinates);	//access last element in list
			myBox.cord[myBox.cord.size()-1].x = x; 
			myBox.cord[myBox.cord.size()-1].y = y;
			return true;
		}
	}
	return false;
}

//check if two boxes are in range of each other by calling inRange()
bool boxInRange(box box1, box box2){
	if(inRange(box1.max_x, box2.min_x, box1) || inRange(box1.min_x, box2.max_x, box1) || inRange(box1.min_y, box2.max_y, box1) || inRange(box1.max_y, box2.min_y, box1)){ //have to check 4 different things depending if above, below, left or right of each other.  
		copyBoxes(box1, box2);
		return true;
	}
	return false;
}

//looks at the max/min y/x to draw a line between the coordinates creating the box
bool draw_box(box myBox, vector<vector<int> >& matrix){
	int yDistance = abs(myBox.max_y - myBox.min_y);
	int xDistance = abs(myBox.max_x - myBox.min_x);

	for(int i=0; i<=yDistance; ++i){
		matrix[myBox.min_y+i][myBox.min_x]=1;
		matrix[myBox.min_y+i][myBox.max_x]=1;
	}
	for(int i=0; i<=xDistance; ++i){
		matrix[myBox.min_x+i][myBox.min_y]=1;
		matrix[myBox.min_x+i][myBox.max_y]=1;	}
}

char binToHex(string value){
	switch(value){
		case "0000": return '0';
        case "0001": return '1';
        case "0010": return '2';
        case "0011": return '3';
        case "0100": return '4';
        case "0101": return '5';
        case "0110": return '6';
        case "0111": return '7';
        case "1000": return '8';
        case "1001": return '9';
        case "1010": return 'A';
        case "1011": return 'B';
        case "1100": return 'C';
        case "1101": return 'D';
        case "1110": return 'E';
        case "1111": return 'F';
    }
}

string hexToBin(char value){
	switch(toupper(value)){
		case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
	}
}