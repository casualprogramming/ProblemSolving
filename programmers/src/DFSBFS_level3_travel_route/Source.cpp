#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <iostream>
using namespace std;

int ticketSize = 0;
vector<string> answer;

void dfs(string vertexId, unordered_map<string, multiset<string>>& adjacentList) {

	multiset<string> adjacents = adjacentList[vertexId];
	for (const auto& adjacent : adjacents) {
		answer.push_back(adjacent);
		if (answer.size() == ticketSize + 1) {
			return;
		}
		adjacentList[vertexId].erase(adjacentList[vertexId].find(adjacent));
		dfs(adjacent, adjacentList);
		if (answer.size() == ticketSize + 1) {
			return;
		}
		adjacentList[vertexId].insert(adjacent);
		answer.pop_back();
	}
}

vector<string> solution(vector<vector<string>> tickets) {

	unordered_map<string, multiset<string>> adjacentList;

	for (const auto& srcAndDst : tickets) {
		const string& src = srcAndDst[0];
		const string& dst = srcAndDst[1];

		if (adjacentList.find(src) == adjacentList.end()) {
			adjacentList[src] = multiset<string>();
		}
		adjacentList[src].insert(dst);

	}
	ticketSize = tickets.size();
	answer.push_back("ICN");
	dfs(string("ICN"), adjacentList);

	return answer;
}

void main()
{

}