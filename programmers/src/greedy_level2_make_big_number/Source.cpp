#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;


/***
1. wrong way : combination
***/
//int Number(string const& s, int k)
//{
//	int sum = 0;
//	for (int i = 0; i < s.size(); i++)
//	{
//		char c = s[i];
//		sum += pow(10, k - i-1) * atoi(&c);
//	}
//	return sum;
//}
//int maxNum = 0;
//void comb(string& selects, string& remains, int k)
//{
//	if (selects.size() + remains.size() < k)
//		return;
//	else
//	{
//		cout << "selects : " << selects << endl;
//		cout << "number : " << Number(selects, k) << endl;
//		cout << "remains : " << remains << endl;
//		cout << "max : " << maxNum << endl << endl;
//
//	}
//	if (selects.size() <k && selects.size() > 0)
//	{
//		int greedNum = Number(selects, k) + pow(10, k-selects.size());
//		if (maxNum > greedNum)
//			return;
//	}
//	else if (selects.size() == k)
//	{
//		maxNum = max(maxNum, stoi(selects));
//		return;
//	}
//	else if (remains.size() == 0)
//		return;
//	//case : select
//	selects.push_back(remains.back());
//	remains.pop_back();
//	comb(selects, remains, k);
//	remains.push_back(selects.back());
//	selects.pop_back();
//	//case : non-select
//	int temp = remains.back();
//	remains.pop_back();
//	comb(selects, remains, k);
//	remains.push_back(temp);
//	return;
//}

//2. correct way : find max number
int findMax(string const& number, int begin, int k)
{
	int idx = -1;
	int max = 0;
	for (int i = begin; i < number.size()-k; i++)
	{
		if (number[i] > max)
		{
			idx = i;
			max = number[i];
		}
	}
	return idx;
}

//
string solution(string number, int k) {
	string answer = "";

	int begin = 0;
	int remains = number.size() - k;
	while (remains!=0)
	{
		int maxIdx = findMax(number, begin, remains-1);
		answer.push_back(number[maxIdx]);
		begin = maxIdx+1;
		remains--;
	}

	return answer;
}

void main()
{
	cout<<solution("103920392",3);
	//string str1 = "";
	//string str2 = "999";
	//string rstr2(str2.rbegin(), str2.rend());
	//comb(str1, rstr2, 2);
	//cout << "final maxNum : " << maxNum << endl;
}