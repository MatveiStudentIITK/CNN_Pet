#include<iostream>

using namespace std;

#include"Matrix.h"

using namespace My;

int main(const int Argc, const char* const* const Args)
{
	cout << Argc << endl << Args[0] << endl;
	const long double a[] = { 1,2,3,4,5,6,7,8,9 }, b[] = { 9,8,7,6,5,4,3,2,1 };
	Matrix A(3, 3, a), B(3, 3, b), C;
	cout << A << endl << B << endl;
	C = A * B / 9;
	cout << C << endl;
	return 0;
}