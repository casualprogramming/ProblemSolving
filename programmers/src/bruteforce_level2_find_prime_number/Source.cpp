#include <algorithm>
#include <functional>
using namespace std;

template<typename Iter>
class Permutation
{
public:
	int query_depth_min;
	int query_depth_max;
	function<void(Iter, Iter)> delegate_function;
	void run(Iter begin, Iter end, int _query_depth_min, int _query_depth_max, function<void(Iter, Iter)> func)
	{
		query_depth_min = min(1,_query_depth_min); query_depth_max = _query_depth_max; delegate_function = func;
		permutation_internal(begin, end, 0);
	};
private:
	void permutation_internal(Iter begin, Iter end, int depth)
	{
		if (query_depth_min <= depth)
		{
			if (depth <= query_depth_max)
				delegate_function(begin, begin + depth);
			else
				return;
		}

		for (auto iter = begin + depth; iter != end; iter++)
		{
			std::iter_swap(begin + depth, iter);
			permutation_internal(begin, end, depth + 1);
			std::iter_swap(begin + depth, iter);
		}
	}
};

#include <string>
#include <sstream>
#include <math.h> 
#include <unordered_set>
#include <iostream>
//https://programmers.co.kr/learn/courses/30/lessons/42839

bool IsPrimeNumber(int number)
{
	if (number < 2) return false;
	int n = int(sqrt(number));
	for (int i = 2; i <= n; i++)
	{
		if (number % i ==0)
			return false;
	}
	return true;
}

int solution(string numbers) {
	int prime_number= 0;
	Permutation<string::iterator> Permutation;
	unordered_set<int> checked;
	Permutation.run(numbers.begin(), numbers.end(), 4, 4, [&](auto begin, auto end)
		{
			std::stringstream ss(string(begin, end));
			int number;
			ss >> number;
			if (checked.find(number)!=checked.end())
				return;
			if (IsPrimeNumber(number))
			{
				checked.insert(number);
				prime_number++;
			}
		}
	);
	return prime_number;
}



void main()
{
	//cout << "solution:" << solution("17") << endl;
	cout << "solution:" << solution("321548651321") << endl;
}