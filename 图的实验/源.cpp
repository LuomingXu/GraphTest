#include"graph.h"

int main()
{
	int NumOfVertex = 0;//顶点个数
	int NumOfArc = 0;//弧数	
	std::cout << "Please input the number of vertex :" << endl;
	std::cin >> NumOfVertex;
	std::cout << "Please input the number of arc :" << endl;
	std::cin >> NumOfArc;

	Graph G(NumOfVertex, NumOfArc);
	G.InputVertexInfo();
	G.CreatAdjMartix();
	G.OutputVertexInfo();
	G.OutputAdjMartix();
	G.OutputDegree();

	std::cout << "Depth-first search:\n1  ";
	try {G.DepthFirsrSearch(0);}
	catch (const std::exception&) {}

	//G.test();
	G.ClearShown();
	std::cout << endl;

	std::cout << "Broadth-first search:\n1  ";
	G.BroadthFirstSearch();

	std::cout << endl << "Please input any key to exit..." << endl;
	getchar();
	getchar();
	return 0;
}