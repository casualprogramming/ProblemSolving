#include <iostream>


#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <queue>
using namespace std;
struct Edge
{
	int startV;
	int endV;
	int cost;
	Edge(int v1, int v2, int cost) :startV(v1), endV(v2), cost(cost) {}
	string getString() const
	{
		return "startV : " + to_string(startV) + " end : " + to_string(endV) + " cost : " + to_string(cost) + "\n";

	}
};
struct cmpEdge
{
	bool operator()(Edge const& a, Edge const& b)
	{
		return a.cost > b.cost;
	}
};
//unordered_set<int> remainVertexs;
//unordered_map<int, unordered_set<int>> remainEdges;
//
//
//
////prim algorithm
//
//void insert(unordered_map<int, unordered_map<int, int>>& map, int key1, int key2, int value)
//{
//	if ((map.find(key1) == map.end()))
//		map[key1] = unordered_map<int, int>();
//	map[key1][key2] = value;
//}
//void insert(unordered_map<int, unordered_set<int>>& map, int value1, int value2)
//{
//	if ((map.find(value1) == map.end()))
//		map[value1] = unordered_set<int>();
//	map[value1].insert(value2);
//}
//void erase(unordered_map<int, unordered_set<int>>& map, int value1, int value2)
//{
//	if ((map.find(value1) != map.end()))
//	{
//		map[value1].erase(value2);
//		if (map[value1].empty())
//			map.erase(value1);
//	}
//}
//template<class Container, class KEY>
//bool inline exist(Container const& map, KEY k) { return map.find(k) != map.end(); }
//
//

//
//vector<Edge> getRemainEdges(unordered_map<int, unordered_map<int, int>> const& edges, int vertex)
//{
//	vector<Edge> candidates;
//	//for outgoing vertex
//	for (auto const& edge : edges.at(vertex))
//	{
//		int value1 = min(vertex, edge.first), value2=max(vertex, edge.first);
//		//visited vertex already
//		if (!exist(remainVertexs,edge.first))
//			continue;
//		//for remain edge
//		if (exist(remainEdges,value1))
//		{
//			auto const& outEdges = remainEdges.at(value1);
//			if (exist(outEdges,value2))
//				candidates.push_back(Edge(value1, value2, edge.second));
//		}
//	}
//	return candidates;
//}
//
//
//int solution(int n, vector<vector<int>> costs) {
//	int answer = 0;
//	unordered_map<int, unordered_map<int, int>> edges;
//	for (auto const& cost : costs)
//	{
//		insert(edges, cost[0], cost[1], cost[2]);
//		insert(edges, cost[1], cost[0], cost[2]);
//		remainVertexs.insert(cost[0]);
//		remainVertexs.insert(cost[1]);
//		insert(remainEdges,min(cost[0], cost[1]), max(cost[0], cost[1]));
//	}
//
//	priority_queue<Edge, vector<Edge>, cmpEdge> candidates;
//	int currentV= costs[0][0];
//	remainVertexs.erase(currentV);
//	int cost = 0;
//	while (!remainVertexs.empty())
//	{
//		//expand
//		auto outRemains = getRemainEdges(edges, currentV);
//		for (auto const& remain : outRemains)
//		{
//			candidates.push(remain);
//		}
//		auto next=candidates.top();
//		candidates.pop();
//		if (!exist(remainVertexs, next.startV)&& !exist(remainVertexs, next.endV))
//			continue;
//		cost += next.cost;
//		erase(remainEdges,next.startV, next.endV);
//		currentV = exist(remainVertexs,next.startV)?next.startV:next.endV;
//		remainVertexs.erase(next.startV);
//		remainVertexs.erase(next.endV);
//	}
//
//	return cost;
//}
int solution(int n, vector<vector<int>> costs);
void main()
{
	vector<vector<int>> inputs = {
		{0,1,1},{0,2,2},{1,2,5},{1,3,1},{2,3,8}
	};
	cout<<"answer:"<<solution(4,inputs);
}

//simple version prim
unordered_set<int> remainVertices;
bool visitedEdge[101][101];
int edge[101][101];
int solution(int n, vector<vector<int>> costs) {
	int answer = 0;
	for (int i = 0; i < n; i++)
	{
		remainVertices.insert(i);
		for (int j = 0; j < n; j++)
			visitedEdge[i][j] = false;
	}
	for (auto const& cost : costs)
	{
		edge[cost[0]][cost[1]] = cost[2];
		edge[cost[1]][cost[0]] = cost[2];
	}
	auto visited = [&](int i)->bool
	{
		return remainVertices.find(i) == remainVertices.end();
	};
	auto setVisited= [&](Edge const& edge)
	{
		remainVertices.erase(edge.startV);
		remainVertices.erase(edge.endV);
		visitedEdge[edge.startV][edge.endV] = true;
		visitedEdge[edge.endV][edge.startV] = true;
	};
	priority_queue<Edge, vector<Edge>, cmpEdge> candidates;
	int vertex=0;
	remainVertices.erase(vertex);
	while (!remainVertices.empty())
	{
		//expand
		for (int i = 0; i < n; i++)
		{
			if (!visitedEdge[vertex][i] && !visited(i) && edge[vertex][i]!=0)
				candidates.push(Edge(vertex, i, edge[vertex][i]));
		}
		auto edge = candidates.top();
		candidates.pop();
		if (visited(edge.startV) && visited(edge.endV))
			continue;
		answer += edge.cost;
		vertex = visited(edge.startV) ? edge.endV : edge.startV;
		setVisited(edge);
	}
	
	return answer;
}