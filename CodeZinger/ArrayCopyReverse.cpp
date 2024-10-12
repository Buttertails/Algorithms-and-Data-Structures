#include<iostream>
using namespace std;

void reverseCopy(int source[], int destination[], int size);

int main()
{
	const int SIZE = 5;
	int source[SIZE] = { 9,0,2,1,8 };
	int destination[SIZE] = {0,0,0,0,0};
	reverseCopy(source, destination, SIZE);
	for (int i = 0; i < SIZE; i++)
	{
		cout << destination[i] << endl;
	}
	return 0;
}

void reverseCopy(int source[], int destination[], int size)
{
	int j = size - 1;
	for (int i = 0; i < size; i++)
	{
		destination[i] = source[j];
		j--;
	}
}