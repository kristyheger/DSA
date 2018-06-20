#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

int main(void){
	int num, a[4] = {0}, cnt = 0;
	char Name[4][10] = {"Vic", "Rick", "John", "David"};
	srand(time(NULL));
	while(cnt < 4)
	{
		int conflict = 0;
		num = rand() % 4 + 1;
		for(int i = 0; i < 4; i++)
		{
			if(num == a[i])
			{
				conflict = 1;
				break;
			}
		}
		if(!conflict)	a[cnt++] = num;
	}
	for(int i = 0; i < 4; i++)
	{
		if(i == 0) printf("A:   ");
		else if (i == 1) printf("B:   ");
		else if (i == 2) printf("C:   ");
		else if (i == 3) printf("D:   ");
		printf("%s\n", Name[a[i]-1]);
	}
	return 0;
}