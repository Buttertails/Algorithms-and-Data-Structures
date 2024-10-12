#include<iostream>
using namespace std;

void replaceElements(int array[], int size);

int main()
{
	const int SIZE = 4;
	int array[SIZE] = { 1,2,3,4 };
	replaceElements(array, SIZE);
	for (int i = 0; i < SIZE; i++)
	{
		cout << array[i] << endl;
	}
	return 0;
}

void replaceElements(int array[], int size)
{
	for (int i = size - 1; i > 0; i--)
	{
		array[i] = array[i - 1];
	}
	array[0] = -1;
	
}