#include <bits/stdc++.h>
using namespace std;

int n;
stack<int> a;

void pop()
{
	while(!a.empty())
	{
		cout << a.top() << " ";
		a.pop();
	}
	cout << endl;
}
void function(int num)
{
	a.push(num);
	if(num == n)
	{
		pop();
		return;
	}
	function(num+1);
	cout << a.top() << " ";
	a.pop();
	function(num+1);
}

int main(void)
{
	cin >> n;
	function(1);
	return 0;
}