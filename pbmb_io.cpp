# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <cmath>

using namespace std;

# include "pbmb_io.hpp"

//****************************************************************************80

char ch_cap ( char ch )

//****************************************************************************80
//
//  Purpose:
//
//    CH_CAP capitalizes a single character.
//
//  Discussion:
//
//    This routine should be equivalent to the library "toupper" function.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    19 July 1998
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, char CH, the character to capitalize.
//
//    Output, char CH_CAP, the capitalized character.
//
{
  if ( 97 <= ch && ch <= 122 ) 
  {
    ch = ch - 32;
  }   

  return ch;
}
//****************************************************************************80

bool pbmb_check_data ( int xsize, int ysize, int *barray )

//****************************************************************************80
//
//  Purpose:
//
//    PBMB_CHECK_DATA checks the data for a binary portable bit map file.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    17 April 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int XSIZE, YSIZE, the number of rows and columns of data.
//
//    Input, int *BARRAY, the array of XSIZE by YSIZE bits.
//
//    Output, bool PBMB_CHECK_DATA, is true if an error occurred.
//
{
  int i;
  int *indexb;
  int j;

  if ( xsize <= 0 )
  {
    cout << "\n";
    cout << "PBMB_CHECK_DATA - Fatal error!\n";
    cout << "  XSIZE <= 0\n";
    cout << "  XSIZE = " << xsize << "\n";
    return true;
  }

  if ( ysize <= 0 )
  {
    cout << "\n";
    cout << "PBMB_CHECK_DATA - Fatal error!\n";
    cout << "  YSIZE <= 0\n";
    cout << "  YSIZE = " << ysize << "\n";
    return true;
  }

  if ( barray == NULL )
  {
    cout << "\n";
    cout << "PBMB_CHECK_DATA - Fatal error!\n";
    cout << "  Null pointer to data.\n";
    return true;
  }

  indexb = barray;

  for ( j = 0; j < ysize; j++ )
  {
    for ( i = 0; i < xsize; i++ )
    {
      if ( *indexb != 0 && *indexb != 1 )
      {
        cout << "\n";
        cout << "PBMB_CHECK_DATA - Fatal error!\n";
        cout << "  b(" << i << "," << j << ") = "
          << *indexb << ".\n";
        return true;
      }

      indexb = indexb + 1;
    }
  }

  return false;
}
//****************************************************************************80

bool pbmb_example ( int xsize, int ysize, int *barray )

//****************************************************************************80
//
//  Purpose:
//
//    PBMB_EXAMPLE sets up some sample PBMB data.
//
//  Discussion:
//
//    The data represents an ellipse.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    17 April 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int XSIZE, YSIZE, the number of rows and columns of data.
//    Values of 200 would be reasonable.
//
//    Output, int *BARRAY, the array of XSIZE by YSIZE data values.
//
//    Output, bool PBMB_EXAMPLE, is true if an error occurred.
//
{
  int i;
  int *indexb;
  int j;
  float r;
  float test;
  float x;
  float xc;
  float y;
  float yc;
 
  indexb = barray;
  if ( xsize < ysize )
  {
    r = ( float ) xsize / 3.0;
  }
  else
  {
    r = ( float ) ysize / 3.0;
  }
  xc = ( xsize ) / 2.0;
  yc = ( ysize ) / 2.0;

  for ( i = 0; i < ysize; i++ )
  {
    y = ( float ) i;
    for ( j = 0; j < xsize; j++ )
    {
      x = ( float ) j;
      test = r - sqrt ( ( x - xc ) * ( x - xc ) 
               + 0.75 * ( y - yc ) * ( y - yc ) );
      if ( fabs ( test ) <= 3.0 )
      {
        *indexb = 1;
      }
      else
      {
        *indexb = 0;
      }
      indexb = indexb + 1;
    }
  }

  return false;
}
//****************************************************************************80

bool pbmb_read ( string input_name, int &xsize, int &ysize, int **barray )

