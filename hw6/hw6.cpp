#include <vector>
#include <stdio.h>
#include <time.h>
using namespace std;

vector<double> P, Q;
vector<int> Ans;

double abs(double num)
{
	if(num < 0)	num *= -1;
	return num;
}

int main(void)
{
	int m, n;
	double p, q;
	scanf("%d", &m);
	for(int i = 0; i < m; i++)
	{
		scanf("%lf", &p);
		P.push_back(p);
	}
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
		scanf("%lf", &q);
		Q.push_back(q);
	}
	double matrix[n][m];
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			matrix[i][j] = abs(Q[i] - P[j]);
			if(!i && !j)	continue;
			else if(!i)	matrix[i][j] += matrix[i][j-1];
			else if(j < i)	matrix[i][j] = 10000;
			else
			{
				if(matrix[i][j-1] < matrix[i-1][j-1])	matrix[i][j] += matrix[i][j-1];
				else	matrix[i][j] += matrix[i-1][j-1];	
			}
		}
	}
	double diff = 1000000;
	int idx;
	for(int i = 0; i < n; i++)
		if(matrix[i][m-1] < diff)	{diff = matrix[i][m-1]; idx = i;}
	for(int i = m-1; i > 0; i--)
	{
		if(!idx)	break;
		if(matrix[idx][i-1] >= matrix[idx-1][i-1])	{idx--; Ans.push_back(i);}
	}
	Ans.push_back(0);
	printf("%f\n", diff);
	int size = Ans.size();
	for(int i = size-1; i >= 0; i--)
		printf("%d ", Ans[i]);
	puts("");
	// for(int i = 0; i < n; i++)
	// {
	// 	for(int j = 0; j < m; j++){
	// 		printf("(%3d): %f ", j, matrix[i][j]);
	// 	}
	// 	puts("");
	// }
	return 0;
}
