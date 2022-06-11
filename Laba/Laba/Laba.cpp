#include <iostream>
#include <cstdlib>
#include <vector>
#include <chrono>

using namespace std;

vector<float> averageTimes;
float averageTime;
float coeffIncrease;

void BubbleFlag(int arr[], int lenArr) {
	bool flag = false;
	for (int i = 0; i < lenArr && !flag; ++i) {
		flag = true;
		for (int j = 0; j < lenArr - i - 1; ++j) {
			if (arr[j] > arr[j+1]) {
				int buffer = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = buffer;
				flag = false;
			}
		}
	}
}

//функция, сливающая массивы
void Merge(int A[], int first, int last)
{
	int middle, start, final, count = 0;
	int* mas = new int[10000000];
	middle = first + (first + last) / 2; //вычисление среднего элемента
	start = first; //начало левой части
	final = middle + 1; //начало правой части
	while (start <= middle && final <= last) {
		if (A[start] <= A[final]) {
			mas[count] = A[start];
			start++;
		}
		else {
			mas[count] = A[final];
			final++;
		}
		count++;
	}

	while (start <= middle) {
		mas[count] = A[start];
		count++;
		start++;
	}
	while (final <= last) {
		mas[count] = A[final];
		count++;
		final++;
	}

	for (int i = 0; i < count; ++i) {
		mas[first + i] = mas[i];
	}
		
	delete[] mas;
};

//рекурсивная процедура сортировки
void MergeSort(int A[], int first, int last)
{
	{
		if (first < last)
		{
			MergeSort(A, first, (first + last) / 2); //сортировка левой части
			MergeSort(A, (first + last) / 2 + 1, last); //сортировка правой части
			Merge(A, first, last); //слияние двух частей
		}
	}
};

int main()
{
	for (int n = 10; n <= 1000000000; n *= 10) {
		for (int exp = 0; exp < 10; ++exp) {
			cout << "\nCount of elements:" << n << endl;
			int* arr = new int[n];
			cout << "Creating new array..." << endl;
			for (int i = 0; i < n; ++i) {
				arr[i] = rand();
			}
			cout << "Array created!";
			cout << endl;


			/*auto startTime = chrono::steady_clock::now();
			BubbleFlag(arr, n);
			auto endTime = chrono::steady_clock::now();
			auto searchTime = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
			float seconds = (float)searchTime.count() / 1000000;
			cout << "Completed Time of Bubble Search with Flag = " << seconds << "s" << endl;
			averageTime += seconds;*/

			auto startTime = chrono::steady_clock::now();
			MergeSort(arr, 0, n);
			auto endTime = chrono::steady_clock::now();
			auto searchTime = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
			float seconds = (float)searchTime.count() / 1000000;
			cout << "Completed Time of MergeSort = " << seconds << "s" << endl;
			averageTime += seconds;
			cout << "\ncycle completed" << endl;
			delete[] arr;
		}

		averageTimes.push_back(averageTime / 10);
		cout << "Average time: " << averageTime / 10 << endl;
	}

	for (int i = 1; i < 9; i++) {
		coeffIncrease = averageTimes[i] / averageTimes[i - 1];
		cout << i << "Coefficient of increase: " << coeffIncrease << endl;
	}

}