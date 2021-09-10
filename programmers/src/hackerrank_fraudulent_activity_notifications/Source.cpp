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
void PrintContainer(Iter const& Begin, Iter const& End)
{
	string txt = "[";
	for (auto iter = Begin; iter != End; iter++)
		txt += to_string(*iter) + ", ";
	txt += "]";
	cout << txt << endl;
}
using namespace std;
//https://www.hackerrank.com/challenges/fraudulent-activity-notifications/problem
//계속해서 중앙값 계산
//주의 0<expenditure<200
//nth_element: wong O(n)
//sorting: worng O(dlogd)오더링 + O(n)원소찾기
//count sorting:corrent

inline int my_nth_element(vector<int>& data, int k)
{
    nth_element(data.begin(), data.begin() + k, data.end());
    return data[k];
}

const int expense_size = 201;
array<int, expense_size> expense_count;//[??][count]

int find_expense(int begin_expense)
{
    if (begin_expense< expense_count.size() && expense_count[begin_expense] >= 2)
        return begin_expense;
    for (int e = begin_expense+1; e < expense_count.size(); e++)
    {
        if (expense_count[e] >= 1)
            return e;
    }
    return -1;
}

//k=0~
int find_nth_expense(int k)
{
    int count = 0;
    for (int expense=0; expense < expense_count.size(); expense++)
    {
        count += expense_count[expense];
        if (count > k)
            return expense;
    }
    return -1;
}

int activityNotifications(vector<int> expenditure, int d)
{
    int alert = 0;
    for (int i = 0; i < expense_count.size();i++)
        expense_count[i] = 0;
    for (int i = 0; i < d-1; i++)
        expense_count[expenditure[i]]++;
    
    //day 0~
    for (int day = d; day < expenditure.size(); day++)
    {
        expense_count[expenditure[day-1]]++;//insert
        int k = d / 2;
        if (d % 2 == 0)
        {
            int median = 0;
            int nth_expesne = find_nth_expense(k-1);
            median += nth_expesne;
            median += find_expense(nth_expesne);
            if(expenditure[day]>=median)
                alert++;
        }
        else
        {
            int median = 0;
            median = find_nth_expense(k);
            if (expenditure[day]>= median*2)
                alert++;
        }
        expense_count[expenditure[day - d]]--;//erase
    }
    cout << alert;
    return alert;
}

int main()
{
	activityNotifications({ 1, 2, 3, 4, 4 }, 4);
    //activityNotifications({ 0, 0, 0, 0, 0 }, 3);
	return 0;
}
