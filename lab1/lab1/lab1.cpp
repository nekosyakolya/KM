#include "stdafx.h"
#include "Graph.h"


void InitGraphs(CGraph& firstGraph, CGraph& secondGraph)
{
	std::string firstGraphDataFileName;
	std::string secondGraphDataFileName;


	std::ifstream firstGraphDataFile("b1.txt");
	std::ifstream secondGraphDataFile("b2.txt");

	if (!firstGraphDataFile.is_open() || !secondGraphDataFile.is_open())
	{
		throw std::runtime_error("Failed to open datafile for reading\n");
	}

	firstGraph.Fill(firstGraphDataFile);
	secondGraph.Fill(secondGraphDataFile);
}


bool IsIsomorphic(const CGraph& firstGraph, const CGraph& secondGraph)
{
	return firstGraph.GetFormula() == secondGraph.GetFormula();
}


int main()
{
	try
	{
		CGraph firstGraph;
		CGraph secondGraph;

		InitGraphs(firstGraph, secondGraph);
		firstGraph.FindCircles();
		secondGraph.FindCircles();

		std::cout << "first graph formula :\n";
		firstGraph.PrintFormula();
		std::cout << "second graph formula :\n";
		secondGraph.PrintFormula();
		std::cout << "Graphs are " << (IsIsomorphic(firstGraph, secondGraph) ? "isomorphic" : "not isomorphic") << std::endl;
	}
	catch (const std::exception& err)
	{
		std::cerr << err.what();
	}
	return EXIT_SUCCESS;
}

