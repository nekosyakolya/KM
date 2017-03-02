#pragma once

typedef std::vector<std::vector<bool>> Matrix;
typedef std::map<int, int> Formula;

class CGraph
{
public:
	CGraph();

	void Fill(std::ifstream& input );
	void FindCircles();
	Formula GetFormula() const;
	void PrintFormula() const;
	
	~CGraph();
private:
	void SetFormula();
	void FindMultidimensionalCycle(const size_t& row, const size_t& col);
	
	Matrix m_matrix;
	Formula m_formula;
	std::vector<int> m_circles;
};
