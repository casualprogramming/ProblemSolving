#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>
using namespace std;

/* best solution O(NlogN)
*  add process time to end time
*  Create log by separating start and end, and sort by time
*  if end-log then decrement count, if start-log then increment count 
*/
struct Log
{
public:
	bool IsStartLog;//start or end
	int time;
	Log(bool StartLog, int time) :IsStartLog(StartLog), time(time) {}
};
array<Log,2> CreateStartLogAndEndLog(string const& log)
{
	//log.substr(0, 10);//2016-09-15
	int hour = stoi(log.substr(11, 2));
	int minite = stoi(log.substr(14, 2));
	int second = stoi(log.substr(17, 2));
	int demical = stoi(log.substr(20, 3));
	int end = (hour * 3600 + minite * 60 + second) * 1000 + demical;
	int elapsed = int(stod(log.substr(24, log.size() - 25)) * 1000);
	int start = end - (elapsed - 1);
	const int processTime = 1000;
	return { Log(true, start), Log(false, end + processTime - 1) };
}

int solution(vector<string> lines) {
	int answer = 0;

	//convert string to log
	vector<Log> logs;
	for (auto const& line : lines)
		for (auto const& log : CreateStartLogAndEndLog(line))
			logs.push_back(log);
	sort(logs.begin(), logs.end(), [](Log const& a, Log const& b)
		{
			if (a.time == b.time)
				return a.IsStartLog;
			return a.time < b.time;
		}
	);
	
	int count = 0;
	for (auto const& log : logs)
	{
		if (log.IsStartLog)
			count++;
		else
			count--;
		answer = max(answer, count);
	}
	return answer;
}


void main()
{
	vector<string> logs =
	{
		"2016-09-15 20:59:57.421 0.351s",
		"2016-09-15 20:59:58.233 1.181s",
		"2016-09-15 20:59:58.299 0.8s",
		"2016-09-15 20:59:58.688 1.041s",
		"2016-09-15 20:59:59.591 1.412s",
		"2016-09-15 21:00:00.464 1.466s",
		"2016-09-15 21:00:00.741 1.581s",
		"2016-09-15 21:00:00.748 2.31s",
		"2016-09-15 21:00:00.966 0.381s",
		"2016-09-15 21:00:02.066 2.62s"
	};
	cout<<solution(logs);
}



//
////basic solution O(n^2): find process count at start and end time of log.
//struct Log
//{
//public:
//	int start;//3demical
//	int end;//3demical
//
//	Log(string const& log)
//	{
//		//log.substr(0, 10);//2016-09-15
//		int hour = stoi(log.substr(11, 2));
//		int minite = stoi(log.substr(14, 2));
//		int second = stoi(log.substr(17, 2));
//		int demical = stoi(log.substr(20, 3));
//		end = (hour * 3600 + minite * 60 + second) * 1000 + demical;
//		int elapsed = int(stod(log.substr(24, log.size() - 25)) * 1000);
//		start = end - (elapsed - 1);
//	}
//};
//
//
////find process count at query time
//int findProcessCount(vector<Log> const& logs, int queryTime)
//{
//	int processTime = 1000;
//	int endTime = queryTime + processTime;
//	int count = 0;
//	for (auto const& log : logs)
//	{
//		if (log.end >= queryTime && log.end < endTime)
//			count++;
//		else if (log.start >= queryTime && log.start < endTime)
//			count++;
//		else if (log.start < queryTime && log.end >= endTime)
//			count++;
//	}
//	return count;
//}
//
//int solution(vector<string> lines) {
//	int answer = 0;
//
//	//convert string to log
//	vector<Log> logs;
//	for (auto const& line : lines)
//		logs.emplace_back(line);
//
//	//solution
//	for (int i = 0; i < logs.size(); i++)
//	{
//		answer = max(answer, findProcessCount(logs, logs[i].start));
//		answer = max(answer, findProcessCount(logs, logs[i].end));
//	}
//
//	return answer;
//}