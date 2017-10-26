#include "stdafx.h"
#include "functions.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <string>


using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution <int> dis(0, 13);
uniform_int_distribution <int> disNum(0, 13);
uniform_int_distribution <int> disOp(10, 13);
uniform_int_distribution <int> dis5050(0, 1);
uniform_int_distribution <int> disMutate(0, 7);
uniform_int_distribution <int> dis9(0, 8);


chromosome::chromosome()
{

	for (int i = 0; i < 9; i++)
	{
		if (!(i % 2)) {
			this->genes.push_back(disNum(gen));
		}
		else
		{
			this->genes.push_back(disOp(gen));
		}
	}
	this->checkvalue();
}

chromosome::chromosome(vector <int> a)
{
	this->genes = a;
	this->checkvalue();
}


void chromosome::print()
{
	for (int i = 0; i < 9; i++)
	{
		cout << this->genes[i] << "\n";
	}
}

void chromosome::checkvalue()
{
	double result = 0;
	const double cob = 0.296974204373370089379887843;
	for (int i = 0; i < 9; i++)
	{
		if (this->genes[i] < 0 || this->genes[i] > 13)
		{
			this->value = -1;
			this->fitness = 1;
			return;
		}
	}


	for (int j = 0; j < 4; j++)
	{
		if (j == 0) {

			switch (genes[1 + j * 2])
			{
			case 10:
			{
				result += genes[j * 2] + genes[(j + 1) * 2];
				break;
			}
			case 11:
			{
				result += genes[j * 2] - genes[(j + 1) * 2];
				break;
			}
			case 12:
			{
				result += genes[j * 2] * genes[(j + 1) * 2];
				break;
			}
			case 13:
			{
				if (genes[(j + 1) * 2] == 0)
				{
					this->value = -1;
					this->fitness = 1;
					return;
				}
				result += genes[j * 2] / genes[(j + 1) * 2];
				break;
			}
			// default case is addition
			default:
			{
				//cout << "Something went wrong" << "\n";
				this->value = -1;
				this->fitness = 1;
				return;
			}
			}
		}
		else
		{
			switch (genes[1 + j * 2])
			{
			case 10:
			{
				result += genes[(j + 1) * 2];
				break;
			}
			case 11:
			{
				result -= genes[(j + 1) * 2];
				break;
			}
			case 12:
			{
				result *= genes[(j + 1) * 2];
				break;
			}
			case 13:
			{
				if (genes[(j + 1) * 2] == 0)
				{
					this->value = -1;
					this->fitness = 1;
					return;
				}
				result /= genes[(j + 1) * 2];
				break;
			}
			default:
			{
				//cout << "Something went wrong" << "\n";
				this->value = -1;
				this->fitness = 1;
				return;
			}
			}
		}

	}
	this->value = abs(result);
	if (this->value <= 1)
	{
		this->fitness = 1;
	}
	else {
		this->fitness = abs(1 - log(value) * cob);
	}

}

double chromosome::getvalue()
{
	return this->value;
}

double chromosome::getfitness()
{
	return this->fitness;
}

void chromosome::changegenes(vector <int> a)
{
	this->genes.clear();
	this->genes = a;
}

void chromosome::changegene(int a, int b)
{
	this->genes[a] = b;
}

vector<int> chromosome::getgenes()
{
	return this->genes;
}

int chromosome::getgene(int a)
{
	return this->genes[a];
}

bool chromosome::operator<(const chromosome & other) const
{
	return (this->fitness < other.fitness);
}

chromosome & chromosome::operator=(const chromosome & other)
{
	if (this == &other) {
		return (*this);
	}
	else
	{
		this->changegenes(other.genes);
		this->value = other.value;
		this->fitness = other.fitness;
		return (*this);
	}
}

string chromosome::tochar(int a)
{
	if (!(a % 2))
	{
		return to_string(genes[a]);
	}
	else
	{
		switch (genes[a])
		{
		case 10:
		{
			return "+";
		}
		case 11:
		{
			return "-";
		}
		case 12:
		{
			return "*";
		}
		case 13:
		{
			return "/";
		}
		default:
			return "Something went wrong";
		}
	}
}

void chromosome_sorter(vector <chromosome> &a)
{
	//vector <chromosome> temp = a;
	sort(a.begin(), a.end());
	for (int i = 0; i < a.size(); i++)
	{
		a[i].checkvalue();
	}
	//return temp;
}

chromosome reproduce(chromosome a, chromosome b)
{
	vector <int> vec1 = a.getgenes();
	vector <int> vec2 = b.getgenes();
	vector <int> result;

	for (int i = 0; i < 9; i++)
	{
		if (dis5050(gen))
		{
			result.push_back(vec1[i]);
		}
		else
		{
			result.push_back(vec2[i]);
		}
	}

	return chromosome(result);
}

void mutate(vector <chromosome> &a)
{
	for (int i = 0; i < a.size(); i++)
	{
		if (disMutate(gen) == 1)
		{
			int index = dis9(gen);
			int change = 0;
			if (dis5050(gen))
			{
				change++;

			}
			else
			{
				change--;
			}
			a[i].changegene(index, (a[1].getgene(index) + change));
			if ((index % 2))
			{
				if (a[i].getgene(index) > 13)
				{
					a[i].changegene(index, 10);
				}
				else if (a[i].getgene(index) < 10)
				{
					a[i].changegene(index, 13);
				}
			}

		}
		a[i].checkvalue();
	}

}

void display_pool(string message, vector <chromosome> pool)
{
	cout << message << "\n";
	for (int i = 0; i < pool.size(); i++)
	{
		cout << "Value: " << pool[i].getvalue() << "\t\t Fitness: " << pool[i].getfitness() << "\n";
	}
	cout << "\n";
}

void regen_pool(vector <chromosome> &pool)
{
	while (pool.size() < 9)
	{
		chromosome* c1 = new chromosome();
		if (c1->getvalue() != -1)
		{
			pool.push_back(*c1);
		}
		else
		{
			delete c1;
		}
	}
}

void cull_pool(vector <chromosome> &pool)
{
	pool.erase(pool.end() - 5, pool.end());
}

void reproduce_pool(vector <chromosome> &pool)
{

	pool.push_back(reproduce(pool[0], pool[1]));
	pool.push_back(reproduce(pool[1], pool[2]));
	pool.push_back(reproduce(pool[2], pool[3]));
	regen_pool(pool);
}

double avg_member(vector <chromosome> pool)
{
	double counter = 0;
	for (int i = 0; i < pool.size(); i++)
	{
		counter += pool[i].getfitness();
	}
	counter /= pool.size();
	return counter;
}

void best_member(vector <chromosome> pool)
{
	cout << "Best member: " << pool[0].getvalue() << "\n";
}


int life_cycle(vector <chromosome> &pool)
{
	regen_pool(pool);

	chromosome_sorter(pool);
	if (pool[0].getvalue() == 29)
	{
		cout << "Solution: ";
		for (int i = 0; i < 9; i++)
		{
			cout << pool[0].tochar(i);
		}
		cout << "\n";
		return 0;
	}

	cull_pool(pool);


	reproduce_pool(pool);

	mutate(pool);

	

	return -1;
}


void test(vector <chromosome> &pool, int a)
{
	int counter = 0;
	for (int i = 0; i < a; i++) {
		pool.clear();
		regen_pool(pool);
		while (life_cycle(pool) != 0)
		{
			counter++;
		}
		
	}
	counter /= a;


	cout << "Average cycles: " << counter << "\n";
}