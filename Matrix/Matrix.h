#pragma once
#include<iostream>
namespace My
{
	struct Matrix
	{
		const size_t Height, Width, Size;
		long double* const Elements;
		Matrix() : Height(0), Width(0), Size(0), Elements(nullptr) {}
		Matrix(const size_t& Height, const size_t& Width) : Height(Height), Width(Width), Size(Height* Width), Elements(Size ? new long double[Size] : nullptr) {}
		Matrix(const size_t& Height, const size_t& Width, const long double* const& Elements) : Height(Height), Width(Width), Size(Height* Width), Elements(Size ? new long double[Size] : nullptr) { if (Elements) for (size_t i = 0; i < Size; i++) { this->Elements[i] = Elements[i]; } }
		~Matrix() { if (Elements) { delete[Size * sizeof(long double)] Elements; } }
		Matrix& operator=(const Matrix& Other);
		inline long double* const operator[](const size_t& Row) { return &Elements[Row]; }
		inline const long double* const operator[](const size_t& Row) const { return &Elements[Row]; }
		const Matrix Transpose() const;
	};

	const bool IsSameSize(const Matrix& A, const Matrix& B);
	const bool IsMultipliedSize(const Matrix& A, const Matrix& B);
	const bool IsCollapsibleSize(const Matrix& A, const Matrix& B);

	template<typename T> const Matrix operator+(const Matrix& A, const T& B)
	{
		Matrix Result(A.Height, A.Width);
		for (size_t i = 0; i < A.Size; i++) { Result.Elements[i] = A.Elements[i] + B; }
		return Result;
	}
	template<typename T> const Matrix operator+(const T& A, const Matrix& B)
	{
		Matrix Result(B.Height, B.Width);
		for (size_t i = 0; i < B.Size; i++) { Result.Elements[i] = A + B.Elements[i]; }
		return Result;
	}
	const Matrix operator+(const Matrix& A, const Matrix& B);
	template<typename T> Matrix& operator+=(Matrix& A, const T& B)
	{
		for (size_t i = 0; i < B.Size; i++) { A.Elements[i] += B; } return A;
	}
	Matrix& operator+=(Matrix& A, const Matrix& B);
	template<typename T> const Matrix operator-(const Matrix& A, const T& B)
	{
		Matrix Result(A.Height, A.Width);
		for (size_t i = 0; i < A.Size; i++) { Result.Elements[i] = A.Elements[i] - B; }
		return Result;
	}
	template<typename T> const Matrix operator-(const T& A, const Matrix& B)
	{
		Matrix Result(B.Height, B.Width);
		for (size_t i = 0; i < B.Size; i++) { Result.Elements[i] = A - B.Elements[i]; }
		return Result;
	}
	const Matrix operator-(const Matrix& A, const Matrix& B);
	template<typename T> Matrix& operator-=(Matrix& A, const T& B)
	{
		for (size_t i = 0; i < B.Size; i++) { A.Elements[i] -= B; } return A;
	}
	Matrix& operator-=(Matrix& A, const Matrix& B);
	template<typename T> const Matrix operator*(const Matrix& A, const T& B)
	{
		Matrix Result(A.Height, A.Width);
		for (size_t i = 0; i < A.Size; i++) { Result.Elements[i] = A.Elements[i] * B; }
		return Result;
	}
	template<typename T> const Matrix operator*(const T& A, const Matrix& B)
	{
		Matrix Result(B.Height, B.Width);
		for (size_t i = 0; i < B.Size; i++) { Result.Elements[i] = A * B.Elements[i]; }
		return Result;
	}
	const Matrix operator*(const Matrix& A, const Matrix& B);
	template<typename T> Matrix& operator*=(Matrix& A, const T& B)
	{
		for (size_t i = 0; i < B.Size; i++) { A.Elements[i] *= B; } return A;
	}
	Matrix& operator*=(Matrix& A, const Matrix& B);
	template<typename T> const Matrix operator/(const Matrix& A, const T& B)
	{
		Matrix Result(A.Height, A.Width);
		for (size_t i = 0; i < A.Size; i++) { Result.Elements[i] = A.Elements[i] / B; }
		return Result;
	}
	template<typename T> const Matrix operator/(const T& A, const Matrix& B)
	{
		Matrix Result(B.Height, B.Width);
		for (size_t i = 0; i < B.Size; i++) { Result.Elements[i] = A / B.Elements[i]; }
		return Result;
	}
	const Matrix operator/(const Matrix& A, const Matrix& B);
	template<typename T> Matrix& operator/=(Matrix& A, const T& B)
	{
		for (size_t i = 0; i < B.Size; i++) { A.Elements[i] /= B; } return A;
	}
	Matrix& operator/=(Matrix& A, const Matrix& B);

	const Matrix MultiplyByElements(const Matrix& A, const Matrix& B);

	std::ostream& operator<<(std::ostream& Output, const Matrix& M);
	std::istream& operator>>(std::istream& Input, Matrix& M);
}