#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

int main(void){
	int n;
	cin >> n;
	int cnt = 0;
	double matrix[n][n], inverse[n][n], original[n][n];
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			cin >> matrix[i][j];
	for(int i = 0; i < n; i++)	
		for(int j = 0; j < n; j++){
			if(i == j) inverse[i][j] = 1;
			else inverse[i][j] = 0;
		}
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			original[i][j] = matrix[i][j];
	for(int i = 0; i < n; i++){
		double times1 = matrix[i][i];
		if(!times1){
			for(int j = i; j < n; j++){
				if(matrix[j][i]){
					for(int k = 0; k < n; k++){
						matrix[i][k] += matrix[j][k];
						inverse[i][k] += inverse[j][k];
					}
					times1 = matrix[j][i];
					break;
				}	
			}
		}
		for(int j = 0; j < n; j++){
			matrix[i][j] /= times1;
			inverse[i][j] /= times1;
		}
		for(int j = 0; j < n; j++){
			if(i == j)	continue;
			double times2 = matrix[j][i];
			for(int k = 0; k < n; k++){
				matrix[j][k] -= matrix[i][k]*times2;
				inverse[j][k] -= inverse[i][k]*times2;
			}
		}
	}
	double max = 0, err = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			err = 0;
			for(int k = 0; k < n; k++){
				err += original[i][k]*inverse[k][j];
			}
			err = fabs(err);
		if(i == j) err = 1 - err;
		}
		if(err > max)	max = err;
	}
	cout << max << endl;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			cout << inverse[i][j] << " ";
		cout << endl;
	}
	
	return 0;
}