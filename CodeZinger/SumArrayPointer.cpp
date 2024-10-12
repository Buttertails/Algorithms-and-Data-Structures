#include<iostream>
using namespace std;

long sumArray(int* array, int size);

int main()
{
	const int SIZE = 5;
	int array[SIZE] = { 1,2,3,4,5 };
	cout << "Sum: " << sumArray(&array[0], SIZE);
	return 0;
}
long sumArray(int* array, int size)
{
	long sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += *array;
		array++;
	}

	return sum;
}