//****************************************************************************80
//
//  Purpose:
//
//    PBMB_READ reads the header and data from a binary portable bit map file.
// 
//  Discussion:
//
//    Thanks to Jonas Schwertfeger for pointing out that, especially on Microsoft
//    Windows systems, a binary file needs to be opened as a binary file!
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
// 
//    22 July 2011
// 
//  Author:
// 
//    John Burkardt
//
//  Parameters:
//
//    Input, string INPUT_NAME, the name of the file containing the binary
//    portable bit map data.
//
//    Output, int &XSIZE, &YSIZE, the number of rows and columns of data.
//
//    Output, int **BARRAY, the array of XSIZE by YSIZE data values.
//
//    Output, bool PBMB_READ, is true if an error occurred.
//
{
  bool error;
  ifstream input;

  input.open ( input_name.c_str ( ), ios::binary );

  if ( !input )
  {
    cout << "\n";
    cout << "PBMB_READ: Fatal error!\n";
    cout << "  Cannot open the input file " << input_name << "\n";
    return true;
  }
//
//  Read the header.
//
  error = pbmb_read_header ( input, xsize, ysize );

  if ( error )
  {
    cout << "\n";
    cout << "PBMB_READ: Fatal error!\n";
    cout << "  PBMB_READ_HEADER failed.\n";
    return true;
  }
//
//  Allocate storage for the data.
//
  *barray = new int [ xsize * ysize ];
//
//  Read the data.
//
  error = pbmb_read_data ( input, xsize, ysize, *barray );

  if ( error )
  {
    cout << "\n";
    cout << "PBMB_READ: Fatal error!\n";
    cout << "  PBMB_READ_DATA failed.\n";
    return true;
  }
//
//  Close the file.
//
  input.close ( );

  return false;
}
//****************************************************************************80

bool pbmb_read_data ( ifstream &input, int xsize, int ysize, int *barray )

//****************************************************************************80
//
//  Purpose:
//
//    PBMB_READ_DATA reads the data in a binary portable bit map file.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    16 December 2004
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, ifstream &INPUT, a pointer to the file containing the binary
//    portable bit map data.
//
//    Input, int &XSIZE, &YSIZE, the number of rows and columns of data.
//
//    Output, int *BARRAY, the array of XSIZE by YSIZE data values.
//
//    Output, bool PBMB_READ_DATA, is true if an error occurred.
//
{
  int bit;
  char c;
  unsigned char c2;
  int i;
  int *indexb;
  int j;
  int k;
  int numbyte;

  indexb = barray;
  numbyte = 0;

  for ( j = 0; j < ysize; j++ )
  {
    for ( i = 0; i < xsize; i++ )
    {
      if ( i%8 == 0 )
      {
        input.read ( &c, 1 );
        c2 = ( unsigned char ) c;
        if ( input.eof ( ) )
        {
          cout << "\n";
          cout << "PBMB_CHECK_DATA - Fatal error!\n";
          cout << "  Failed reading byte " << numbyte << "\n";
          return true;
        }
        numbyte = numbyte + 1;
      }

      k = 7 - i%8;
      bit = ( c2 >> k )%2;

      *indexb = bit;
      indexb = indexb + 1;
    }
  }
  return false;
}
//****************************************************************************80

bool pbmb_read_header ( ifstream &input, int &xsize, int &ysize )

//****************************************************************************80
//
//  Purpose:
//
//    PBMB_READ_HEADER reads the header of a binary portable bit map file.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    22 July 2011
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, ifstream &INPUT, a pointer to the file containing the binary
//    portable bit map data.
//
//    Output, int &XSIZE, &YSIZE, the number of rows and columns of data.
//
//    Output, bool PBMB_READ_HEADER, is true if an error occurred.
//
{
  int count;
  string line;
  string rest;
  int step;
  int width;
  string word;

  step = 0;

  while ( 1 )
  {
    getline ( input, line );

    if ( input.eof ( ) )
    {
      cout << "\n";
      cout << "PBMB_READ_HEADER - Fatal error!\n";
      cout << "  End of file.\n";
      return true;
    }

    if ( line[0] == '#' )
    {
      continue;
    }

    if ( step == 0 )
    {
      s_word_extract_first ( line, word, rest );

      if ( s_len_trim ( word ) <= 0 )
      {
        continue;
      }
      
      if ( !s_eqi ( word, "P4" ) )
      {
        cout << "\n";
        cout << "PBMB_READ_HEADER - Fatal error.\n";
        cout << "  Bad magic number = \"" << word << "\".\n";
        return true;
      }
      line = rest;
      step = 1;
    }

    if ( step == 1 )
    {
      s_word_extract_first ( line, word, rest );
 
      if ( s_len_trim ( word ) <= 0 )
      {
        continue;
      }
      xsize = atoi ( word.c_str ( ) );
      line = rest;
      step = 2;
    }

    if ( step == 2 )
    {
      s_word_extract_first ( line, word, rest );
 
      if ( s_len_trim ( word ) <= 0 )
      {
        continue;
      }
      ysize = atoi ( word.c_str ( ) );
      break;
    }

  }

  return false;
}
//****************************************************************************80

