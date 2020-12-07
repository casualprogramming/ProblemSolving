#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>
using namespace std;

unordered_set<int> visited;

void insert(unordered_set<int>& numbers, int n)
{
	//method 1 :Avoid duplication
	if (visited.find(n) == visited.end())
	{
		numbers.insert(n);
		visited.insert(n);
	}
	//method 2: Don't care
	//numbers.insert(n);
}

void print(vector<unordered_set<int>>const& sets)
{
	for (int i=0;i<sets.size();i++)
	{
		cout << "set [" + to_string(i) + "] :";
		for (auto const& value : sets[i])
		{
			cout << " " << value;
		}
		cout << endl;

	}
}

unordered_set<int> getCases(vector<unordered_set<int>>const& sets, int C, int N)
{
	unordered_set<int> numbers;
	if (C - 1 != sets.size())
		throw "ERROR";
	int digit = 1;
	int multipleN = 0;
	for (int i = 0; i < C; i++)
	{
		multipleN += N * digit;
		digit *= 10;
	}
	insert(numbers,multipleN);
	//combination
	for (int i = 0; i < C /2; i++)
	{
		for (auto const& a : sets[i])
			for (auto const& b : sets[C-1 - i-1])
			{
				insert(numbers,a + b);
				insert(numbers,a * b);
				insert(numbers,a - b);
				insert(numbers,b + a);
				insert(numbers,b - a);
				if(b!=0)
					insert(numbers, a / b);
				if (a != 0)
					insert(numbers, b / a);
			}
	}
	return numbers;
}

int solution(int N, int number) {
	int answer = -1;
	vector<unordered_set<int>> sets;//minimum : 8
	for (int i = 0; i < 8; i++)
	{
		//print(sets);
		sets.push_back(getCases(sets, i+1, N));
		cout << "size : " << sets.back().size() << endl;
		for (auto const& lastSet : sets.back())
		{
			if (lastSet == number)
				return i+1;
		}
	}


	return answer;
}

void main()
{
	cout<<solution(5, 31168)<<endl;
}