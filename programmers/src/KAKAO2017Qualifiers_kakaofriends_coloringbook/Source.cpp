#include <iostream>
#include <queue>
#include <unordered_set>
#include <sstream>
#include <set>
#include <cmath>

using namespace std;
//https://programmers.co.kr/learn/courses/30/lessons/1829

#include <vector>

using namespace std;

bool IsConnect(int x, int y, int other_x, int other_y, vector<vector<int>> const& picture)
{
    //boundary check
    if (other_y >= picture.size() || other_x >= picture[0].size() || other_x <0 || other_y <0)
        return false;
    if (picture[y][x] == picture[other_y][other_x])
        return true;
    else 
        return false;
}

void dfs(int x, int y, vector<vector<int>> const& picture, vector<vector<bool>> &visited, int& out_ConnectCount)
{
    if (visited[y][x]) return;
    visited[y][x] = true;
    out_ConnectCount++;

    //right
    if (IsConnect(x, y, x, y + 1, picture))
        dfs(x,y+1, picture,visited, out_ConnectCount);

    //down
    if (IsConnect(x, y, x + 1, y, picture))
        dfs(x+1, y, picture, visited, out_ConnectCount);

    //left
    if (IsConnect(x, y, x, y + 1, picture))
        dfs(x, y + 1, picture, visited, out_ConnectCount);

    //up
    if (IsConnect(x, y, x, y + 1, picture))
        dfs(x, y + 1, picture, visited, out_ConnectCount);
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    int number_of_area = 0;
    int max_size_of_one_area = 0;
    vector<vector<bool>> visited(picture.size(),vector<bool>(picture[0].size(),false));
    
    for (int y = 0; y < picture.size(); y++)
    {
        for (int x = 0; x < picture[0].size(); x++)
        {
            int ConnectCount = 0;
            if(picture[y][x]!=0)
                dfs(x, y, picture, visited, ConnectCount);
            if (ConnectCount > 0)
            {
                number_of_area++;
                max_size_of_one_area = max(max_size_of_one_area, ConnectCount);
            }
        }
    }

    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;
    return answer;
}

void main()
{
    vector<vector<int>> picture =
    { {1, 1, 1, 0}, {1, 2, 2, 0}, {1, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 3}, {0, 0, 0, 3} };
    auto answer = solution(picture.size(),picture[0].size(),picture);

    cout << answer[0]<< answer[1];
}