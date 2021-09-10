#include <iostream>
#include <queue>
#include <unordered_set>
#include <set>
#include <map>
#include <unordered_map>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <execution>

using namespace std;

using namespace std;
template <typename T, typename U>
std::pair<T, U> operator+(const std::pair<T, U>& l, const std::pair<T, U>& r) { return { l.first + r.first,l.second + r.second }; }
template <typename T, typename U>
std::pair<T, U> operator-(const std::pair<T, U>& l, const std::pair<T, U>& r) { return { l.first - r.first,l.second - r.second }; }

string to_string(string const& str) { return str; }

template<typename T1, typename T2>
string to_string(pair<T1, T2> const& pair)
{
	return "(" + to_string(pair.first) + "," + to_string(pair.second) + ")";
}

template<class T>
void Print(T const& data)
{
	cout << to_string(data) << endl;
}
template<class Iter>
void PrintContainer(Iter const& Begin,Iter const& End)
{
	string txt = "[";
	for (auto iter = Begin; iter !=End;iter++)
		txt += to_string(*iter) + ", ";
	txt += "]";
	cout << txt << endl;
}

void TestString()
{
	cout << "\n\n******************** string ***************\n\n";

	cout<<stoi("1.1")<<endl;
	cout<<stod("1.2")<<endl;
	cout<<stof("1.3")<<endl;
	vector<string> data = { "aba","aab","aaa","abb" };
	//cout<<std::reduce(std::execution::par, data.begin(), data.end(), string(), [](string const& a, string const& b) {return a +" "+b; });
	sort(data.begin(), data.end(), [](const string& a, const string& b) { return a > b; });
	PrintContainer(data.begin(), data.begin());
}

void TestMapAndSet()
{
	cout << "\n\n******************** map, set ***************\n\n";
	vector<string> data = { "", };
	multiset<int> sorted_set= { 1,1,3,5,7,9,9 };
	PrintContainer(sorted_set.begin(), sorted_set.end());
	auto iter = sorted_set.upper_bound(5);

	struct Comparator {
		bool operator()(int a, int b)const { return a > b; }
	};
	multiset<int, Comparator> descending(sorted_set.begin(), sorted_set.end());
	PrintContainer(descending.begin(), descending.end());

}

void TestPair()
{
	cout << "\n\n******************** pair ***************\n\n";

	vector<string> data = { "", };

	set<pair<int, pair<int, int>>> pairs;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
				pairs.insert(make_pair(i, make_pair(j, k)));
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
				pairs.insert(make_pair(i, make_pair(j, k)));

	vector<pair<int, pair<int, int>>> datas1 = { {0,{0,0}}, {1,{1,1}} };
	pair<int, pair<int, int>> p1 = { 2,{2,2} };
	pair<int, pair<int, int>> p2 = { 1,{1,1} };
	Print(p1 + p2);
	PrintContainer(pairs.begin(), pairs.end());
}

void TestQueue()
{
	vector<int> data = { 1,1,3,5,7,9,9 };
	cout << "\n\n******************** queue ***************\n\n";
	struct Comparator {
		bool operator()(int a, int b)const { return a > b; }
	};
	//value, container, comparator
	priority_queue<int, vector<int>, Comparator> pqueue(data.begin(),data.end());
	cout << "top:" << pqueue.top() << endl;
}
void TestVector()
{
	const int n = 5;
	vector<vector<bool>> beams(n + 3, vector<bool>(n + 3, false));//initialize with false 
}

void TestAlgorithm()
{
	cout << "\n\n******************** algorithm ***************\n\n";
	vector<pair<int, string>> data = { {1,"a"},{1,"c"},{2,"b"},{4,"d"},{3,"e"},{3,"f"} };
	int k = data.size() / 2;
	//quick select
	for (int k = 0; k < data.size(); k++)
	{
		nth_element(data.begin(), data.begin() + k, data.end(), [](pair<int, string> const& a, pair<int, string>const& b) {return a.first < b.first; });
		Print(data[k]);
	}
}

int main()
{
	TestString();
	TestPair();
	TestMapAndSet();
	TestQueue();
	TestAlgorithm();
	return 0;
}
