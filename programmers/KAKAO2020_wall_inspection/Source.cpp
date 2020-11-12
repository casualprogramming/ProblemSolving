#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<vector<int>> getCombIntervalSet(int fence_count, vector<int> const& weak_interval)
{
    vector<vector<int>> combIntervalSet;
    size_t size = weak_interval.size();
    vector<int> fences(size,0);

    for (int i = 0; i < fence_count; i++)
        fences[size-1-i] = 1;

    auto getMergedIntervals = [](vector<int> const& weak_interval, vector<int> const& fences)
    {
        vector<int> mergedIntervals;
        int const sz = fences.size();
        int const begin = find(fences.begin(), fences.end(), 1) - fences.begin();
        int intervalSum = 0;
        for (int i = (begin + 1)% sz; ; i = (i + 1) % sz)
        {
            if (fences[i] == 1)
            {
                mergedIntervals.push_back(intervalSum);
                intervalSum = 0;
                if (i == begin)
                    break;
            }
            else
                intervalSum += weak_interval[i];
        }
        return mergedIntervals;
    };

    do
    {
        cout << "fence :";
        for (auto fence : fences)
            cout << fence << " ";
        cout<<endl;
        combIntervalSet.push_back(getMergedIntervals(weak_interval,fences));
    } while (next_permutation(fences.begin(), fences.end()));
    return combIntervalSet;
}

bool inspectable(vector<int> const& sorted_intervalset, vector<int> const& sorted_dist)
{
    int i = sorted_intervalset.size() - 1;
    int j = sorted_dist.size() - 1;
    if (i > j)//weak_intervals > inspector
        return false;
    while (i>=0 && j>=0)
    {
        if (sorted_intervalset[i]<=sorted_dist[j])
        {
            i--; j--;
        }
        else
            return false;
    }
    return true;
}

int solution(int n, vector<int> weak, vector<int> dist) {
    vector<int> weak_interval(weak.size());
    weak_interval[0] = n - weak[weak.size() - 1] + weak[0];
    for (int i = 1; i < weak.size(); i++)
    {
        weak_interval[i] = weak[i] - weak[i - 1];
    }
    sort(dist.begin(), dist.end());

    for (int i = 0; i <weak.size(); i++)
    {
        auto combIntervalSet = getCombIntervalSet(i+1, weak_interval);
        for (auto& intervalset : combIntervalSet)
        {
            sort(intervalset.begin(), intervalset.end());
            cout << "interval set: ";
            for (auto const& interval : intervalset)
            {
                cout << interval <<" ";
            }
            cout << endl;
            if (inspectable(intervalset, dist))
            {
                cout << "inpectable!" << endl;
                return i + 1;
            }
        }
    }
}

//@other approach
//n = inspector nunmber
//for each permutation(dist,n)
//  for each inspect case(vector shifting)
//      dist_premutation->isInspectable
// 

void main()
{
    vector<int> weak = { 1, 5, 6, 10 };
    vector<int> dist = { 1, 2, 3, 4 };
    int n = 12;
    solution(n,weak,dist);
}