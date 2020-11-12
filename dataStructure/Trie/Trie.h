#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <functional>
namespace acclerate
{
using namespace std;
class Trie
{
private:
	bool hasItem = false;// if it has a Item, the word(Item) exists
	Trie* parent=nullptr;
	unordered_map<char, Trie*> childs;
public:
	Trie() {};
	void insert(string const& s);
	Trie* traversal(string const& s) const;
	bool exist(string const& s) const;
	bool erase(string const& s);
	bool isLeaf() const;
	static vector<string> getLeaves(Trie const& trie);
	static vector<string> getItems(Trie const& trie);
	static vector<string> query(string const& str, Trie const& trie);
	vector<string> getLeaves();
	vector<string> getItems();

};

}