#include "stdafx.h"
#include "Graph.h"

CGraph::CGraph()
{
}

void CGraph::Fill(std::ifstream & input)
{
	Matrix matrix;
	std::string str;
	while (getline(input, str))
	{
		std::vector<bool> tempVector;
		for (auto el : str)
		{
			tempVector.push_back(el == '1');
		}
		matrix.push_back(tempVector);
	}
	std::swap(m_matrix, matrix);
}

void CGraph::FindCircles()
{
	for (size_t row = 0; row < m_matrix.size(); ++row)
	{
		for (size_t col = 0; col < m_matrix[row].size(); ++col)
		{
			if (m_matrix[row][col])
			{
				if (col == row)
				{
					m_circles.push_back(1);
					m_matrix[row][col] = false;
				}
				else if (m_matrix[col][row])
				{
					m_circles.push_back(2);
					m_matrix[row][col] = false;
					m_matrix[col][row] = false;
				}
				else
				{
					FindMultidimensionalCycle(row, col);
				}
			}
		}
	}
	SetFormula();
}

Formula CGraph::GetFormula() const
{
	return m_formula;
}

void CGraph::PrintFormula(std::ofstream & out) const
{
	for (auto circle : m_formula)
	{
		out << circle.first << " : " << circle.second << std::endl;
	}
}

void CGraph::SetFormula()
{
	std::vector<int> tmp = m_circles;
	std::sort(tmp.begin(), tmp.end());
	while (!tmp.empty())
	{
		if (m_formula.find(*tmp.begin()) == m_formula.end())
		{
			m_formula.emplace(std::pair<int, int>(*tmp.begin(), 1));
		}
		else
		{
			++m_formula.find(*tmp.begin())->second;
		}
		tmp.erase(tmp.begin());
	}
}

void CGraph::FindMultidimensionalCycle(const size_t& row, const size_t& col)
{
	int lenght = 1;
	bool isFind = false;
	m_matrix[row][col] = false;
	int tmpRow = col;
	while (!isFind)
	{
		for (size_t i = 0; i < m_matrix.size(); )
		{
			isFind = true;
			if (m_matrix[tmpRow][i])
			{
				m_matrix[tmpRow][i] = false;
				++lenght;
				tmpRow = i;
				i = 0;
				isFind = false;
			}
			else if (tmpRow == row)
			{
				m_circles.push_back(lenght);
				break;
			}
			else
			{
				++i;
			}
		}
	}
}

CGraph::~CGraph()
{
}
