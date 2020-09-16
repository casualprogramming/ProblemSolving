#include <string>
#include <vector>

using namespace std;

//TODO : tries
bool exist(string const& word, string const& query)
{
	if (word.size() != query.size())
		return false;
	for (int i = 0; i < word.size(); i++)
	{
		if (query[i] != '?' && word[i] != query[i])
			return false;
	}
	return true;
}

vector<int> solution(vector<string> words, vector<string> queries) {
	vector<int> answer;
	for (auto const& query : queries)
	{
		int matches = 0;
		for (auto const& word : words)
			if (exist(word, query))
				matches++;
		answer.push_back(matches);
	}

	return answer;
}

void main()
{

}