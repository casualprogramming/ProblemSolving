#include <iostream>
#include <vector>
using namespace std;
template <typename T, typename U>
std::pair<T, U> operator+(const std::pair<T, U>& l, const std::pair<T, U>& r) {return { l.first + r.first,l.second + r.second };}
template <typename T, typename U>
std::pair<T, U> operator-(const std::pair<T, U>& l, const std::pair<T, U>& r) {return { l.first + r.first,l.second + r.second };}
enum STATE
{
	HORIZONTAL,VERTICAL
};
struct robotState
{
	pair<int, int> src[2];
	STATE state;
	vector<pair<int, int>> getDirections()
	{
		if (state == HORIZONTAL)
	{
		vector<robotState> directions;
		//left-down
		if (isRotatable(src[0], src[1], src[0] + pair<int,int>{0,1}))
			directions.push_back({ src[0] ,src[0] + pair<int,int>{0,1}});
		//left-up
		if(isRotatable(src[0], src[1], {x-1,y-1}))
			directions.push_back({x-1,y-1});
		//right-down
		if(isRotatable({x,y}, {x-1,y}, {x,y+1}))
			directions.push_back({x,y+1});
		//right-up
		if(isRotatable({x,y}, {x-1,y}, {x,y-1}))
			directions.push_back({x,y-1});
		return directions;
	}
	
	//VERTICAL
	else
	{
		vector<pair<int, int>> directions;
		//left-up
		if(isRotatable({x,y-1}, {x,y}, {x-1,y-1}))
			directions.push_back({x-1,y-1});
		//right-up
		if(isRotatable({x,y-1}, {x,y}, {x+1,y-1}))
			directions.push_back({x+1,y-1});
		//left-down
		if(isRotatable({x,y}, {x,y-1}, {x-1,y}))
			directions.push_back({x-1,y});
		//right-down
		if(isRotatable({x,y}, {x,y-1}, {x+1,y}))
			directions.push_back({x+1,y});
		return directions;
	}
	}

};

int minimalStep[2][102][102];
int myboard[102][102];
int n = 0;

bool isRotatable(pair<int, int> source0, pair<int, int> move_source1, pair<int, int> dst)
{
	if (myboard[dst.first][dst.second] == 1)
		return false;
	pair<int, int> check = source0 + (source0 - move_source1) + (source0 - dst);
	if (myboard[check.first][check.second] == 1)
		return false;
	return true;
}
vector<pair<int, int>> getDirections(STATE state, int x, int y)
{
	
}
void move(STATE state, int x, int y, int step)
{
	if (minimalStep[state][x][y] <= step)
		return;
	minimalStep[state][x][y] = step;
	for (auto const& dir : getDirections(state, x, y))
	{
		move(state == HORIZONTAL ? VERTICAL : HORIZONTAL, dir.first, dir.second, step + 1);
	}
}

int solution(vector<vector<int>> board) {
	int answer = 0;
	n = board.size();
	for(int i=0;i<n+2;i++)
		for (int j=0;j<n+2;j++)
			myboard[i][j]=1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for(int s=0;s<2;s++)
				minimalStep[s][i + 1][j + 1] =INT_MAX;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			myboard[i+1][j+1]=board[i][j];
	move(HORIZONTAL, 2, 1, 0);
	return answer;
}
void main()
{
	vector<vector<int>> input = { {0, 0, 0, 1, 1}, {0, 0, 0, 1, 0}, {0, 1, 0, 1, 1}, {1, 1, 0, 0, 1}, {0, 0, 0, 0, 0} };
	solution(input);
}