bool pbmb_read_test ( string input_name )

//****************************************************************************80
//
//  Purpose:
//
//    PBMB_READ_TEST tests the binary portable bit map read routines.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    22 July 2011
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, string INPUT_NAME, the name of the file containing the binary
//    portable bit map data.
//
//    Output, bool PBMB_READ_TEST, is true if an error occurred.
//
{
  int *barray;
  bool error;
  int xsize;
  int ysize;

  barray = NULL;
//
//  Read the data.
//
  error = pbmb_read ( input_name, xsize, ysize, &barray );

  if ( error )
  {
    cout << "\n";
    cout << "PBMB_READ_TEST: Fatal error!\n";
    cout << "  PBMB_READ failed.\n";
    delete [] barray;
    return true;
  }
//
//  Check the data.
//
  error = pbmb_check_data ( xsize, ysize, barray );

  delete [] barray;

  if ( error )
  {
    cout << "\n";
    cout << "  PBMB_CHECK_DATA reports bad data from the file.\n";
    return true;
  }

  cout << "\n";
  cout << "  PBMB_CHECK_DATA passes the data from the file.\n";

  return false;
}
//****************************************************************************80

bool pbmb_write ( string output_name, int xsize, int ysize, int *barray )

//****************************************************************************80
//
//  Purpose:
//
//    PBMB_WRITE writes the header and data for a binary portable bit map file.
// 
//  Discussion:
//
//    Thanks to Jonas Schwertfeger for pointing out that, especially on Microsoft
//    Windows systems, a binary file needs to be opened as a binary file!
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
// 
//    02 April 2005
// 
//  Author:
// 
//    John Burkardt
//
//  Parameters:
//
//    Input, string OUTPUT_NAME, the name of the file to contain the binary
//    portable bit map data.
//
//    Input, int XSIZE, YSIZE, the number of rows and columns of data.
//
//    Input, int *BARRAY, the array of XSIZE by YSIZE data values.
//
//    Output, bool PBMB_WRITE, is true if an error occurred.
//
{
  bool error;
  ofstream output;

  output.open ( output_name.c_str ( ), ios::binary );

  if ( !output )
  {
    cout << "\n";
    cout << "PBMB_WRITE: Fatal error!\n";
    cout << "  Cannot open the output file " << output_name << "\n";
    return true;
  }
//
//  Write the header.
//
  error = pbmb_write_header ( output, xsize, ysize );

  if ( error )
  {
    cout << "\n";
    cout << "PBMB_WRITE: Fatal error!\n";
    cout << "  PBMB_WRITE_HEADER failed.\n";
    return true;
  }
//
//  Write the data.
//
  error = pbmb_write_data ( output, xsize, ysize, barray );

  if ( error )
  {
    cout << "\n";
    cout << "PBMB_WRITE: Fatal error!\n";
    cout << "  PBMB_WRITE_DATA failed.\n";
    return true;
  }
//
//  Close the file.
//
  output.close ( );

  return false;
}
//****************************************************************************80

bool pbmb_write_data ( ofstream &output, int xsize, int ysize, int *barray )

