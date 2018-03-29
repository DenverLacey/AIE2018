#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void Fibonacci(int fib[], int length, int i)
{
	if (i < length) {
		//Add previous two indexes to the current index
		fib[i] = fib[i - 1] + fib[i - 2];
		++i;
		Fibonacci(fib, length, i);
	}
}

int Raise(int& result, int& base, int& expo)
{
	//Checks count checker expo is greater than 1
	if (expo > 1) {
		//times result by base
		result *= base;
		//decrements the count checker expo
		--expo;
		//comences next iterator
		Raise(result, base, expo);
	}
	return result;
}

int main()
{
	//-----------------------------RAISE-----------------------------//
	int base, expo, result;

	cout << "Base Number: ";
	cin >> base;
	result = base;
	cout << "Exponent: ";
	cin >> expo;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());

	result = Raise(result, base, expo);

	cout << "Result: " << result;
	//---------------------------------------------------------------//
	cout << endl << endl;
	//---------------------------FIBONACCI---------------------------//
	const int size = 16;
	int fib[size] = { 0,1 };

	Fibonacci(fib, size, 2);

	cout << "Fibonacci Sequence:" << endl;
	for (int i = 0; i < size; ++i) {
		cout << '[' << fib[i] << ']' << ' ';
	}
	//---------------------------------------------------------------//

	cout << endl << endl << "Press 'Enter' to exit the program.";
	cin.get();
	return 0;
}