#include <iostream>

#include <vector>
#include <deque>
#include <unordered_set>
#include <utility>
using namespace std;
enum Path
{
	PUDDLE = -1
};

//if you boundary check & PUDDLE & step at once while for loop increase efficiency about twice..
//overhead : boundary check -> PUDDLE check -> step check 
//efficiency : boundary check && PUDDLE check && step check 
vector<pair<int, int>> nextCoordsBoundaryChecked(pair<int, int>const& xy, int m, int n)
{
	static const vector<pair<int, int>> directions = { {0,1},{0,-1},{1,0},{-1,0} };
	vector<pair<int, int>> avilables;
	for (auto const& d : directions)
	{
		pair<int, int> next_xy = { xy.first + d.first,xy.second + d.second };
		if (0 <= next_xy.first && next_xy.first < m && next_xy.second < n && 0 <= next_xy.second)
		{
			avilables.push_back(next_xy);
		}
	}
	return avilables;
}

int solution(int m, int n, vector<vector<int>> puddles) {
	int answer = 0;
	vector<vector<int>> paths(m, vector<int>(n, 0));//number of minimal routes
	vector<vector<int>> minimunSteps(m, vector<int>(n, 0x7FFFFFFF));
	vector<vector<bool>> opened(m, vector<bool>(n, false));

	for (auto const& puddle : puddles)
	{
		paths[puddle[0] - 1][puddle[1] - 1] = PUDDLE;
	}
	deque<pair<int, int>> opens;
	opens.push_back({ 0, 0 }); opened[0][0] = true; paths[0][0] = 1;
	int step = 0;
	while (paths[m - 1][n - 1] == 0 && !opens.empty())
	{
		step++;
		vector<pair<int, int>> next_opens;
		while (!opens.empty())
		{
			pair<int, int> expand = opens.front(); opens.pop_front();
			vector<pair<int, int>> coordinates(std::move(nextCoordsBoundaryChecked(expand, m, n)));
			for (auto const& c : coordinates)
			{

				int const& x = c.first, y = c.second;
				if (paths[x][y] == PUDDLE)
					continue;
				if (minimunSteps[x][y] > step)
				{
					minimunSteps[x][y] = step;
					paths[x][y] = paths[expand.first][expand.second] % 1000000007;
					if (!opened[x][y])
					{
						opened[x][y] = true;
						next_opens.push_back(c);
					}
				}
				else if (minimunSteps[x][y] == step)
					paths[x][y] = (paths[expand.first][expand.second] + paths[x][y]) % 1000000007;
			}
		}
		for (auto const& open : next_opens)
		{
			opens.push_back(open);
		}
	}


	return paths[m - 1][n - 1] % 1000000007;
}

void main()
{
	cout<<solution(4, 3, { {2,2} });
}