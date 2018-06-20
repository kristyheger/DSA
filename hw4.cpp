#include <bits/stdc++.h>
using namespace std;

typedef struct
{
	int bidID, clientID, action, price, shareCount;
}Data;
vector<Data> buy;
vector<Data> sell;
vector<int> cancel;
int cnt = 0;

void print()
{
	cout << "buy" << endl;
	for(int i = 0; i < buy.size(); i++)
		printf("%d\t%d\t%d\t%d\t%d\n", buy[i].bidID, buy[i].clientID, buy[i].action, buy[i].price, buy[i].shareCount);
	cout << "sell" << endl;
	for(int i = 0; i < sell.size(); i++)
		printf("%d\t%d\t%d\t%d\t%d\n", sell[i].bidID, sell[i].clientID, sell[i].action, sell[i].price, sell[i].shareCount);
}

bool cmp_b(Data a, Data b)
{
	if(a.price == b.price)
		return (a.bidID > b.bidID);
	return (a.price < b.price);
}

bool cmp_s(Data a, Data b)
{
	if(a.price == b.price)
		return (a.bidID > b.bidID);
	return (a.price > b.price);
}

void trade()
{
	while(true)
	{
		if(buy.size() && !cancel[buy[0].bidID])
		{
			// cout << "*****in_1*****" << endl;
			cancel[buy[0].bidID] = 1;
			pop_heap(buy.begin(), buy.end(), cmp_b);
			buy.pop_back();
			if(!buy.size())	break;
			continue;
		}
		if(sell.size() && !cancel[sell[0].bidID])
		{
			cancel[sell[0].bidID] = 1;
			pop_heap(sell.begin(), sell.end(), cmp_s);
			sell.pop_back();
			if(!sell.size()) break;
			continue;
		}
		if(buy.size() && sell.size() && buy[0].price >= sell[0].price)
		{
			if(buy[0].shareCount > sell[0].shareCount)
			{
				printf("%d\t%d\t%d\t%d\t%d\n", cnt, buy[0].clientID, sell[0].clientID, sell[0].price, sell[0].shareCount);
				cnt++;
				buy[0].shareCount -= sell[0].shareCount;
				pop_heap(sell.begin(), sell.end(), cmp_s);
				sell.pop_back();
				if(sell.size()) continue;
			}
			else if(buy[0].shareCount < sell[0].shareCount)
			{
				printf("%d\t%d\t%d\t%d\t%d\n", cnt, buy[0].clientID, sell[0].clientID, sell[0].price, buy[0].shareCount);
				cnt++;
				sell[0].shareCount -= buy[0].shareCount;
				pop_heap(buy.begin(), buy.end(), cmp_b);
				buy.pop_back();
				if(buy.size()) continue;
			}
			else
			{
				printf("%d\t%d\t%d\t%d\t%d\n", cnt, buy[0].clientID, sell[0].clientID, sell[0].price, sell[0].shareCount);
				cnt++;
				pop_heap(sell.begin(), sell.end(), cmp_s);
				pop_heap(buy.begin(), buy.end(), cmp_b);
				buy.pop_back();
				sell.pop_back();
				if(sell.size() && buy.size()) continue;
			}
		}
		break;
	}
}

int main(void)
{
	int n = 0;
	int a, b, c, d, e;
	Data D;
	while(scanf("%d%d%d%d%d", &a, &b, &c, &d, &e) != EOF)
	{
		D.bidID = a, D.clientID = b, D.action = c, D.price = d, D.shareCount = e;
		if(c == 0){	buy.push_back(D);	cancel.push_back(1);}
		else if(c == 1){ sell.push_back(D);   cancel.push_back(1);}
		else if(c == 2){ cancel.push_back(1);	cancel[d] = 0; }
		make_heap(buy.begin(), buy.end(), cmp_b);
		make_heap(sell.begin(), sell.end(), cmp_s);
		// cout << "before---------- " << n << endl;
		// print();
		trade();
		// cout << "after----------- " << n << endl;
		// print();
		n++;
	}
	return 0;
}