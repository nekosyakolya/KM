// lab2.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <fstream>

#include <iostream>



typedef std::vector<std::vector<int>> Matrix;



struct Node
{
	std::vector<std::vector<int>> data;
	Node *father;
};



void Fill(std::ifstream & input, Matrix &matrix)
{
	Matrix tmp;
	std::string str;
	while (getline(input, str))
	{
		std::vector<int> tempVector;
		for (auto el : str)
		{
			tempVector.push_back(el);
		}
		tmp.push_back(tempVector);
	}
	std::swap(matrix, tmp);
}


int main()
{
	std::ifstream input("input.txt");
	std::vector<std::vector<int>> tree;
	Fill(input, tree);


	//��������� ������

	//���������� � �������


	//���� ������� �� ������
	//

	return 0;
}

