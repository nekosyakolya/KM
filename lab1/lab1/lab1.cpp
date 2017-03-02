#include "stdafx.h"
#include "Graph.h"

void InitGraphs(CGraph& firstGraph, CGraph& secondGraph);
void ProcessGraphs(CGraph& firstGraph, CGraph& secondGraph);
bool IsIsomorphic(const Formula& first, const Formula& second);

int main()
{
	try
	{
		CGraph firstGraph;
		CGraph secondGraph;

		InitGraphs(firstGraph, secondGraph);
		ProcessGraphs(firstGraph, secondGraph);
		
		std::cout << "first graph formula :\n";
		firstGraph.PrintFormula();
		std::cout << "second graph formula :\n";
		secondGraph.PrintFormula();
		std::cout << "Graphs are " << (IsIsomorphic(firstGraph.GetFormula(), secondGraph.GetFormula()) ? "isomorphic" : "not isomorphic") << std::endl;
	}
	catch (const std::exception& err)
	{
		std::cerr << err.what();
	}
	return EXIT_SUCCESS;
}

void InitGraphs(CGraph& firstGraph, CGraph& secondGraph)
{
	std::string firstGraphDataFileName;
	std::string secondGraphDataFileName;


	std::ifstream firstGraphDataFile("4.txt");
	std::ifstream secondGraphDataFile("6.txt");
	
	if (!firstGraphDataFile.is_open() || !secondGraphDataFile.is_open())
	{
		throw std::runtime_error("Failed to open datafile for reading\n");
	}

	firstGraph.Fill(firstGraphDataFile);
	secondGraph.Fill(secondGraphDataFile);
}

void ProcessGraphs(CGraph& firstGraph, CGraph& secondGraph)
{
	firstGraph.FindCircles();
	secondGraph.FindCircles();
}

bool IsIsomorphic(const Formula & first, const Formula & second)
{
	return first == second;
}
