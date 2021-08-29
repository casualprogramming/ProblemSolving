#include <iostream>
#include <queue>
#include <unordered_set>
#include <sstream>
#include <set>
using namespace std;
//https://programmers.co.kr/learn/courses/30/lessons/42628

vector<int> solution(vector<string> operations) {
	vector<int> answer;
	set<int> ordered_set;
	for (auto const& operation : operations)
	{
		char command = operation[0];
		stringstream ss(operation.substr(2));
		int number;
		ss >> number;
		if (command == 'I')
		{
			ordered_set.insert(number);
		}
		else
		{
			if (ordered_set.empty())
				continue;
			//delete max
			if (number == 1)
			{
				ordered_set.erase(--ordered_set.end());
			}
			//delete min
			else//number == -1
			{
				ordered_set.erase(ordered_set.begin());
			}
		}
	}
	if (ordered_set.empty()) 
	{
		return { 0,0 };
	}
	else
	{
		answer.push_back(*ordered_set.begin());
		answer.push_back(*(--ordered_set.end()));
	}
	return answer;
}

int main()
{
	//vector<string> operations = { "I 16", "D 1" };
	//vector<string> operations = { "I 7", "I 5", "I -5", "D -1" };
	vector<string> operations = { "I 16", "I -5643", "D -1", "D 1", "D 1", "I 123", "D -1" };
	auto answer = solution(operations);
	for (auto n : answer)
	{
		cout << n;
	}
	return 0;
}
