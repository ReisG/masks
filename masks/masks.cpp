#include <iostream>
#include <string>
#include <map>

using namespace std;

struct Log
{
	map<char, Log*> data;
	bool read;
	Log()
	{
		read = false;
	}
};

void addLogBranch(Log* node, char symb)
{
	if (node->data.find(symb) == node->data.end()) 
		node->data[symb] = new Log();
}

struct Bor
{
	map<char, Bor*> data;
	int number;
	Bor()
	{
		number = 0;
	}

	bool exist(char symb)
	{
		return data.find(symb) != data.end();
	}
};


void add(Bor* root, string s)
{
	for (int i = 0; i < s.size(); i++)
	{
		if (!root->exist(s[i]))
		{
			root->data[s[i]] = new Bor();
		}
		root = root->data[s[i]];
	}
	root->number++;
}


void simple(Bor* node, const string& s, int inspIdx = 0, string collected = "", Log* logNow=new Log());
void question(Bor* node, const string& s, int inspIdx = 0, string collected = "", Log* logNow = new Log());
void star(Bor* node, const string& s, int inspIdx = 0, string collected = "", Log* logNow = new Log());


void simple(Bor* node, const string &s, int inspIdx, string collected, Log* logNow)
{
	if (inspIdx == s.size())
	{
		if (logNow->read) return;
		for (int i = 0; i < node->number; i++) cout << collected << ' ';
		logNow->read = true;
		return;
	}

	if (s[inspIdx] == '?')
	{
		question(node, s, inspIdx, collected, logNow);
		return;
	}
	else if (s[inspIdx] == '*')
	{
		star(node, s, inspIdx, collected, logNow);
		return;
	}

	if (node->exist(s[inspIdx]))
	{
		addLogBranch(logNow, s[inspIdx]);
		simple(node->data[s[inspIdx]], s, inspIdx + 1, collected + s[inspIdx], logNow->data[s[inspIdx]]);
	}
}


void question(Bor* node, const string& s, int inspIdx, string collected, Log* logNow)
{
	for (auto i : node->data)
	{
		addLogBranch(logNow, i.first);
		simple(node->data[i.first], s, inspIdx + 1, collected + i.first, logNow->data[i.first]);
	}
}

void star(Bor* node, const string& s, int inspIdx, string collected, Log* logNow)
{
	simple(node, s, inspIdx+1, collected, logNow);
	question(node, s, inspIdx, collected, logNow);
	for (auto i : node->data)
	{
		addLogBranch(logNow, i.first);
		star(node->data[i.first], s, inspIdx, collected + i.first, logNow->data[i.first]);
	}
}


string makeMaskSimplier(string mask)
{
	string res = "";
	if (mask.size() != 0) res += mask[0];
	for (int i = 1; i < mask.size(); i++)
	{
		if (mask[i - 1] != '*' || mask[i] != '*') res += mask[i];
	}
	return res;
}

int main()
{
	int n;
	cin >> n;
	string user;

	Bor* root = new Bor();
	for (int i = 0; i < n; i++)
	{
		cin >> user;
		add(root, user);
	}

	cout << endl << "Enter masks" << endl;
	while (true)
	{
		cin >> user;
		simple(root, makeMaskSimplier(user));
		cout << endl << endl;
	}

}