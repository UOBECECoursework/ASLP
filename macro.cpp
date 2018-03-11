#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
  if(argc != 5)
    {
      cerr << "Usage: " << argv[0] << " VECSIZE PARAMETER_TYPE infile outfile" << endl;
      return 0;
    }

  ifstream fs_in(argv[3]);
  if(!fs_in.is_open())
    {
      cerr << "Cannot open file " << argv[3] << endl;
      return 0;
    }

  ofstream fs_out(argv[4]);
  if(!fs_out.is_open())
    {
      cerr << "Cannot open file " << argv[4] << endl;
      return 0;
    }

  fs_out << "~o\n<STREAMINFO> 1 " << argv[1] << endl;
  fs_out << "<VECSIZE> " << argv[1] << endl;
  fs_out << "<NULLD>\n<" << argv[2] << ">" << endl;

  char c;
  while(fs_in.get(c))
    fs_out << c;

  fs_in.close();
  fs_out.close();
}

