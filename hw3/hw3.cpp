#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <vector>
using namespace std;

int m, n, matrix[100][100] = {{0}};
vector<vector<int> > Row, Col;

int check(int cnt)
{
	// cout << "check_cnt: " << cnt << endl;
	int r = cnt / n, c = cnt % n;
	int lines_row = Row[r].size(), lines_col = Col[c].size(), conflict = 0, tmp = 0;
	int fragment = 0;
	int len[50] = {0};
	// for(int i = 0; i < m; i++){
	// 	for(int j = 0; j <n; j++)
	// 		cout << matrix[i][j] << " ";
	// 	cout << endl;
	// }
	for(int i = 0; i <= c; i++)
	{
		if(matrix[r][i])
		{
			while(matrix[r][i])
			{
				if(i > c)	break;
				len[fragment]++;
				i++;
				tmp = i;
			}
			fragment++;
		}
	}
	if(fragment > lines_row)	return 0;
	for(int i = 0; i < fragment; i++)
	{
		if(len[i] == Row[r][i])
		{
			continue;
		}
		else if(len[i] > Row[r][i])	return 0;
		else if(len[i] < Row[r][i] && tmp <= c)	return 0;
	}
	int space = 0;
	for(int i = fragment; i < lines_row; i++)
		space += Row[r][i];
	if(lines_row - fragment >= 1)
		space += lines_row - fragment - 1;
	if(n - 1 - c < space)	return 0;
// Col
	for(int i = 0; i < 20; i++)	len[i] = 0;
	fragment = 0, tmp = 0;
	for(int i = 0; i <= r; i++)
	{
		if(matrix[i][c])
		{
			while(matrix[i][c])
			{
				if(i > r)	break;
				len[fragment]++;
				i++;
				tmp = i;
			}
			fragment++;
		}
	}
	if(fragment > lines_col)	return 0;
	for(int i = 0; i < fragment; i++)
	{
		if(len[i] == Col[c][i])
		{
			continue;
		}
		else if(len[i] > Col[c][i])	return 0;
		else if(len[i] < Col[c][i] && tmp <= r)	return 0;
	}
	space = 0;
	for(int i = fragment; i < lines_col; i++)
		space += Col[c][i];
	if(lines_col - fragment >= 1)
		space += lines_col - fragment - 1;
	if(m - 1 - r < space)	return 0;
	return 1;
}

int FILL(int cnt)
{	
	// cout << "fill:cnt " << cnt << endl;
	int r = cnt / n, c = cnt % n;
	int err_0 = 0, err_1 = 0;
	matrix[r][c] = 0;
	if(!check(cnt))	err_0 = 1;
	if(cnt == m*n - 1)
	{
		if(check(cnt))
		{	
			for(int i = 0; i < m; i++)
			{
				for(int j = 0; j < n; j++)
				{
					if(matrix[i][j])	cout << "#";
					else	cout << ".";
				}
				cout << endl;
			}
			return 1;
		}
		matrix[r][c] = 1;
		if(check(cnt))
		{
			for(int i = 0; i < m; i++)
			{
				for(int j = 0; j < n; j++)
				{
					if(matrix[i][j])	cout << "#";
					else	cout << ".";
				}
				cout << endl;
			}
			return 1;
		}
	}
	if(!err_0 && FILL(cnt+1))	return 1;
	matrix[r][c] = 1;
	if(!check(cnt))	err_1 = 1;
	if(err_0 && err_1)
	{
		matrix[r][c] = 0;
		return 0;
	}
	if(FILL(cnt+1)) return 1;
	return 0;
}

int main(void)
{
	vector<int> v;
	int num, tmp = 0;
	char c;
	cin >> m >> n;
	for(int i = 0; i < m; i++)
	{
		while(1)
		{
			scanf("%d", &num);
			v.push_back(num);
			c = getchar();
			if(c == '\n')
			{
				break;
			}
		}
		Row.push_back(v);
		v.clear();
	}
	for(int i = 0; i < n; i++)
	{
		while(1)
		{
			scanf("%d", &num);
			v.push_back(num);
			c = getchar();
			if(c == '\n')
			{
				break;
			}
		}
		Col.push_back(v);
		v.clear();
	}
	// while(scanf("%d%c", &num, &c) != EOF)
	// {
	// 	if(tmp >= m)
	// 	{
	// 		if(c == '\n')
	// 		{
	// 			v.push_back(num);
	// 			Col.push_back(v);
	// 			v.clear();
	// 		}
	// 		else
	// 			v.push_back(num);
	// 	}
	// 	else
	// 	{
	// 		if(c == '\n')
	// 		{
	// 			v.push_back(num);
	// 			Row.push_back(v);
	// 			tmp++;
	// 			v.clear();
	// 		}
	// 		else
	// 			v.push_back(num);
	// 	}
	// }
	FILL(0);
	return 0;
}
