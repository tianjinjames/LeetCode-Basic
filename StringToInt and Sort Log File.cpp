// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <vector>
#include <unordered_set>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <map>
#include <stack>
#include <string>
#include <fstream>
#include <iterator>
using namespace std;
int getLineNumber(string str);
struct comp
{
	bool operator() (const pair<int, string>& a, const pair<int, string>& b)
	{
		return a.first > b.first;
	}
};

int SortLine(string fileName)
{
	ifstream ifs(fileName);
	if (!ifs.is_open())
		return -1;

	vector<string> file;
	priority_queue<pair<int, string>, vector<pair<int, string>>, comp> q;
	string line;
	while (std::getline(ifs, line))
	{
		file.push_back(line);
	}

	for(auto line : file)
	{
		auto linenumber = getLineNumber(line);
		if (linenumber >= 0)
			q.push(make_pair(linenumber, line));
	}

	file.clear();
	while(!q.empty())
	{
		file.push_back(q.top().second);
		q.pop();
	}

	std::ofstream ofs{ fileName, std::ios_base::trunc };
	if (!ofs.is_open())
		return -1; // or some other error handling
	std::copy(file.begin(), file.end(), std::ostream_iterator<std::string>(ofs, "\n"));
	return 1;
}

int getLineNumber(string str)
{
	int pos = 0, sign = 1;
	long res = 0;
	while (pos < str.size() && str[pos] == ' ')
		pos++;

	if (str[pos] == '+')
		pos++;
	else if (str[pos] == '-') {
		pos++;
		sign = -1;
	}

	while (pos < str.size() && str[pos] > 47 && str[pos] < 58) {
		res = res * 10 + (str[pos] - 48)*sign;
		pos++;
		if (res > INT_MAX)    return INT_MAX;
		if (res < INT_MIN)    return INT_MIN;
	}

	return (int)(res);
}

int main()
{
	auto res = SortLine("file.txt");
}
