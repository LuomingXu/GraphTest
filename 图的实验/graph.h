#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<sstream>
#include<exception>
using namespace std;

template<class T>
void convertFromStringToInt(T &value, const std::string &s)
{
	std::stringstream ss(s);
	ss >> value;
}

std::vector<std::string> Split(const std::string& s, const std::string& delim)
{//#include string vector algorithm
	std::vector<std::string> v;

	if (!delim.empty())
	{
		auto b = s.begin();
		auto i = s.end();
		while ((i = std::search(b, s.end(), delim.begin(), delim.end())) != s.end())
		{
			if (i - b > 0) // token can't be empty string
			{
				v.emplace_back(std::string(b, i));
			}

			b = i + delim.length();
		}

		if (b != s.end())
		{
			v.emplace_back(std::string(b, s.end()));
		}
	}
	else
	{
		throw "Delimiter can't be empty string";
	}

	return v;
}

class Arc//矩阵类
{
public:
	int info;
	int value;
	bool visited;
};

class Graph//图
{
public:
	Graph(int NumOfVertex, int NumOfArc);
	~Graph();
	void InputVertexInfo();
	void CreatAdjMartix();
	void OutputVertexInfo();
	void OutputAdjMartix();
	void OutputDegree();
	void DepthFirsrSearch(int i);
	void BroadthFirstSearch();
	void ClearShown();
	void test();
	int* Vertex;//储存顶点的信息
	Arc** MatrixOfGraph;//邻接矩阵
	int NumOfVertex = 0;//顶点个数
	int NumOfArc = 0;//弧数
private:
	int GetFormer(int row);
	bool Shown(int vertex);
	//Judge(int row, int column);
	int count = 0;
	int* shown;//通过这个数组来判断是否已经出现过了这个vex
};

Graph::Graph(int NumOfVertex, int NumOfArc)
{
	this->NumOfVertex = NumOfVertex;
	this->NumOfArc = NumOfArc;

	Vertex = (int*)malloc(sizeof(int)*NumOfVertex);
	shown = (int*)malloc(sizeof(int)*NumOfVertex);
	this->MatrixOfGraph = (Arc**)malloc(sizeof(Arc*)*NumOfVertex);
	for (int i = 0; i < NumOfVertex; i++)
		this->MatrixOfGraph[i] = (Arc*)malloc(sizeof(Arc)*NumOfVertex);//初始化三个指针变量

	//initialize martic
	for (int i = 0; i < this->NumOfVertex; i++)
		for (int j = 0;  j < this->NumOfVertex;  j++)
		{
			this->MatrixOfGraph[i][j].info = NULL;
			this->MatrixOfGraph[i][j].value = 0;//因为是无向图, 所以初始化为"0"
			this->MatrixOfGraph[i][j].visited = false;
		}
}

Graph::~Graph()//析构函数释放内存
{
	free(this->Vertex);
	for (int i = 0; i < this->NumOfVertex; i++)
		free(this->MatrixOfGraph[i]);
	free(this->MatrixOfGraph);
}

inline void Graph::InputVertexInfo()
{
	std::cout << "Please input info of Vertex :" << endl;
	for (int i = 0; i < this->NumOfVertex; i++)
	{
		std::cout << "the " << i + 1 << "th Vertex :";
		std::cin >> Vertex[i];
	}
	std::cout << "Input info succeed !" << endl << endl;
}

inline void Graph::CreatAdjMartix()
{
	int row = 0, column = 0, info = 0;
	string str;
	std::cout << "Please input AdjMatrix of Graph..." << endl;
	for (int i = 0; i < this->NumOfArc; i++)
	{
		//std::cout << "Please input the " << i + 1 << "th arc. LIKE :1,2,100. one vertex, the other vertex, arc's info" << endl;
		std::cin >> str;
		auto v = Split(str, ",");
		convertFromStringToInt(row, v[0]); convertFromStringToInt(column, v[1]); convertFromStringToInt(info, v[2]);
		/*std::cout << "Please input " << i + 1 << "th arc's row :" << endl;
		std::cin >> row;
		std::cout << "Please input " << i + 1 << "th arc's column :" << endl;
		std::cin >> column;
		std::cout << "Please input its info. If there no info for it, please input \"0\"" << endl;
		std::cin >> info;*/

		this->MatrixOfGraph[row - 1][column - 1].value = 1;
		this->MatrixOfGraph[column - 1][row - 1].value = 1;

		if (info != 0)
		{
			this->MatrixOfGraph[row - 1][column - 1].info = info;
			this->MatrixOfGraph[column - 1][row - 1].info = info;
		}
	}

	std::cout << "Input AdjMatrix succeed !" << endl << endl;
}

