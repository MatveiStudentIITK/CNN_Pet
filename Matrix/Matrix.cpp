#include<stdexcept>
#include"Matrix.h"
using namespace std;
using namespace My;
Matrix& My::Matrix::operator=(const Matrix& Other)
{
	if (!IsSameSize(*this, Other))
	{
		if (Elements) { delete[Size * sizeof(long double)] Elements; }
		const_cast<size_t&>(Height) = Other.Height;
		const_cast<size_t&>(Width) = Other.Width;
		const_cast<size_t&>(Size) = Height * Width;
		const_cast<long double*&>(Elements) = new long double[Size];
	}
	for (size_t i = 0; i < Size; i++) { Elements[i] = Other.Elements[i]; }
	return *this;
}
const Matrix My::Matrix::Transpose() const
{
	Matrix Result(Width, Height);
	for (size_t i = 0; i < Height; i++)
	{
		for (size_t j = 0; j < Width; j++)
		{
			Result.Elements[j * Result.Width + i] = Elements[i * Width + j];
		}
	}
	return Result;
}
const bool My::IsSameSize(const Matrix& A, const Matrix& B) { return A.Height == B.Height && A.Width == B.Width; }
const bool My::IsMultipliedSize(const Matrix& A, const Matrix& B) { return A.Width == B.Height; }
const bool My::IsCollapsibleSize(const Matrix& A, const Matrix& B)
{
	return false;
}
const Matrix My::operator+(const Matrix& A, const Matrix& B)
{
	if (!IsSameSize(A, B)) { throw invalid_argument("Matrices must have same size."); }
	Matrix Result(A.Height, B.Width);
	for (size_t i = 0; i < Result.Size; i++) { Result.Elements[i] = A.Elements[i] + B.Elements[i]; }
	return Result;
}
Matrix& My::operator+=(Matrix& A, const Matrix& B)
{
	if (!IsSameSize(A, B)) { throw invalid_argument("Matrices must have same size."); }
	for (size_t i = 0; i < A.Size; i++) { A.Elements[i] += B.Elements[i]; }
	return A;
}
const Matrix My::operator-(const Matrix& A, const Matrix& B)
{
	if (!IsSameSize(A, B)) { throw invalid_argument("Matrices must have same size."); }
	Matrix Result(A.Height, B.Width);
	for (size_t i = 0; i < Result.Size; i++) { Result.Elements[i] = A.Elements[i] - B.Elements[i]; }
	return Result;
}
Matrix& My::operator-=(Matrix& A, const Matrix& B)
{
	if (!IsSameSize(A, B)) { throw invalid_argument("Matrices must have same size."); }
	for (size_t i = 0; i < A.Size; i++) { A.Elements[i] -= B.Elements[i]; }
	return A;
}
const Matrix My::operator*(const Matrix& A, const Matrix& B)
{
	if (!IsMultipliedSize(A, B)) { throw invalid_argument("Matrices must have multiplied size."); }
	Matrix Result(A.Height, B.Width);
	for (size_t i = 0; i < Result.Height; i++)
	{
		for (size_t j = 0; j < Result.Width; j++)
		{
			long double Sum = 0;
			for (size_t k = 0; k < A.Width; k++)
			{
				Sum += A.Elements[i * A.Width + k] * B.Elements[k * B.Width + j];
			}
			Result.Elements[i * Result.Width + j] = Sum;
		}
	}
	return Result;
}
Matrix& My::operator*=(Matrix& A, const Matrix& B)
{
	if (!IsMultipliedSize(A, B)) { throw invalid_argument("Matrices must have multiplied size."); }
	for (size_t i = 0; i < A.Height; i++)
	{
		for (size_t j = 0; j < A.Width; j++)
		{
			long double Sum = 0;
			for (size_t k = 0; k < A.Width; k++)
			{
				Sum += A.Elements[i * A.Width + k] * B.Elements[k * B.Width + j];
			}
			A.Elements[i * A.Width + j] = Sum;
		}
	}
	return A;
}
const Matrix My::operator/(const Matrix& A, const Matrix& B)
{
	if (!IsSameSize(A, B)) { throw invalid_argument("Matrices must have same size."); }
	Matrix Result(A.Height, B.Width);
	for (size_t i = 0; i < Result.Size; i++) { Result.Elements[i] = A.Elements[i] / B.Elements[i]; }
	return Result;
}
Matrix& My::operator/=(Matrix& A, const Matrix& B)
{
	// TODO: вставьте здесь оператор return
	return A;
}
const Matrix My::MultiplyByElements(const Matrix& A, const Matrix& B)
{
	if (!IsSameSize(A, B)) { throw invalid_argument("Matrices must have same size."); }
	Matrix Result(A.Height, B.Width);
	for (size_t i = 0; i < Result.Size; i++) { Result.Elements[i] = A.Elements[i] * B.Elements[i]; }
	return Result;
}
ostream& My::operator<<(ostream& Output, const Matrix& M)
{
	if (&Output == &cout) { Output << M.Height << ' ' << M.Width << endl; }
	for (size_t i = 0; i < M.Size; i++) { Output << M.Elements[i] << ((i + 1) % M.Width ? ' ' : '\n'); }
	return Output;
}
istream& My::operator>>(istream& Input, Matrix& M)
{
	delete[M.Size * sizeof(long double)] M.Elements;
	Input >> const_cast<size_t&>(M.Height) >> const_cast<size_t&>(M.Width);
	const_cast<size_t&>(M.Size) = M.Height * M.Width;
	const_cast<long double*&>(M.Elements) = new long double[M.Size];
	for (size_t i = 0; i < M.Size; i++) { Input >> M.Elements[i]; }
	return Input;
}