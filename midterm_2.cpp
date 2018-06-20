#include <bits/stdc++.h>
using namespace std;

vector<int> v;
int size;
void preorder(int idx)
{
	if(idx >= size)	return;
	if(v[idx] != -1)	cout << v[idx] << " ";
	preorder(idx*2);
	preorder(idx*2+1);
}

void inorder(int idx)
{
	if(idx >= size)	return;
	inorder(idx*2);
	if(v[idx] != -1)	cout << v[idx] << " ";
	inorder(idx*2+1);
}

void postorder(int idx)
{
	if(idx >= size)	return;
	postorder(idx*2);
	postorder(idx*2+1);
	if(v[idx] != -1)	cout << v[idx] << " ";
}

int main(void)
{
	int x;
	while(cin >> x)
	{
		v.push_back(x);
	}
	size = v.size();
	preorder(1);
	puts("");
	inorder(1);
	puts("");
	postorder(1);
	return 0;
}