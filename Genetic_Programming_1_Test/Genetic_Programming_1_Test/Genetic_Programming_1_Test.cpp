// Genetic_Programming_1_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "functions.h"
#include <iostream>
#include <vector>
#include <random>
#include <windows.h>

using namespace std;
vector <chromosome> pool;
LARGE_INTEGER frequency;
LARGE_INTEGER t1;
LARGE_INTEGER t2;
double elapsed;


int main()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&t1);

	test(pool, 1);
	
	QueryPerformanceCounter(&t2);

	elapsed = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	elapsed /= 1000;
	cout << "Time elapsed: " << elapsed << "\n";

	return 0;
}

