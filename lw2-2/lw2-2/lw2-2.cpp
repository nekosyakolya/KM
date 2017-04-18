#include "stdafx.h"
#include <vector>
#include <string>
#include <fstream>
#include <set>
#include <iostream>

typedef std::vector<std::vector<size_t>> Matrix;
const size_t FIELD_SIZE = 3;

struct Position
{
	Position(size_t x, size_t y) :
		x(x),
		y(y)
	{
	}
	size_t x = 0;
	size_t y = 0;
};

struct Node
{
	size_t hash = 0;
	Matrix matrix;
	Position zeroPosition = Position(0, 0);
	Node *father = nullptr;
	void CalculateZeroPosition()
	{
		for (size_t i = 0; i < matrix.size(); ++i)
		{
			for (size_t j = 0; j < matrix[i].size(); ++j)
			{
				if (matrix[i][j] == 0)
				{
					zeroPosition = Position(j, i);
					break;
				}
			}
		}
	}
	void GetHash()
	{
		for (size_t i = 0; i < matrix.size(); i++)
		{
			for (size_t j = 0; j < matrix.front().size(); j++)
			{
				hash = hash * 10 + matrix[i][j];
			}
		}
	}
};


Matrix GetMatrix(std::ifstream & input)
{
	Matrix tmp;
	std::string str;
	while (getline(input, str))
	{
		std::vector<size_t> tempVector;
		for (auto el : str)
		{
			tempVector.push_back(el - '0');
		}
		tmp.push_back(tempVector);
	}
	return tmp;
}


bool IsHashValid(const std::set<size_t> &passedHashes, size_t hash)
{
	return (passedHashes.find(hash) == passedHashes.end());
}


Node *CreateNewNode(Node *currentNode, int directionX, int directionY)
{
	Node *newNode = new Node;
	newNode->zeroPosition = Position(currentNode->zeroPosition.x + directionX, currentNode->zeroPosition.y + directionY);
	newNode->matrix = currentNode->matrix;
	std::swap(newNode->matrix[currentNode->zeroPosition.y + directionY][currentNode->zeroPosition.x + directionX], newNode->matrix[currentNode->zeroPosition.y][currentNode->zeroPosition.x]);
	newNode->GetHash();

	return newNode;
}


void ProcessSearch(std::vector<Node*> &searchQueue, std::set<size_t> &hashes)
{
	Node *currNode = searchQueue.front();
	searchQueue.erase(searchQueue.begin());

	if (IsHashValid(hashes, currNode->hash))
	{
		if (currNode->zeroPosition.x > 0)
		{
			searchQueue.emplace(searchQueue.begin(), CreateNewNode(currNode, -1, 0));
		}
		if (currNode->zeroPosition.y > 0)
		{
			searchQueue.emplace(searchQueue.begin(), CreateNewNode(currNode, 0, -1));
		}
		if (currNode->zeroPosition.x < FIELD_SIZE - 1)
		{
			searchQueue.emplace(searchQueue.begin(), CreateNewNode(currNode, 1, 0));
		}
		if (currNode->zeroPosition.y < FIELD_SIZE - 1)
		{
			searchQueue.emplace(searchQueue.begin(), CreateNewNode(currNode, 0, 1));
		}
		hashes.emplace(currNode->hash);
	}
}

size_t GetResult(Node **root)
{
	std::set<size_t> hashes;
	std::vector<Node*> nodesQueue;

	(*root)->CalculateZeroPosition();
	(*root)->GetHash();
	nodesQueue.push_back(*root);
	while (!nodesQueue.empty())
	{
		ProcessSearch(nodesQueue, hashes);
	}
	return hashes.size();
}

int main()
{
	std::ifstream input("input.txt");
	Node *root = new Node;
	root->matrix = GetMatrix(input);

	std::cout << GetResult(&root) << std::endl;
	return EXIT_SUCCESS;
}


