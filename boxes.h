#ifndef BOXES_H
#define BOXES_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <pthread.h>
#include <stdlib.h>
#include <cmath>

struct coordinates{
	int x;
	int y;
	// coordinates();
};

struct box{
	int max_x;			//the furthest right point in the matrix
	int max_y; 			//the lowest point in the matrix
	int min_x;			//the most left point in the matrix
	int min_y; 			//the highest point int he matrix
	std::vector<coordinates> cord;	//pairs inside of the known boxes
	// box();
};

void setBox(box& myBox);
void input_data(std::vector<std::vector<int> >& matrix, int col, int row, int *barray);
bool draw_box(box myBox, std::vector<std::vector<int> >& matrix);
bool inRange(int max_var, int min_var);
bool inRangeCord(int x, int y, box myBox);
bool boxInRange(box& box1, box& box2);
void copyBoxes(box& box1, box& box2);



/************************   to do   ***************************************
3. Parallel version
4. output to cerr: vector<coordinates> cord.size()
5. create new document with prefix .new
*/


// struct hex{
// 	coordinates hexcord;
// 	int one;
// 	int two;
// 	int four;
// 	int eight;
// 	hex();
// 	hex(char value);
// };
// void open_file(std::ifstream& fin, std::string file);
// void output_data(std::vector<std::vector<int> >& matrix, std::ofstream& fout, int col, int row);
// std::string hexToBin(char value, int col, int row);
// char binToHex(std::string value);
#endif