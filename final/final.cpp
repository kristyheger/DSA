#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;

typedef struct can
{
	string s;
	int freq;
	bool operator< (const struct can &A) const
	{
		if(A.freq != freq)
			return A.freq < freq;
		return A.s > s;
	}
	bool operator== (const struct can &A) const
	{
		return A.s==s && A.freq==freq;
	}
}Can;

unordered_map<string, int> Dic;
typedef unordered_map<string, int>::iterator Umit;
Umit got;
vector<string> Query;
vector<string> Candidate, TMP;
vector<int> space_pos, space_pos_2;
vector<int> prep_pos, length;
vector<Can> Ans;
char s[4][100] = {"/tmp2/dsa2016_project/2gm.small.txt", "/tmp2/dsa2016_project/3gm.small.txt", "/tmp2/dsa2016_project/4gm.small.txt", "/tmp2/dsa2016_project/5gm.small.txt"};
string prep[20] = {"of", "to", "in", "for", "with", "on", "at", "by", "from", "up", "about", "than", "after", "before", "down", "between", "under", "since", "without", "near"};

void READFILE()
{
	Dic.reserve(400000000);
	char s1[400];
	for(int i = 0; i < 4; i++)
	{
		FILE *fin = fopen(s[i], "r");
		assert(fin != NULL);
		while(fgets(s1, 400, fin) != NULL)
		{
			char s2[400];
			memset(s2, '\0', 400);
			int j = 0;
			while(s1[j] != '\t')	j++;
			for(int k = 0; k < j; k++)	s2[k] = s1[k];
			string str = s2;
			j++;
			int num = s1[j] - 48;
			j++;
			while(s1[j] != '\n' && s1[j] != EOF)
			{
				num = 10*num + (s1[j] - 48);
				j++; 
			}
			Dic.emplace(str, num);
		}
		fclose(fin);
	}
}

void Search()
{
	int size = Candidate.size();
	for(int i = 0; i < size; i++)
	{
		got = Dic.find(Candidate[i]);
		if(got != Dic.end())
		{
			Can A;
			A.s = got->first;
			A.freq = got->second;
			Ans.push_back(A);
		}
	}
	sort(Ans.begin(), Ans.end());
	auto it = unique(Ans.begin(), Ans.end());
	Ans.resize(distance(Ans.begin(), it));
	int Ans_size = Ans.size();
	if(Ans_size >= 10)	printf("output: 10\n");
	else	printf("output: %d\n", Ans_size);
	for(int i = 0; i < Ans_size; i++)
	{
		if(i >= 10)	break;
		printf("%s\t%d\n", Ans[i].s.c_str(), Ans[i].freq);
	}
}

int part = 0;
void PREP(vector<string> Can_Vec, int pos, int cnt)
{
	TMP = Can_Vec;
	string candidate;
	int size = Can_Vec.size();
	for(int i = 0; i < size; i++)	candidate += (i == size-1)? Can_Vec[i] : Can_Vec[i] + " ";
	Candidate.push_back(candidate);
	int prep_cnt = prep_pos.size();
	if(cnt > part-1)	return;
	if(pos >= length.size())	return;
	if(prep_pos[pos] >= size)	return;
	for(int i = 0; i < length[cnt]; i++)
	{
		TMP.erase(TMP.begin()+prep_pos[pos]+i);
		for(int k = pos+i; k < prep_cnt; k++)	prep_pos[k]--;
		PREP(TMP, pos+1, cnt+1);
		for(int k = pos+i; k < prep_cnt; k++)	prep_pos[k]++;
		TMP.clear();
		TMP = Can_Vec;
		for(int j = 0; j < 20; j++)
		{
			TMP.insert(TMP.begin()+prep_pos[pos]+i, prep[j]);
			for(int k = pos+i; k < prep_cnt; k++)	prep_pos[k]++;
			PREP(TMP, pos+1, cnt+1);
			for(int k = pos+i; k < prep_cnt; k++)	prep_pos[k]--;
			TMP.clear();
			TMP = Can_Vec;

			TMP.insert(TMP.begin()+prep_pos[pos]+i+1, prep[j]);
			for(int k = pos+i; k < prep_cnt; k++)	prep_pos[k]++;
			PREP(TMP, pos+1, cnt+1);
			for(int k = pos+i; k < prep_cnt; k++)	prep_pos[k]--;
			TMP.clear();
			TMP = Can_Vec;
			
			TMP.erase(TMP.begin()+prep_pos[pos]+i);
			TMP.insert(TMP.begin()+prep_pos[pos]+i, prep[j]);
			PREP(TMP, pos+1, cnt+1);
			TMP.clear();
			TMP = Can_Vec;
		}
		TMP = Can_Vec;
	}
}

