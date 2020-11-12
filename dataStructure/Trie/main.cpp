#include "Trie.h"
#include <iostream>
using namespace acclerate;
vector<int> solution(vector<string> words, vector<string> queries);
void main()
{
	Trie trie;
	trie.insert("asd");
	trie.insert("asdf");
	
	cout << trie.exist("asd") << endl;
	cout << trie.exist("asdf") << endl;
	cout << trie.erase("asd")<<endl;
	//cout << trie.erase("asd") << endl;
	cout << "leaves\n";
	for (auto const& leaf : trie.getLeaves())
	{
		cout << leaf << endl;
	}
	cout << "items\n";
	for (auto const& item : trie.getItems())
	{
		cout << item << endl;
	}
	cout << "query\n";
	for (auto const& item : Trie::query("asd?",trie))
	{
		cout << item << endl;
	}
	
	vector<string> words = { "frodo", "front", "frost", "frozen", "frame", "kakao" };
	vector<string> queries = { "fro??", "????o", "fr???", "fro???", "pro?" };
	solution(words, queries);
}

vector<int> solution(vector<string> words, vector<string> queries) {
	Trie trie;
	vector<int> answer;
	for (auto const& word : words)
	{
		trie.insert(word);
	}

	for (auto const& query : queries)
	{
		printf("exsit:");
		for (auto const& q : Trie::query(query, trie))
			printf("%s ", q.c_str());
		printf("\n");
		//Trie* query_in_trie=trie.traversal(query);
	}

	return answer;
}