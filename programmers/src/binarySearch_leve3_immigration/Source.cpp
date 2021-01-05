#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits.h>

//@@Make sure to check long long type

//--final simple version
using namespace std;
long long isEnough(long long t, vector<int> const& times, long long n)
{
	long long processed = 0;
	for (auto time : times)
		processed += t / time;

	return processed >= n ? true : false;
}

long long solution(int n, vector<int> times) {
	long long answer = 0;
	sort(times.begin(), times.end());
	long long l = 0, r = n * times.front();
	while (r - l != 1)
	{
		long long processed = 0;
		long long t = (r - l) / 2 + l;

		if (isEnough(t, times, n))
			r = t;
		else
			l = t;
	}
	answer = r;
	return answer;
}

void main()
{
	cout << solution(6, {7,10}) << endl;
}

//--old dirty version: 3 type of return value
//--difference: eliminates wasted time when equal
//enum { LESS, EQUAL, GREATER };
//long long getCompactTime(long long t, vector<int> const& times, long long n)
//{
//	long long remainTimes = LLONG_MAX;
//	for (auto time : times)
//	{
//		remainTimes = min(remainTimes, t % time);
//	}
//	return t - remainTimes;
//}
//
//long long getState(long long t, vector<int> const& times, long long n)
//{
//	long long processed = 0;
//	for (auto time : times)
//	{
//		processed += t / time;
//	}
//	if (processed > n)
//		return GREATER;
//	else if (processed == n)
//		return EQUAL;
//	else
//		return LESS;
//}
//
//long long solution(int n, vector<int> times) {
//	long long answer = 0;
//	sort(times.begin(), times.end());
//	long long l = 0, r = n * times.front();
//	while (r - l != 1)
//	{
//		long long processed = 0;
//		long long t = (r - l) / 2 + l;
//
//		auto type = getState(t, times, n);
//		if (type == GREATER)
//		{
//			r = t;
//		}
//		else if (type == LESS)
//		{
//			l = t;
//		}
//		else//EQUAL
//		{
//			answer = getCompactTime(t, times, n);
//			break;
//		}
//	}
//	if (answer == 0)
//		answer = r;
//	return answer;
//}