//****************************************************************************80
//
//  Purpose:
//
//    PBMB_WRITE_DATA writes the data for a binary portable bit map file.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    17 April 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, ofstream &OUTPUT, a pointer to the file to contain the binary
//    portable bit map data.
//
//    Input, int XSIZE, YSIZE, the number of rows and columns of data.
//
//    Input, int *BARRAY, the array of XSIZE by YSIZE data values.
//
//    Output, bool PBMB_WRITE_DATA, is true if an error occurred.
//
{
  int bit;
  unsigned char c;
  int i;
  int *indexb;
  int j;
  int k;

  indexb = barray;
  c = 0;

  for ( j = 0; j < ysize; j++ )
  {
    for ( i = 0; i < xsize; i++ )
    {
      k = 7 - i%8;
      bit = (*indexb)%2;
      c = c | ( bit << k );

      indexb = indexb + 1;

      if ( (i+1)%8 == 0 || i == ( xsize - 1 ) )
      {
        output << c;
        c = 0;
      }
    }
  }
  return false;
}
//****************************************************************************80

bool pbmb_write_header ( ofstream &output, int xsize, int ysize )

//****************************************************************************80
//
//  Purpose:
//
//    PBMB_WRITE_HEADER writes the header of a binary portable bit map file.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    17 April 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, ofstream &OUTPUT, a pointer to the file to contain the binary
//    portable bit map data.
//
//    Input, int XSIZE, YSIZE, the number of rows and columns of data.
//
//    Output, bool PBMB_WRITE_HEADER, is true if an error occurred.
//
{
  output << "P4" << " "
           << xsize << " "
           << ysize << "\n";
 
  return false;
}
//****************************************************************************80

bool pbmb_write_test ( string output_name )

//****************************************************************************80
//
//  Purpose:
//
//    PBMB_WRITE_TEST tests the binary portable bit map write routines.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    17 April 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, string OUTPUT_NAME, the name of the file to contain the binary
//    portable bit map data.
//
//    Output, bool PBMB_WRITE_TEST, is true if an error occurred.
//
{
  int *barray;
  bool error;
  int xsize;
  int ysize;
//
//  Set the data.
//
  xsize = 250;
  ysize = 150;
 
  barray = new int [ xsize * ysize ];

  if ( barray == NULL )
  {
    cout << "\n";
    cout << "PBMB_WRITE_TEST: Fatal error!\n";
    cout << "  Unable to allocate memory for data.\n";
    return true;
  }

  error = pbmb_example ( xsize, ysize, barray );

  if ( error )
  {
    cout << "\n";
    cout << "PBMB_WRITE_TEST: Fatal error!\n";
    cout << "  PBM_EXAMPLE failed.\n";
    return true;
  }

  error = pbmb_write ( output_name, xsize, ysize, barray );

  delete [] barray;

  if ( error )
  {
    cout << "\n";
    cout << "PBMB_WRITE_TEST: Fatal error!\n";
    cout << "  PBMB_WRITE failed.\n";
    return true;
  }

  return false;
}
//****************************************************************************80

bool s_eqi ( string s1, string s2 )

//****************************************************************************80
//
//  Purpose:
//
//    S_EQI reports whether two strings are equal, ignoring case.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    05 July 2009
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, string S1, S2, two strings.
//
//    Output, bool S_EQI, is true if the strings are equal. 
//
{
  int i;
  int nchar;
  int s1_length;
  int s2_length;

  s1_length = s1.length ( );
  s2_length = s2.length ( );

  if ( s1_length < s2_length )
  {
    nchar = s1_length;
  }
  else
  {
    nchar = s2_length;
  }
//
//  The strings are not equal if they differ over their common length.
//
  for ( i = 0; i < nchar; i++ ) 
  {

    if ( ch_cap ( s1[i] ) != ch_cap ( s2[i] ) ) 
    {
      return false;
    }
  }
//
//  The strings are not equal if the longer one includes nonblanks
//  in the tail.
//
  if ( nchar < s1_length ) 
  {
    for ( i = nchar; i < s1_length; i++ ) 
    {
      if ( s1[i] != ' ' ) 
      {
        return false;
      }
    } 
  }
  else if ( nchar < s2_length ) 
  {
    for ( i = nchar; i < s2_length; i++ )
    {
      if ( s2[i] != ' ' ) 
      {
        return false;
      }
    } 
  }

  return true;
}
//****************************************************************************80

