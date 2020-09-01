#include <iostream>
#include <queue>
using namespace std;
//https://programmers.co.kr/learn/courses/30/lessons/42627

/***

difficulty
- random input
inputs are not sorted by request time(start)
solution : deque -> proirity queue(or sorting input)
- Disk state : idle
[0,3][1,9][500,6]
1,9 -> 500,6
***/



struct Job
{
	int start;
	int time;
	Job(int start, int time)
	{
		this->start = start;
		this->time = time;
	}
	//suppose 2 value in vector
	Job(vector<int> const& startend)
	{
		this->start = startend[0];
		this->time = startend[1];
	}
};
struct cmpCandidates {
	bool operator()(Job const& a, Job const& b) {
		return a.time > b.time;
	}
};
/***
@simpler method
if candidates empty -> insert minimum start and minimum time
***/
struct cmpJobQ {
	bool operator()(Job const& a, Job const& b) {
		if (a.start > b.start)
			return true;
		else if (a.start == b.start)
			return a.time > b.time;
		else 
			return false;
	}
};

void insertJob(priority_queue<Job, vector<Job>, cmpCandidates>& candidates, priority_queue<Job, vector<Job>, cmpJobQ>& jobs, int end_time)
{
	if (jobs.empty())
		return;
	//insert candidates
	while (jobs.top().start <= end_time)
	{
		candidates.push(jobs.top());
		jobs.pop();
		if (jobs.empty())
			break;
	}
	//no candidates? push first job
	if (candidates.empty() && !jobs.empty())
	{
		candidates.push(jobs.top()); jobs.pop();
	}
}

int solution(vector<vector<int>> jobs)
{
	priority_queue<Job, vector<Job>, cmpCandidates> candidates;
	priority_queue<Job, vector<Job>, cmpJobQ> jobQ;
	for (const auto& j : jobs)
	{
		jobQ.push(j);
	}
	insertJob(candidates, jobQ, -1);
	int end_time = 0;
	int sum = 0;
	while (!candidates.empty())
	{
		auto job = candidates.top(); candidates.pop();
		//processing job
		end_time = max(end_time + job.time, job.start + job.time);
		sum += end_time - job.start;
		insertJob(candidates, jobQ, end_time);
	}

	int answer = (float)sum / jobs.size();
	cout << answer;
	return answer;
}







int main()
{
	vector<vector<int>> jobs;
	//jobs.push_back({ 0,3 });
	//jobs.push_back({ 1,9 });
	//jobs.push_back({ 500,6 });
	jobs.push_back({ 0,9 });
	jobs.push_back({ 0,4 });
	jobs.push_back({ 0,5 });
	jobs.push_back({ 0,7 });
	jobs.push_back({ 0,3 });


	solution(jobs);
	return 0;
}

/***
my first correct solution
no candidates? push next minimum start time jobs (n)
simpler version above
***/
//
//struct Job
//{
//	int start;
//	int time;
//	Job(int start, int time)
//	{
//		this->start = start;
//		this->time = time;
//	}
//	//suppose 2 value in vector
//	Job(vector<int> const& startend)
//	{
//		this->start = startend[0];
//		this->time = startend[1];
//	}
//};
//struct cmpCandidates {
//	bool operator()(Job const& a, Job const& b) {
//		return a.time > b.time;
//	}
//};
//struct cmpJobQ {
//	bool operator()(Job const& a, Job const& b) {
//		return a.start > b.start;
//	}
//};
//
//void insertJob(priority_queue<Job, vector<Job>, cmpCandidates>& candidates, priority_queue<Job, vector<Job>, cmpJobQ>& jobs, int end_time)
//{
//	if (jobs.empty())
//		return;
//	//insert candidates
//	while (jobs.top().start <= end_time)
//	{
//		candidates.push(jobs.top());
//		jobs.pop();
//		if (jobs.empty())
//			break;
//	}
//}
//
//int solution(vector<vector<int>> jobs)
//{
//	priority_queue<Job, vector<Job>, cmpCandidates> candidates;
//	priority_queue<Job, vector<Job>, cmpJobQ> jobQ;
//	for (const auto& j : jobs)
//	{
//		jobQ.push(j);
//	}
//	//initialize : move to candidates who start time <= front start time
//	int end_time = jobQ.top().start;
//	insertJob(candidates, jobQ, end_time);
//
//	int sum = 0;
//	while (!candidates.empty())
//	{
//		auto job = candidates.top(); candidates.pop();
//		//processing job
//		end_time = end_time + job.time;
//		sum += end_time - job.start;
//		insertJob(candidates, jobQ, end_time);
//		if (candidates.empty() && !jobQ.empty())
//		{
//			end_time = jobQ.top().start;
//			insertJob(candidates, jobQ, end_time);
//		}
//	}
//
//	int answer = (float)sum / jobs.size();
//	cout << answer;
//	return answer;
//}