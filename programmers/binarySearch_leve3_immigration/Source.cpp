#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

//TODO : not completed
long long solution(int n, vector<int> times) {
	long long answer = 0;
	sort(times.begin(), times.end());
	long long l=0, r= n * times[0];
	cout << "t:" << r-l << endl;

	while (r - l!=1)
	{
		int processed = 0;
		long long t = (r - l) / 2+l;

		for (auto time : times)
		{
			processed += t / time;
		}
		cout << "t:" << t << "l:" << l << "r:" << r << "p:" << processed << endl;

		if (processed > n)
		{
			r = t;
		}
		else
			l = t;
	}
	int count = 0;
	for (auto time : times)
	{
		count += r / time;
	}
	cout << "count"<<count<<endl;
	return r;
}
void main()
{
	cout << solution(6, {7,10}) << endl;
}