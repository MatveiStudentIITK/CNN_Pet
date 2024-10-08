#include<cmath>
using namespace std;
#include "Functions.h"
using namespace My;
const Matrix My::Function::CalculateFunction(const Matrix& Arg) const
{
	Matrix Result(Arg.Height, Arg.Width);
	for (size_t i = 0; i < Arg.Size; i++) { Result.Elements[i] = CalculateFunction(Arg.Elements[i]); }
	return Result;
}
const Matrix* My::Function::CalculateFunction(const Matrix* const& Arg, const size_t& Argc) const
{
	Matrix* Result = new Matrix[Argc];
	for (size_t i = 0; i < Argc; i++) { Result[i] = CalculateFunction(Arg[i]); }
	return Result;
}
const Matrix My::Function::CalculateDerivative(const Matrix& Arg) const
{
	Matrix Result(Arg.Height, Arg.Width);
	for (size_t i = 0; i < Arg.Size; i++) { Result.Elements[i] = CalculateDerivative(Arg.Elements[i]); }
	return Result;
}
const Matrix* My::Function::CalculateDerivative(const Matrix* const& Arg, const size_t& Argc) const
{
	Matrix* Result = new Matrix[Argc];
	for (size_t i = 0; i < Argc; i++) { Result[i] = CalculateDerivative(Arg[i]); }
	return Result;
}

#include"D:/My/Pets/Matrix/Matrix.cpp"