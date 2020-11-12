#include <iostream>
#include <vector>

using namespace std;
template <typename T, typename U>
std::pair<T, U> operator+(const std::pair<T, U>& l, const std::pair<T, U>& r) {return { l.first + r.first,l.second + r.second };}
template <typename T, typename U>
std::pair<T, U> operator-(const std::pair<T, U>& l, const std::pair<T, U>& r) {return { l.first - r.first,l.second - r.second };}

typedef typename pair<int, int> XY;
int minimalStep[2][102][102];
int myboard[102][102];
int n = 0;
enum STATE
{
	HORIZONTAL,VERTICAL
};

bool isMovable(XY src)
{
	if (src.second < 0 || src.first < 0)
		printf("warning\n");
	return myboard[src.second][src.first]== 0;
}

bool isRotatable(XY source0, XY move_source1, XY dst)
{
	if (!isMovable(dst))
		return false;
	XY check = source0 + (move_source1-source0) + (dst-source0);
	if (!isMovable(check))
		return false;
	return true;
}

bool isMovable(XY src0, XY src1, XY dir)
{
	src0 = src0 + dir;
	src1 = src1 + dir;
	return isMovable(src0) && isMovable(src1);
}

struct robotState
{
	XY src;
	STATE state;
	vector<robotState> getNextStates()
	{
		vector<robotState> states;

		vector<XY> dirs = { {0,1},{0,-1},{1,0},{-1,0}};
		for (auto dir : dirs)
		{
			XY src0 = (state == HORIZONTAL) ? src - XY(1, 0) : src - XY(0, 1);
			if (isMovable(src0, src, dir))
				states.push_back({ src + dir , state});
		}

		if (state == HORIZONTAL)
		{
			XY src0 = { src - XY(1,0) };
			//left-down
			if (isRotatable(src0, src,	src0 + XY(0,1)))
				states.push_back({	src0 + XY(0,1),  VERTICAL});
			//left-up
			if (isRotatable(src0, src,	src0 + XY(0,-1)))
				states.push_back({	src0, VERTICAL});
			//right-down
			if (isRotatable(src, src0,	src	+ XY(0,1)))
				states.push_back({	src + XY(0,1) ,	 VERTICAL});
			//right-up
			if (isRotatable(src, src0,	src + XY(0,-1)))
				states.push_back({	src ,  VERTICAL});
		}

		//VERTICAL
		else
		{
			XY src0 = { src - XY(0,1) };
			//right-up
			if (isRotatable(src0, src, src0 + XY(1,0)))
				states.push_back({ src0 + XY(1,0),  HORIZONTAL });
			//left-up
			if (isRotatable(src0, src, src0 + XY(-1,0)))
				states.push_back({ src0 , HORIZONTAL });
			//right-down
			if (isRotatable(src, src0, src + XY(1,0)))
				states.push_back({ src + XY(1,0) ,	HORIZONTAL });
			//right-up
			if (isRotatable(src, src0, src + XY(-1,0)))
				states.push_back({ src ,  HORIZONTAL });
		}
		return states;
	}

};



void move(robotState s, int step)
{
	if (minimalStep[s.state][s.src.second][s.src.first] <= step)
		return;
	printf("state: %s %d %d step:%d\n", s.state==VERTICAL?"VERTICAL":"HORIZON", s.src.first, s.src.second, step);
	minimalStep[s.state][s.src.second][s.src.first] = step;
	for (auto const &next_state : s.getNextStates())
	{
		move(next_state, step+1);
	}
}

int solution(vector<vector<int>> board) {
	int answer = 0;
	n = board.size();
	for(int i=0;i<n+2;i++)
		for (int j=0;j<n+2;j++)
			myboard[i][j]=1;
	for (int i = 0; i < n+2; i++)
		for (int j = 0; j < n+2; j++)
			for(int s=0;s<2;s++)
				minimalStep[s][i + 1][j + 1] =INT_MAX;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			myboard[i+1][j+1]=board[i][j];
	move({ {2, 1}, HORIZONTAL}, 0);
	return min(minimalStep[0][n][n], minimalStep[1][n][n]);
}
void main()
{
	vector<vector<int>> input = { {0, 0, 0, 1, 1}, {0, 0, 0, 1, 0}, {0, 1, 0, 1, 1}, {1, 1, 0, 0, 1}, {0, 0, 0, 0, 0} };
	cout<<solution(input)<<endl;
}


//TODO : Don't find the next possible state, go ahead and check if that current state is correct or not
//that will be simpler code