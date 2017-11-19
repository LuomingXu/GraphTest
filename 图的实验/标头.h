#pragma once
#include<iostream>
using namespace std;

int** askArray(int row, int column);
void CreatGraph(int** array, int row, int column);
void PrintVertexInfo(int** array, int row, int column);
void PrintGraph(int** array, int row, int column);
void freeArray(int** array, int row, int column);

int mai()
{
	int numberOfVertex = 0;
	int** arrayOfGraph;

	std::cout << "Please input the number of your Graph's vertexes" << endl;
	std::cin >> numberOfVertex;
	arrayOfGraph = askArray(numberOfVertex, numberOfVertex);
	CreatGraph(arrayOfGraph, numberOfVertex, numberOfVertex);
	PrintVertexInfo(arrayOfGraph, numberOfVertex, numberOfVertex);
	PrintGraph(arrayOfGraph, numberOfVertex, numberOfVertex);


	freeArray(arrayOfGraph, numberOfVertex, numberOfVertex);
	std::cout << "Pleast input any key to exit..." << endl;
	getchar();
	getchar();
	return 0;
}

int** askArray(int row, int column)
{
	int** array;
	array = (int**)malloc(sizeof(int*)*row);

	for (int i = 0; i < row; i++)
		array[i] = (int*)malloc(sizeof(int)*column);

	return array;
}

void CreatGraph(int** array, int row, int column)
{
	std::cout << "Please input array :" << endl;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
			std::cin >> array[i][j];
}

void PrintVertexInfo(int** array, int row, int column)
{
	std::cout << "OutPut graph's info" << endl;
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < column; j++)
		{
			if (array[i][j] != 0)
			{
				std::cout << i + 1 << "与" << j + 1 << "之间的权为" << array[i][j] << endl;
			}
		}
	}
}

void PrintGraph(int** array, int row, int column)
{
	std::cout << "Output graph :" << endl;
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < column; j++)
		{
			std::cout << array[i][j] << "  ";
		}
		std::cout << endl;
	}
}

void freeArray(int** array, int row, int column)
{
	for (int i = 0; i < row; i++)
		free(array[i]);

	free(array);
}
