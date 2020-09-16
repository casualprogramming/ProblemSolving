#include <string>
#include <vector>
#include <iostream>
using namespace std;
int pad = 1;
enum OBJECT
{
	COLUNM,BEAM
};
enum ACTION
{
	ERASE, INSTALL
};

//@@ambiguos : not one end, it is at least one
bool installableBeam(vector<vector<bool>>const& beams, vector<vector<bool>>const& columns, int x, int y)
{
	return columns[x][y - 1] || columns[x + 1][y - 1] || (beams[x + 1][y] && beams[x - 1][y]);
}

bool installableColumn(vector<vector<bool>>const& beams, vector<vector<bool>>const& columns, int x, int y)
{
	return y == pad || columns[x][y - 1] || beams[x - 1][y] || beams[x][y];
}

bool erasableBeam(vector<vector<bool>>& beams, vector<vector<bool>>const& columns, int x, int y)
{
	if (!beams[x][y])
		return false;
	beams[x][y] = false;//temporally setting
	auto resetAndReturn =[&](bool b)->bool
	{
		beams[x][y] = true;//reset
		return b;
	};
	//check left beam
	if (
		(beams[x - 1][y] && !installableBeam(beams, columns, x - 1, y)) ||//check left beam
		(beams[x + 1][y] && !installableBeam(beams, columns, x + 1, y)) ||//check right right beam
		(columns[x][y] && !installableColumn(beams, columns, x, y)) ||//check current colunm
		(columns[x + 1][y] && !installableColumn(beams, columns, x + 1, y)))//check right colun
	{
		return resetAndReturn(false);
	}
	return resetAndReturn(true);
}
bool erasableColunm(vector<vector<bool>>const& beams, vector<vector<bool>>& columns, int x, int y)
{
	if (!columns[x][y])
		return false;
	columns[x][y] = false;//temporally setting
	auto resetAndReturn = [&](bool b)->bool
	{
		columns[x][y] = true;//reset
		return b;
	};

	//check upper colunm
	if ((columns[x][y + 1] && !installableColumn(beams, columns, x, y + 1)) ||//check upper colunm
		(beams[x][y + 1] && !installableBeam(beams, columns, x, y + 1)) ||//check upper right beam
		(beams[x - 1][y + 1] && !installableBeam(beams, columns, x - 1, y + 1)))//check upper left beam
	{
		return resetAndReturn(false);
	}

	return resetAndReturn(true);
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
	vector<vector<int>> answer;
	vector<vector<bool>> beams(n+3,vector<bool>(n+3,false));
	vector<vector<bool>> columns(n + 3, vector<bool>(n + 3, false));


	for (auto const& args : build_frame)
	{
		int x = args[0]+ pad; int y = args[1] + pad;
		if (args[2] == BEAM && args[3] == INSTALL)
		{
			if (installableBeam(beams, columns, x, y))
				beams[x][y] = true;

		}
		else if (args[2] == COLUNM && args[3] == INSTALL)
		{
			if (installableColumn(beams, columns, x, y))
				columns[x][y] = true;
		}
		else if (args[2] == BEAM && args[3] == ERASE)
		{
			if (erasableBeam(beams, columns, x, y))
				beams[x][y] = false;
		}
		else if (args[2] == COLUNM && args[3] == ERASE)
		{
			if (erasableColunm(beams, columns, x, y))
				columns[x][y] = false;
		}
	}
	int size = beams.size();
	for (int r = 0; r < size; r++)
	{
		for (int c = 0; c < size; c++)
		{
			if (columns[r][c])
				answer.push_back({ r - pad,c - pad,COLUNM });
			if (beams[r][c])
				answer.push_back({ r- pad,c- pad,BEAM });
		}
	}

	return answer;
}

void main()
{
	vector<vector<int>> inputs = { {1, 0, 0, 1}, {1, 1, 1, 1}, {2, 1, 0, 1}, {2, 2, 1, 1}, {5, 0, 0, 1}, {5, 1, 0, 1}, {4, 2, 1, 1}, {3, 2, 1, 1} };
	vector<vector<int>> inputs2 = { {0, 0, 0, 1}, {2, 0, 0, 1}, {4, 0, 0, 1}, {0, 1, 1, 1}, {1, 1, 1, 1}, {2, 1, 1, 1}, {3, 1, 1, 1}, {2, 0, 0, 0}, {1, 1, 1, 0}, {2, 2, 0, 1} };
	
	auto results = solution(5, inputs2);
	for (auto const& result : results)
	{
		printf("x:%d y:%d a:%d\n", result[0], result[1], result[2]);
	}
}