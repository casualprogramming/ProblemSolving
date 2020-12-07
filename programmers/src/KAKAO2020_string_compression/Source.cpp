#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//cut them in not order
//string compression(string const& s, int unit)
//{
//	auto getCompressionCount = [&](int begin)->int
//	{
//		int count = 1;
//		if (!(begin + unit < s.size()))
//			return 1;
//		string sub = s.substr(begin, unit);
//		for (int i = begin + unit; i < s.size(); i += unit)
//		{
//			if (sub == s.substr(i, unit))
//			{
//				count++;
//			}
//			else
//				break;
//		}
//		return count;
//	};
//	string compressed;
//	for (int i = 0; i < s.size(); )
//	{
//		int count=getCompressionCount(i);
//		if (count > 1)
//		{
//			compressed += std::to_string(count)+ s.substr(i, unit);
//			i += count * unit;
//		}
//		else
//		{
//			compressed += s[i];
//			i++;
//		}
//	}
//	return compressed;
//}

//cut them in order
string compression(string const& s, int unit)
{
	auto getCompressionCount = [&](int begin)->int
	{
		int count = 1;
		if (!(begin + unit < s.size()))
			return 1;
		string sub = s.substr(begin, unit);
		for (int i = begin + unit; i < s.size(); i += unit)
		{
			if (sub == s.substr(i, unit))
			{
				count++;
			}
			else
				break;
		}
		return count;
	};
	string compressed;
	for (int i = 0; i < s.size(); )
	{
		int count=getCompressionCount(i);
		if(count>1)
			compressed += std::to_string(count);
		compressed += s.substr(i, unit);
		i += count * unit;
	}
	return compressed;
}

//brute force
int bruteForce(string const& s)
{
	int minCompressed = s.size();
	for (int i = 1; i < (s.size() / 2)+1; i++)
	{
		minCompressed = min(int(compression(s, i).size()), minCompressed);
	}
	return minCompressed;
}

int solution(string s) {
	int answer = 0;
	answer = bruteForce(s);
	return answer;
}

void main()
{
	cout << solution("aabbaccc");
}