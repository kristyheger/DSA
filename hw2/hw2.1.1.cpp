#include <cstdlib>
#include <iostream>
using namespace std;

int main(void){
	int n;
	cin >> n;
	int matrix[n][n];
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			cin >> matrix[i][j];
	for(int i = 0; i < n; i++){
		for(int j = 0; j < i; j++){
			int tmp = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = tmp;
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
	return 0;
}