int s_len_trim ( std::string s )

//****************************************************************************80
//
//  Purpose:
//
//    S_LEN_TRIM returns the length of a string to the last nonblank.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    05 July 2009
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, string S, a string.
//
//    Output, int S_LEN_TRIM, the length of the string to the last nonblank.
//    If S_LEN_TRIM is 0, then the string is entirely blank.
//
{
  int n;

  n = s.length ( );

  while ( 0 < n ) 
  {
    if ( s[n-1] != ' ' )
    {
      return n;
    }
    n = n - 1;
  }

  return n;
}
//****************************************************************************80

void s_word_extract_first ( std::string s, std::string &s1, std::string &s2 )

//****************************************************************************80
//
//  Purpose:
//
//    S_WORD_EXTRACT_FIRST extracts the first word from a string.
//
//  Discussion:
//
//    A "word" is a string of characters terminated by a blank or
//    the end of the string.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    25 October 2010
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, string S, the string.
//
//    Output, string &S1, the first word (initial blanks removed).
//
//    Output, string &S2, the remainder of the string, after removing
//    the first word (initial blanks removed).
//
{
  int i;
  int mode;
  int s_len;

  s_len = s.length ( );
  s1 = "";
  s2 = "";
  mode = 1;

  for ( i = 0; i < s_len; i++ )
  {
    if ( mode == 1 )
    {
      if ( s[i] != ' ' )
      {
         mode = 2;
      }
    }
    else if ( mode == 2 )
    {
      if ( s[i] == ' ' )
      {
        mode = 3;
      }
    }
    else if ( mode == 3 )
    {
      if ( s[i] != ' ' )
      {
        mode = 4;
      }
    }
    if ( mode == 2 )
    {
      s1 = s1 + s[i];
    }
    else if ( mode == 4 )
    {
      s2 = s2 + s[i];
    }
  }

  return;
}
# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <cmath>

using namespace std;

# include "pbma_io.hpp"

//****************************************************************************80

void pbma_check_data ( int xsize, int ysize, int *b )

//****************************************************************************80
//
//  Purpose:
//
//    PBMA_CHECK_DATA checks the data for an ASCII PBM file.
//
//  Discussion:
//
//    XSIZE and YSIZE must be positive, the pointers must not be null,
//    and the data must be 0 or 1.
//
//  Example:
//
//    P1
//    # feep.pbm
//    24 7
//    0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//    0 1 1 1 1 0 0 1 1 1 1 0 0 1 1 1 1 0 0 1 1 1 1 0
//    0 1 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 1 0 0 1 0
//    0 1 1 1 0 0 0 1 1 1 0 0 0 1 1 1 0 0 0 1 1 1 1 0
//    0 1 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0
//    0 1 0 0 0 0 0 1 1 1 1 0 0 1 1 1 1 0 0 1 0 0 0 0
//    0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    05 June 2010
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int XSIZE, YSIZE, the number of rows and columns of data.
//
//    Input, int *B, the array of XSIZE by YSIZE data values.
//
{
  int i;
  int *index;
  int j;
  int k;

  if ( xsize <= 0 )
  {
    cerr << "\n";
    cerr << "PBMA_CHECK_DATA: Error!\n";
    cerr << "  XSIZE <= 0.\n";
    cerr << "  XSIZE = " << xsize << "\n";
    exit ( 1 );
  }

  if ( ysize <= 0 )
  {
    cerr << "\n";
    cerr << "PBMA_CHECK_DATA: Error!\n";
    cerr << "  YSIZE <= 0.\n";
    cerr << "  YSIZE = " << ysize << "\n";
    exit ( 1 );
  }

  if ( b == NULL )
  {
    cerr << "\n";
    cerr << "PBMA_CHECK_DATA: Error!\n";
    cerr << "  Null pointer to B.\n";
    exit ( 1 );
  }

  index = b;

  for ( j = 0; j < ysize; j++ )
  {
    for ( i = 0; i < xsize; i++ )
    {
      if ( *index < 0 )
      {
        cerr << "\n";
        cerr << "PBMA_CHECK_DATA - Fatal error!\n";
        cerr << "  Negative data.\n";
        cerr << "  B(" << i << "," << j << ")=" << *index << "\n";
        exit ( 1 );
      }
      else if ( 1 < *index )
      {
        cerr << "\n";
        cerr << "PBMA_CHECK_DATA - Fatal error!\n";
        cerr << "  Data exceeds 1\n";
        cerr << "  B(" << i << "," << j << ")=" << *index << "\n";
        exit ( 1 );
      }

      index = index + 1;
    }
  }
  return;
}
//****************************************************************************80

