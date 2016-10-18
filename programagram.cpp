/*	Wesley Burlani - Federal University of Fronteira Sul	1511100022
 *  The Gram Schimdt's Orthogonalization process to R5. 
 * 	contact.: wesleyburlani@gmail.com	Copyleft ©2016
*/

/*	inclusions  */

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdlib.h>

#include "src/vector.cpp"
#include "src/functions.cpp"


/*	Defines to clean code to algebraists settings */

#define t_scalar double
#define t_set  vector<t_vector>

using namespace std;


/*	Start Program	*/

int main(void){

	vector<string> input;
	string allInput = "";
	string output = "";

	readInput(input, "../ortogonaliza.txt", allInput);

	t_set set;

	for(vector<string>::iterator inputLine = input.begin(); inputLine != input.end(); ++inputLine){

		vector<string> strSet = split(*inputLine, ',');

		set.push_back(toVector(strSet));
	}
	
	if(!isBase(set))
		output += "This inputs is a non-base of R5 vetorial space.\n";
	
	else{

		t_set orthogonalized;

		for(int i = 0; i < 5; i++){
			set[i] = ortogonalizate(set, i);
			orthogonalized.push_back(set[i]);
		}

		ofstream outputFile("../ortogonaliza.txt");
		outputFile << allInput <<  setToString(orthogonalized) << endl;	
	}
}
