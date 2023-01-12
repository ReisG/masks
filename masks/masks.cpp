#include <iostream>
#include <string>
using namespace std;

struct Log
{
	Log* data['z' - 'a' + 1];
	bool read;
	Log()
	{
		for (int i = 0; i < 'z' - 'a' + 1; i++) data[i] = nullptr;
		read = false;
	}
};

void addLogBranch(Log* node, int idx)
{
	if (node->data[idx] == nullptr) node->data[idx] = new Log();
}

struct Bor
{
	Bor* data['z' - 'a' + 1] = {nullptr};
	int number = 0;
	Bor()
	{
		for (int i = 0; i < 'z' - 'a' + 1; i++)
		{
			data[i] = nullptr;
		}
	}
};


void add(Bor* root, string s)
{
	for (int i = 0; i < s.size(); i++)
	{
		if (root->data[s[i] - 'a'] == nullptr)
		{
			root->data[s[i] - 'a'] = new Bor();
		}
		root = root->data[s[i] - 'a'];
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

	if (node->data[s[inspIdx] - 'a'] != nullptr)
	{
		addLogBranch(logNow, s[inspIdx] - 'a');
		simple(node->data[s[inspIdx] - 'a'], s, inspIdx + 1, collected + s[inspIdx], logNow->data[s[inspIdx] - 'a']);
	}
}


void question(Bor* node, const string& s, int inspIdx, string collected, Log* logNow)
{
	for (int i = 0; i < 'z' - 'a' + 1; i++)
	{
		if (node->data[i] != nullptr)
		{
			addLogBranch(logNow, i);
			simple(node->data[i], s, inspIdx + 1, collected + (char)('a' + i), logNow->data[i]);
		}
	}
}

void star(Bor* node, const string& s, int inspIdx, string collected, Log* logNow)
{
	simple(node, s, inspIdx+1, collected, logNow);
	question(node, s, inspIdx, collected, logNow);
	for (int i = 0; i < 'z' - 'a' + 1; i++)
	{
		if (node->data[i] != nullptr)
		{
			addLogBranch(logNow, i);
			star(node->data[i], s, inspIdx, collected + (char)('a' + i), logNow->data[i]);
		}
	}
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

	cout << endl << "Masks" << endl;
	while (true)
	{
		cin >> user;
		simple(root, user);
		cout << endl;
	}

}