#pragma once
#include "stdafx.h"
#include <vector>

using namespace std;


class chromosome
{
public:
	chromosome();
	chromosome(vector <int>);
	void print();
	void checkvalue();
	double getvalue();
	double getfitness();
	void changegenes(vector <int>);
	void changegene(int, int);
	vector <int> getgenes();
	int getgene(int);
	string tochar(int);

	bool operator< (const chromosome &) const;
	chromosome& operator= (const chromosome &);

private:
	vector <int> genes;
	double value;
	double fitness;
};

void chromosome_sorter(vector <chromosome> &);
chromosome reproduce(chromosome, chromosome);
void mutate(vector <chromosome> &);
void display_pool(string, vector <chromosome>);
void regen_pool(vector <chromosome> &);
void cull_pool(vector <chromosome> &);
void reproduce_pool(vector <chromosome> &);
double avg_member(vector <chromosome>);
void best_member(vector <chromosome>);


int life_cycle(vector <chromosome> &);

void test(vector <chromosome> &, int a);