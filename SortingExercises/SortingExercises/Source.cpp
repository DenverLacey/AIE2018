#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

void BubbleSort(int A[], int size)
{
	for (int j = 0; j < size; ++j) {
		bool isSorted = true;
		//Goes through Array 
		for (int i = 0; i < size; ++i) {
			if (A[i] < A[i - 1]) {
				//swap
				int temp = A[i - 1];
				A[i - 1] = A[i];
				A[i] = temp;
				isSorted = false;
			}
		}
		//If array has been sorted
		if (isSorted) {
			break;
		}
	}
}

void InsertionSort(int B[], int size)
{
	for (int i = 1; i < size; ++i) {
		int key = B[i];
		int j = i - 1;

		if (j >= 0 && B[j] > key) {
			B[j + 1] = B[j];
			j -= 1;
			B[j + 1] = key;
		}
	}
}


int main()
{
	const int size = 10;

	//create large array
	int A[size] = { 1,5,2,6,50,35,21,87,44,3 };  //1, 2, 3, 5, 6, 21, 35, 44, 50, 87
	int B[size] = { 1,5,2,6,50,35,21,87,44,3 };

	high_resolution_clock::time_point t1, t2;

	t1 = high_resolution_clock::now();
	BubbleSort(A, size);
	t2 = high_resolution_clock::now();

	for (int i = 0; i < size; ++i) {
		cout << A[i] << ", ";
	}
	cout << endl << endl;

	cout << "Modified Bubble sort took " << (t2 - t1).count() << " nanoseconds.";

	t1 = high_resolution_clock::now();
	InsertionSort(B, size);
	t2 = high_resolution_clock::now();

	cout << endl << endl;

	for (int i = 0; i < size; ++i) {
		cout << B[i] << ", ";
	}
	cout << endl << endl;

	cout << "Insertion sort took " << (t2 - t1).count() << " nanoseconds.";

	//delete[] values;
	//delete[] A;
	//delete[] B;

	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.get();
	return 0;
}