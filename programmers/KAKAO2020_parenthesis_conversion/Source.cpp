#include <string>
#include <vector>
#include <iostream>
using namespace std;

pair<string, string> divide(string const& s)
{
	int l = 0;
	int r = 0;
	for (int i=0; i < s.size(); i++)
	{
		if (s[i] == '(')
			l++;
		else
			r++;
		if (l == r)
			break;
	}
	int length = l + r;
	return { s.substr(0,length),s.substr(length,s.size() - length) };
}
bool correct(string const& s)
{
	int l = 0;
	int r = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '(')
			l++;
		else
			r++;
		if (l - r < 0)
			return false;
	}
	return true;
}
void flipParenthesis(string& str)
{
	for (auto& s : str)
		s = s == '(' ? ')' : '(';
}

string process(string const& w)
{
	cout << w<<endl;
	if (w.size() == 0)
		return "";
	pair<string,string> uv = divide(w);
	if (correct(uv.first))
		return uv.first + process(uv.second);
	else
	{
		string v_recursive = '(' + process(uv.second) + ')';
		string u_cut = uv.first.substr(1, uv.first.size() - 2);
		flipParenthesis(u_cut);
		return v_recursive+u_cut;
	}
}

string solution(string p) {
	string answer = "";
	answer = process(p);
	return answer;
}
void main()
{
	cout << solution("()))((()");
}