void pbma_example ( int xsize, int ysize, int *b )

//****************************************************************************80
//
//  Purpose:
//
//    PBMA_EXAMPLE sets up some ASCII PBM data.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    05 June 2010
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int XSIZE, YSIZE, the number of rows and columns of data.
//
//    Output, int *B, the array of XSIZE by YSIZE gray values.
//
{
  int i;
  int *indexb;
  int j;
  double r;
  double test;
  double x;
  double xc;
  double y;
  double yc;

  indexb = b;

  if ( xsize < ysize )
  {
    r = ( double ) xsize / 3.0;
  }
  else
  {
    r = ( double ) ysize / 3.0;
  }

  xc = ( ( double ) xsize ) / 2.0;
  yc = ( ( double ) ysize ) / 2.0;

  for ( i = 0; i < ysize; i++ )
  {
    y = ( ( double ) i );
    for ( j = 0; j < xsize; j++ )
    {
      x = ( ( double ) j );
      test = r - sqrt ( ( x - xc ) * ( x - xc )
               + 0.75 * ( y - yc ) * ( y - yc ) );
      if ( fabs ( test ) <= 3.0 )
      {
        *indexb = 1;
      }
      else
      {
        *indexb = 0;
      }
      indexb = indexb + 1;
    }
  }

  return;
}
//****************************************************************************80

void pbma_read ( string file_in_name, int &xsize, int &ysize, int **b )

//****************************************************************************80
//
//  Purpose:
//
//    PBMA_READ reads the header and data from an ASCII PBM file.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    22 July 2011
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, string FILE_IN_NAME, the name of the file.
//
//    Output, int &XSIZE, &YSIZE, the number of rows and columns of data.
//
//    Output, int **B, the array of XSIZE by YSIZE data values.
//
{
  ifstream file_in;
  int numbytes;

  file_in.open ( file_in_name.c_str ( ) );

  if ( !file_in )
  {
    cerr << "\n";
    cerr << "PBMA_READ - Fatal error!\n";
    cerr << "  Cannot open the input file \"" << file_in_name << "\".\n";
    exit ( 1 );
  }
//
//  Read the header.
//
  pbma_read_header ( file_in, xsize, ysize );
//
//  Allocate storage for the data.
//
  numbytes = xsize * ysize * sizeof ( int );

  *b = new int[numbytes];
//
//  Read the data.
//
  pbma_read_data ( file_in, xsize, ysize, *b );
//
//  Close the file.
//
  file_in.close ( );

  return;
}
//****************************************************************************80

void pbma_read_data ( ifstream &file_in, int xsize, int ysize, int *b )

//****************************************************************************80
//
//  Purpose:
//
//    PBMA_READ_DATA reads the data in an ASCII PBM file.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    05 June 2010
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, ifstream &FILE_IN, a pointer to the file.
//
//    Input, int XSIZE, YSIZE, the number of rows and columns of data.
//
//    Output, int *B, the array of XSIZE by YSIZE data values.
//
{
  int i;
  int j;

  for ( j = 0; j < ysize; j++ )
  {
    for ( i = 0; i < xsize; i++ )
    {
      file_in >> *b;
      if ( file_in.eof ( ) )
      {
        exit ( 1 );
      }
      b = b + 1;
    }
  }
  return;
}
//****************************************************************************80

void pbma_read_header ( ifstream &file_in, int &xsize, int &ysize )

