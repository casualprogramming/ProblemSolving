#include "Trie.h"
#include <iostream>
namespace acclerate
{
	Trie* Trie::traversal(string const& str) const
	{
		Trie* current = (Trie*)this;
		for (char c : str)
		{
			if (current->childs.find(c) != current->childs.end())
			{
				current = current->childs[c];
			}
			else
				return nullptr;
		}
		return current;
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
		current = current->childs[c];
	}
	current->hasItem = true;
}

bool Trie::Trie::exist(string const& str) const
{
	Trie* ptr = traversal(str);
	if (ptr&&ptr->hasItem)
		return true;
	return false;
}

bool Trie::Trie::erase(string const& str)
{
	//traversal
	Trie* trie = traversal(str);
	if (!trie||!trie->hasItem)
		return false;

	//case 1: if interior
	if (!trie->isLeaf() && trie->hasItem)
	{
		trie->hasItem = false;
		return true;
	}

	//case 2: leaf
	//leaf to root: erase leaf
	for (auto iter = str.rbegin(); iter != str.rend(); iter++)
	{
		Trie* parent = trie->parent;
		if (parent == nullptr)
			break;
		delete trie; parent->childs.erase(*iter);
		if (parent->childs.empty())
			trie = parent;
		else
			break;
	}
	return true;
}

bool Trie::isLeaf() const
{
	return childs.empty();
}

vector<string> Trie::getLeaves(Trie const& trie)
{
	vector<string> temp;
	for (const auto& [c,child] : trie.childs)
	{
		for (const auto& str : getLeaves(*child))
		{
			temp.emplace_back(c + str);
		}
	}
	if (trie.isLeaf())
		temp.emplace_back("");
	return temp;
}

vector<string> Trie::getItems(Trie const& trie)
{
	vector<string> temp;
	for (const auto& [c, child] : trie.childs)
	{
		for (const auto& str : getItems(*child))
		{
			temp.emplace_back(c + str);
		}
	}
	if (trie.hasItem)
		temp.emplace_back("");
	return temp;
}

vector<string> Trie::query(string const& queryStr, Trie const& trie)
{
	
	
	vector<string> temp;
	auto queryChild = [&](char c, Trie const& child)
	{	for (const auto& str : query(queryStr.substr(1), child))
	{
		//printf("t-insert");
		temp.emplace_back(c + str);
	}};

	if (!queryStr.empty())
	{
		if (trie.isLeaf())
			return {};
		char key = queryStr.front();
		//printf("t-query %c\n", key);

		if (key == '?')
		{
			for (const auto& [c, child] : trie.childs)
			{
				queryChild(c, *child);
			}
		}
		else
		{
			if (trie.childs.find(key) != trie.childs.end())
				queryChild(key, *(trie.childs.at(key)));
			else
			{
				return {};
			}
		}
	}
	for (const auto& str : temp)
	{
		//printf("temp : %s\n",str.c_str());
	}
	if (trie.hasItem)
		temp.emplace_back("");
	return temp;
}

vector<string> Trie::Trie::getLeaves()
{
	return getLeaves(*this);
}
vector<string> Trie::Trie::getItems()
{
	return getItems(*this);
}

}