inline void Graph::OutputVertexInfo()
{
	std::cout << "Output Vertex'info start..." << endl;
	for (int i = 0; i < this->NumOfVertex; i++)
		std::cout << "The " << i + 1 << "th Vertex's info :" << Vertex[i] << endl;
	std::cout << "Vertex'info END !" << endl << endl;
}

inline void Graph::OutputAdjMartix()
{
	std::cout << "Output AdjMatrix start..." << endl;

	for (int i = 0; i < this->NumOfVertex; i++)
	{
		for (int j = 0; j < this->NumOfVertex; j++)
		{
			std::cout << this->MatrixOfGraph[i][j].value << "  ";
		}
		std::cout << endl;
	}

	std::cout << "AdjMatrix END !" << endl << endl;
}

inline void Graph::OutputDegree()
{
	std::cout << "Output Degree start..." << endl;

	int count = 0;
	for (int i = 0; i < this->NumOfVertex;)
	{
		count = 0;
		for (int j = 0; j < this->NumOfVertex; j++)
		{
			if (this->MatrixOfGraph[i][j].value == 1)
				count++;
		}
		std::cout << "The " << ++i << "th vertex'degree is :" << count << endl;
	}
	std::cout << "Degree END" << endl << endl;
}

inline void Graph::DepthFirsrSearch(int i)
{
	exception ex;
	for (int j = i + 1; j < this->NumOfVertex; j++)
	{
		if (this->MatrixOfGraph[i][j].value == 1 && this->MatrixOfGraph[i][j].visited == false)
		{
			if (!Graph::Shown(j + 1))
				std::cout << j + 1 << "  ";
			//std::cout << i << "," << j <<endl;
			this->shown[count] = j + 1;this->count++;

			this->MatrixOfGraph[i][j].visited = true;
			this->MatrixOfGraph[j][i].visited = true;//在用到GetFormer函数的时候, 因为遍历过了, 就可以知道这个之前的那个i是什么

			if(this->count == this->NumOfVertex)
				throw ex;
			Graph::DepthFirsrSearch(j);
		}
	}
	Graph::DepthFirsrSearch(Graph::GetFormer(i));
}

inline void Graph::BroadthFirstSearch()
{
	for (int i = 0; i < this->NumOfVertex; i++)
		for (int j = i + 1; j < this->NumOfVertex; j++)
			if (this->MatrixOfGraph[i][j].value == 1)
			{
				if (!Graph::Shown(j + 1))
					std::cout << j + 1 << "  ";
				this->shown[count] = j + 1;
				this->count++;
			}
}

inline void Graph::ClearShown()
{
	this->count = 0;
	for (int i = 0; i < this->NumOfVertex; i++)
		this->shown[i] = NULL;
}

inline void Graph::test()
{
	for (int i = 0; i < this->NumOfVertex; i++)
		std::cout << this->shown[i];
}

//inline bool Graph::Judge(int row, int column)
//{
//	for (int i = row; i < column; i++)
//	{
//		for (int j = column; j < this->NumOfVertex; j++)
//		{
//			if (this->MatrixOfGraph[i][j].value == 1 /*|| this->MatrixOfGraph[i][j].visited == true*/)
//			{
//				return false;
//			}
//		}
//	}
//	return true;
//}

inline int Graph::GetFormer(int row)
{
	for (int  i = 0; i < row; i++)
		if (this->MatrixOfGraph[row][i].value == 1 && this->MatrixOfGraph[row][i].visited == true)
			return i;
	return 0;
}

inline bool Graph::Shown(int vertex)
{
	for (int i = 0; i < this->NumOfVertex; i++)
		if (this->shown[i] == vertex)
			return true;
	return false;
}
