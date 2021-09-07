#include <string>
#include <vector>
#include <iostream>
using namespace std;

int Goal = 0;
int answer = 0;

void dfs(vector<int> const& numbers, int idx, int sum)
{
	if (numbers.size() == idx+1)
	{
		if (sum == Goal) 
			answer++;
		return;
	}

	dfs(numbers, idx+1, sum +numbers[idx+1]);
	dfs(numbers, idx+1, sum -numbers[idx+1]);
}

int solution(vector<int> numbers, int target) 
{
	Goal = target;
	dfs(numbers,-1,0);
	
	return answer;
}

void main()
{
	vector<int> numbers = { 1, 1, 1, 1, 1 };
	cout<<solution(numbers,3);
}