#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <string>
#include <ctype.h>
using namespace std;

typedef struct{
	int UserID, ItemID, Result, Time;
}Rec;

vector<Rec> rec_u;
vector<Rec> rec_i;

int user_ac[100000000] = {0};

int compare_u(Rec a, Rec b){
	if(a.UserID == b.UserID){
		if(a.ItemID == b.ItemID){
			return (a.Time < b.Time);
		}
		return (a.ItemID < b.ItemID);
	}
	return (a.UserID < b.UserID);
}

int compare_i(Rec a, Rec b){
	if(a.ItemID == b.ItemID){
		if(a.UserID == b.UserID){
			return (a.Time < b.Time);
		}
		return (a.UserID < b.UserID);
	}
	return (a.ItemID < b.ItemID);
}

inline int sort_T(int a, int b){
	return (a < b);
}

int accept(int u, int i, int t){
	int left = 0, right = rec_u.size() - 1, tmp = -1;
	while(left <= right){
		int mid = (left + right)/2;
		if(u == rec_u[mid].UserID){
			tmp = mid;
			right = mid - 1;
		}
		else if(u < rec_u[mid].UserID){
			right = mid - 1;
		}
		else if(u > rec_u[mid].UserID){
			left = mid + 1;
		}
	}
	if(tmp == -1)	return 0;
	int size = rec_u.size();
	for(int j = tmp; j < size; j++){
		if(rec_u[j].UserID != u)	break;
		if(rec_u[j].ItemID == i && rec_u[j].Time == t){
			return rec_u[j].Result;
		}
	}
	return 0;
}

void items(int u1, int u2){
	int size = rec_u.size();
	int left = 0, right = size - 1, tmp = -1;
	vector<int> i_u1;
	while(left <= right){
		int mid = (left + right)/2;
		if(rec_u[mid].UserID == u1){
			tmp = mid;
			right = mid - 1;
		}
		else if(rec_u[mid].UserID < u1){
			left = mid + 1;
		}
		else if(rec_u[mid].UserID > u1){
			right = mid - 1;
		}
	}
	if(tmp == -1){	cout << "EMPTY" << endl; return;}
	for(int i = tmp; i < size; i++){
		if(rec_u[i].UserID != u1)	break;
		i_u1.push_back(rec_u[i].ItemID);
	}
	left = 0, right = size - 1, tmp = -1;
	while(left <= right){
		int mid = (left + right)/2;
		if(rec_u[mid].UserID == u2){
			tmp = mid;
			right = mid - 1;
		}
		else if(rec_u[mid].UserID < u2){
			left = mid + 1;
		}
		else if(rec_u[mid].UserID > u2){
			right = mid - 1;
		}
	}
	if(tmp == -1){	cout << "EMPTY" << endl; return;}
	int yes = 0, size_i = i_u1.size();
	for(int i = tmp; i < size; i++){
		if(rec_u[i].UserID != u2)	break;
		if((i > 0) && (rec_u[i].ItemID == rec_u[i-1].ItemID)) continue;
		for(int j = 0; j < size_i; j++){
			if(rec_u[i].ItemID == i_u1[j]){
				cout << rec_u[i].ItemID << endl;
				yes = 1;
				break;
			}
		}
	}
	if(!yes)	cout << "EMPTY" << endl;
	return;
}

void users(int i1, int i2, int t1, int t2){
	int tmp = -1;
	vector<int> U;
	Rec rec1 = {-1, i1, -1, -1};
	Rec rec2 = {-1, i2, -1, -1};
	vector<Rec>::iterator it1 = lower_bound(rec_i.begin(), rec_i.end(), rec1, compare_i);
	vector<Rec>::iterator it2 = lower_bound(rec_i.begin(), rec_i.end(), rec2, compare_i);
	while(it1->ItemID == i1 && it2->ItemID == i2){
		if(it1->UserID == it2->UserID){
			if(it1->UserID == tmp){
				it1++;
				it2++;
				continue;
			}
			else if(it1->Time >= t1 && it1->Time <= t2 && it2->Time >= t1 && it2->Time <= t2){
				U.push_back(it1->UserID);
				tmp = it1->UserID;
				it1++;
				it2++;
			}
			else if(it1->Time < t1 || it1->Time > t2)
				it1++;
			else if(it2->Time < t1 || it2->Time > t2)
				it2++;
		}
		else if(it1->UserID > it2->UserID)
			it2++;
		else if(it1->UserID < it2->UserID)
			it1++;
	}
	int size = U.size();
	if(!size){cout << "EMPTY" << endl;	return;}
	for(int i = 0; i < size; i++){
		cout << U[i] << endl;
	}
	return;
}

