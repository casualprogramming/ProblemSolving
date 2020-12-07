#include <string>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

class Trie
{
private:
	bool hasItem = false;// if it has a Item, the word(Item) exists
	Trie* parent = nullptr;
	int itemCounts = 0;
	unordered_map<char, Trie*> childs;
public:
	Trie() {};
	void insert(string const& s);
	bool isLeaf() const;
	int query(string const& str);
};
inline bool isUseReverse(string const& word)
{
	return word[0] == '?';
}
//Trie trie[10000];
//Trie rtrie[10000];
vector<int> solution(vector<string> words, vector<string> queries) {
	Trie trie[10000];
	Trie rtrie[10000];
	vector<int> answer;
	for (auto const& word : words)
	{
		trie[word.size()-1].insert(word);
		rtrie[word.size() - 1].insert(string(word.rbegin(), word.rend()));
	}
	for (auto const& query : queries)
	{
		int s = int(query.size()-1);
		int count = isUseReverse(query) ? rtrie[s].query(string(query.rbegin(), query.rend())) : trie[s].query(query);
		answer.emplace_back(count);
		printf("count:%d\n", count);
		//Trie* query_in_trie=trie.traversal(query);
	}
	return answer;
}
vector<int> solution(vector<string> words, vector<string> queries);

int main()
{
	vector<string> words = { "frodo", "front", "frost", "frozen", "frame", "kakao" };
	vector<string> queries = { "fro??", "????o", "fr???", "fro???", "pro?" };
	solution(words, queries);

	return 0;
}

void Trie::Trie::insert(string const& str)
{
	if (str.empty())
		return;
	Trie* current = this;
	for (char c : str)
	{
		if (current->childs.find(c) == current->childs.end())
		{
			Trie* child = new Trie();
			child->parent = current;
			current->childs[c] = child;
		}
		current->itemCounts++;
		current = current->childs[c];
	}
	current->itemCounts++;
	current->hasItem = true;
}


bool Trie::isLeaf() const
{
	return childs.empty();
}

int Trie::query(string const& queryStr)
{
	Trie* current = this;
	for (char c : queryStr)
	{
		if (c == '?')
			return current->itemCounts;
		if (current->childs.find(c) != current->childs.end())
		{
			current = current->childs[c];
		}
		else
			return 0;
	}
	return 0;
}



//TODO : brute force -> trie
//brute force method
//bool exist(string const& word, string const& query)
//{
//	if (word.size() != query.size())
//		return false;
//	for (int i = 0; i < word.size(); i++)
//	{
//		if (query[i] != '?' && word[i] != query[i])
//			return false;
//	}
//	return true;
//}
//
//vector<int> solution(vector<string> words, vector<string> queries) {
//	vector<int> answer;
//	for (auto const& query : queries)
//	{
//		int matches = 0;
//		for (auto const& word : words)
//			if (exist(word, query))
//				matches++;
//		answer.push_back(matches);
//	}
//
//	return answer;
//}

//method 2 : simple hashmap [timeout]
//unordered_map<string, int>	wordMap[10001];
//unordered_map<string, int>	rwordMap[10001];
//vector<int> solution2(vector<string> words, vector<string> queries) {
//	vector<int> answer;
//	for (auto const& word : words)
//	{
//		
//		for (int i = 1; i <= word.size(); i++)
//		{
//			string str = word.substr(0,i);
//			auto& wm = wordMap[word.size() - 1];
//			if (wm.find(str) == wm.end())
//				wm[str]=0;
//			wm[str]++;
//		}
//		for (int i = 1; i <= word.size(); i++)
//		{
//			string str = string(word.rbegin(), word.rbegin()+i);
//			auto& rwm = rwordMap[word.size() - 1];
//			if (rwm.find(str) == rwm.end())
//				rwm[str] = 0;
//			rwm[str]++;
//		}
//	}
//	for (auto const& query : queries)
//	{
//		int s = query.size() - 1;
//		auto const& q = isUseReverse(query) ? string(query.rbegin(), query.rend()) : query;
//		auto & wm = isUseReverse(query) ? rwordMap[s]:wordMap[s];
//		string token = q.substr(0, q.find('?'));
//		int count = 0;
//		if (wm.find(token) != wm.end())
//			count = wm[token];
//		answer.emplace_back(count);
//	}
//	return answer;
//}