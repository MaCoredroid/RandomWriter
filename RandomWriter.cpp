/*
 * File: RandomWriter.cpp
 * ----------------------
 * [TODO: fill in your name and student ID]
 * Name:马致远
 * Student ID:517021910070
 * This file is the starter project for the random writer problem of Lab 2.
 * [TODO: extend the documentation]
 */


#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
using namespace std;
#define MAX_CHAR_NUM 2000//write MAX_CHAR_NUM at a time
vector<char> line;//to store the origin article

// get filename
void read_file(ifstream &file_input);

// get order number
int read_order();

// build model
void model_read(ifstream &file_input, const int &order, map<string, vector<char>> &model);

// write
void random_write(const int &order, map<string, vector<char>> &model);

void read_file()
{
	cout << "Please enter filename containing source text:";
	string file_name;
	cin >> file_name;
	ifstream file_input;
	file_input.open(file_name.c_str());
	char ch;
	while (file_input.get(ch))
	{
		line.push_back(ch);//input every char
	}
	

}

int read_order()
{
	cout << "Please enter order:";
	int order = 1;
	cin >> order;//read the order
	return order;
}

void model_read(const int &order, map<string, vector<char>> &model)
{
	for (int i = 0; i < line.size() - order; i++)
	{
		string seed = "";
		for(int n=i;n<i+order;n++)
		{
			seed += line[n];//generate seed
		}
		if (model.find(seed) == model.end())//if the seed is not in the map, add a new pair
		{
			vector<char> temp;
			temp.push_back(line[i+order]);
			model.insert(pair< string, vector<char>>(seed, temp));

		}
		else
		{
			model[seed].push_back(line[i + order]);//if the seed is in the map, add to the following
		}
	}
	
}

void random_write(const int &order, map<string, vector<char>> &model)
{
	srand((unsigned)time(NULL));
	int maxlength = 0;
	map<string, vector<char>>::iterator iter;
	map<string, vector<char>>::iterator temp;
	iter = model.begin();
	while (iter != model.end())//run throungh the map to get the most popular seed
	{
		
		if (maxlength < iter->second.size())
		{
			maxlength = iter->second.size();
			temp = iter;
		}
		iter++;

	}
	cout << temp->first;
	string firstseed = temp->first;//the most popular seed
	int num = order;
	while (model.find(firstseed) != model.end()&&num<=MAX_CHAR_NUM)//write MAX_CHAR_NUM at a time
	{
		string tempstr = firstseed;
		for (int i = 0; i < order-1; i++)
		{
			firstseed[i] = tempstr[i + 1];
		}
		int tempsize = model[tempstr].size();
		int c =int( tempsize * rand() / (RAND_MAX + 1));
	    firstseed[order - 1] =model[tempstr][c];//add the last char according to its occurence randomly
		cout << model[tempstr][c];
		num++;//calculate the num of char taht has been written
	}
}

int main()
{
	const int order=read_order();
	map<string, vector<char>> model;
	read_file();
	model_read(order, model);
	random_write(order, model);
	return 0;
}