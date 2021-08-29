#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

//https://programmers.co.kr/learn/courses/30/lessons/42884
//예시 잘못됨. 2021-08-25 기준 -5 지점에 카메라를 설치하면 첫번 째, 두 번째, 네 번째 차량이 카메라를 만납니다. (O)

//sort by route's end and set new camera at end if it don't see camera
// |         |c          0(set camera)
//    |           |      3(ignore by 2)
//         |   |         1(ignore by 0)
//            |  |c      2(set camera)
//       |           |   4(ignore by 2)


struct Log
{
public:
	int start;
	int end;
	Log(int enter, int out)
	{
		start = min(enter, out);
		end = max(enter, out);
	}
	bool IsMeetCamera(int camera_position) const { return start <= camera_position && camera_position <= end; }
};


int solution(vector<vector<int>> routes) {
	vector<Log> logs;
	for (auto const& route : routes)
	{
		logs.emplace_back(route[0], route[1]);
	}
	sort(logs.begin(), logs.end(), [](Log const& a, Log const& b)
		{
			return a.end < b.end;
		}
	);

	if (logs.empty()) return 0;

	int camera_count = 1;
	int camera_position = logs[0].end;
	for (auto const& log:logs)
	{
		if (!log.IsMeetCamera(camera_position))
		{
			camera_position = log.end;
			camera_count++;
		}
	}
	return camera_count;
}

void main()
{
	vector<vector<int>> routes = { {-20, 15}, {-14, -5}, {-18, -13}, {-5, -3} };
	cout<<solution(routes);
}