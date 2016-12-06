char ch_cap ( char ch );

bool pbmb_check_data ( int xsize, int ysize, int *barray );
bool pbmb_example ( int xsize, int ysize, int *barray );

bool pbmb_read ( std::string file_in_name, int &xsize, int &ysize, int **barray );
bool pbmb_read_data ( std::ifstream &file_in, int xsize, int ysize, int *barray );
bool pbmb_read_header ( std::ifstream &file_in, int &xsize, int &ysize );
bool pbmb_read_test ( std::string file_in_name );

bool pbmb_write ( std::string file_out_name, int xsize, int ysize, int *barray );
bool pbmb_write_data ( std::ofstream &file_out, int xsize, int ysize, int *barray );

bool pbmb_write_header ( std::ofstream &file_out, int xsize, int ysize );
bool pbmb_write_test ( std::string file_out_name );

bool s_eqi ( std::string s1, std::string s2 );
int s_len_trim ( std::string s );
void s_word_extract_first ( std::string s, std::string &s1, std::string &s2 );