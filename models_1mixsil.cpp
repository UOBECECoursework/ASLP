/***********************************************
 * Author: liyao
 * Usage: models_1mixsil HMMnamelist deffile modelfile
 * Description: Takes hmmdef file(deffile) and expand it into model file(modelfile) according to word/phoneme name list(HMMnamelist)
 *************************************************/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

inline void copyModel(ifstream& in_fs, ofstream& out_fs, streampos beg, streampos end);

int main(int argc, char** argv)
{
  if(argc != 4)
    {
      cerr << "Usage: " << argv[0] << " HMMnamelist deffile modelfile" << endl;
      return 0;
    }

  ifstream fs_list, fs_def;
  ofstream fs_models;

  vector<string> vec_HMM_names;
  string HMM_name;
  //Read from model name list
  fs_list.open(argv[1]);
  if(!fs_list.is_open())
    {
      cerr << "Invalid model name list file!" << endl;
      return 0;
    }

  while(fs_list >> HMM_name)
    vec_HMM_names.push_back(HMM_name);
  fs_list.close();
  
  fs_def.open(argv[2]);
  if(!fs_def.is_open())
    {
      cerr << "Invalid def file name!" << endl;
      return 0;
    }
  
  //Find model definition starting and end point
  streampos stream_beg, stream_end;  
  string line;
  while(getline(fs_def, line))
    {
      if(line.substr(0, 2) == "~h")
	{
	  stream_beg = fs_def.tellg();
	  break;
	}
    }
  
  if(!fs_def)
    {
      cerr << "def file format error" << endl;
      return 0;
    }
  
  fs_list.seekg(0, ios_base::end);
  stream_end = fs_list.tellg();
  
  //Copy model definitions
  fs_models.open(argv[3]);
  if(!fs_models.is_open())
    {
      cerr << "Invalid model file name!" << endl;
      return 0;
    }
  
  for(auto HMM_names_it = vec_HMM_names.begin(); HMM_names_it != vec_HMM_names.end(); ++HMM_names_it)
    {
      fs_models << "~h " << "\"" << *HMM_names_it << "\"" << endl;
      copyModel(fs_def, fs_models, stream_beg, stream_end);
    }

  fs_def.close();
  fs_models.close();
}


void copyModel(ifstream& in_fs, ofstream& out_fs, streampos beg, streampos end)
{
  in_fs.clear(ios::goodbit);
  in_fs.seekg(beg);
  char c;
  while(in_fs.get(c).tellg() != end)
    out_fs.put(c);
}
