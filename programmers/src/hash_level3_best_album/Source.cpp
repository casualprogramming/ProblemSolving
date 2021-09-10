#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <algorithm>
using namespace std;
//https://programmers.co.kr/learn/courses/30/lessons/42579

struct Comparator {
	bool operator()(int a, int b)const { return a > b; }
};

vector<int> solution(vector<string> genres, vector<int> plays)
{
	vector<int> answer;
	unordered_map<string, multimap<int, int, Comparator>> BestAlbum;
	unordered_set<string> GenreTypes;
	for (int i=0;i<genres.size();i++)
	{
		if (BestAlbum.find(genres[i]) == BestAlbum.end())
		{
			GenreTypes.insert(genres[i]);
			BestAlbum[genres[i]] = multimap<int, int, Comparator>();
		}
		BestAlbum[genres[i]].insert(pair<int, int>(plays[i],i));
	}

	vector<pair<string, int>> genre_count;
	for (auto const& genre : GenreTypes)
	{
		int total_plays = 0;
		for (auto const& music : BestAlbum[genre])
		{
			total_plays += music.first;
		}
		genre_count.push_back(make_pair(genre, total_plays));
	}

	sort(genre_count.begin(), genre_count.end(), [](pair<string, int> const& a, pair<string, int> const& b)
		{
			return a.second < b.second;
		});

	int target_select = 2;

	for (auto giter = genre_count.rbegin();giter!= genre_count.rend();giter++)
	{
		auto const& Album = BestAlbum[giter->first];
		int selects = 1;
		for (auto iter = Album.begin(); iter!=Album.end();iter++)
		{
			answer.push_back(iter->second);
			if (target_select == selects)
				break;
			selects++;
		}
	}

	return answer;
}



int main()
{
	solution({ "classic", "pop", "classic", "classic", "pop" }, { 500, 600, 150, 800, 2500 });

	return 0;
}