void NO_PREP()
{
	string candidate;
	int size = Query.size();
	for(int i = 0; i < size; i++)
		candidate += (i == size-1)? Query[i] : Query[i] + " ";
	Candidate.push_back(candidate);
	int len = candidate.size();
	space_pos.push_back(0);
	for(int i = 0; i < len; i++)
		if(candidate[i] == ' ')	space_pos.push_back(i+1);
	int space_cnt = space_pos.size();
	string tmp = candidate;
	string tmp2;
	for(int i = 0; i < 20; i++)
	{
		for(int j = 0; j < space_cnt; j++)
		{
			tmp.insert(space_pos[j], prep[i] + " ");
			Candidate.push_back(tmp);
			int tmp_size = tmp.size();
			space_pos_2.push_back(0);
			for(int k = 0; k < tmp_size; k++)
				if(tmp[k] == ' ')	space_pos_2.push_back(k+1);
			int space_cnt_2 = space_pos_2.size(); 
			for(int k = 0; k < 20; k++)	
			{	
				for(int l = 0; l < space_cnt_2; l++)
				{
					tmp2 = tmp;
					tmp2.insert(space_pos_2[l], prep[k] + " ");
					Candidate.push_back(tmp2);
				}
				tmp2 = tmp;
				tmp2 += " " + prep[k];
				Candidate.push_back(tmp2);
				tmp2 = tmp;
			}
			tmp = candidate;
			space_pos_2.clear();
		}
		tmp += " " + prep[i];
		Candidate.push_back(tmp);
		tmp = candidate;
	}
	space_pos.clear();
}

int main(void)
{
	READFILE();
	char q[1000], c;
	string candidate;
	int n = 1, flag = 0;
	while(scanf("%s%c", q, &c) != EOF)
	{
		string query = q;
		for(int i = 0; i < 20; i++)
			if(query == prep[i])	{flag = 1;	break;}
		if(c != '\n' && c != EOF)
		{
			Query.push_back(query);
			n++;
			continue;
		}
		Query.push_back(query);
		int size = Query.size();
		for(int i = 0; i < size; i++)	candidate += (i == size-1)? Query[i] : Query[i] + " ";
		int tmp = -1;
		if(flag)
		{
			for(int i = 0; i < size; i++)
			{
				for(int j = 0; j < 20; j++)
				{
					if(Query[i] == prep[j])
					{	
						if(i == 0)	part++;
						if(tmp != i-1)	part++;
						tmp = i;
						prep_pos.push_back(i);
						break;
					}
				}
			}
			int prep_cnt = prep_pos.size(), len = 1;
			for(int i = 0; i < prep_cnt; i++)
			{
				if(i < prep_cnt-1 && prep_pos[i]+1 == prep_pos[i+1]){len++;	continue;}
				else	{length.push_back(len); len = 1;}
			}
			PREP(Query, 0, 0);
			printf("query: %s\n", candidate.c_str());
			Search();
			Candidate.clear();
			Ans.clear();
			part = 0;
			prep_pos.clear(), length.clear();
		}
		else	{NO_PREP();	printf("query: %s\n", candidate.c_str());	Search();	Candidate.clear();	Ans.clear();}
		Query.clear();
		candidate.clear();
		flag = 0;
		n = 1;
	}
	return 0;
}