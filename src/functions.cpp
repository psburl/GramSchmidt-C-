/*	Wesley Burlani - Federal University of Fronteira Sul	1511100022
 *  The Gram Schimdt's Orthogonalization process to R5. 
 * 	contact.: wesleyburlani@gmail.com	Copyleft ©2016
*/

#ifndef FUNC_CPP
#define FUNC_CPP

/*	inclusions  */

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdlib.h>

#include "vector.cpp"

using namespace std;

#define t_scalar double
#define t_set  vector<t_vector>

/*	Functions signatures	*/

bool readInput(vector<string>& readLines, const char* FilePath);

vector<string> split(const string &s, char delim);

double toDouble(string s);
t_vector toVector(vector<string>& strSet);
void removeAllOcurrences(string& string_value, char toremove);

bool isBase(vector<t_vector>& sets);
t_vector proj(t_vector set, t_vector base);
t_vector ortogonalizate(t_set set, int iterations);


/*	Functions implementations	*/

bool readInput(vector<string>& readLines, const char* FilePath, string& allInput){

	fstream file(FilePath, std::ios::in);

	if(!file.is_open()){
		cout << "The file " << FilePath << " was not found!\n";
		return false;
	}

	try{

		string line;

		getline(file, line);
		allInput += line + "\n"; 

		while(getline(file, line)){

			removeAllOcurrences(line, '(');
			removeAllOcurrences(line, ')');
			readLines.push_back(line);	
			allInput += line  + "\n";
		}

		if(readLines.size() > 0)
			readLines.erase(readLines.begin() + readLines.size()-1);
			
		return true;

	}catch(...){

		cout  << "Function 'readInput': Error reading this line in input.\n";
	}
};

t_vector proj(t_vector set, t_vector base){

	double internalProduct = set * base;
	double internalProductBase = base * base;

	return  base * (internalProduct/internalProductBase);
};

t_vector ortogonalizate(t_set set, int iterations){

	int position = iterations-1;

	t_vector u = set [position];
	int j = 0;
	while(j < (position-1)){

		u = u - proj(set[position], set[j]);
		j++;
	}

	return u;
};

void removeAllOcurrences(string& string_value, char toremove){
	string_value.erase(std::remove(string_value.begin(), string_value.end(), toremove), string_value.end());
}

double toDouble(string string_value){ 

    return atof(string_value.c_str());
};

vector<string> split(const string &string_split, char delimiter) {
    

    stringstream stream_string(string_split);
    string item;
    vector<string> tokens;
    
    while (getline(stream_string, item, delimiter)) 
        tokens.push_back(item);
    
    return tokens;
}	

bool isBase(t_set& set){

	return true;
};

t_vector toVector(vector<string>& strSet){

	t_vector _vector;
	for(vector<string>::iterator string_value = strSet.begin(); string_value != strSet.end(); ++string_value)
		_vector.push_back(toDouble(*string_value));

	return _vector;
}

#endif