#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

//too easy.. not level 3

int solution(vector<vector<int>> triangle) {
	int answer = 0;
	auto nextPath = [&](int n)->vector<int>
	{
		vector<int> maxPath(triangle[n+1].size(),0);
		//n = 0~triangle.size()-1
		for (int i = 0; i < triangle[n].size(); i++)
		{
			maxPath[i] = max(maxPath[i], triangle[n][i] + triangle[n + 1][i]);//left
			maxPath[i+1] = max(maxPath[i+1], triangle[n][i] + triangle[n+1][i+1]);//right
		}
		return maxPath;
	};
	for (int i = 0; i < triangle.size() - 1; i++)
	{
		triangle[i+1] = nextPath(i);
	}
	for (auto const& n : triangle[triangle.size() - 1])
	{
		answer = max(answer, n);
	}
	return answer;
}

void main()
{
	vector<vector<int>> inputs = { {7}, {3, 8}, {8, 1, 0}, {2, 7, 4, 4}, {4, 5, 2, 6, 5} };
	cout<<solution(inputs);
}