#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct MultipleA
{
	int begin;
	int end;
	MultipleA(int begin, int end) :begin(begin), end(end)
	{

	}
	int backAndForth(int size)
	{
		//begin~end
		if (end > begin)
		{
			//forward is best
			if (end == size)
			{
				return (begin-1);
			}
			//backward is best
			else if (begin == 0)
			{
				return size - end;
			}
			//compare backAndForth
			else
			{
				int forthAndBack = (begin-1) * 2 + (size - end);
				int backAndForth = begin + (size - end) * 2;
				int forward = size - 1;
				return min(forward, min(forthAndBack, backAndForth));
			}

		}
		//end~begin
		else
		{
			int forward = begin-1;
			int backward = size-end;
			return min(forward, backward);
		}
	}
};

bool cmp(MultipleA a, MultipleA b) { return (a.end-a.begin) < (b.end - b.begin); }
//return move count
//1. wrong way : compare only correct count
//int moveCount(string name)
//{
//	int rightCorrect = 0;
//	for (int i = 1; i < name.size(); i++)
//	{
//		if (name[i] == 'A')
//			rightCorrect++;
//		else
//			break;
//	}
//	int leftCorrect = 0;
//	for (int i=name.size()-1;i>0;i--)
//	{
//		if (name[i] == 'A')
//			leftCorrect++;
//		else
//			break;
//	}
//	cout << rightCorrect << endl;
//	cout << leftCorrect << endl;
//	return rightCorrect>leftCorrect? name.size()-1-rightCorrect: name.size() - 1 - leftCorrect;
//}



//1. correct way : compare back and forth
//but complex...
//int moveCount(string name)
//{
//	MultipleA a(-1,-1);
//	//find multiple a
//	vector<MultipleA> candidates;
//	int begin = -1;
//	name[0] = 'A';
//	for (int i = 1; i < name.size(); i++)
//	{
//		if (name[i] != 'A')
//		{
//			begin = i; break;
//		}
//	}
//	if (begin == -1)
//		return name.size()-1;
//	int end = begin;
//	do
//	{
//		begin = (begin + 1) % name.size();
//		if (name[begin] == 'A')
//		{
//			if (a.begin == -1)
//			{
//				a.begin = begin;
//				a.end = begin + 1;
//			}
//			else
//				a.end = begin + 1;
//		}
//		else
//		{
//			if(a.begin!=-1)
//				candidates.push_back(a);
//			a.begin = -1;
//			a.end = -1;
//		}
//
//	} while (begin != end);
//	int minimum = 0x7FFFFFFF;
//	for (auto a : candidates)
//	{
//		cout << "begin : " <<a.begin<< endl;
//		cout << "end : " <<a.end<< endl;
//		minimum = min(minimum,a.backAndForth(name.size()));
//	}
//	return minimum;
//}

//@best way : simple and correct way
//refered to other code
int moveCount(string name)
{
	int minimum= 0x7FFFFFFF;
	for (int i = 0; i < name.size();)
	{
		int endA = i + 1;
		while (endA < name.size() && name[endA] == 'A')
			endA++;
		int const& leftRemains = i;
		int rightRemains = name.size() - endA;
		int minLeftRightRemains=min(leftRemains, rightRemains);
		int remains = leftRemains + rightRemains + minLeftRightRemains;
		minimum = min(minimum, remains);
		i += endA;
	}
	return minimum;
}

int changeCount(string name)
{
	//B:1 Z :1 M :12 O:12 N:13
	int count = 0;
	for (auto c : name)
	{
		count += 'N'- 'A' - abs(c - 'N');
	}
	return count;
}

int solution(string name) {
	int answer = 0;
	return answer;
}

void main()
{
	//cout << moveCount("AAAABAAAD")<<endl;
	//cout << changeCount("ZZ");
	//cout<<circularStep(10, 7, 3);
	//moveCount("AABAA");
	moveCount("AABAABAA");
	
	MultipleA a1(1,6);
	MultipleA a2(6,0);
	cout<<a1.backAndForth(10);
	cout<<a2.backAndForth(10);

	cout << "move : " << moveCount("JEROEN") << endl;
	cout << "change : " << changeCount("JEROEN") << endl;

}