//****************************************************************************80
//
//  Purpose:
//
//    PBMA_READ_HEADER reads the header of an ASCII PBM file.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    22 July 2011
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, ifstream &FILE_IN, a pointer to the file.
//
//    Output, int &XSIZE, &YSIZE, the number of rows and columns of data.
//
{
  int count;
  string line;
  string rest;
  int step;
  int width;
  string word;

  step = 0;

  while ( 1 )
  {
    getline ( file_in, line );

    if ( file_in.eof ( ) )
    {
      cerr << "\n";
      cerr << "PBMA_READ_HEADER - Fatal error!\n";
      cerr << "  End of file.\n";
      exit ( 1 );
    }

    if ( line[0] == '#' )
    {
      continue;
    }

    if ( step == 0 )
    {
      s_word_extract_first ( line, word, rest );

      if ( s_len_trim ( word ) == 0 )
      {
        continue;
      }
      line = rest;

      if ( ( word[0] != 'P' && word[0] != 'p' ) ||
             word[1] != '1' )
      {
        cerr << "\n";
        cerr << "PBMA_READ_HEADER - Fatal error.\n";
        cerr << "  Bad magic number = \"" << word << "\".\n";
        exit ( 1 );
      }
      step = 1;
    }

    if ( step == 1 )
    {
      s_word_extract_first ( line, word, rest );

      if ( s_len_trim ( word ) == 0 )
      {
        continue;
      }
      xsize = atoi ( word.c_str ( ) );
      line = rest;
      step = 2;
    }

    if ( step == 2 )
    {
      s_word_extract_first ( line, word, rest );

      if ( s_len_trim ( word ) == 0 )
      {
        continue;
      }
      ysize = atoi ( word.c_str ( ) );
      line = rest;
      break;
    }
  }
  return;
}
//****************************************************************************80

void pbma_read_test ( string file_in_name )

//****************************************************************************80
//
//  Purpose:
//
//    PBMA_READ_TEST tests the ASCII PBM read routines.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    22 July 2011
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, string FILE_IN_NAME, the name of the file.
//
{
  int *b;
  int xsize;
  int ysize;

  b = NULL;
//
//  Read the data.
//
  pbma_read ( file_in_name, xsize, ysize, &b );

  cout << "\n";
  cout << "  PBMA_READ was able to read \"" << file_in_name << "\".\n";
//
//  Check the data.
//
  pbma_check_data ( xsize, ysize, b );

  delete [] b;

  cout << "\n";
  cout << "  PBMA_CHECK_DATA approved the data from the file.\n";

  return;
}
//****************************************************************************80

void pbma_write ( string file_out_name, int xsize, int ysize, int *b )

//****************************************************************************80
//
//  Purpose:
//
//    PBMA_WRITE writes the header and data for an ASCII PBM file.
//
//  Example:
//
//    P1
//    # feep.pbm
//    24 7
//    0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//    0 1 1 1 1 0 0 1 1 1 1 0 0 1 1 1 1 0 0 1 1 1 1 0
//    0 1 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 1 0 0 1 0
//    0 1 1 1 0 0 0 1 1 1 0 0 0 1 1 1 0 0 0 1 1 1 1 0
//    0 1 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0
//    0 1 0 0 0 0 0 1 1 1 1 0 0 1 1 1 1 0 0 1 0 0 0 0
//    0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    05 June 2010
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, string FILE_OUT_NAME, the name of the file.
//
//    Input, int XSIZE, YSIZE, the number of rows and columns of data.
//
//    Input, int *B, the array of XSIZE by YSIZE data values.
//
{
  ofstream file_out;
  int i;
  int *indexg;
  int j;
//
//  Open the output file.
//
  file_out.open ( file_out_name.c_str ( ) );

  if ( !file_out )
  {
    cerr << "\n";
    cerr << "PBMA_WRITE - Fatal error!\n";
    cerr << "  Cannot open the output file \"" << file_out_name << "\".\n";
    exit ( 1 );
  }
//
//  Write the header.
//
  pbma_write_header ( file_out, file_out_name, xsize, ysize );
//
//  Write the data.
//
  pbma_write_data ( file_out, xsize, ysize, b );
//
//  Close the file.
//
  file_out.close ( );

  return;
}
//****************************************************************************80

void pbma_write_data ( ofstream &file_out, int xsize, int ysize, int *b )

