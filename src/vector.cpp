/*	Wesley Burlani - Federal University of Fronteira Sul	1511100022
 *  The Gram Schimdt's Orthogonalization process to R5. 
 * 	contact.: wesleyburlani@gmail.com	Copyleft ©2016
*/

#ifndef VECTOR_CPP
#define VECTOR_CPP

/*	inclusions  */

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <stdlib.h>

#define t_scalar double
#define t_set  vector<t_vector>

using namespace std;

/*	Definition of class Set and your overloaded operators */

class t_vector : public vector<double>
{
public:
/*	Defines to clean code to algebraists settings */
    t_scalar operator*(t_vector);
    t_vector operator*(double);
    t_vector operator+(t_vector);
    t_vector operator-(t_vector);

    string toString();
};

/* Overloading operators */

string t_vector::toString(){


	string _string = "(";

	for(int j = 0; j < this->size(); j++){
		
		std::ostringstream strs;
		strs << (*this)[j];

		_string += strs.str();

		if(j != this->size()-1)
			_string += ",";
	}

	_string += ")";

	return _string;
};

t_scalar t_vector::operator*(t_vector u){

	t_scalar internalProduct =  0.00;

	for(int i = 0; i < this->size(); i++)
		internalProduct += (*this)[i] * u[i];

	return internalProduct;	
};

t_vector t_vector::operator*(double d){

	t_vector dotProduct;

	for(int i = 0; i < this->size(); i++)
		dotProduct.push_back((*this)[i] * d);

	return dotProduct;	
};

t_vector t_vector::operator+(t_vector u){

	t_vector sum;

	for(int i = 0; i < this->size(); i++)
		sum.push_back((*this)[i] + u[i]);

	return sum;	
};

t_vector t_vector::operator-(t_vector u){

	t_vector sub;

	for(int i = 0; i < this->size(); i++)
		sub.push_back((*this)[i] - u[i]);

	return sub;	
};

#endif