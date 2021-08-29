#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;



int Matching(vector<int>& weightMap,int weight, int limit)
{
    int total = 0;

    for (int partner_weight = limit - weight; partner_weight >= weight; partner_weight--)
    {
        //self matching
        if (partner_weight == weight)
        {
            int matching_count = (weightMap[weight] / 2) + (weightMap[weight] % 2);
            total += matching_count;
            weightMap[weight] = 0;
        }
        else 
        {
            int matching_count = min(weightMap[partner_weight], weightMap[weight]);

            total += matching_count;

            weightMap[partner_weight] -= matching_count;
            weightMap[weight] -= matching_count;
        }

        if (weightMap[weight] == 0)
            break;
    }

    return total + weightMap[weight];
}

int solution(vector<int> people, int limit) {
    int answer = 0;

    vector<int> weightMap(241);

    for (int weight = 0; weight < weightMap.size(); weight++)
    {
        weightMap[weight] = 0;
    }
    for (auto const& weight : people)
    {
        weightMap[weight]++;
    }

    for (int weight = 40; weight < weightMap.size(); weight++)
    {
        if (weightMap[weight] == 0)
            continue;
        int count = Matching(weightMap, weight, limit);
        answer += count;
    }

    return answer;
}

void main()
{
    vector<int> people = { 70, 50, 80, 50 };
    cout << solution(people, 100) << endl;
    return;
}


//
//
//vector<int>::const_iterator FindPartner(vector<int> const& peoples, int current_boat_weight, int limit)
//{
//    int partner_max_weight = limit - current_boat_weight;
//    int find_weight = -1;
//    vector<int>::const_iterator find_iter = peoples.end();
//    //find best
//    for (auto iter = peoples.begin(); iter != peoples.end(); iter++)
//    {
//        int weight = *iter;
//        if (partner_max_weight >= weight && find_weight < weight)
//        {
//            find_weight = weight;
//            find_iter = iter;
//        }
//    }
//    return find_iter;
//}
//
//int solution(vector<int> people, int limit) {
//    int answer = 0;
//    while (!people.empty())
//    {
//        int p1 = people.back();
//        people.pop_back();
//        auto partner = FindPartner(people, p1, limit);
//        if (partner != people.end())
//        {
//            people.erase(partner);
//        }
//        answer++;
//    }
//    return answer;
//}