//****************************************************************************80
//
//  Purpose:
//
//    PBMA_WRITE_DATA writes the data for an ASCII PBM file.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    05 June 2010
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, ofstream &FILE_OUT, a pointer to the file.
//
//    Input, int XSIZE, YSIZE, the number of rows and columns of data.
//
//    Input, int *B, the arrays of XSIZE by YSIZE data values.
//
{
  int i;
  int *indexb;
  int j;
  int numval;

  indexb = b;
  numval = 0;

  for ( j = 0; j < ysize; j++ )
  {
    for ( i = 0; i < xsize; i++ )
    {
      file_out << *indexb << " ";
      numval = numval + 1;
      indexb = indexb + 1;

      if ( numval % 12 == 0 || i == xsize - 1 || numval == xsize * ysize )
      {
        file_out << "\n";
      }
      else
      {
        file_out << " ";
      }

    }
  }
  return;
}
//****************************************************************************80

void pbma_write_header ( ofstream &file_out, string file_out_name, int xsize,
  int ysize )

//****************************************************************************80
//
//  Purpose:
//
//    PBMA_WRITE_HEADER writes the header of an ASCII PBM file.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    05 June 2010
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, ofstream &FILE_OUT, a pointer to the file.
//
//    Input, string FILE_OUT_NAME, the name of the file.
//
//    Input, int XSIZE, YSIZE, the number of rows and columns of data.
//
{
  file_out << "P1\n";
  file_out << "# " << file_out_name << " created by PBMA_IO::PBMA_WRITE.\n";
  file_out << xsize << "  " << ysize << "\n";

  return;
}
//****************************************************************************80

void pbma_write_test ( string file_out_name )

//****************************************************************************80
//
//  Purpose:
//
//    PBMA_WRITE_TEST tests the ASCII PBM routines.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    05 June 2010
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, string FILE_OUT_NAME, the name of the file.
//
{
  int *b;
  int xsize;
  int ysize;

  xsize = 200;
  ysize = 200;
//
//  Allocate memory.
//
  b = new int[xsize * ysize];
//
//  Set the data.
//
  pbma_example ( xsize, ysize, b );
//
//  Write the data to the file.
//
  pbma_write ( file_out_name, xsize, ysize, b );

  delete [] b;

  return;
}
//****************************************************************************80

int s_len_trim ( std::string s )

//****************************************************************************80
//
//  Purpose:
//
//    S_LEN_TRIM returns the length of a string to the last nonblank.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    05 July 2009
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, string S, a string.
//
//    Output, int S_LEN_TRIM, the length of the string to the last nonblank.
//    If S_LEN_TRIM is 0, then the string is entirely blank.
//
{
  int n;

  n = s.length ( );

  while ( 0 < n )
  {
    if ( s[n-1] != ' ' )
    {
      return n;
    }
    n = n - 1;
  }

  return n;
}
//****************************************************************************80

void s_word_extract_first ( std::string s, std::string &s1, std::string &s2 )

//****************************************************************************80
//
//  Purpose:
//
//    S_WORD_EXTRACT_FIRST extracts the first word from a string.
//
//  Discussion:
//
//    A "word" is a string of characters terminated by a blank or
//    the end of the string.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    25 October 2010
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, string S, the string.
//
//    Output, string &S1, the first word (initial blanks removed).
//
//    Output, string &S2, the remainder of the string, after removing
//    the first word (initial blanks removed).
//
{
  int i;
  int mode;
  int s_len;

  s_len = s.length ( );
  s1 = "";
  s2 = "";
  mode = 1;

  for ( i = 0; i < s_len; i++ )
  {
    if ( mode == 1 )
    {
      if ( s[i] != ' ' )
      {
         mode = 2;
      }
    }
    else if ( mode == 2 )
    {
      if ( s[i] == ' ' )
      {
        mode = 3;
      }
    }
    else if ( mode == 3 )
    {
      if ( s[i] != ' ' )
      {
        mode = 4;
      }
    }
    if ( mode == 2 )
    {
      s1 = s1 + s[i];
    }
    else if ( mode == 4 )
    {
      s2 = s2 + s[i];
    }
  }

  return;
}