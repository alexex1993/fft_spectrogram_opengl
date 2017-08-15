#ifndef _ARRAY_SAMPLE__
#define _ARRAY_SAMPLE_
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::ostream;
using std::endl;

class ClassArraySample
{
private:
	string filename;
	vector<double> v;
	bool answer;
public:
	ClassArraySample();
	ClassArraySample(string filename_, bool answer_);
	void addFileName(string filename_);
	void addElementVector(double addElement);
	int getSizeVector();
	double& operator[] (int x) 
	{  
	  return v[x]; 
	  
	}
        
        friend ostream& operator<< (ostream& os, const ClassArraySample& e)
	{
	  
	  for(int i = 0; i < e.v.size(); i++)
	  {
		os << e.v[i] << " ";
	  }
	  os << endl;
	  
	  return os;
	}
        

};

#endif
