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
#include <math.h>

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
string setToString(t_set set);
double det(double **m, int n);
double **matrizMenor(double **m, double **m2, int c, int n);
int **freeMQ(double **m, int n);
double **alocarMQ(int n);


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

	if(iterations == 0)
		return set[0];

	t_vector u = set[iterations];
	int j = 0;
	while(j < iterations){

		u = u - proj(u, set[j]);
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


t_vector toVector(vector<string>& strSet){

	t_vector _vector;
	for(vector<string>::iterator string_value = strSet.begin(); string_value != strSet.end(); ++string_value)
		_vector.push_back(toDouble(*string_value));

	return _vector;
}


string setToString(t_set set){

	string _string = "{";

	for(int i = 0; i < set.size(); i++){

		_string += set[i].toString();

		if(i != set.size() - 1)
			_string += ',';
	}
	
	return _string + "}";
}

//Retorna o determinante da matriz m de ordem n por Laplace
double det(double **m, int n){
	//Caso fundamental
	if(n == 1)
		return **m;
	
	//Criando a matriz do cofator
	int c;
	double cof, **m2 = alocarMQ(n-1), d;
	
	//Para cada coluna
	for(c=0; c<n; c++){
		//Calculando o cofator
		cof = (c%2?-1:1) * det(matrizMenor(m, m2, c, n), n-1);
		//Somando a parcela ao determinante final
		d += m[0][c]*cof;
	}
	
	//Liberando o espaço alocado da matriz do cofator
	freeMQ(m2, n-1);
	
	//Retornando o determinante
	return d;
}

//Retira a primeira linha a coluna c de m e armazena em m2. n é a ordem de m
double **matrizMenor(double **m, double **m2, int c, int n){
	int i, j; 
	double **p=m2, *p2;
	for(i = 1; i < n; i++){
		p2 = *p++;
		for(j = 0; j < n; j++)
			if(j==c) continue;
			else *p2++ = m[i][j];
	}
	return m2;
}

//Aloca espaço para uma matriz quadrada
double **alocarMQ(int n){
	double **m;
	int i;
	m = (double**)calloc(n, sizeof(double*));
	if(m == NULL) exit(1);
	for(i=0; i<n; i++){
		*(m+i) = (double*)calloc(n, sizeof(double));
		if(*(m+i) == NULL) exit(1);
	}
	return m;
}


//Desaloca espaço de uma matriz quadrada
int **freeMQ(double **m, int n){
	int i;
	if(m == NULL) return NULL;
	for(i=0; i<n; i++) free(m[i]);
	free(m);
	return NULL;
}

bool isBase(t_set& set){
	
	double **mt = alocarMQ(6);

	for(int it = 0; it < set.size(); it++)
		for(int j = 0; j < set[it].size(); j++)
			mt[it][j] = set[it][j];

	double retorno = det(mt, 5);

	if(fabs(retorno-0) < 0.0000001)
		return false;

	return true;
};

#endif