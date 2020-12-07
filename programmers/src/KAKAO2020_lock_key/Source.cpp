#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include  <iostream>
using namespace std;
enum ROTATE
{
	R0,R90, R180, R270
};
enum RESULT
{
	DONT_CARE=-1, FALSE, TRUE
};
//ex) m:4 
//[0,0 -> 0,3] [0,1 -> 1,3]
//[1,0 -> 0,2] [1,1 -> 1,2]

pair<int, int> Rotate(pair<int, int>const& key, ROTATE rotate, int m)
{
	switch (rotate) {
	case ROTATE::R0:
		return key;
	case ROTATE::R90:
		return { key.second, m - 1 - key.first };
	case ROTATE::R180:
		return { m-1-key.first, m-1-key.second};
	case ROTATE::R270:
		return {m-1-key.second, key.first};
	}
}

//0: don't care, 1: correct, 0: meet protrusion
RESULT check(vector<vector<int>>const& locks, pair<int, int> key)
{
	auto const& x = key.first; auto const& y = key.second;
	if (x >= locks.size() || y >= locks.size() || x < 0 || y < 0)//out of region
		return DONT_CARE;
	else if (locks[x][y] == 0)
		return TRUE;
	else
		return FALSE;
}

bool check(vector<pair<int, int>>const& keys, vector<vector<int>>const& locks, int x, int y, ROTATE rotate, int m, int grooveGoal)
{
	int corrects = 0;
	for (auto const& key : keys)
	{
		pair<int,int> rotatedKey= Rotate(key,rotate,m);
		RESULT result = check(locks, { rotatedKey.first + x,rotatedKey.second + y });
		if (result == FALSE)
			return false;
		else if (result == TRUE)
			corrects++;
	}
	if (corrects == grooveGoal)
		return true;
	else 
		return false;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
	bool answer = true;

	vector<pair<int,int>> keys;
	for (int r = 0; r < key.size(); r++)
		for (int c = 0; c < key[r].size(); c++)
		{
			if (key[r][c] == 1)
				keys.push_back({ r, c });
		}
	int grooveGoal = 0;
	for (int r = 0; r < lock.size(); r++)
		for (int c = 0; c < lock[r].size(); c++)
		{
			if (lock[r][c] == 0)
				grooveGoal++;
		}
	int m = key.size();
	int n = lock.size();
	for (int x = -(m-1); x < n; x++)
	{
		for (int y = -(m-1); y < n; y++)
		{
			for (int r = R0; r <= R270; r++)
			{
				if(check(keys, lock, x, y, ROTATE(r), m, grooveGoal))
					return true;
			}
		}
	}

	return false;
}

void main()
{
	vector<vector<int>> keys = { {0, 0, 0}, {1, 0, 0}, {0, 1, 1} };
	vector<vector<int>> lock = {{1, 1, 1},{1, 1, 0},{1, 0, 1}};
	cout << solution(keys,lock);
}