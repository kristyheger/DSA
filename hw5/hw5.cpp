#include <bits/stdc++.h>
using namespace std;

vector<string> Dic[10000];
vector<string> ED1, Possible;
vector<string>::iterator eraseit;
hash<string> str_hash;
int flag = 0;

bool cmp(string a, string b)
{
	return a < b;
}

int find(string s)
{
	int key = str_hash(s);
	key = (key < 0)? (-key)%10000 : key%10000;
	int size = Dic[key].size();
	for(int i = 0; i < size; i++)
		if(s == Dic[key][i])
			return 1;
	return 0;
}
void Ins(string s, int n)
{
	for(int i = 'a'; i <= 'z'; i++)
	{
		s.insert(n, 1, i);
		if(flag)
		{
			if(find(s))	Possible.push_back(s);
		}
		else ED1.push_back(s);
		s.erase(n, 1);
	}
}

void Del(string s, int n)
{
	int c = s[n];
	s.erase(n, 1);
	if(flag)
	{
		if(find(s))	Possible.push_back(s);
	}
	else ED1.push_back(s);
	s.insert(n, 1, c);
}

void Sub(string s, int n)
{
	for(int i = 'a'; i <= 'z'; i++)
	{
		int tmp = s[n];
		s[n] = i;
		if(flag)
		{
			if(find(s))	Possible.push_back(s);
		}
		else ED1.push_back(s);
		s[n] = tmp;
	}
}

void Trans(string s, int n)
{
	swap(s[n], s[n+1]);
	if(flag)
	{
		if(find(s))	Possible.push_back(s);
	}
	else ED1.push_back(s);
	swap(s[n], s[n+1]);
}

void check(string s)
{
	int len = s.size();
	if(find(s))	{ printf("%s ==> OK\n", s.c_str());	return;	}
	for(int i = 0; i <= len; i++)
		Ins(s, i);
	for(int i = 0; i < len; i++)
		Del(s, i);
	for(int i = 0; i < len; i++)
		Sub(s, i);
	for(int i = 0; i < len-1; i++)
		Trans(s, i);
	sort(ED1.begin(), ED1.end(), cmp);
	ED1.erase(unique(ED1.begin(), ED1.end()), ED1.end());
	flag = 1;
	int size = ED1.size();
	for(int i = 0; i < size; i++)
	{
		len = ED1[i].size();
		for(int j = 0; j <= len; j++)
			Ins(ED1[i], j);
		for(int j = 0; j < len; j++)
			Del(ED1[i], j);
		for(int j = 0; j < len; j++)
			Sub(ED1[i], j);
		for(int j = 0; j < len-1; j++)
			Trans(ED1[i], j);
	}
	for(int i = 0; i < size; i++)
	{
		if(find(ED1[i]))	Possible.push_back(ED1[i]);
	}
	if(!Possible.size()){	printf("%s ==> NONE\n", s.c_str()); return; }
	else
	{
		sort(Possible.begin(), Possible.end(), cmp);
		Possible.erase(unique(Possible.begin(), Possible.end()), Possible.end());
		int n = Possible.size();
		printf("%s ==> ", s.c_str());
		for(int i = 0; i < n; i++){
			printf( (i == n-1)? "%s\n" : "%s ", Possible[i].c_str() );
		}
	}
	return;
}

int main(void)
{
	FILE *fin = fopen("/tmp2/dsa2016_hw5/cmudict-0.7b", "r");
	char s1[200], s2[200];
	// int x = 0;
	while(fgets(s1, 200, fin) != NULL)
	{
		if(isalpha(s1[0]))
		{
			sscanf(s1, "%s", s2);
			if(!isalpha(s2[strlen(s2) - 1]))	continue;
			int len = strlen(s2);
			for(int i = 0; i < len; i++)	s2[i] = tolower(s2[i]);
			int key = str_hash(s2);
			key = (key < 0)? (-key)%10000 : key%10000;
			Dic[key].push_back(s2);
			// x++;
		}
	}
	fclose(fin);
	// printf("%d\n", x);
	char s3[200], s4[200];
	while(fgets(s3, 200, stdin) != NULL)
	{
		sscanf(s3, "%s", s4);
		string s = s4;
		check(s);
		flag = 0;
		ED1.erase(ED1.begin(), ED1.end());
		Possible.erase(Possible.begin(), Possible.end());
	}
	// int max = 0;
	// for(int i = 0; i < 10000; i++)
	// {
	// 	if(Dic[i].size() > max)	max = Dic[i].size();
	// }
	// printf("%d\n", max);
	return 0;
}