typedef struct{
	int pos, cnt;
}User;
User user[2000000];
int first = 0, tmp = 0;

void ratio(int i, int threshold){
	int size = rec_u.size(), cnt = 1, ac = 0;
	vector<int> tot_user_pos;
	if(!first){
		for(int j = 0; j < size; j++){
			if(j > 0 && rec_u[j].UserID == rec_u[j-1].UserID && rec_u[j].ItemID == rec_u[j-1].ItemID && rec_u[j].Time == rec_u[j-1].Time)
				continue;
			if(j > 0 && rec_u[j].UserID == rec_u[j-1].UserID)	cnt++;
			else if(j > 0 && rec_u[j].UserID != rec_u[j-1].UserID){
				user[tmp].pos = j-1;
				user[tmp].cnt = cnt;
				tmp++;
				if(cnt > threshold)
					tot_user_pos.push_back(j-1);
				cnt = 1;
			}
		}
		if(cnt > threshold){
			user[tmp].pos = size - 1, user[tmp].cnt = cnt;
			tmp++;
			tot_user_pos.push_back(size - 1);
		}
	}
	else{
		for(int j = 0; j < tmp; j++){
			if(user[j].cnt > threshold)
				tot_user_pos.push_back(user[j].pos);
		}
	}
	int size_tot = tot_user_pos.size();
	for(int j = 0; j < size_tot; j++){
		for(int k = tot_user_pos[j]; k >= 0; k--){
			if(k < tot_user_pos[j] && (rec_u[k].UserID != rec_u[k+1].UserID))	break;
			if(rec_u[k].ItemID == i && rec_u[k].Result == 1){
				ac++;
				break;
			}
		}
	}
	cout << ac << "/" << size_tot << endl;
	first = 1;
	return;
}

void findtime_item(int i, vector<int> Us){
	vector<int> T;
	int size = rec_i.size(), size_us = Us.size();
	int left = 0, right = size - 1, tmp = -1;
	while(left <= right){
		int mid = (left + right)/2;
		if(i == rec_i[mid].ItemID){
			tmp = mid;
			right = mid - 1;
		}
		else if(i < rec_i[mid].ItemID){
			right = mid - 1;
		}
		else if(i > rec_i[mid].ItemID){
			left = mid + 1;
		}
	}
	if(tmp == -1){	cout << "EMPTY" << endl; return;}
	for(int j = tmp; j < size; j++){
		if(rec_i[j].ItemID != i)	break;
		for(int k = 0; k < size_us; k++){
			if(rec_i[j].UserID == Us[k])
				T.push_back(rec_i[j].Time);
		}
	}
	sort(T.begin(), T.end(), sort_T);
	int size_T = T.size();
	if(!size_T){ cout << "EMPTY" << endl; return;}
	for (int j = 0; j < size_T; j++){
		if(j > 0 && T[j] == T[j-1])	continue;
		cout << T[j] << endl;
	}
	return;
}

int main(void){
	for(int i = 0; i < 2000000; i++){
		user[i].pos = -1;
		user[i].cnt = -1;
	}
	int a, b, c, d;
	Rec R;
	FILE *fin = fopen("/tmp2/KDDCUP2012/track1/rec_log_train.txt", "r");
	while(fscanf(fin, "%d%d%d%d", &a, &b, &c, &d) != EOF){
		R.UserID = a, R.ItemID = b, R.Result = c, R.Time = d;
		rec_u.push_back(R);
		rec_i.push_back(R);
	}
	fclose(fin);
	sort(rec_u.begin(), rec_u.end(), compare_u);
	sort(rec_i.begin(), rec_i.end(), compare_i);
	int n;
	char s[100];
	s[0] = 'x';
	cin >> n;
	for(int i = 0; i < n; i++){
		if(s[0] == 'x'){
			cin >> s;
		}
		if(s[0] == 'a'){
			int u, i, t;
			cin >> u >> i >> t;
			int acc = accept(u, i, t);
			cout << acc << endl;
		}
		if(s[0] == 'i'){
			int u1, u2;
			cin >> u1 >> u2;
			items(u1, u2);
		}
		if(s[0] == 'u'){
			int i1, i2, t1, t2;
			cin >> i1 >> i2 >> t1 >> t2;
			users(i1, i2, t1, t2);
		}
		if(s[0] == 'r'){
			int i, threshold;
			cin >> i >> threshold;
			ratio(i, threshold);
		}
		if(s[0] == 'f'){
			vector<int> Us;
			int i, us;
			cin >> i;
			while(scanf("%s", s)!= EOF && isdigit(s[0])){
				sscanf(s, "%d", &us);
				Us.push_back(us);
			}
			findtime_item(i, Us);
			continue;
		}
		s[0] = 'x';
	}
	return 0;
}
