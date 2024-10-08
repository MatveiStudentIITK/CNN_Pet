#include<iostream>
using namespace std;
#include"Functions.h"
using namespace My;

void abc(const Matrix& Arg, const Function* const& F)
{
	Matrix C;
	cout << Arg << endl;
	C = F->CalculateFunction(Arg);
	cout << C << endl;
	C = F->CalculateDerivative(Arg);
	cout << C << endl;
	delete F;
}

int main(const int Argc, const char* const* const Args)
{
	cout << Argc << endl << Args[0] << endl;
	const long double a[] = { 1,2,3,4,5,6,7,8,9 }, b[] = { 9,8,7,6,5,4,3,2,1 };
	Matrix A(3, 3, a), B(3, 3, b), C = A + B;
	cout << A << endl << B << endl;
	abc(C, new Gaus());
	abc(C, new Sigm());
	abc(C, new SoftSign());
	abc(C, new Th());
	return 0;
}