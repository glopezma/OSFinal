struct coordinates{
	int x = 0;
	int y = 0;
};

struct hex{
	coordinates hexcord;
	int one;
	int two;
	int four;
	int eight;
	hex();
	hex(char value);
};

struct box{
	int max_x = 0;			//the furthest right point in the matrix
	int max_y = 0; 			//the lowest point in the matrix
	int min_x = 0;			//the most left point in the matrix
	int min_y = 0; 			//the highest point int he matrix
	vector<coordinates> cord;	//pairs inside of the known boxes
	setBox();
};

void open_file(ifstream& fin, string file);
void input_data(vector<vector<int> >& matrix, ifstream& fin, int& col, int& row);
bool draw_box(box myBox, vector<vector<int> >& matrix);
bool inRange(int max_var, int min_var, box myBox);
bool inRangeCord(int x, int y, box myBox);
bool boxInRange(box box1, box box2);
string hexToBin(char value);
char binToHex(string value);


/************************   to do   ***************************************
3. Parallel version
4. output to cerr: vector<coordinates> cord.size()
5. create new document with prefix .new
*/