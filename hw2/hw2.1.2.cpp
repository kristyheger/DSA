#include <cstdlib>
#include <iostream>
using namespace std;

int main(void){
	int n;
	cin >> n;
	int matrix[n][n], a[n*(n+1)/2];
	int p = 0;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			cin >> matrix[i][j];
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i >= j){
				a[p++] = matrix[i][j];
			}
		}
	}
	int tmp = 0, N = n*n;
	p = 0;
	for(int i = 0; i < N; i++){
		if(i%n <= tmp)
			cout << a[p++] << " ";
		else
			cout << "0 ";
		if((i+1)%n == 0){
			cout << endl;
			tmp++;
		}
	}
	return 0;
}