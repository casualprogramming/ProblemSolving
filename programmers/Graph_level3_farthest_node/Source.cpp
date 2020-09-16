#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
using namespace std;

template<class Key,class Vector>
void insert(unordered_map<Key, Vector>& map, int key, int value)
{
	if ((map.find(key) == map.end()))
		map[key] = Vector();
	map[key].push_back(value);
}

int solution(int n, vector<vector<int>> edge) {
	int answer = 0;
	unordered_set<int> notVisited;
	for (int i = 1; i <= n; i++)
		notVisited.insert(i);
	unordered_map<int, vector<int>> nodes;
	for (auto const& e : edge)
	{
		insert(nodes,e[0], e[1]);
		insert(nodes,e[1], e[0]);
	}
	vector<int> expendNodes; expendNodes.push_back(1); notVisited.erase(1);
	int step = 0;
	while (!notVisited.empty())
	{
		vector<int> nextExpandNodes;
		step++;
		//cout << "step : " << step<<endl;
		for (int node : expendNodes)
		{
			//cout << "node :"<<node << endl;
			for (auto const& adjacent : nodes[node])
			{
				
				//if not visited
				if (notVisited.find(adjacent) != notVisited.end())
				{
					nextExpandNodes.push_back(adjacent);
					notVisited.erase(adjacent);
					//cout << adjacent << endl;
				}
			}
		}
		expendNodes = nextExpandNodes;
	}
	answer = expendNodes.size();
	return answer;
}
void main()
{
	vector<vector<int>> nodes = { {3, 6}, {4, 3}, {3, 2}, {1, 3}, {1, 2}, {2, 4}, {5, 2} };
	cout<<(solution(6, nodes));
}